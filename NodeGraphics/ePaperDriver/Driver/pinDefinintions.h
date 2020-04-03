/*
 * pinDefinintions.h
 *
 *  Created on: Mar 27, 2020
 *      Author: andres
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/drivers/SPI.h>
#include <string.h>


#define EPD_READY   GPIO_PIN0
#define EPD_RESET   GPIO_PIN4
#define EPD_DC      GPIO_PIN6
#define EPD_CS      GPIO_PIN7
#define LOW         0
#define HIGH        1
