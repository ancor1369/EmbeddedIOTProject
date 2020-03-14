/*
 * Epaper Demonstrtion code:
 *
 * I write this software to create an interface over the Crystalfontz E-Paper displays.
 *
 * This softwre ports the vendor provided code which is created for Arduino IDE initially,
 * So I am contributiong this work to enable MSP430 platforms to drive this kind of screens.*
 *
 *
 * EXP430F5529 Port | Screen pin
 * -----------------+-----------
 *  3.3 V           | 3.3 V
 *  GND             | GND
 *  P3.2| SPI CLK   | SCK
 *  P3.0| SPI MOSI  | MOSI
 *  P8.2| GPIO      | ~CS
 *  P3.7| GPIO      | D/~C
 *  P4.0| GPIO      | ~RST
 *  P4.3| GPIO      | Busy
 */



#include <msp430.h>
#include "driverlib/MSP430F5xx_6xx/driverlib.h"
#include "GraphElements/LUTs_for_CFAP128296D00290.h"
#include "GraphElements/Images_for_CFAP128296D00290.h"

#define EPD_READY   3
#define EPD_RESET   GPIO_PIN0
#define EPD_DC      GPIO_PIN7
#define EPD_CS      GPIO_PIN2
#define SD_CS       GPIO_PIN4

//Create functions to address this function call
#define ePaper_RST_0  (digitalWrite(EPD_RESET, LOW))
#define ePaper_RST_1  (digitalWrite(EPD_RESET, HIGH))
#define ePaper_CS_0   (digitalWrite(EPD_CS, LOW))
#define ePaper_CS_1   (digitalWrite(EPD_CS, HIGH))
#define ePaper_DC_0   (digitalWrite(EPD_DC, LOW))
#define ePaper_DC_1   (digitalWrite(EPD_DC, HIGH))

#define HRES 128
#define VRES 296



/**
 * main.c
 */
int main(void)
{

   //Initialize the interfaces and modules



    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    GPIO_setAsOutputPin(GPIO_PORT_P3, selectedPins);
    GPIO_setAsOutputPin(GPIO_PORT_P4, selectedPins);
    GPIO_setAsOutputPin(GPIO_PORT_P8, selectedPins);


	


	return 0;
}
