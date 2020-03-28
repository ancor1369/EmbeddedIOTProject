
#include "ePaper.h"

uint8_t GLOBAL_framebuffer[VRES][HRES / 8];

void powerON(void);
void powerOff(void);

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

void initEPD()
{
    uint8_t j = 0;

    //Reset the screen
    digitalLow(EPD_RESET);
    for(j=0;j<10;j++);
    digitalHigh(EPD_RESET);
    for(j=0;j<10;j++);


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

void updateEPD(void)
{
    //Power on the display
    uint32_t i = 0;
    uint8_t j = 0;
    uint8_t color1 = 0x00;
    uint8_t color2 = 0x00;

    powerON();

    writeCMD(0x10);

    for (i = 0; i < VRES; i++)
    {
      //This is divided by 8 because it
      //is represented as
      for (j = 0; j < HRES / 8; j++)
      {
          writeData(GLOBAL_framebuffer[i][j]);
      }
    }
    writeCMD(0x13);
    for (i = 0; i < VRES; i++)
    {
      for (j = 0; j < HRES / 8; j++)
      {
        writeData(color2);
      }
    }

    writeCMD(0x12);
    while (!digitalRead(EPD_READY));

    powerOff();
}

void turnWhite()
{
    //power on the display
      uint32_t i = 0;
      powerON();

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
