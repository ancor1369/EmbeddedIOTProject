
/*
 *  ======== rfEasyLinkEchoRx.c ========
 */
/* Standard C Libraries */
#include <stdlib.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>

/* Board Header files */
#include "Board.h"

#include <Drivers/startUart.h>

#include <Task/taskDefinition.h>
#include "mqueue.h"

/* Undefine to not use async mode */
#define RFEASYLINKECHO_ASYNC

#define RFEASYLINKECHO_TASK_STACK_SIZE    1024
#define RFEASYLINKECHO_TASK_PRIORITY      2


static Task_Params TaskParams;
static Task_Handle radioTaskHandle;
static Task_Handle uartReceiveHandle;
static Task_Handle uartSendhandle;

static uint8_t echoTaskStack[RFEASYLINKECHO_TASK_STACK_SIZE];
//
///* Pin driver handle */
static PIN_Handle pinHandle;
static PIN_State pinState;
static UART_Handle uart = NULL;

//
///*
// * Application LED pin configuration table:
// *   - All LEDs board LEDs are off.
// */
PIN_Config pinTable[] = {
    Board_PIN_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_PIN_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

Semaphore_Handle uartSendHandlesem = NULL;

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call driver init functions. */
    Board_initGeneral();

    /* Create a semaphore for Async */
    Semaphore_Params params;
    Error_Block      eb;

    /* Init params */
    Semaphore_Params_init(&params);
    Error_init(&eb);

    uartSendHandlesem = Semaphore_create(0, &params, &eb);
    if(uartSendHandlesem == NULL)
    {
       System_abort("Semaphore creation failed");
    }

    /* Open LED pins */
    pinHandle = PIN_open(&pinState, pinTable);
    Assert_isTrue(pinHandle != NULL, NULL);

    /* Clear LED pins */
    PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
    PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);

    startUART(&uart);

    Task_Params_init(&TaskParams);
    TaskParams.stackSize = RFEASYLINKECHO_TASK_STACK_SIZE;
    TaskParams.arg1 = (xdc_UArg)uart;
    TaskParams.arg0 = (xdc_UArg)uartSendHandlesem;

    TaskParams.priority = 2;
    radioTaskHandle = Task_create((Task_FuncPtr)radioTask,&TaskParams,NULL);
    if(radioTaskHandle == NULL)
    {
        while(1);
    }

    TaskParams.priority = 2;
    uartReceiveHandle = Task_create((Task_FuncPtr)serialReceive,&TaskParams,NULL);
    if(uartReceiveHandle == NULL)
    {
        //Failed to start the task
        while(1);
    }

    TaskParams.priority = 4;
    uartSendhandle = Task_create((Task_FuncPtr)serialSend,&TaskParams,NULL);
    if(uartSendhandle == NULL)
    {
          //Failed to initialize the task
        while(1);
    }

    /* Start BIOS */
    BIOS_start();

    return (0);
}
