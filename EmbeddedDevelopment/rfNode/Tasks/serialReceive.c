#include <ti/drivers/UART.h>
#include <unistd.h>
#include <mqueue.h>
#include "taskDefinition.h"

UART_Handle uart;
char buffer[MSGLENGHT];

void *serialReceive(UArg *arg0, UArg *arg1)
{
    uart = (UART_Handle)arg1;
    mqd_t tQm = NULL;
    tQm = mq_open(rfTXQueue, O_WRONLY);
    uint8_t number=0;

    while(1)
    {
        number = UART_read(uart, &buffer, sizeof(buffer));
        if(number!=0)
        {
            mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
            number=0;
        }
        usleep(50000);
    }
}
