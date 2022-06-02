#include "jshardware.h"
#include "jswrap_onewire.h"
#include "pico/stdlib.h"

JsVarInt NO_INLINE OneWireRead(Pin pin, int bits) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  JsVarInt result = 0;
  JsVarInt mask = 1;
  while (bits-- > 0) {
    gpio_set_dir(pin,GPIO_OUT);
	gpio_put(pin,0);
	sleep_us(8);
	gpio_set_dir(pin,GPIO_IN);
	sleep_us(2);
	if(gpio_get(pin)) result = result | mask;
	sleep_us(60);
	mask = mask << 1;
  }
  return result;
}
writeBitOneWire(Pin pin,bool b){
  int delay1,delay2;
  if(b){delay1 = 6; delay2 = 64;}
  else {delay1 = 60; delay2 = 10; }
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT);
  jshPinSetValue(pin,0);
  sleep_us(delay1);
  jshPinSetState(pin, JSHPINSTATE_GPIO_IN);
  sleep_us(delay2);
}
void NO_INLINE OneWireWrite(Pin pin, int bits, unsigned long long data) {
  unsigned long long mask = 1;
  while (bits-- > 0) {
    writeBitOneWire(pin,(data & mask) != 0);
    mask = mask << 1;
  }
}

