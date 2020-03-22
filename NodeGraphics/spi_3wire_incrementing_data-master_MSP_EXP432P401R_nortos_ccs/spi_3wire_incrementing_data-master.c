/*
 * Epaper Demonstration code:
 *
 * I write this software to create an interface over the Crystalfontz E-Paper displays.
 *
 * This software ports the vendor provided code which is created for Arduino IDE initially,
 * So I am contributing this work to enable MSP430 platforms to drive this kind of screens.*
 *
 *
 * EXP430F5529 Port | Screen pin
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
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/drivers/SPI.h>


/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#define EPD_READY   GPIO_PIN0
#define EPD_RESET   GPIO_PIN4
#define EPD_DC      GPIO_PIN6
#define EPD_CS      GPIO_PIN7
#define LOW         0
#define HIGH        1

#define ePaper_RST_0  (digitalLow(EPD_RESET))
#define ePaper_RST_1  (digitalHigh(EPD_RESET))
#define ePaper_CS_0   (digitalLow(EPD_CS))
#define ePaper_CS_1   (digitalHigh(EPD_CS))
#define ePaper_DC_0   (digitalLow(EPD_DC))
#define ePaper_DC_1   (digitalHigh(EPD_DC))

#define HRES 128
#define VRES 296

/* Statics */
static volatile uint8_t RXData = 0;

void digitalLow(uint8_t pin)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, pin);
}

void digitalHigh(uint8_t pin)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, pin);
}

uint8_t result = 0;
uint8_t j;
uint8_t digitalRead(uint8_t pin)
{
    result = GPIO_getInputPinValue(GPIO_PORT_P3, pin);
    //for(j=0;j<50;j++);
    return result;
}


void writeCMD(uint8_t command)
{

  digitalLow(EPD_DC);
  digitalLow(EPD_CS);
  SPI_transmitData(EUSCI_B0_BASE, command);
  digitalHigh(EPD_CS);
  GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);
}

//this function will take in a byte and send it to the display with the
//command bit high for data transmission
void writeData(uint8_t data)
{
  digitalHigh(EPD_DC);
  digitalLow(EPD_CS);
  SPI_transmitData(EUSCI_B0_BASE, data);
  digitalHigh(EPD_CS);
  GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);
}

//![Simple SPI Config]
/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
        3000000,                                   // SMCLK = DCO = 3MHZ
        500000,                                    // SPICLK = 500khz
        EUSCI_B_SPI_MSB_FIRST,                     // MSB First
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,  // High polarity
        EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};
//![Simple SPI Config]


void initEPD()
{
    //-----------------------------------------------------------------------------
     // more detail on the following commands and additional commands not used here
     // can be found on the CFAP128296D0-0290 datasheet on the Crystalfontz website
     //-----------------------------------------------------------------------------

     //Power Setting
     writeCMD(0x01);
     writeData(0x03);
     writeData(0x00);
     writeData(0x0A);
     writeData(0x00);
     writeData(0x03);

     //Booster Soft Start
     writeCMD(0x06);
     writeData(0x17);
     writeData(0x17);
     writeData(0x17);

     //Power On
     writeCMD(0x04);
     //Serial.println("before wait");
     //wait until powered on

     while (!digitalRead(EPD_READY));
     //Serial.println("after wait");

     //Panel Setting
     writeCMD(0x00);
     writeData(0x83);

     //PLL Control
     writeCMD(0x30);
     writeData(0x3c);

     //Resolution
     writeCMD(0x61);
     writeData(HRES);
     writeData(VRES>>8);
     writeData(VRES&0xff);

     //VCOM_DC Setting
     writeCMD(0x82);
     writeData(0x0A);

     //Vcom and data interval setting
     writeCMD(0x50);
     writeData(0x87);
}




void initDevices()
{
    //SPI interface
    /* Halting WDT  */
   WDT_A_holdTimer();

   //GPIO initialization
   GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_CS | EPD_DC | EPD_RESET);
   GPIO_setOutputLowOnPin(GPIO_PORT_P2, EPD_CS | EPD_DC);
   GPIO_setAsInputPin(GPIO_PORT_P3, EPD_READY);

   //![Simple SPI Example]
   /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
   GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
           GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
   /* Configuring SPI in 3wire master mode */
   SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
   /* Enable SPI module */
   SPI_enableModule(EUSCI_B0_BASE);

   ePaper_RST_0;
   for(j=0;j<10;j++);
   ePaper_RST_1;
   for(j=0;j<10;j++);


   initEPD();

}

int main(void)
{
    initDevices();
    PCM_gotoLPM0();
    __no_operation();
}





