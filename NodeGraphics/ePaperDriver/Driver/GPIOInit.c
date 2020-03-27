#include "GPIOInit.h"

void GPIO_Init(void)
{
    //GPIO initialization
       GPIO_setAsOutputPin(GPIO_PORT_P2, EPD_CS | EPD_DC | EPD_RESET);
       GPIO_setOutputLowOnPin(GPIO_PORT_P2, EPD_CS | EPD_DC);
       GPIO_setAsInputPin(GPIO_PORT_P3, EPD_READY);

       //![Simple SPI Example]
       /* Selecting P1.5 P1.6 and P1.7 in SPI mode */
       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
               GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
}


void digitalLow(uint8_t pin)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, pin);
}

void digitalHigh(uint8_t pin)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, pin);
}

uint8_t result = 0;
uint8_t digitalRead(uint8_t pin)
{
    result = GPIO_getInputPinValue(GPIO_PORT_P3, pin);
    return result;
}
