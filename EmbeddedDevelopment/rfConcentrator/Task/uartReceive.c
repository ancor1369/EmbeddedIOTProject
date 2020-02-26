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
#include <unistd.h>
#include "mqueue.h"

char buffer[MSGLENGHT];
UART_Handle uart1 = NULL;

void serialReceive(UArg arg0, UArg arg1)
{
    uart1 = (UART_Handle)arg1;
    mqd_t tQm = NULL;
    tQm = mq_open(rfTXQueue, O_WRONLY);
    uint8_t number=0;

    while(1)
    {
       number = UART_read(uart1, &buffer, sizeof(buffer));
       if(number!=0)
       {
           //UART_write(uart1, &buffer, sizeof(buffer));
           mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
           number=0;
       }
       Task_sleep(5000);
    }
}
