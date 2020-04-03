/*
 * SPIInit.h
 *
 *  Created on: Mar 27, 2020
 *      Author: andres rogelio cordoba
 */

#include "pinDefinintions.h"


void SPI_Init(void);


void writeCMD(uint8_t command);


void writeData(uint8_t data);


void SPI_transmit(uint8_t data);
