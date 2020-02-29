#include <ti/drivers/UART.h>
#include <ti/sysbios/knl/Task.h>
#include <unistd.h>
#include <mqueue.h>
#include "taskDefinition.h"

UART_Handle uart;
char buffer[MSGLENGHT];
char i;

//Testing puroses
char whatsNew[] = "{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}";


void *serialReceive(UArg *arg0, UArg *arg1)
{
    uart = (UART_Handle)arg1;
    mqd_t tQm = NULL;
    tQm = mq_open(rfTXQueue, O_WRONLY);
    uint8_t number=0;
    //uint8_t number=1;

    memcpy(buffer,&whatsNew,sizeof(whatsNew));

    while(1)
    {
        number = UART_read(uart, &i, 1);

        if(number!=0)
        {
            mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
            number=0;
        }
        Task_sleep(5000);
    }
}
