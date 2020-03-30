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

#define test                \
"{"                         \
  "\"ProductID\": \"45\""    \
"}"



int main(void)
{
    SPI_Init();
    GPIO_Init();


    createLabel(test);


    printLabel();


    //Start the engine which starts the EPAPER screen and then
    //send a message the the screen
//    gfxInit();
//    gfxWriteText(&FONT_ubuntu_bold_16, 115, 0, "Scientific calculator for large");
//    gfxWriteText(&FONT_ubuntu_bold_16, 100, 0, "and digital part");
//    gfxWriteText(&FONT_ubuntu_medium_48, 24, 0, "545");
//    gfxWriteText(&FONT_ubuntu_bold_24, 58, 100, "98");
//    gfxWriteText(&FONT_ubuntu_bold_16, 20, 0, "SKU: 4568, 12/13/2020");
//    gfxWriteText(&FONT_ubuntu_bold_16, 0, 0, "Model: MFX4587");
//
////    LabelJSON object;
////
////    object.Description = "Scientific calculator for large and digital part";
////    object.PriceDollar = "545";
////    object.PriceCents = "98";
////    object.SKU = "456879";
////    object.DueDate = "12/13/2020";
////    object.Model = "MX4579";
//
//    updateEPD();

    PCM_gotoLPM0();
    __no_operation();
}
