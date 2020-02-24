 /* Standard C Libraries */
#include <stdlib.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

///* BIOS Header files */33
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

///* Board Header files */
#include "Board.h"

#include <Tasks/taskDefinition.h>
#include <Drivers/startUart.h>

#define RFEASYLINKECHO_TASK_STACK_SIZE    1024
#define RFEASYLINKECHO_TASK_PRIORITY      2

static uint8_t echoTaskStack[RFEASYLINKECHO_TASK_STACK_SIZE];

Task_Params taskParams;
Task_Handle radioTaskHandle;

Task_Handle uartReceiveHandle;
Task_Handle uartSendHandle;

UART_Handle handleUART;

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call driver init functions. */
    Board_initGeneral();

    startUART(&handleUART);

    Task_Params_init(&taskParams);
    taskParams.stackSize = RFEASYLINKECHO_TASK_STACK_SIZE;
    taskParams.priority = RFEASYLINKECHO_TASK_PRIORITY;
    //taskParams.stack = &echoTaskStack;
    taskParams.arg0 = (UInt)1000000;
    taskParams.arg1 = (xdc_UArg)handleUART;


    radioTaskHandle = Task_create((Task_FuncPtr)radioTaskFunction,&taskParams,NULL);
    if(radioTaskHandle == NULL)
    {
        //Task Initialization failed
        while(1);
    }

   taskParams.priority = 3;
   uartSendHandle = Task_create((Task_FuncPtr)serialSend,&taskParams,NULL);
   if(uartSendHandle == NULL)
   {
       //Task initialization failed
       while(1);
   }

    taskParams.priority = 2;
    uartReceiveHandle = Task_create((Task_FuncPtr)serialReceive,&taskParams,NULL);
    if(uartReceiveHandle == NULL)
    {
        //Task initialization failed
        while(1);
    }




    /* Start BIOS */
    BIOS_start();

    return (0);
}
