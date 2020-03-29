#include "SPIinit.h"


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


void SPI_Init(void)
{
    //SPI interface
     /* Halting WDT  */
    WDT_A_holdTimer();

//    //GPIO initialization
//    GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_CS | EPD_DC | EPD_RESET);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P2, EPD_CS | EPD_DC);
//    GPIO_setAsInputPin(GPIO_PORT_P3, EPD_READY);
//
//    //![Simple SPI Example]
//    /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
//    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
//            GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    /* Configuring SPI in 3wire master mode */
    SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
    /* Enable SPI module */
    SPI_enableModule(EUSCI_B0_BASE);
}


//This needs to be donen by SPI
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
