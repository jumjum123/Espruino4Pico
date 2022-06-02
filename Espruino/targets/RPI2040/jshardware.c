/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2022 Juergen Marsch <juergenmarsch@googlemail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Platform Specific part of Hardware interface Layer of RPI2040 (Raspberry Pi pico)
 * ----------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <inttypes.h>

#include "platform_config.h"
#include "jshardware.h"
#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"

#include "jshardwarePin.h"
#include "jshardwareAnalog.h"
#include "jshardwareFlash.h"
#include "jshardwareI2C.h"
#include "jshardwarePulse.h"
#include "jshardwarePWM.h"
#include "jshardwareSPI.h"
#include "jshardwareTimer.h"
#include "jshardwareUart.h"


/* pico libs */
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include   "pico/util/datetime.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/uart.h"
#include   "hardware/rtc.h"
#include <tusb.h>
// ----------------------------------------------------------------------------

Pin eventFlagsToPin[16];
int timeToSleep = -1;
bool firstIdle = true;

void jshInit() {
  jshInitDevices();
  jshPinDefaultPullup();
  ADCReset();
rtc_init();
  firstIdle = true;
}

void jshReset() {
  jshResetDevices();
  jshPinDefaultPullup();
  ADCReset();
  FlashReset();
  SPIReset();
  I2CReset();
  PulseReset();
  PWMReset();
  TimerReset();
  UartReset();
}

void jshKill() {
}

int64_t idleDelayCB(alarm_id_t id, void *user_data) {
  jsiOneSecondAfterStartup();
}
void jshIdle() {
  if (firstIdle){
	add_alarm_in_ms(1000, idleDelayCB, NULL, false);
    firstIdle = false;
  }
}


void jshBusyIdle() {

}

// ----------------------------------------------------------------------------

int jshGetSerialNumber(unsigned char *data, int maxChars) {
	int r,i;
	pico_unique_board_id_t board_id;
	pico_get_unique_board_id(&board_id);
	r = 0;
	for(i = PICO_UNIQUE_BOARD_ID_SIZE_BYTES - 4;i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES;i++){
		r << 4;
		r += board_id.id[i];
	}
    return r;
}

// ----------------------------------------------------------------------------
uint32_t irqMask;
void jshInterruptOff() {
  irqMask = getIrqMask();
  irq_set_mask_enabled(irqMask, false);  //dont stop timer irq 3
}

void jshInterruptOn() {
  irq_set_mask_enabled(irqMask, true);
}

/// Are we currently in an interrupt?
bool jshIsInInterrupt() {
  return false; // or check if we're in the IO handling thread?
}

void jshDelayMicroseconds(int microsec) {
  sleep_us((uint32_t)microsec);
}

bool jshIsDeviceInitialised(IOEventFlags device) { return true; }

bool jshIsUSBSERIALConnected() {
  return tud_cdc_connected();
}

JsSysTime jshGetTimeFromMilliseconds(JsVarFloat ms) {
  return (JsSysTime)(ms*1000);
}

JsVarFloat jshGetMillisecondsFromTime(JsSysTime time) {
  return ((JsVarFloat)time)/1000;
}

JsSysTime sys_startTime = 0;
JsSysTime jshGetSystemTime() {
  return sys_startTime + (JsSysTime)time_us_64();
}

void jshSetSystemTime(JsSysTime time) {
  sys_startTime = (time - (JsSysTime)time_us_64());
}

// ----------------------------------------------------------------------------

IOEventFlags jshGetEventFlagsForPin(Pin pin) {
  for (int i=0;i<16;i++)
    if (eventFlagsToPin[i]==pin)
      return EV_EXTI0+i;
  return EV_NONE;
}

bool jshGetWatchedPinState(IOEventFlags device) {
  return jshPinGetValue(eventFlagsToPin[device-EV_EXTI0]);
}

bool jshIsEventForPin(IOEvent *event, Pin pin) {
  return IOEVENTFLAGS_GETTYPE(event->flags) == jshGetEventFlagsForPin(pin);
}

/** Kick a device into action (if required). For instance we may need
 * to set up interrupts */
void jshUSARTKick(IOEventFlags device) {
  int c;
    c = jshGetCharToTransmit(device);
    while(c >= 0) {
	  switch(device){
	    case EV_USBSERIAL:
	      putchar(c);
		  break;
		case EV_LIMBO:
		  putchar(c);
		  break;
	    case EV_SERIAL1:
          uart_putc_raw(uart0,c);
	      break;
		case EV_SERIAL2:
		  uart_putc_raw(uart1,c);
		  break;
	    default:
	  
	      break;
	  }
	  c = jshGetCharToTransmit(device);
    }
}

/// Enter simple sleep mode (can be woken up by interrupts). Returns true on success
bool jshSleep(JsSysTime timeUntilWake) {
  JsVarFloat t = jshGetMillisecondsFromTime(timeUntilWake);
  if (t>0x7FFFFFFF) t=0x7FFFFFFF;
  timeToSleep = (int)t;
  return false;
}

JshPinFunction jshGetCurrentPinFunction(Pin pin) {
  return JSH_NOTHING;
}

void jshSetOutputValue(JshPinFunction func, int value) {
  jsError(">> no DAC available");
}

void jshEnableWatchDog(JsVarFloat timeout) {
}

void jshKickWatchDog() {
}

JsVarFloat jshReadTemperature() { return NAN; };
JsVarFloat jshReadVRef()  { return NAN; };
unsigned int jshGetRandomNumber() { return rand(); }

unsigned int jshSetSystemClock(JsVar *options) {
  return 0;
}

/// Perform a proper hard-reboot of the device
void jshReboot() {
  printf("Reboot in a second\n");
  watchdog_reboot(0,0,1000);
  //jsExceptionHere(JSET_ERROR, "Not implemented");
}
