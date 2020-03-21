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
 *  P3.2| SPI CLK   | SCK
 *  P3.0| SPI MOSI  | MOSI
 *  P8.2| GPIO      | ~CS
 *  P3.7| GPIO      | D/~C
 *  P4.0| GPIO      | ~RST
 *  P4.3| GPIO      | Busy
 */



#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include "driverlib/MSP430F5xx_6xx/driverlib.h"
#include "GraphElements/LUTs_for_CFAP128296D00290.h"
#include "GraphElements/Images_for_CFAP128296D00290.h"

#define EPD_READY   GPIO_PIN3
#define EPD_RESET   GPIO_PIN0
#define EPD_DC      GPIO_PIN7
#define EPD_CS      GPIO_PIN2
#define LOW         0
#define HIGH       1

//Create functions to address this function call
#define ePaper_RST_0  (digitalWrite(EPD_RESET, LOW))
#define ePaper_RST_1  (digitalWrite(EPD_RESET, HIGH))
#define ePaper_CS_0   (digitalWrite(EPD_CS, LOW))
#define ePaper_CS_1   (digitalWrite(EPD_CS, HIGH))
#define ePaper_DC_0   (digitalWrite(EPD_DC, LOW))
#define ePaper_DC_1   (digitalWrite(EPD_DC, HIGH))

#define HRES 128
#define VRES 296

#define SPICLK                          2000000

uint8_t tempPort;
uint8_t returnValue = 0x00;

void sipTransmitData(uint8_t data)
{
    //USCI_A0 TX buffer ready?
      while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
                 USCI_B_SPI_TRANSMIT_INTERRUPT)) ;
      //Transmit Data to slave
      USCI_B_SPI_transmitData(USCI_B0_BASE, data);
}


//=============================================================================
//this function will take in a byte and send it to the display with the
//command bit low for command transmission
void writeCMD(uint8_t command)
{
  ePaper_DC_0;
  ePaper_CS_0;
  //USCI_A0 TX buffer ready?
    while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
               USCI_B_SPI_TRANSMIT_INTERRUPT)) ;
    //Transmit Data to slave
    USCI_B_SPI_transmitData(USCI_B0_BASE, command);
  ePaper_CS_1;
}

//this function will take in a byte and send it to the display with the
//command bit high for data transmission
void writeData(uint8_t data)
{
  ePaper_DC_1;
  ePaper_CS_0;
  //USCI_A0 TX buffer ready?
     while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
                USCI_B_SPI_TRANSMIT_INTERRUPT)) ;
     //Transmit Data to slave
     USCI_B_SPI_transmitData(USCI_B0_BASE, data);
  ePaper_CS_1;
}

void digitalWrite(uint8_t pin, uint8_t state)
{
    switch(pin)
    {
        case EPD_RESET:
            tempPort = GPIO_PORT_P4;
        case EPD_DC:
            tempPort = GPIO_PORT_P3;
        case EPD_CS:
            tempPort = GPIO_PORT_P8;
    }
    if(state == LOW)
    {
        GPIO_setOutputHighOnPin(tempPort, pin);
    }
    else
    {
        GPIO_setOutputLowOnPin(tempPort, pin);
    }
}

uint8_t result;
uint8_t digitalRead(uint8_t pin)
{
    //result = GPIO_getInputPinValue(GPIO_PORT_P4, pin);
    __delay_cycles(50000);
    result=1;
    return result;
}

void initEPD(void)
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

     while (0 == digitalRead(EPD_READY));
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

/*
 * This initialization is done first
 * to implement the example the maker provides
 * and then it is going to be further ported to make
 * sure it implements other modules necessary to
 * create a complete integration with the communications
 * module.
 *
 */

void initDevices(void)
{
    //Initialize the interfaces and modules
    //stop watchdog timer
     WDTCTL = WDTPW | WDTHOLD;


     //Set the GPIO needed for managing the screen
     GPIO_setAsOutputPin(GPIO_PORT_P3, EPD_DC);
     GPIO_setAsOutputPin(GPIO_PORT_P4, EPD_RESET);
     GPIO_setAsOutputPin(GPIO_PORT_P8, EPD_CS);
     GPIO_setAsInputPin(GPIO_PORT_P4, EPD_READY);

     USCI_B_SPI_initMasterParam param = {0};
     param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
     param.clockSourceFrequency = UCS_getSMCLK();
     param.desiredSpiClock = SPICLK; //Not supported for this setting
     param.msbFirst = USCI_B_SPI_MSB_FIRST;
     param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
     returnValue = param.clockPolarity = USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

     if(STATUS_FAIL == returnValue)
     {
         return;
     }
     USCI_B_SPI_enable(USCI_B0_BASE);

     ePaper_RST_0;
     __delay_cycles(6000);
     ePaper_RST_1;
     __delay_cycles(6000);

     initEPD();
}


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

//================================================================================
void Load_Flash_Image_To_Display_RAM(uint16_t width_pixels,
  uint16_t height_pixels,
  const unsigned char *BW_image,
  const unsigned char *Y_image)
{
  //Index into *image, that works with pgm_read_byte()
  uint16_t
    index;
  index = 0;

  //Get width_bytes from width_pixel, rounding up
  uint8_t
    width_bytes;
  width_bytes = (width_pixels + 7) >> 3;

  //Make sure the display is not busy before starting a new command.
  while (0 == digitalRead(EPD_READY));
  //Select the controller
  ePaper_CS_0;

  //Aim at the command register
  ePaper_DC_0;
  //Write the command: DATA START TRANSMISSION 1 (DTM2) (R13H)
  //  Display Start transmission 1
  //  (DTM1, BW Data)
  //
  // This command starts transmitting data and write them into SRAM. To complete
  // data transmission, command DSP (Data transmission Stop) must be issued. Then
  // the chip will start to send data/VCOM for panel.
  //  * In B/W mode, this command writes �OLD� data to SRAM.
  //  * In B/W/Red mode, this command writes �BW� data to SRAM.
  //SPI.transfer(0x10);
  sipTransmitData(0x10);
  //Pump out the BW data.
  ePaper_DC_1;
  index = 0;
  uint16_t y = 0;
  uint8_t x = 0;
  //Serial.println("first loop");
  for (y = 0; y<height_pixels; y++)
  {
    for (x = 0; x<width_bytes; x++)
    {
      //SPI.transfer(&BW_image[index]);
      sipTransmitData(&BW_image[index]);
      index++;
    }
  }

  //Aim at the command register
  ePaper_DC_0;
  //Write the command: DATA START TRANSMISSION 2 (DTM2) (R13H)
  //  Display Start transmission 2
  //  (DTM2, Red Data)
  //
  // This command starts transmitting data and write them into SRAM. To complete
  // data transmission, command DSP (Data transmission Stop) must be issued. Then
  // the chip will start to send data/VCOM for panel.
  //  * In B/W mode, this command writes �NEW� data to SRAM.
  //  * In B/W/Red mode, this command writes �Red� data to SRAM.
  //SPI.transfer(0x13);
  sipTransmitData(0x13);
  //Pump out the Red data.
  ePaper_DC_1;
  index = 0;
  //Serial.println("second loop");
  for (y = 0; y<height_pixels; y++)
  {
    for (x = 0; x<width_bytes; x++)
    {
      //SPI.transfer(&Y_image[index]);
      sipTransmitData(&Y_image[index]);
      index++;
    }
  }

  //Aim back at the command register
  ePaper_DC_0;
  //Write the command: DATA STOP (DSP) (R11H)
  //SPI.transfer(0x11);
  sipTransmitData(0x11);
  //Write the command: Display Refresh (DRF)
  //SPI.transfer(0x12);
  sipTransmitData(0x12);
  //Deslect the controller
  ePaper_CS_1;
}

//================================================================================
void send_pixels_BW(uint16_t byteCount, uint8_t *dataPtr)
{
  uint8_t data;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t i = 0;
  while (byteCount != 0)
  {
    uint8_t data = 0;
    //the first byte received from a .BMP file is red, then green, then blue.
    red = *dataPtr;
    dataPtr++;
    byteCount--;
    green = *dataPtr;
    dataPtr++;
    byteCount--;
    blue = *dataPtr;
    dataPtr++;
    byteCount--;

    //check to see if pixel should be set as black or white
    if (127 > ((red*.21) + (green*.72) + (blue*.07)))
    {
      data = data | 0x01;
    }

    for (i = 0; i < 7; i++)
    {
      red = *dataPtr;
      dataPtr++;
      byteCount--;
      green = *dataPtr;
      dataPtr++;
      byteCount--;
      blue = *dataPtr;
      dataPtr++;
      byteCount--;

      //shift data over one bit so we can store the value
      data = data << 1;

      //check to see if pixel should be set as black or white
      if (127 > ((red*.21) + (green*.72) + (blue*.07)))
      {
        data = data | 0x01;
      }
      else
      {
        data = data & 0xFE;
      }
    }
    writeData(data);
  }
}

//================================================================================
void send_pixels_Y(uint8_t byteCount, uint8_t *dataPtr)
{
  uint8_t data;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t i = 0;
  while (byteCount != 0)
  {
    uint8_t data = 0;
    blue = *dataPtr;
    dataPtr++;
    byteCount--;
    green = *dataPtr;
    dataPtr++;
    byteCount--;
    red = *dataPtr;
    dataPtr++;
    byteCount--;

    //check to see if pixel should be set as red
    if ((228 < red) && (208 < green) && (blue < 250))
    {
      data |= 0x01;
    }

    for (i = 0; i < 7; i++)
    {
      blue = *dataPtr;
      dataPtr++;
      byteCount--;
      green = *dataPtr;
      dataPtr++;
      byteCount--;
      red = *dataPtr;
      dataPtr++;
      byteCount--;
      data = data << 1;

      //check to see if pixel should be set as red
      if ((228 < red) && (208 < green) && (blue < 250))
      {
        data |= 0x01;
      }
      else
      {
        data &= 0xFE;
      }
    }
    writeData(data);
  }
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


/**
 * main.c
 *
 *
 * Bare metal implementation to drive
 * the screen
 *
 */

#define waittime 20000
#define splashscreen 0

int main(void)
{
    initDevices();

    uint8_t i = 0;

    //for(;;)
    {
        //I will clear the screen and make it white!

          //power on the display
          powerON();
          ePaper_CS_0;
          ePaper_DC_0;
          //start data transmission 1
          //SPI.transfer(0x10);
          sipTransmitData(0x10);
          ePaper_DC_1;

          for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
          {
            //SPI.transfer(0x00);
              sipTransmitData(0x00);
          }
          //start data transmission 2
          ePaper_DC_0;
          //SPI.transfer(0x13);
          sipTransmitData(0x13);
          ePaper_DC_1;
          for (i = 0; i < (uint32_t)VRES*HRES >> 3; i++)
          {
            //SPI.transfer(0x00);
              sipTransmitData(0x00);
          }

          //Aim back at the command register
          ePaper_DC_0;
          //Write the command: DATA STOP (DSP) (R11H)
          //SPI.transfer(0x11);
          sipTransmitData(0x11);
          //Write the command: Display Refresh (DRF)
          //SPI.transfer(0x12);
          sipTransmitData(0x12);
          //Deslect the controller
          ePaper_CS_1;
          //refresh the display
          //Serial.println("before refresh wait");
          while (0 == digitalRead(EPD_READY));
          //Serial.println("after refresh wait");
          //for maximum power conservation, power off the EPD
          powerOff();
          //delay(waittime);


    }


//    #if splashscreen
//      //power on the display
//      powerON();
//      //load an image to the display
//      Load_Flash_Image_To_Display_RAM(HRES, VRES, Splash_Mono_1BPP, Splash_Red_1BPP);
//
//      //Serial.print("refreshing . . . ");
//      while (0 == digitalRead(EPD_READY));
//      //Serial.println("refresh complete");
//      //for maximum power conservation, power off the EPD
//      powerOff();
//      //delay(waittime);
//    #endif

	return 0;
}
