/*
 * This file is designed to support Analog functions in Espruino,
 * a JavaScript interpreter for Microcontrollers designed by Gordon Williams
 *
 * Copyright (C) 2022 by Juergen Marsch 
 *
 * This Source Code Form is subject to the terms of the Mozilla Publici
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * This file is designed to be parsed during the build process
 *
 * Contains RPI2040 board specific functions.
 * ----------------------------------------------------------------------------
 */

#include "jshardware.h"
#include "jsdevices.h" 
#include "jshardwareSPI.h"
#include "jsinteractive.h"

#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#define UNUSED(x) (void)(x)
 
void SPIReset(){
  UNUSED(1);  
}
void SPIInit(){
  UNUSED(1);
}
void setupDevice(spi_inst_t *spi,JshSPIInfo *inf){
  spi_init(spi, 500 * 1000);
  switch (inf->spiMode){
    case 0:spi_set_format(spi,inf->numBits,SPI_CPOL_0,SPI_CPHA_0,true);break;
	case 1:spi_set_format(spi,inf->numBits,SPI_CPOL_0,SPI_CPHA_1,true);break;
	case 2:spi_set_format(spi,inf->numBits,SPI_CPOL_1,SPI_CPHA_0,true);break;
	case 3:spi_set_format(spi,inf->numBits,SPI_CPOL_1,SPI_CPHA_1,true);break;
	default: break;
  }
} 
void jshSPISetup(IOEventFlags device, JshSPIInfo *inf) {
  switch (device){
	case EV_SPI1:
	  if(inf->pinMISO == 0xff) inf->pinMISO = 4;
	  if(inf->pinMOSI == 0xff) inf->pinMOSI = 3;
	  if(inf->pinSCK == 0xff) inf->pinSCK = 2;
      setupDevice(spi0,inf);
	  break;
	case EV_SPI2:
	  if(inf->pinMISO == 0xff) inf->pinMISO = 12;
	  if(inf->pinMOSI == 0xff) inf->pinMOSI = 11;
	  if(inf->pinSCK == 0xff) inf->pinSCK = 10;
	  setupDevice(spi1,inf);
	  break;
	default: break;
  }
  gpio_set_function(4, GPIO_FUNC_SPI);
  gpio_set_function(2, GPIO_FUNC_SPI);
  gpio_set_function(3, GPIO_FUNC_SPI);
}

/** Send data through the given SPI device (if data>=0), and return the result
 * of the previous send (or -1). If data<0, no data is sent and the function
 * waits for data to be returned */
int jshSPISend(IOEventFlags device, int data) {
  printf("SPI send:%i\n",data);
}

/** Send 16 bit data through the given SPI device. */
void jshSPISend16(IOEventFlags device, int data) {
  printf("SPI send16:%i\n",data);
}

/** Set whether to send 16 bits or 8 over SPI */
void jshSPISet16(IOEventFlags device, bool is16) {
  printf("SPI SET16:%i\n",is16);
}

/** Set whether to use the receive interrupt or not */
void jshSPISetReceive(IOEventFlags device, bool isReceive) {
printf("SPISetReceive:%i\n",isReceive);
}

/** Wait until SPI send is finished, */
void jshSPIWait(IOEventFlags device) {
printf("SPIWait\n");
  switch (device){
	case EV_SPI1:
      while(spi_is_busy(spi0));
      break;
    case EV_SPI2:
      while(spi_is_busy(spi1));
      break;
    default:
	  break;
  }	  
}

void sendDevice(spi_inst_t *spi,unsigned char *tx,unsigned char *rx,size_t count){
  uint8_t wBuff[2] = {0xAB};
  uint8_t rBuff[2];
  int n = 0;
printf(" %X %X \n", wBuff[0], rBuff[0]);
  if(rx) n = spi_write_read_blocking(spi,tx,rx,count);
  else spi_write_blocking(spi,tx,count);
  //if(rx) n = spi_write_read_blocking(spi,wBuff,rBuff,1);
  //else spi_write_blocking(spi,wBuff,1);
printf(" %X %X %d \n", wBuff[0], rBuff[0], n);
  
}
bool jshSPISendMany(IOEventFlags device, unsigned char *tx, unsigned char *rx, size_t count, void (*callback)()) {
printf("sendMany tx:%i,rx:%i,count:%i,callback:%i\n",tx,rx,count,callback);
  switch(device){
	case EV_SPI1: sendDevice(spi0,tx,rx,count); break;
	case EV_SPI2: sendDevice(spi1,tx,rx,count); break;
  }
  return true;
}
