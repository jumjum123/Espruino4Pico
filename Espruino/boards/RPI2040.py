#!/bin/false
# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# ----------------------------------------------------------------------------------------
# This file contains information for a specific board - the available pins, and where LEDs,
# Buttons, and other in-built peripherals are. It is used to build documentation as well
# as various source and header files for Espruino.
# ----------------------------------------------------------------------------------------

import pinutils;
info = {
 'name'                     : "RPI2040",
 'espruino_page_link'       : 'RPI2040',
 'default_console'          : "EV_USBSERIAL",
 'default_console_baudrate' : "115200",
 'variables'                : 2500, # JSVAR_MALLOC is defined below - so this can vary depending on what is initialised
 'binary_name'              : 'espruino.uf2',
 'build' : {
   'optimizeflags' : '',
   'libraries' : [	 
   ],
   'makefile' : [
   ]
 }
};

chip = {
  'part'    : "RPI2040",
  'family'  : "RPI2040",
  'package' : "",
  'ram'     : 256,
  'flash'   : 0,
  'speed'   : 48,
  'usart'   : 1,
  'spi'     : 1,
  'i2c'     : 1,
  'adc'     : 0,
  'dac'     : 0,
  'saved_code' : {
    'address' : 0x8000000,
    'page_size' : 4096,
    'pages' : 256, # Entire 4MB of external flash
    'flash_available' : 256 # lots - this is fake
  },
};
devices = {
  'USB' : {}
};

# left-right, or top-bottom order
board_RPI2040 = {
   'top' : [],
   'left' : [],
   'right' : []
};
board_RPI2040["_css"] = """
#board {
  width: 550px;
  height: 272px;
  top: 300px;
  left : 100px;
  background-image: url(img/PICO_R1_3.png);
}
""";

boards = [ board_RPI2040 ];

def get_pins():

  pins = pinutils.generate_pins(0,22) # General Purpose I/O Pins.
  pins.extend(pinutils.generate_pins(25,28))
  
  return pins
