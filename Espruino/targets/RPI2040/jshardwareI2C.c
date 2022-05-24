/*
 * This file is designed to support Analog functions in Espruino,
 * a JavaScript interpreter for Microcontrollers designed by Gordon Williams
 *
 * Copyright (C) 2016 by Juergen Marsch 
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
#include "jshardwareI2C.h"
#define UNUSED(x) (void)(x)

#include "hardware/gpio.h"
#include "hardware/i2c.h"
 
void I2CReset(){
   UNUSED(1); 	 
}

void i2c_setup(i2c_inst_t *i2c,JshI2CInfo *inf){
  gpio_set_function(inf->pinSDA,GPIO_FUNC_I2C);
  gpio_set_function(inf->pinSCL,GPIO_FUNC_I2C);
  gpio_pull_up(inf->pinSDA);
  gpio_pull_up(inf->pinSCL);
  i2c_init(i2c,inf->bitrate); 
}
void jshI2CSetup(IOEventFlags device, JshI2CInfo *inf) {
  switch(device){
    case EV_I2C1:
	  if(inf->pinSCL == 0xff) inf->pinSCL = 13;
	  if(inf->pinSDA == 0xff) inf->pinSDA = 12;
	  i2c_setup(i2c0,inf);
	  break;
	case EV_I2C2:
	  if(inf->pinSCL == 0xff) inf->pinSCL = 15;
	  if(inf->pinSDA == 0xff) inf->pinSDA = 14;
	  i2c_setup(i2c1,inf);
	  break;
	default: break;
  }
}

void i2c_write(i2c_inst_t *i2c,unsigned char address,int nBytes,const unsigned char *data,bool sendStop){
  i2c_write_blocking(i2c0,address,data,nBytes,sendStop);
}
void jshI2CWrite(IOEventFlags device, unsigned char address, int nBytes, const unsigned char *data, bool sendStop) {
  int i2c;
  switch (device){
    case EV_I2C1: i2c_write(i2c0,address,nBytes,data,sendStop); break;
	case EV_I2C2: i2c_write(i2c1,address,nBytes,data,sendStop); break;
	default: break;
  }
}

void i2c_read(i2c_inst_t *i2c,unsigned char address, int nBytes,unsigned char *data,bool sendStop){
  i2c_read_blocking(i2c,address,data,nBytes,sendStop);
}
void jshI2CRead(IOEventFlags device, unsigned char address, int nBytes, unsigned char *data, bool sendStop) {
  int i2c;
  switch (device){
    case EV_I2C1: i2c_read(i2c0,address,nBytes,data,sendStop); break;
	case EV_I2C2: i2c_read(i2c1,address,nBytes,data,sendStop); break;
	default: break;
  }
}

 