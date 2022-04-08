/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk> for Espruino
 * Copyright (C) 2022 Juergen Marsch <juergenmarsch@googlemail.com> for RPI2040 port
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * RPI2040 USB Console specific functions
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include <tusb.h>

#include "jsinteractive.h"

int initConsole(){//Init USB console
	
}; 
void espruinoToConsole(int c){
  putchar(c);
}
int consoleToEspruino(){ //read chars from USB console
  int charsFound;
  if(!tud_cdc_connected()){
	return -1;
  }
  else{
	charsFound = tud_cdc_available();
	while(charsFound > 0){
	  char c = getchar();
	  charsFound--;
	  jshPushIOCharEvents(EV_USBSERIAL, &c, 1);
	}
    return 0;	
  }    
}
