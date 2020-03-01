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

/*
 *  ======== rfEasyLinkEchoTx.c ========
 */

#include <stdlib.h>
#include "unistd.h"

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
#include <DataStructures/QueueData.h>

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>

/* Board Header files */
#include "Board.h"

/* Application Header files */
#include "smartrf_settings/smartrf_settings.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

#include "taskDefinition.h"
#include "mqueue.h"

PIN_Config pinTable[] = {
    Board_PIN_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_PIN_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

#define RFEASYLINKECHO_PAYLOAD_LENGTH     40



/* Pin driver handle */
static PIN_Handle pinHandle;
static PIN_State pinState;

static Semaphore_Handle echoDoneSem;

EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};
char packet[MSGLENGHT];

mqd_t txQm = NULL;
mqd_t rxQm = NULL;

struct mq_attr attr;

bool sendOK = false;

Queue_Handle qHandle = NULL;

//This is to hold each of the messages
//arriving to the device

msgBuffer_t bufferSend;
msgBuffer_t bufferSend1;
msgBuffer_t bufferSend2;
msgBuffer_t bufferSend3;
msgBuffer_t bufferSend4;

uint8_t pkgNum = 0;

void echoTxDoneCb(EasyLink_Status status)
{
    if (status == EasyLink_Status_Success)
    {
        /* Toggle LED1 to indicate TX */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1,!PIN_getOutputValue(Board_PIN_LED1));
        /* Turn LED2 off, in case there was a prior error */
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);
    }
    else
    {
        /* Set both LED1 and LED2 to indicate error */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 1);
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 1);
    }

    Semaphore_post(echoDoneSem);
}

void echoRxDoneCb(EasyLink_RxPacket * rxPacket, EasyLink_Status status)
{
    //Received packages are used here. The package needs to be filtered
    //so that I just recognize packages sent for this node

    //This value needs to be taken from any configuration file so that
    //it is possible to configure this device according to the deployment
    //requirements. The adders of the concentrator shall be set able as well

    if ((status == EasyLink_Status_Success))// && rxPacket->payload[1] == 0x41)
    {
        /* Toggle LED1, clear LED2 to indicate Echo RX */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1,!PIN_getOutputValue(Board_PIN_LED1));
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);

        //Push the received message over the serial interface
        //mq_send(rxQm, (char *)&rxPacket->payload, sizeof(rxPacket->len), 0);
//        memcpy(bufferSend.buffer,rxPacket->payload, sizeof(bufferSend.buffer));
//        Queue_enqueue(qHandle,&(bufferSend.elem));

        pkgNum = rxPacket->payload[3];

        switch(pkgNum)
        {
            case 1:
                memcpy(bufferSend.buffer,rxPacket->payload, sizeof(rxPacket->payload));
                Queue_enqueue(qHandle,&(bufferSend.elem));
                break;
            case 2:
                memcpy(bufferSend1.buffer,rxPacket->payload, sizeof(rxPacket->payload));
                Queue_enqueue(qHandle,&(bufferSend1.elem));
                break;
            case 3:
                memcpy(bufferSend2.buffer,rxPacket->payload, sizeof(rxPacket->payload));
                Queue_enqueue(qHandle,&(bufferSend2.elem));
                break;
            case 4:
                memcpy(bufferSend3.buffer,rxPacket->payload, sizeof(rxPacket->payload));
                Queue_enqueue(qHandle,&(bufferSend3.elem));
                break;
            case 5:
                memcpy(bufferSend4.buffer,rxPacket->payload, sizeof(rxPacket->payload));
                Queue_enqueue(qHandle,&(bufferSend4.elem));
                break;
        }

        //if(rxPacket->payload[3] == rxPacket->payload[2])
        {
            sendOK = true;
        }
    }
    else if (status == EasyLink_Status_Aborted)
    {
        /* Set LED2 and clear LED1 to indicate Abort */
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 1);
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
    }
    else
    {
        /* Set both LED1 and LED2 to indicate error */
        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 1);
        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 1);
    }

    //if(rxPacket->payload[3] == rxPacket->payload[2])
    {
        Semaphore_post(echoDoneSem);
    }
}


void radioTaskFunction(UArg *arg0,UArg *arg1)
{
       qHandle = (Queue_Handle)arg0;

       uint32_t absTime;
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

       //Start the send queue to send over RF
       ssize_t bytes_read;
       attr.mq_flags = 0;
       attr.mq_maxmsg = 1;
       attr.mq_msgsize = MSGLENGHT;
       attr.mq_curmsgs = 0;
       txQm = mq_open(rfTXQueue, O_CREAT | O_RDONLY, 0644, &attr);


       //start the receive queue to sent over UART
       rxQm = mq_open(rfRXQueue, O_WRONLY);

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

       /* Open LED pins */
          pinHandle = PIN_open(&pinState, pinTable);
          Assert_isTrue(pinHandle != NULL, NULL);

          /* Clear LED pins */
          PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
          PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);

       //memcpy(txPacket.payload,&whatsNew,sizeof(whatsNew));


       while(1) {
//
//           //Always in receiver mode for testing purposes
//
           EasyLink_receiveAsync(echoRxDoneCb, 0);

          /* Wait for Tx to complete. A Successful TX will cause the echoTxDoneCb
           * to be called and the echoDoneSem to be released, so we must
           * consume the echoDoneSem
           */
           Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);





           //Waits to get any new messages from the serial interface
//           bytes_read = mq_receive(txQm, (char *)packet, MSGLENGHT, NULL);
//           sendOK = false;
//
//           if(bytes_read>=0)
//           {
//              txPacket.len = MSGLENGHT;
//              /*
//               * Address filtering is enabled by default on the Rx device with the
//               * an address of 0xAA. This device must set the dstAddr accordingly.
//               */
//              txPacket.dstAddr[0] = 0xAA;
//               //Receive the message from the Queue to then be sent over the RF Interface
//              memcpy(txPacket.payload,&packet,sizeof(packet));
//              txPacket.payload[0] = 0x41; //This is the address of this device. This might come from a confile
//              txPacket.payload[1] = 0X42;
//              txPacket.payload[2] = 0x01;
//              txPacket.payload[3] = 0x01;
//               while(!sendOK)
//               {
//                   /* Set Tx absolute time to current time + 1000ms */
//                   if(EasyLink_getAbsTime(&absTime) != EasyLink_Status_Success)
//                   {
//                       // Problem getting absolute time
//                   }
//                   txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(1000);
//
//
//                   EasyLink_transmitAsync(&txPacket, echoTxDoneCb);
//
//                   /* Wait for Tx to complete. A Successful TX will cause the echoTxDoneCb
//                    * to be called and the echoDoneSem to be released, so we must
//                    * consume the echoDoneSem
//                    */
//                   Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);
//
//                   /* Switch to Receiver */
//                   EasyLink_receiveAsync(echoRxDoneCb, 0);
//                   /* Wait 500ms for Rx */
//                   if(Semaphore_pend(echoDoneSem, (500000 / Clock_tickPeriod)) == FALSE)
//                   {
//                       /* RX timed out abort */
//                       if(EasyLink_abort() == EasyLink_Status_Success)
//                       {
//                          /* Wait for the abort */
//                          Semaphore_pend(echoDoneSem, BIOS_WAIT_FOREVER);
//                       }
//                   }
//                   //remain in Rx Mode to get the answer coming from the concentrator Device
//                   if(sendOK)
//                   {
//                       EasyLink_receiveAsync(echoRxDoneCb,0);
//                       //Remain waiting for ever until the concentrator sends the
//                       //message that is pending for me to continue to do my work
//                       Semaphore_pend(echoDoneSem,BIOS_WAIT_FOREVER);
//                   }
//               }



           //}
           //Task_sleep(5000);
       }
}
