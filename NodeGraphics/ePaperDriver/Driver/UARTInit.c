/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
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
 * --/COPYRIGHT--*/

#include "UARTInit.h"

uint8_t TXData = 1;
uint8_t RXData = 0;
uint8_t counter = 0;
uint8_t i = 0;

//This is the buffer I need to contain
//all the characters that are coming to modify the
//image on the screen!
char buffer[512];


//The parameters to initialize the micro controller are provided in the following web site
//http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html

const eUSCI_UART_ConfigV1 uartConfig =
{
         EUSCI_A_UART_CLOCKSOURCE_SMCLK,            // SMCLK Clock Source
         6,                                         // BRDIV = 13
         8,                                         // UCxBRF = 8
         0,                                         // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                     // No Parity
        EUSCI_A_UART_LSB_FIRST,                     // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,                  // One stop bit
        EUSCI_A_UART_MODE,                          // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                      // 8 bit data length
};
//![Simple UART Config]

void UART_Init(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

   //![Simple UART Example]
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        RXData = MAP_UART_receiveData(EUSCI_A2_BASE);
        //Accumulate everything but car return
        if(RXData != 0x0D)
        {
            buffer[counter] = RXData;
            counter++;
            if(counter == sizeof(buffer))
            {
                counter=0;
                memset(buffer,0x00,sizeof(buffer));
            }
        }
        else
        {
            buffer[counter] = RXData;
            for(i=0 ; i <= counter ; i++)
            {
                MAP_UART_transmitData(EUSCI_A2_BASE, buffer[i]);
            }
            counter = 0;
            //clear the buffer
            memset(buffer,0x00,sizeof(buffer));
        }
    }
}

