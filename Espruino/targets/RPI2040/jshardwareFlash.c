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
#include "jshardwareFlash.h"
#include "jshardwareTools.h"
#define UNUSED(x) (void)(x)

#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/irq.h"

#define FLASH_TARGET_OFFSET (1024 * 1024)
#define FLASH_MAX 0x10200000
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
void addFlashArea(JsVar *jsFreeFlash, uint32_t addr, uint32_t length) {
  JsVar *jsArea = jsvNewObject();
  if (!jsArea) return;
  jsvObjectSetChildAndUnLock(jsArea, "addr", jsvNewFromInteger((JsVarInt)addr));
  jsvObjectSetChildAndUnLock(jsArea, "length", jsvNewFromInteger((JsVarInt)length));
  jsvArrayPushAndUnLock(jsFreeFlash, jsArea);
}
JsVar *jshFlashGetFree() {
  JsVar *jsFreeFlash = jsvNewEmptyArray();
  addFlashArea(jsFreeFlash, 0x10100000, 0x100000);
  return jsFreeFlash;
}
void jshFlashErasePage(uint32_t addr) {
  uint32_t mask;
  uint32_t flashAddr = addr & 0x1fffff;
  mask = getIrqMask();
  irq_set_mask_enabled(mask, false);
  flash_range_erase(flashAddr,4096);
  irq_set_mask_enabled(mask, true);
}
void jshFlashRead(void *buf, uint32_t addr, uint32_t len) {
  int i;
  uint32_t flashAddr = addr & 0xfffff;
  for(i = 0; i < len; i++){
	*(uint8_t *)buf++ = flash_target_contents[flashAddr + i];
  }
}
void jshFlashWritePage(unsigned char *dptr,uint32_t addr,uint32_t len){
  int i;
  uint8_t writeBuf[FLASH_PAGE_SIZE];
  int writeBufPnt = addr  & 0x000000ff;
  jshFlashRead(writeBuf,addr & 0xffffff00,FLASH_PAGE_SIZE);
  for(i = 0; i < len; i++){
	writeBuf[writeBufPnt++] = *dptr++;
  }
  writeFlashPage(writeBuf,addr);
}
void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) {
  //int i;
  int iLoop;
  unsigned char *dptr = (unsigned char *)buf;
  //uint8_t writeBuf[FLASH_PAGE_SIZE];
  //int writeBufPnt = addr & 0x000000ff;
  while(((addr & 0x000000ff) + len) > 256){
	iLoop = 256 - addr & 0x000000ff;
	jshFlashWritePage(dptr,addr,iLoop);
	//iLoop = 256 - writeBufPnt;
    //jshFlashRead(writeBuf,addr & 0xffffff00,FLASH_PAGE_SIZE);		
    //for(i = 0; i < iLoop; i++){
    //  writeBuf[writeBufPnt++] = *dptr++;
    //writeFlashPage(writeBuf,addr,len);
	len -= iLoop;
	addr += iLoop;
	dptr += iLoop;
  }
  if(len > 0) jshFlashWritePage(dptr,addr,len);
}
void writeFlashPage(uint8_t *buf,uint32_t addr){
  uint32_t mask;
  uint32_t flashAddr = addr & 0xfffff;
  mask = getIrqMask();
  irq_set_mask_enabled(mask,false);
  flash_range_program(FLASH_TARGET_OFFSET + (flashAddr & 0xffffff00),buf,FLASH_PAGE_SIZE);
  irq_set_mask_enabled(mask,true);
}

// Just pass data through, since we can access flash at the same address we wrote it
size_t jshFlashGetMemMapAddress(size_t addr) {
  return 0;
}
