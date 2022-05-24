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
#include "jshardwareTimer.h"
#include "hardware/timer.h"
#include "pico/time.h"
#define UNUSED(x) (void)(x)

alarm_id_t hwTimer;

int64_t timer_callback(alarm_id_t id, void *user_data) {
printf("alarm:%i\n",id);
  jstUtilTimerInterruptHandler();
  return 0;
}
void TimerReset(){
   UNUSED(1);  
}

void jshUtilTimerDisable() {
  cancel_alarm(hwTimer);
}

void jshUtilTimerReschedule(JsSysTime period) {
printf("tr;%i\n",period);
  cancel_alarm(hwTimer);
  hwTimer = add_alarm_in_ms(period, timer_callback, NULL, false);
}


void jshUtilTimerStart(JsSysTime period) {
  hwTimer = add_alarm_in_ms(period, timer_callback, NULL, false);
}

 