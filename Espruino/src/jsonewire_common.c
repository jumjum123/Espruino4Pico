#include "jshardware.h"
#include "jswrap_onewire.h"

/** Reset one-wire, return true if a device was present */
__attribute__((weak)) bool NO_INLINE OneWireReset(Pin pin) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  //jshInterruptOff();
  jshPinSetValue(pin, 0);
  jshDelayMicroseconds(500);
  jshPinSetValue(pin, 1);
  jshDelayMicroseconds(80);
  bool hasDevice = !jshPinGetValue(pin);
  //jshInterruptOn();
  jshDelayMicroseconds(420);
  return hasDevice;
}

/** Write 'bits' bits, and return what was read (to read, you must send all 1s) */
__attribute__((weak)) JsVarInt NO_INLINE OneWireRead(Pin pin, int bits) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  JsVarInt result = 0;
  JsVarInt mask = 1;
  while (bits-- > 0) {
    jshInterruptOff();
    jshPinSetValue(pin, 0);
    jshDelayMicroseconds(3);
    jshPinSetValue(pin, 1);
    jshDelayMicroseconds(10); // leave time to let it rise
    if (jshPinGetValue(pin))
      result = result | mask;
    jshInterruptOn();
    jshDelayMicroseconds(53);
    mask = mask << 1;
  }
  return result;
}

/** Write 'bits' bits, and return what was read (to read, you must send all 1s) */
__attribute__((weak)) void NO_INLINE OneWireWrite(Pin pin, int bits, unsigned long long data) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  unsigned long long mask = 1;
  while (bits-- > 0) {
    if (data & mask) { // short pulse
      jshInterruptOff();
      jshPinSetValue(pin, 0);
      jshDelayMicroseconds(10);
      jshPinSetValue(pin, 1);
      jshInterruptOn();
      jshDelayMicroseconds(55);
    } else {  // long pulse
      jshInterruptOff();
      jshPinSetValue(pin, 0);
      jshDelayMicroseconds(65);
      jshPinSetValue(pin, 1);
      jshInterruptOn();
      jshDelayMicroseconds(5);
    }
    mask = mask << 1;
  }
}
