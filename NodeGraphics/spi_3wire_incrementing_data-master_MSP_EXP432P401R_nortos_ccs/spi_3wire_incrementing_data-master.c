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

void SPI_transmit(uint8_t data)
{
    digitalLow(EPD_CS);
    SPI_transmitData(EUSCI_B0_BASE, data);
    digitalHigh(EPD_CS);
}


void powerON()
{
  writeCMD(0x04);
}

void powerOff()
{
  writeCMD(0x02);
  writeCMD(0x03);
  writeData(0x00);
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

void partialUpdateSolid(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2, uint8_t color1, uint8_t color2)
{
  //turn on partial update mode
  writeCMD(0x91);

  //set the partial area
  writeCMD(0x90);
  writeData(((x1 / 8) << 1) | 0x07);    //x1
  writeData(((x2 / 8) << 1));   //x2
  writeData(y1 >> 8);     //1st half y1
  writeData(y1 & 0xff); //2nd half y1
  writeData(y2 >> 8);     //1st half y2
  writeData(y2 & 0xff); //2nd half y2

  writeData(0x01);

  int i;
  int h;

  //send black and white information
  writeCMD(0x10);
  for (h = 0; h < y2 - y1; h++)
  {
    for (i = 0; i < (x2 - x1) / 8; i++)
    {
      writeData(color1);
    }
  }
  //send red information
  writeCMD(0x13);
  for (h = 0; h < y2 - y1; h++)
  {
    for (i = 0; i < (x2 - x1) / 8; i++)
    {
      writeData(color2);
    }
  }

  //partial refresh of the same area as the partial update
  writeCMD(0x12);
  while (0 == digitalRead(EPD_READY));

  //turn off partial update mode
  writeCMD(0x92);
}


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


void turnWhite()
{
    //power on the display
      uint32_t i = 0;
      powerON();
      //SPI.transfer(0x10);
      writeCMD(0x10);

      for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
      {
          writeData(0x00);
      }
      //start data transmission 2
      writeCMD(0x13);
      for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
      {
          writeData(0x00);
      }
      //Aim back at the command register
      //Write the command: DATA STOP (DSP) (R11H)
      writeCMD(0x11);
      //Write the command: Display Refresh (DRF)
      writeCMD(0x12);
      //refresh the display
      //Serial.println("before refresh wait");
      while (!digitalRead(EPD_READY));
      //Serial.println("after refresh wait");
      //for maximum power conservation, power off the EPD
      powerOff();
      //delay(waittime);
}

void turnBlack()
{
    //power on the display
      uint32_t i = 0;
      powerON();
      //SPI.transfer(0x10);
      writeCMD(0x10);

      for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
      {
          writeData(0xff);
      }
      //start data transmission 2
      writeCMD(0x13);
      for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
      {
          writeData(0x00);
      }
      //Aim back at the command register
      //Write the command: DATA STOP (DSP) (R11H)
      writeCMD(0x11);
      //Write the command: Display Refresh (DRF)
      writeCMD(0x12);
      //refresh the display
      //Serial.println("before refresh wait");
      while (!digitalRead(EPD_READY));
      //Serial.println("after refresh wait");
      //for maximum power conservation, power off the EPD
      powerOff();
      //delay(waittime);
}

void turnYellow()
{
        //power on the display
         uint32_t i = 0;
         powerON();
         //SPI.transfer(0x10);
         writeCMD(0x10);

         for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
         {
             writeData(0x00);
         }
         //start data transmission 2
         writeCMD(0x13);
         for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
         {
             writeData(0xff);
         }
         //Aim back at the command register
         //Write the command: DATA STOP (DSP) (R11H)
         writeCMD(0x11);
         //Write the command: Display Refresh (DRF)
         writeCMD(0x12);
         //refresh the display
         //Serial.println("before refresh wait");
         while (!digitalRead(EPD_READY));
         //Serial.println("after refresh wait");
         //for maximum power conservation, power off the EPD
         powerOff();
         //delay(waittime);
}

void makeSquarePattern()
{
    //power on the display
        powerON();

        //color1 is for the bw data, color2 is for the red data
        uint8_t color1 = 0x00;
        uint8_t color2 = 0xff;

        //start data transmission 1
        writeCMD(0x10);
        uint32_t i = 0;
        uint8_t j = 0;
        for (i = 0; i < VRES; i++)
        {
          //every 8 rows, change the color
          if (i % 8 == 0)
          {
            color1 = ~color1;
          }
          //run for 13 loops to complete a row --- 104 / 8 = 13
          for (j = 0; j < HRES / 8; j++)
          {
            writeData(color1);
            //every 8 pixels, change the color
            color1 = ~color1;
          }
        }
        writeCMD(0x13);
        for (i = 0; i < VRES; i++)
        {
          if (i % 8 == 0)
          {
            color2 = ~color2;
          }
          for (j = 0; j < HRES / 8; j++)
          {
            writeData(color2);
            color2 = ~color2;
          }
        }

        //Serial.println("before refresh wait");
        //refresh the display
        writeCMD(0x12);
        while (0 == digitalRead(EPD_READY));
        //Serial.println("after refresh wait");
        //for maximum power conservation, power off the EPD
        powerOff();
        //delay(waittime);

}

int main(void)
{
    initDevices();

    turnBlack();

//    for(;;)
//    {


//        turnYellow();
//
//        //for(jj=0;jj<255;j++);
//
//        turnBlack();
//
//        //for(jj=0;jj<255;j++);
//
//        turnWhite();
//
//        //for(jj=0;jj<255;j++);
//
//        makeSquarePattern();

        //for(jj=0;jj<255;j++);
//    }


    PCM_gotoLPM0();
    __no_operation();
}





