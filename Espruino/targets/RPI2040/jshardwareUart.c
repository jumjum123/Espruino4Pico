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
#include "jshardwareUart.h"
#include "jsinteractive.h"

#include "hardware/irq.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UNUSED(x) (void)(x)
 
void UartReset(){
  UNUSED(1); 
}
void on_uart0_rx(){
  while(uart_is_readable(uart0)){
	char ch = uart_getc(uart0);
    jshPushIOCharEvents(EV_SERIAL1, &ch,1);
  }
}
void on_uart1_rx(){
  while(uart_is_readable(uart1)){
	char ch = uart_getc(uart1);
    jshPushIOCharEvents(EV_SERIAL2, &ch,1);
  }
}
void jshUSARTSetup(IOEventFlags device, JshUSARTInfo *inf) {
  uint uartID;
  if (inf->errorHandling) {
    jsExceptionHere(JSET_ERROR, "ESP32 Espruino builds can't handle framing/parity errors (errors:true)");
    return;
  }
  switch(device){
	case EV_SERIAL1: 
	  uartID = uart0;
	  if(inf->pinTX == 0xff) inf->pinTX = 0;
	  if(inf->pinRX == 0xff) inf->pinRX = 1;
	  break;
	case EV_SERIAL2:
	  uartID = uart1;
	  if(inf->pinTX == 0xff) inf->pinTX = 4;
	  if(inf->pinRX == 0xff) inf->pinRX = 5;
	  break;
	default: break;
  }
  uart_init(uartID, 2400);
  gpio_set_function(inf->pinTX, GPIO_FUNC_UART);
  gpio_set_function(inf->pinRX, GPIO_FUNC_UART);
  int __unused actual = uart_set_baudrate(uartID, inf->baudRate);
  uart_set_hw_flow(uartID, false, false);
  uart_set_format(uartID, inf->bytesize, inf->stopbits, UART_PARITY_NONE);
  uart_set_fifo_enabled(uartID, false);
  switch(device){
	case EV_SERIAL1:
	   irq_set_exclusive_handler(UART0_IRQ, on_uart0_rx);
	   irq_set_enabled(UART0_IRQ, true);
	   break;
	case EV_SERIAL2:
	   irq_set_exclusive_handler(UART1_IRQ, on_uart1_rx);
	   irq_set_enabled(UART1_IRQ, true);
	   break;
  }
  uart_set_irq_enables(uartID, true,false);
}