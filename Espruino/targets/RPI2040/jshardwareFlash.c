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
#include "jshardwareTools.h"
#define UNUSED(x) (void)(x)

#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/irq.h"

#define FLASH_TARGET_OFFSET (1024 * 1024)
#define FLASH_MAX (1024*1024) //1MB
#define FLASH_PAGE_SHIFT 12  //Shift is faster than multiply
#define FLASH_PAGE ((uint32_t)1<<FLASH_PAGE_SHIFT)  //4KB

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void FlashReset(){
   UNUSED(1); 
	
}

bool jshFlashGetPage(uint32_t addr, uint32_t *startAddr, uint32_t *pageSize) {
  if (addr >= FLASH_MAX) return false;
  *startAddr = addr & ~(FLASH_PAGE-1);
  *pageSize = FLASH_PAGE;
  return true;
}
JsVar *jshFlashGetFree() {
  JsVar *jsFreeFlash = jsvNewEmptyArray();
  return jsFreeFlash;
}
void jshFlashErasePage(uint32_t addr) {
  uint32_t mask;
  uint32_t flashAddr = FLASH_TARGET_OFFSET + addr;
  mask = getIrqMask();
  irq_set_mask_enabled(mask, false);
  flash_range_erase(flashAddr,4096);
  irq_set_mask_enabled(mask, true);
}
void jshFlashRead(void *buf, uint32_t addr, uint32_t len) {
  int i;
  for(i = 0; i < len; i++){
	*(uint8_t *)buf = flash_target_contents[addr + i];
  }
}
void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) {
  int i;uint32_t mask;
  for(i = 0; i < 16; i++){
	mask = getIrqMask();
	irq_set_mask_enabled(mask,false);
    flash_range_program(FLASH_TARGET_OFFSET, addr + i * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
	irq_set_mask_enabled(mask,true);
  }
}

// Just pass data through, since we can access flash at the same address we wrote it
size_t jshFlashGetMemMapAddress(size_t addr) {
  return 0;
}
