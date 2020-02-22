/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,

 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_tirtos.c ========
 */
#include <stdint.h>

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <ti/sysbios/BIOS.h>

/* Example/Board Header files */
#include <ti/drivers/Board.h>
#include <ti/drivers/GPIO.h>
#include <ti/sysbios/knl/Task.h>
/*Tasks include files*/
#include <Tasks/taskDefinitions.h>

/*Driver initialization files*/
#include <Drivers/startUart.h>


/* Data structures defined for this development */
#include <DataStructures/llMessage.h>




/* Stack size in bytes */
#define THREADSTACKSIZE    1024

/*
 *  ======== main ========
 */

int main(void)
{
    //Handles for the threads
//    pthread_t           ledThread;
//    pthread_t           uartReadThread;
//    pthread_t           uartWriteThread;
//    pthread_t           txThreadTask;
//    pthread_t           rxThreadTask;

    Task_Params taskParams;
    Task_Handle task0;
    Task_Handle uartReadTaskHandle;
    Task_Handle uartWriteTaskHandle;
    Task_Handle txTaskHandle;
    Task_Handle rxTaskHandle;

    Task_Params_init(&taskParams);

    //Handle for drivers
    UART_Handle uart = NULL;

    //These definitions are used globally among the threads

//    pthread_attr_t      attrs;
//    struct sched_param  priParam;
//    int                 retc;
//    int                 detachState;

    /* Communication facilities initialization */


    /* Call driver init functions */
    Board_init();
    GPIO_init();
    //Pass the argument of the UART so that the hardware is
    //initialized correctly
    startUART(&uart);




    /*Implement as SYS/BIOS tasks instead of threads*/



    taskParams.stackSize = 1024;


//    task0 = Task_create((Task_FuncPtr)ledTask,&taskParams,NULL);
//    if(task0 ==NULL)
//    {
//        while(1);
//    }

    taskParams.arg0 = (xdc_UArg)uart;



    taskParams.priority = 1;
    uartReadTaskHandle = Task_create((Task_FuncPtr)uartReadTask,&taskParams,NULL);
    if(uartReadTaskHandle==NULL)
    {
        while(1);
    }


    taskParams.priority = 2;
    txTaskHandle = Task_create((Task_FuncPtr)txTask,&taskParams,NULL);
    if(txTaskHandle==NULL)
    {
       while(1);
    }

//    taskParams.priority = 1;
//    uartWriteTaskHandle = Task_create((Task_FuncPtr)uartWriteTask,&taskParams,NULL);
//    if(uartWriteTaskHandle==NULL)
//    {
//        while(1);
//    }
//
//    taskParams.priority = 2;
//    rxTaskHandle = Task_create((Task_FuncPtr)rxTask,&taskParams,NULL);
//    if(rxTaskHandle==NULL)
//    {
//        while(1);
//    }



    /* Initialize the attributes structure with default values */
//    pthread_attr_init(&attrs);
//    priParam.sched_priority = 1;

//    detachState = PTHREAD_CREATE_DETACHED;
//    retc = pthread_attr_setdetachstate(&attrs, detachState);
//    if(retc != 0)
//    {
//        //Error in setting the dettached mode of the thread
//        while(1);
//    }
//    pthread_attr_setschedparam(&attrs, &priParam);
//
//    retc |= pthread_attr_setstacksize(&attrs,THREADSTACKSIZE);
//    if(retc!=0)
//    {
//        //Error setting the stack size
//        while(1);
//    }
    /*
     * TX thread
     */

//    priParam.sched_priority = 2;
//    pthread_attr_setschedparam(&attrs, &priParam);
//
//    /*
//     * UART Read Task
//     */
//
//    //Send as parameter the handle of the queue I need to pass data around
//    retc = pthread_create(&uartReadThread, &attrs, uartReadTask, uart);
//    if(retc != 0)
//    {
//        while(1);
//    }

    /*
     * End UART Read Task
     */


//    priParam.sched_priority = 2;
//    pthread_attr_setschedparam(&attrs, &priParam);
//      /*
//       * UART Write Task
//       */
//
//      //Send as parameter the handle of the queue I need to pass data around
//      retc = pthread_create(&uartWriteThread, &attrs, uartWriteTask, uart);
//      if(retc != 0)
//      {
//          while(1);
//      }

      /*
       * End UART Write Task
       */

//
//     priParam.sched_priority = 1;
//     pthread_attr_setschedparam(&attrs, &priParam);
//
//     retc = pthread_create(&txThreadTask, &attrs, txTask, NULL);
//     if(retc != 0)
//     {
//         //Failed to initialize the task
//         while(1);
//     }
     /*
      * End TX thread
      */


     /*
      * Rx thread
      */

//     //Send as parameter the handle of the queue I need to pass data around
//     retc = pthread_create(&rxThreadTask, &attrs, rxTask, NULL);
//     if(retc != 0)
//     {
//         while(1);
//     }

     /*
      * End Rx Thread
      */


    /*
     * Thread 2
     */
//    priParam.sched_priority = 2;
//    pthread_attr_setschedparam(&attrs, &priParam);
//    retc = pthread_create(&ledThread,&attrs,ledTask,NULL);
//    if(retc != 0)
//    {
//        //Failed creating this thread
//        while(1);
//    }
    /*
     * End Thread 2
     */

    BIOS_start();



    return (0);
}
