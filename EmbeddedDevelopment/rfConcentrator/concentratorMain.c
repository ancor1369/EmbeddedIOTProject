
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

///* Undefine to not use async mode */
//#define RFEASYLINKECHO_ASYNC
//
#define RFEASYLINKECHO_TASK_STACK_SIZE    1024
#define RFEASYLINKECHO_TASK_PRIORITY      2

static uint8_t echoTaskStack[RFEASYLINKECHO_TASK_STACK_SIZE];


Task_Params radioTaskParams;
Task_Handle radioTaskHandle;

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call driver init functions. */
    Board_initGeneral();



    Task_Params_init(&radioTaskParams);
    radioTaskParams.stackSize = RFEASYLINKECHO_TASK_STACK_SIZE;
    radioTaskParams.priority = RFEASYLINKECHO_TASK_PRIORITY;
    radioTaskParams.stack = &echoTaskStack;
    radioTaskParams.arg0 = (UInt)1000000;


    radioTaskHandle = Task_create((Task_FuncPtr)radioTaskFunction,&radioTaskParams,NULL);
    if(radioTaskHandle == NULL)
    {
        //Task Initialization failed
        while(1);
    }

    /* Start BIOS */
    BIOS_start();

    return (0);
}
