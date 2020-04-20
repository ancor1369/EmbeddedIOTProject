#include <ti/drivers/UART.h>
#include <ti/drivers/GPIO.h>
#include <ti/sysbios/knl/Task.h>
#include <unistd.h>
#include <mqueue.h>
#include "Board.h"
#include "taskDefinition.h"

UART_Handle uart;
char buffer[MSGLENGHT];
char i;
mqd_t tQm = NULL;

//Testing purposes
char whatsNew[] = "    {\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"02\"}}";

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on Board_GPIO_BUTTON0.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on Board_GPIO_BUTTON1.
 *  This may not be used for all boards.
 */
void gpioButtonFxn1(uint_least8_t index)
{
    mq_send(tQm, (char *)&buffer, sizeof(buffer), 0);
}


void *serialReceive(UArg *arg0, UArg *arg1)
{
     //Get things ready to
     tQm = mq_open(rfTXQueue, O_WRONLY);
     memcpy(buffer,&whatsNew,sizeof(whatsNew));

    /* Call driver init functions */
    GPIO_init();

    GPIO_setConfig(Board_GPIO_BUTTON0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* install Button callback */
    GPIO_setCallback(Board_GPIO_BUTTON0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(Board_GPIO_BUTTON0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on Board_GPIO_BUTTON1.
     */
    if (Board_GPIO_BUTTON0 != Board_GPIO_BUTTON1)
    {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(Board_GPIO_BUTTON1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(Board_GPIO_BUTTON1, gpioButtonFxn1);
        GPIO_enableInt(Board_GPIO_BUTTON1);
    }
}
