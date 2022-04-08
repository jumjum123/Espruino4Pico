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
#include "jshardwareFlash.h"

#include "pico/stdlib.h"
#include "hardware/flash.h"

#define FLASH_TARGET_OFFSET (1024 * 1024)
const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

bool jshFlashGetPage(uint32_t addr, uint32_t *startAddr, uint32_t *pageSize) {
  return true;
}
JsVar *jshFlashGetFree() {
  JsVar *jsFreeFlash = jsvNewEmptyArray();
  return jsFreeFlash;
}
void jshFlashErasePage(uint32_t addr) {
  flash_range_erase(flash_target_contents + addr,4096);
}
void jshFlashRead(void *buf, uint32_t addr, uint32_t len) {
  int i;
  for(i = 0; i < len; i++){
	*(uint8_t *)buf = flash_target_contents[addr + i];
  }
}
void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) {
  int i;
  for(i = 0; i < 16; i++){
    flash_range_program(FLASH_TARGET_OFFSET, addr + i * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
  }
}

// Just pass data through, since we can access flash at the same address we wrote it
size_t jshFlashGetMemMapAddress(size_t addr) {
  return 0;
}
