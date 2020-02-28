#include <ti/drivers/UART.h>
#include <Drivers/startUart.h>
#include "unistd.h"
#include <mqueue.h>
#include "taskDefinition.h"

char packet[MSGLENGHT];
ssize_t bytes_read;
UART_Handle uart;
char enter[] = "\r\n";

void serialSend(UArg *arg0, UArg *arg1)
{
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
        bytes_read = mq_receive(rxQm, (char *)packet, MSGLENGHT, NULL);

        if(bytes_read)
        {
            UART_write(uart, &packet, sizeof(packet));
            UART_write(uart, &enter, sizeof(enter));
        }
        usleep(50000);
    }
}
