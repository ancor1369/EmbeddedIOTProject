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
#include <stdio.h>
#include <unistd.h>
#include "mqueue.h"
char err[]="Error";

char buffer[MSGLENGHT];
char i;
UART_Handle uart1 = NULL;


void serialReceive(UArg arg0, UArg arg1)
{
    uart1 = (UART_Handle)arg1;
    mqd_t tQm = NULL;
    tQm = mq_open(rfTXQueue, O_WRONLY);
    uint8_t number=0;
    uint8_t counter = 0;

    while(1)
    {
        //Fill the buffer one position at a time
        number = UART_read(uart1, &i, 1);
        if(counter < MSGLENGHT)
        {
            buffer[counter] = i;
            counter++;
        }
        if(i==13 || counter == (MSGLENGHT-1))
        {
           if(number!=0)
           {
               number = mq_send(tQm, (char *)&buffer, counter, 0);
               if(number!=0)
               {
                   UART_write(uart1, &err, sizeof(err));
               }
               number = 0;
               counter = 0;
               memset(&buffer[0], 0, sizeof(buffer));
           }
        }

//       number = UART_read(uart1, buffer, sizeof(buffer));
//       if(number!=0)
//       {
//           //UART_write(uart1, &buffer, sizeof(buffer));
//           number = mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
//           if(number!=0)
//           {
//               UART_write(uart1, &err, sizeof(err));
//           }
//           number=0;
//           memset(&buffer[0], 0, sizeof(buffer));
//       }
       //Task_sleep(10);
    }
}
