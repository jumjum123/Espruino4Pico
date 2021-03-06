/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2022 Juergen Marsch <juergenmarsch@googlemail.com> for RPI2040 port
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * RPI2040 USB Console specific functions
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "jshardwareTools.h"
 
uint32_t getIrqMask(){
  uint32_t r;
  int i;
  r = 0;
  for(i = 0;i < 16; i++){
	if(irq_is_enabled(i)) {r += (1 << i);}	  
  }
  return r;
}

// for testing
void rpiTest(){
  printf("testit\n");
}
void print_buf(const uint8_t *buf, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    printf("%02x", buf[i]);
    if (i % 16 == 15)
      printf("\n");
    else
      printf(" ");
  }
  printf("\n");
}
char bool2char(bool v){
  if(v) return 'T';
  else return 'F';
}