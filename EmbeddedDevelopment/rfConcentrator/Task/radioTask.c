/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>



/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>

/* Board Header files */
#include "Board.h"

/* Application Header files */
#include "smartrf_settings/smartrf_settings.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

#include <Drivers/startUart.h>
#include <DataStructures/QueudData.h>
#include <DataStructures/messageReceived.h>

#include "taskDefinition.h"
#include "mqueue.h"

#define RFEASYLINKECHO_TASK_STACK_SIZE    1024

#define RFEASYLINKECHO_PAYLOAD_LENGTH     40

char ackOK[] = "{\"CXT\":\"PRO\",\"Object\":{\"ACK\":\"OK\"}}";
char message[142];

Task_Struct echoTask;    /* not static so you can see in ROV */

mqd_t txQm = NULL;
mqd_t rxQm = NULL;

struct mq_attr attr;

/* Pin driver handle */
static PIN_Handle pinHandle;
static UART_Handle uart = NULL;

static Semaphore_Handle echoDoneSem;

static bool bBlockTransmit = true;

EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};

char enter[] = "\r\n";

msgBuffer_t* bufferReceiver;
Queue_Handle qHandle1 = NULL;

packet_t pack;

void echoTxDoneCb(EasyLink_Status status)
{
    if (status == EasyLink_Status_Success)
    {
        /* Toggle LED2 to indicate Echo TX, clear LED1 */
        PIN_setOutputValue(pinHandle, Board_PIN_LED2,!PIN_getOutputValue(Board_PIN_LED2));
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
    }
    else
    {
        /* Set LED1 and clear LED2 to indicate error */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 1);
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);
    }
    Semaphore_post(echoDoneSem);
}

void echoRxDoneCb(EasyLink_RxPacket * rxPacket, EasyLink_Status status)
{
    if (status == EasyLink_Status_Success)
    {


            /* Toggle LED2 to indicate RX, clear LED1 */
            PIN_setOutputValue(pinHandle, Board_PIN_LED2,!PIN_getOutputValue(Board_PIN_LED2));
            PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
            memcpy(&message,rxPacket->payload,rxPacket->len);

//            memcpy(&pack.addr,rxPacket->dstAddr,sizeof(rxPacket->dstAddr));
//            memcpy(&pack.payload,rxPacket->payload,rxPacket->len);

            /* Permit echo transmission */
            bBlockTransmit = false;

    }
    else
    {
        /* Set LED1 and clear LED2 to indicate error */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 1);
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);
        /* Block echo transmission */
        bBlockTransmit = true;
    }

    Semaphore_post(echoDoneSem);
}


void radioTask(UArg arg0, UArg arg1)
{
    qHandle1 = (Queue_Handle)arg0;
    uart = (UART_Handle)arg1;
    uint32_t absTime;
    //Start the send queue to send over RF
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = MSGLENGHT;
    attr.mq_curmsgs = 0;
    txQm = mq_open(rfTXQueue, O_CREAT | O_RDONLY, 0644, &attr);
    rxQm = mq_open(rfRXQueue, O_WRONLY);

    /* Create a semaphore for Async */
    Semaphore_Params params;
    Error_Block      eb;

    /* Init params */
    Semaphore_Params_init(&params);
    Error_init(&eb);

    /* Create semaphore instance */
    echoDoneSem = Semaphore_create(0, &params, &eb);
    if(echoDoneSem == NULL)
    {
        System_abort("Semaphore creation failed");
    }

    // Initialize the EasyLink parameters to their default values
    EasyLink_Params easyLink_params;
    EasyLink_Params_init(&easyLink_params);

    /*
     * Initialize EasyLink with the settings found in easylink_config.h
     * Modify EASYLINK_PARAM_CONFIG in easylink_config.h to change the default
     * PHY
     */
    if(EasyLink_init(&easyLink_params) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_init failed");
    }


    /*
     * If you wish to use a frequency other than the default, use
     * the following API:
     * EasyLink_setFrequency(868000000);
     */


    while(1) {


        // Wait to receive a packet
        EasyLink_receiveAsync(echoRxDoneCb, 0);
        //Break from receiver to listener on other tasks. This allow the system
        //to review other tasks that need to run
        if(Semaphore_pend(echoDoneSem, (5000000 / Clock_tickPeriod)) == FALSE)
        {
           /* RX timed out abort */
           if(EasyLink_abort() == EasyLink_Status_Success)
           {
              /* Wait for the abort */
              Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);
           }
        }

        if(bBlockTransmit == false)
        {
            /* Switch to Transmitter and echo the packet if transmission
             * is not blocked
             */
            //Send the received package to the UART interface
            UART_write(uart,&(message),sizeof(message));
            UART_write(uart,&enter,sizeof(enter));

            //Add received data to to the Queue and set the semaphore to release showing
            //on the serial interface


            //Load the OK message to be send to the requester
            memset(&txPacket.payload[0], 0, sizeof(txPacket.payload));
            memcpy(txPacket.payload,ackOK,sizeof(ackOK));


            txPacket.len = sizeof(ackOK);//RFEASYLINKECHO_PAYLOAD_LENGTH;

            /*
             * Address filtering is enabled by default on the Rx device with the
             * an address of 0xAA. This device must set the dstAddr accordingly.
             */
            txPacket.dstAddr[0] = 0xAA;  //I need to get the address feom

            /* Set Tx absolute time to current time + 100ms*/
            if(EasyLink_getAbsTime(&absTime) != EasyLink_Status_Success)
            {
                // Problem getting absolute time
            }
            txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(100);

            EasyLink_transmitAsync(&txPacket, echoTxDoneCb);
            /* Wait for Tx to complete. A Successful TX will cause the echoTxDoneCb
             * to be called and the echoDoneSem to be released, so we must
             * consume the echoDoneSem
             */
            Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);

            bBlockTransmit = true;
        }

        //Wait the message to arrive from serial interfaceMAX_LENGTH
        //I can try to get here only the message needed. Not all the messages are
        //going to the same destination. So I need to process the received queue
        //To send the messages to the correct destination and empty the queue

        //Takes messages pending to be sent to the other side and sends

        if(!Queue_empty(qHandle1))
        {
            bufferReceiver = Queue_dequeue(qHandle1);
            //Transmit the response gotten on the serial interface
            memset(&txPacket.payload[0], 0, sizeof(txPacket.payload));
            memcpy(txPacket.payload,&bufferReceiver->buffer,sizeof(bufferReceiver->buffer));
            txPacket.len = sizeof(bufferReceiver->buffer);
            txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(100);
            EasyLink_transmitAsync(&txPacket, echoTxDoneCb);
             /* Wait for Tx to complete. A Successful TX will cause the echoTxDoneCb
              * to be called and the echoDoneSem to be released, so we must
              * consume the echoDoneSem
              */
            Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);
            memset(&bufferReceiver->buffer[0], 0, sizeof(bufferReceiver->buffer));
        }

        Task_sleep(5000);
    }
}
