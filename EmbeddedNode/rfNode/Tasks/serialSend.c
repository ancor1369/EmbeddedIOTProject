#include <ti/drivers/UART.h>
#include <Drivers/startUart.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
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
    extern UART_Handle handleUART;
    extern Queue_Handle receiveHandle;
    extern Semaphore_Handle packProSem;

    while(1)
    {
        //Process the whole queue at the same time to assemble the message
        //It is necessary to remove the header of each message and then
        //locate them in a common buffer one after the other

        bigIndex = 0;

        //Keeps waiting until the message can be processed
        Semaphore_pend(packProSem, BIOS_WAIT_FOREVER);
        while(!Queue_empty(receiveHandle))
        {
            bufferReceiver = Queue_dequeue(receiveHandle);
            memcpy(packet, bufferReceiver->buffer, sizeof(bufferReceiver->buffer));

            for(packetIndex=4;packetIndex<MSGLENGHT;packetIndex++)
            {
                bigMesage[bigIndex] = packet[packetIndex];
                bigIndex++;
            }
            memset(&packet[0],0,sizeof(packet));
            if(bufferReceiver->buffer[3]==bufferReceiver->buffer[2])
            {
                UART_write(handleUART, &bigMesage, sizeof(bigMesage));
                UART_write(handleUART, &enter, sizeof(enter));
                memset(&bigMesage[0],0,sizeof(bigMesage));

                break;
            }
        }
        Task_sleep(5000);
    }
}
