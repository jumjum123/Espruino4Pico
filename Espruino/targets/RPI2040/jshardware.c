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
#include "hardware/timer.h"
#include <tusb.h>
// ----------------------------------------------------------------------------

Pin eventFlagsToPin[16];
int timeToSleep = -1;
bool firstIdle = true;

void jshInit() {
  jshInitDevices();
  jshPinDefaultPullup();
  ADCReset();
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
	//sleep_ms(5000);
	//jsiOneSecondAfterStartup();
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

void jshInterruptOff() {
}

void jshInterruptOn() {
}

/// Are we currently in an interrupt?
bool jshIsInInterrupt() {
  return false; // or check if we're in the IO handling thread?
}

void jshDelayMicroseconds(int microsec) {
}

// see jshardwarePin.c void jshPinSetState(Pin pin, JshPinState state) {}

//JshPinState jshPinGetState(Pin pin) {
//  return JSHPINSTATE_UNDEFINED;
//}

/* see jshardwarePin.c void jshPinSetValue(Pin pin, bool value) {
//  if (pinInfo[pin].port & JSH_PIN_NEGATED) value=!value;
}*/

/* see jshardwarePin.c bool jshPinGetValue(Pin pin) {
  bool value = 0;
  if (pinInfo[pin].port & JSH_PIN_NEGATED) value=!value;
  return value;
}
*/

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

JsSysTime jshGetSystemTime() {
    return (JsSysTime)time_us_64();
}

void jshSetSystemTime(JsSysTime time) {
	printf("jshSetSystemTime not implemented yet");
}

// ----------------------------------------------------------------------------

/*JsVarFloat jshPinAnalog(Pin pin) {
  return (JsVarFloat) ADCRead(pin) * 3.3f / 4096;
}

int jshPinAnalogFast(Pin pin) {
  return ADCRead(pin);
}
*/
JshPinFunction jshPinAnalogOutput(Pin pin, JsVarFloat value, JsVarFloat freq, JshAnalogOutputFlags flags) { // if freq<=0, 
  return JSH_NOTHING;
}

void jshPinPulse(Pin pin, bool value, JsVarFloat time) {
}

bool jshCanWatch(Pin pin) {
  return true;
}

IOEventFlags jshGetEventFlagsForPin(Pin pin) {
  for (int i=0;i<16;i++)
    if (eventFlagsToPin[i]==pin)
      return EV_EXTI0+i;
  return EV_NONE;
}

IOEventFlags jshPinWatch(Pin pin, bool shouldWatch) {
  if (shouldWatch)
    for (int i=0;i<16;i++)
      if (eventFlagsToPin[i]==PIN_UNDEFINED) {
        eventFlagsToPin[i]=pin;
        return EV_EXTI0+i;
      }
  else {
    for (int i=0;i<16;i++)
      if (eventFlagsToPin[i]==pin)
        eventFlagsToPin[i]=PIN_UNDEFINED;
  }
  return EV_NONE;
}

bool jshGetWatchedPinState(IOEventFlags device) {
  return jshPinGetValue(eventFlagsToPin[device-EV_EXTI0]);
}

bool jshIsEventForPin(IOEvent *event, Pin pin) {
  return IOEVENTFLAGS_GETTYPE(event->flags) == jshGetEventFlagsForPin(pin);
}

void jshUSARTSetup(IOEventFlags device, JshUSARTInfo *inf) {
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
	  
	      break;
	    default:
	  
	      break;
	  }
	  c = jshGetCharToTransmit(device);
    }
}

//void jshSPISetup(IOEventFlags device, JshSPIInfo *inf) {}

/** Send data through the given SPI device (if data>=0), and return the result
 * of the previous send (or -1). If data<0, no data is sent and the function
 * waits for data to be returned */
//int jshSPISend(IOEventFlags device, int data) {}

/** Send 16 bit data through the given SPI device. */
//void jshSPISend16(IOEventFlags device, int data) {}

/** Set whether to send 16 bits or 8 over SPI */
//void jshSPISet16(IOEventFlags device, bool is16) {}

/** Set whether to use the receive interrupt or not */
//void jshSPISetReceive(IOEventFlags device, bool isReceive) {}

/** Wait until SPI send is finished, */
//void jshSPIWait(IOEventFlags device) {}

//void jshI2CSetup(IOEventFlags device, JshI2CInfo *inf) {}

//void jshI2CWrite(IOEventFlags device, unsigned char address, int nBytes, const unsigned char *data, bool sendStop) {}

//void jshI2CRead(IOEventFlags device, unsigned char address, int nBytes, unsigned char *data, bool sendStop) {}

/// Enter simple sleep mode (can be woken up by interrupts). Returns true on success
bool jshSleep(JsSysTime timeUntilWake) {
  JsVarFloat t = jshGetMillisecondsFromTime(timeUntilWake);
  if (t>0x7FFFFFFF) t=0x7FFFFFFF;
  timeToSleep = (int)t;
  return false;
}

void jshUtilTimerDisable() {
}

void jshUtilTimerReschedule(JsSysTime period) {
}

void jshUtilTimerStart(JsSysTime period) {
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

/*
bool jshFlashGetPage(uint32_t addr, uint32_t *startAddr, uint32_t *pageSize) {
  return true;
}
JsVar *jshFlashGetFree() {
  JsVar *jsFreeFlash = jsvNewEmptyArray();
  return jsFreeFlash;
}
void jshFlashErasePage(uint32_t addr) {

}
void jshFlashRead(void *buf, uint32_t addr, uint32_t len) {
  return;
}
void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) {
  return;
}

// Just pass data through, since we can access flash at the same address we wrote it
size_t jshFlashGetMemMapAddress(size_t addr) {
  return 0;
}
*/

unsigned int jshSetSystemClock(JsVar *options) {
  return 0;
}

/// Perform a proper hard-reboot of the device
void jshReboot() {
  jsExceptionHere(JSET_ERROR, "Not implemented");
}
