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

#include "Driver/SPIinit.h"
#include "Driver/GPIOInit.h"
//#include "Driver/pinDefinintions.h"
//#include "Driver/ePaper.h"
//#include "grx/graphics.h"
//#include "fonts/resources.h"
//#include "LabelEngine/labelEngine.h"

#include "LabelEngine/labelEngine.h"

//
//#define test                \
//"{"                         \
//  "\"ProductID\": \"45\""    \
//"}"

#define test                                                        \
"{"                                                                 \
 "\"ProductID\": \"46\","                                           \
 "\"PriceDollar\": \"5\","                                        \
 "\"PriceCents\": \"97\","                                          \
 "\"Description\": \"Scientific calculator that is able to print long lines\","    \
 "\"URL\": \"https://bit.ly/largo1\","                              \
 "\"SKU\": \"4532321\","                                            \
 "\"Model\": \"FM7548\","                                           \
 "\"DueDate\": \"11/22/18\","                                       \
 "\"LayoutName\": \"RegularTag\","                                  \
 "\"Update\": \"true\","                                            \
 "\"Blink\": \"False\""                                             \
"}"


int main(void)
{
    SPI_Init();
    GPIO_Init();


    createLabel(test);


    printLabel();


    PCM_gotoLPM0();
    __no_operation();
}
