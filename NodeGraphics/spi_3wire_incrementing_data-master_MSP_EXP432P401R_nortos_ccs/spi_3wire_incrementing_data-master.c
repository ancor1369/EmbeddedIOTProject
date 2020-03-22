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

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#define EPD_READY   GPIO_PIN0
#define EPD_RESET   GPIO_PIN4
#define EPD_DC      GPIO_PIN6
#define EPD_CS      GPIO_PIN7
#define LOW         0
#define HIGH        1

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


/* Statics */
static volatile uint8_t RXData = 0;
static uint8_t TXData = 0;

void writeCMD(uint8_t command)
{
  ePaper_DC_0;
  ePaper_CS_0;
//  //USCI_A0 TX buffer ready?
//    while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
//               USCI_B_SPI_TRANSMIT_INTERRUPT)) ;
//    //Transmit Data to slave
//    USCI_B_SPI_transmitData(USCI_B0_BASE, command);

  /* Polling to see if the TX buffer is ready */
  while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_SPI_TRANSMIT_INTERRUPT)));
     /* Transmitting data to slave */
  SPI_transmitData(EUSCI_B0_BASE, command);

  ePaper_CS_1;
}

//this function will take in a byte and send it to the display with the
//command bit high for data transmission
void writeData(uint8_t data)
{
  ePaper_DC_1;
  ePaper_CS_0;
//  //USCI_A0 TX buffer ready?
//     while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
//                USCI_B_SPI_TRANSMIT_INTERRUPT)) ;
//     //Transmit Data to slave
//     USCI_B_SPI_transmitData(USCI_B0_BASE, data);
  while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_SPI_TRANSMIT_INTERRUPT)));
  /* Transmitting data to slave */
  SPI_transmitData(EUSCI_B0_BASE, data);
  ePaper_CS_1;
}

void digitalWrite(uint8_t pin, uint8_t state)
{
    if(state == LOW)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, pin);
    }
    else
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, pin);
    }
}

uint8_t result = 0;
uint8_t j;
uint8_t digitalRead(uint8_t pin)
{
    result = GPIO_getInputPinValue(GPIO_PORT_P3, pin);
    for(j=0;j<50;j++);
    return result;
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
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW, // High polarity
        //EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
        EUSCI_B_SPI_4PIN_UCxSTE_ACTIVE_HIGH
};
//![Simple SPI Config]


void initDevices()
{
    //SPI interface
    /* Halting WDT  */
   WDT_A_holdTimer();

   //![Simple SPI Example]
   /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
   GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
           GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
   /* Configuring SPI in 3wire master mode */
   SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
   /* Enable SPI module */
   SPI_enableModule(EUSCI_B0_BASE);

   /* Enabling interrupts */
//    SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_SPI_RECEIVE_INTERRUPT);
//    Interrupt_enableInterrupt(INT_EUSCIB0);
//    Interrupt_enableSleepOnIsrExit();
   //GPIO initialization
   GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_CS);
   GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_DC);
   GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_RESET);
   GPIO_setAsInputPin(GPIO_PORT_P3, EPD_READY);
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


int main(void)
{
    initDevices();

//    TXData = 0x01;
//    writeCMD(TXData);
//    writeData(0x25);

    initEPD();



//    //![Simple SPI Example]

//    uint32_t jj;
//
//    ePaper_CS_1;
//    //GPIO_setOutputHighOnPin(GPIO_PORT_P2,  BIT7);
//
//
//    /* Polling to see if the TX buffer is ready */
//    while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_SPI_TRANSMIT_INTERRUPT)));
//
//    //GPIO_setOutputLowOnPin(GPIO_PORT_P2,  BIT7);
//    ePaper_CS_0;
//    /* Transmitting data to slave */
//    SPI_transmitData(EUSCI_B0_BASE, TXData);
//    for(jj=0;jj<10;jj++);
//    //GPIO_setOutputHighOnPin(GPIO_PORT_P2,  BIT7);
//    ePaper_CS_1;
//
//
//    for(jj=0;jj<50;jj++);
//    TXData = 0x02;
//
//    /* Polling to see if the TX buffer is ready */
//    while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_SPI_TRANSMIT_INTERRUPT)));
//
//    //GPIO_setOutputLowOnPin(GPIO_PORT_P2,  BIT7);
//    ePaper_CS_0;
//    /* Transmitting data to slave */
//    SPI_transmitData(EUSCI_B0_BASE, TXData);
//    for(jj=0;jj<10;jj++);
//    //GPIO_setOutputHighOnPin(GPIO_PORT_P2,  BIT7);
//    ePaper_CS_1;
//
//    PCM_gotoLPM0();
//    __no_operation();
}
