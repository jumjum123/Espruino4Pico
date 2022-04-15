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
#include "jshardwarePin.h"
#define UNUSED(x) (void)(x)
 
#include "pico/stdlib.h"
 
void jshPinSetStateRange(Pin start, Pin end, JshPinState state){
  for(Pin p = start;p <= end; p++){
	jshPinSetState(p,state);
  }
}
void jshPinDefaultPullup(){
  jshPinSetStateRange(0,22,JSHPINSTATE_GPIO_IN_PULLUP);
  jshPinSetStateRange(25,28,JSHPINSTATE_GPIO_IN_PULLUP);
}
 //The pin to have its state changed, The new desired state of the pin.
void jshPinSetState(Pin pin,JshPinState state ) {
  gpio_init(pin);
  switch(state) {
    case JSHPINSTATE_GPIO_OUT:
      gpio_set_dir(pin, GPIO_OUT);
      break;
    case JSHPINSTATE_GPIO_IN:
      gpio_set_dir(pin, GPIO_IN);
      break;
    case JSHPINSTATE_GPIO_IN_PULLUP:
      gpio_set_dir(pin, GPIO_IN);
      gpio_pull_up(pin);
      break;
    case JSHPINSTATE_GPIO_IN_PULLDOWN:
      gpio_set_dir(pin, GPIO_IN);
      gpio_pull_down(pin);
      break;
    case JSHPINSTATE_GPIO_OUT_OPENDRAIN:
      gpio_set_dir(pin, GPIO_OUT);
      break;
    case JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP:
      gpio_set_dir(pin, GPIO_OUT);
      gpio_pull_up(pin);
      break;
    default:
      jsError( "jshPinSetState: Unexpected state: %d", state);
  }
  return;	  
}
JshPinState jshPinGetState(Pin pin) {
  if(gpio_is_dir_out(pin)){
	return JSHPINSTATE_GPIO_OUT;
  }
  else{
	if(gpio_is_pulled_up(pin)) return JSHPINSTATE_GPIO_IN_PULLUP;
	if(gpio_is_pulled_down(pin)) return JSHPINSTATE_GPIO_IN_PULLDOWN;
	return JSHPINSTATE_GPIO_IN;
  }
}
void jshPinSetValue(Pin pin, bool value) {
  gpio_set_dir(pin, GPIO_OUT);
  if(value) gpio_put(pin,1);
  else gpio_put(pin,0);
}
bool jshPinGetValue(Pin pin) {
  return gpio_get(pin);
}	