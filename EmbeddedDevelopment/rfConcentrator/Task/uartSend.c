#include <ti/drivers/UART.h>
#include <Drivers/startUart.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>
#include "unistd.h"
#include "mqueue.h"
#include "taskDefinition.h"

char packet[MSGLENGHT];
ssize_t bytes_read;
UART_Handle uart;
char taks[] = "taks";
Semaphore_Handle sendSemHandle;

void serialSend(UArg arg0, UArg arg1)
{
    sendSemHandle =  (Semaphore_Handle)arg0;

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
        //Wait the semaphore so that this task can execute when data is available
        Semaphore_pend(sendSemHandle,BIOS_WAIT_FOREVER);
        //Retrive the data from the queue and use it.
        bytes_read = mq_receive(rxQm, (char *)packet, MSGLENGHT, NULL);
        if(bytes_read != 0)
        {
            UART_write(uart, &packet, sizeof(packet));
        }
        UART_write(uart, &taks, sizeof(taks));
        //Task_sleep(5000);
    }
}

