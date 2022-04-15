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
 
void I2CReset(){
   UNUSED(1); 
	 
}

void jshI2CSetup(IOEventFlags device, JshI2CInfo *inf) {
	
}

void jshI2CWrite(IOEventFlags device, unsigned char address, int nBytes, const unsigned char *data, bool sendStop) {
	
}

void jshI2CRead(IOEventFlags device, unsigned char address, int nBytes, unsigned char *data, bool sendStop) {
	
}

 