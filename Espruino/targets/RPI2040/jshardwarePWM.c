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
#include "jshardwarePWM.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#define UNUSED(x) (void)(x)
 
void PWMReset(){
   UNUSED(1); 
	 
}
JshPinFunction jshPinAnalogOutput(Pin pin, JsVarFloat value, JsVarFloat freq, JshAnalogOutputFlags flags) { // if freq<=0, 
  if (value<0) value=0;
  if (value>1) value=1;
  if (!freq) freq = 100;
  if (!isfinite(freq)) freq=100;
  if(pin >= 26 & pin <= 28){
	printf("pins for ADC\n");
  }
  else {
    writePinPWM(pin,(uint16_t) (value * 100),(uint16_t) freq);
  }
  return 0;
}
void writePinPWM(Pin pin,uint16_t value,uint16_t freq){
  gpio_set_function(pin,GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pin);
  uint chan = pwm_gpio_to_channel(pin);
  uint32_t clock = 125000000;
  uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096) != 0);
  if(divider16 / 16 == 0) divider16 = 16;
  uint32_t wrap = clock * 16 / divider16 / freq -1;
  pwm_set_clkdiv_int_frac(slice_num,divider16 / 16, divider16 & 0xf);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_chan_level(slice_num, chan, wrap * value / 100);
  
  pwm_set_enabled(slice_num,true);
}

 