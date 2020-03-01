#include <ti/drivers/UART.h>
#include <Drivers/startUart.h>
#include <ti/sysbios/knl/Task.h>
#include <DataStructures/QueueData.h>
#include <stdbool.h>
#include <string.h>
#include "unistd.h"
#include <mqueue.h>
#include "taskDefinition.h"

/*
 * The messages that arrive to the platform are handled here.
 * This means it will be necessary to assemble the messages again and
 * set them to a correct state
 */

//remove the overhead of the package so that it is possible
//to have a complete one

char packet[MSGLENGHT];
char bigMesage[uartMSGLENGT];
//To keep fractions of the message
char chunk[MSGLENGHT];
//char chunk1[MSGLENGHT];
//char chunk2[MSGLENGHT];
//char chunk3[MSGLENGHT];
//char chunk4[MSGLENGHT];

msgBuffer_t* bufferReceiver;
Queue_Handle qHandle1 = NULL;

ssize_t bytes_read;
UART_Handle uart;
char enter[] = "\r\n";

uint8_t bigIndex = 0; //index in the big array
uint8_t packetIndex = 0; //Index in the package

bool write = false;

void serialSend(UArg *arg0, UArg *arg1)
{
    qHandle1 = (Queue_Handle)arg0;
    uart = (UART_Handle)arg1;


    mqd_t rxQm = NULL;

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = MSGLENGHT;
    attr.mq_curmsgs = 0;
    rxQm = mq_open(rfRXQueue, O_CREAT | O_RDONLY, 0644, &attr);



    while(1)
    {
        //Process the whole queue at the same time to assemble the message
        //It is necessary to remove the header of each message and then
        //locate them in a common buffer one after the other

        bigIndex = 0;

        while(!Queue_empty(qHandle1))
        {
            bufferReceiver = Queue_dequeue(qHandle1);
            memcpy(packet, bufferReceiver->buffer, sizeof(bufferReceiver->buffer));
            //UART_write(uart, &packet, sizeof(packet));

            for(packetIndex=4;packetIndex<MSGLENGHT;packetIndex++)
            {
                bigMesage[bigIndex] = packet[packetIndex];
                bigIndex++;
            }
            if(bufferReceiver->buffer[3]==bufferReceiver->buffer[2])
            {
                UART_write(uart, &bigMesage, sizeof(bigMesage));
                UART_write(uart, &enter, sizeof(enter));
                break;
            }
        }






//        bytes_read = mq_receive(rxQm, (char *)packet, MSGLENGHT, NULL);
//
//        if(bytes_read)
//        {
//            UART_write(uart, &packet, sizeof(packet));
//            UART_write(uart, &enter, sizeof(enter));
//        }
        Task_sleep(5000);
    }
}
