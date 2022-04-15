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
#include "jshardwareAnalog.h"
 
#include "pico/stdlib.h"
#include "hardware/adc.h"
 
void ADCReset(){
  adc_init();
}
int ADCRead(Pin pin){
  if(pin > 25 && pin < 29){
    adc_gpio_init(pin);
	adc_select_input(pin - 26);
	return adc_read();
  }
  else{
    jsError("not an ADC pin");
  }
} 

JsVarFloat jshPinAnalog(Pin pin) {
  return (JsVarFloat) ADCRead(pin) * 3.3f / 4096;
}

int jshPinAnalogFast(Pin pin) {
  return ADCRead(pin);
}
