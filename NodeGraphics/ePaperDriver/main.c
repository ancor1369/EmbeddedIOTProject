/*
 * Electronic Epaper
 *
 * I write this software to create an interface over the Crystalfontz E-Paper displays.
 *
 * This software ports the vendor provided code which is created for Arduino IDE initially,
 * So I am contributing this work to enable MSP430 platforms to drive this kind of screens.
 *
 *
 * EXP432P401R Port | Screen pin
 * -----------------+-----------
 *  3.3 V           | 3.3 V
 *  GND             | GND
 *  P1.5| SPI CLK   | SCK
 *  P1.6| SPI MOSI  | MOSI
 *  P2.7| GPIO      | ~CS
 *  P2.6| GPIO      | D/~C
 *  P2.4| GPIO      | ~RST
 *  P3.0| GPIO      | Busy
 */

/* DriverLib Includes */



/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Included libraries written to integrate the screen*/

#include <Driver/SPIinit.h>
#include <Driver/GPIOInit.h>
#include <Driver/pinDefinintions.h>
#include <Driver/ePaper.h>


int main(void)
{
    SPI_Init();
    GPIO_Init();

    initEPD();

    turnYellow();


    PCM_gotoLPM0();
    __no_operation();
}
