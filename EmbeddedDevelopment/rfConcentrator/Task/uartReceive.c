/*
 * This task when receiving a package to be
 * sent over the rf interface, will need to
 * take control over the RF interface so that
 * i can make sure the message is sent to
 * the every node. Only the node with the identifier
 * containing the needed response will find the answer needed
 */


#include <Task/taskDefinition.h>
#include <ti/drivers/UART.h>
#include <ti/sysbios/knl/Task.h>
#include <DataStructures/QueudData.h>
#include <DataStructures/messageReceived.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mqueue.h"
char err[]="Error";

//char buffer[MSGLENGHT];
char buffer[uartMSGLENGHT];
char buffer1[MSGLENGHT];

char i;
UART_Handle uart1 = NULL;
Queue_Handle qHandle = NULL;

msgBuffer_t bufferSend;
msgBuffer_t bufferSend1;
msgBuffer_t bufferSend2;
msgBuffer_t bufferSend3;
msgBuffer_t bufferSend4;

packet_t packetToSend;

void serialReceive(UArg arg0, UArg arg1)
{
    qHandle = (Queue_Handle)arg0;

    uart1 = (UART_Handle)arg1;

    uint8_t number=0;
    uint8_t counter = 0;
    uint8_t sendAddr = 0; //Address where the package needs to be sent
    uint8_t totalPackages = 0;
    uint8_t currentIndex = 1;
    uint8_t internalIndex = 0;
    uint8_t pkgNumber = 1;

    packetToSend.sdrAddr = 0xAA;


    while(1)
    {
        //Fill the buffer one position at a time
        number = UART_read(uart1, &i, 1);
        if(counter < uartMSGLENGHT)
        {
            buffer[counter] = i;
            counter++;
        }
        if(i==13 || counter == (uartMSGLENGHT-1))
        {
           //Take the big message and start chopping it and creating the packages needed
           sendAddr = buffer[0];
           //remove the first character of the message. It stands for the address of the device to
           //send this answer to
           memmove(buffer,buffer+1,(counter-1));
           //Find out the number of packages to send
           totalPackages = counter / PAYLOADSize;
           totalPackages++;
           currentIndex = 1;
           //Setting parameters of the package to send. However it is not very userful here
           //unless I make reimplementation to fill this one first and then
           //copy all the content into the queue element to push it
           packetToSend.total = totalPackages;
           packetToSend.seqn = pkgNumber;
           packetToSend.dstAddr = sendAddr;

           //Chop chop chop
           for(pkgNumber = 1;pkgNumber <= totalPackages;pkgNumber++)
           {
               buffer1[internalIndex] = 0xAA;
               internalIndex++;
               buffer1[internalIndex] = sendAddr;
               internalIndex++;
               buffer1[internalIndex] = totalPackages;
               internalIndex++;
               buffer1[internalIndex] = pkgNumber;
               for(currentIndex = ((PAYLOADSize*(pkgNumber-1)));currentIndex<(PAYLOADSize*pkgNumber);currentIndex++)
               {
                   internalIndex++;
                   buffer1[internalIndex] = buffer[currentIndex];
               }
               internalIndex = 0;
               //Write each one of the chopped packages
               //UART_write( uart1, &buffer1, sizeof(buffer1));

               //This creation might be implemented by using a linked list
               //At this point I need to have this communication setting up and running because I have
               //Not very much time left

               //This is a dirty implementation. Many things can be improved here! such as using a data structure
               //and calling a dynamic data structure to fill and send the chopped messages. I will support only 5 so far.
               switch(pkgNumber)
               {
                   case 1:
                      memcpy(bufferSend.buffer, buffer1,sizeof(buffer1));
                      Queue_enqueue(qHandle,&(bufferSend.elem));
                      break;
                   case 2:
                      memcpy(bufferSend1.buffer, buffer1,sizeof(buffer1));
                      Queue_enqueue(qHandle,&(bufferSend1.elem));
                      break;
                   case 3:
                      memcpy(bufferSend2.buffer, buffer1,sizeof(buffer1));
                      Queue_enqueue(qHandle,&(bufferSend2.elem));
                      break;
                   case 4:
                      memcpy(bufferSend3.buffer, buffer1,sizeof(buffer1));
                      Queue_enqueue(qHandle,&(bufferSend3.elem));
                      break;
                   case 5:
                      memcpy(bufferSend4.buffer, buffer1,sizeof(buffer1));
                      Queue_enqueue(qHandle,&(bufferSend4.elem));
                      break;
               }
               memset(&buffer1[0],0,sizeof(buffer1));
           }
//           This task does not have an sleep function because it is blocking on receiving

           //Clean the receiver buffer to give space for new data
           memset(&buffer[0], 0, sizeof(buffer));
        }
    }
}
