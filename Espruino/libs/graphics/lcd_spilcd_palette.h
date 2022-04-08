/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2019 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Colour Palettes when using LCDs where we're trying to cut down on memory
 * for the offscreen buffer
 * ----------------------------------------------------------------------------
 */

#if LCD_BPP==4
#define LCD_PALETTED
// 16 color 12 bit Web-safe palette
const uint16_t SPILCD_PALETTE[16] = { 0x0,0x444,0x888,0xbbb,0x963,0x630,0x60,0xa0,0x9f,0xc,0x309,0xf09,0xd00,0xf60,0xff0,0xfff };
#endif

#if LCD_BPP==8
#define LCD_PALETTED
// 256 color 12 bit Web-safe palette
const uint16_t SPILCD_PALETTE[256] = { 0x0,0x3,0x6,0x9,0xc,0xf,0x30,0x33,0x36,0x39,0x3c,0x3f,0x60,0x63,0x66,0x69,0x6c,0x6f,0x90,0x93,0x96,0x99,0x9c,0x9f,0xc0,0xc3,0xc6,0xc9,0xcc,0xcf,0xf0,0xf3,0xf6,0xf9,0xfc,0xff,0x300,0x303,0x306,0x309,0x30c,0x30f,0x330,0x333,0x336,0x339,0x33c,0x33f,0x360,0x363,0x366,0x369,0x36c,0x36f,0x390,0x393,0x396,0x399,0x39c,0x39f,0x3c0,0x3c3,0x3c6,0x3c9,0x3cc,0x3cf,0x3f0,0x3f3,0x3f6,0x3f9,0x3fc,0x3ff,0x600,0x603,0x606,0x609,0x60c,0x60f,0x630,0x633,0x636,0x639,0x63c,0x63f,0x660,0x663,0x666,0x669,0x66c,0x66f,0x690,0x693,0x696,0x699,0x69c,0x69f,0x6c0,0x6c3,0x6c6,0x6c9,0x6cc,0x6cf,0x6f0,0x6f3,0x6f6,0x6f9,0x6fc,0x6ff,0x900,0x903,0x906,0x909,0x90c,0x90f,0x930,0x933,0x936,0x939,0x93c,0x93f,0x960,0x963,0x966,0x969,0x96c,0x96f,0x990,0x993,0x996,0x999,0x99c,0x99f,0x9c0,0x9c3,0x9c6,0x9c9,0x9cc,0x9cf,0x9f0,0x9f3,0x9f6,0x9f9,0x9fc,0x9ff,0xc00,0xc03,0xc06,0xc09,0xc0c,0xc0f,0xc30,0xc33,0xc36,0xc39,0xc3c,0xc3f,0xc60,0xc63,0xc66,0xc69,0xc6c,0xc6f,0xc90,0xc93,0xc96,0xc99,0xc9c,0xc9f,0xcc0,0xcc3,0xcc6,0xcc9,0xccc,0xccf,0xcf0,0xcf3,0xcf6,0xcf9,0xcfc,0xcff,0xf00,0xf03,0xf06,0xf09,0xf0c,0xf0f,0xf30,0xf33,0xf36,0xf39,0xf3c,0xf3f,0xf60,0xf63,0xf66,0xf69,0xf6c,0xf6f,0xf90,0xf93,0xf96,0xf99,0xf9c,0xf9f,0xfc0,0xfc3,0xfc6,0xfc9,0xfcc,0xfcf,0xff0,0xff3,0xff6,0xff9,0xffc,0xfff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfff };
#endif

/*
To generate these palettes, use the following JS code:

// 16 color
a = [
  0x000000, 0x444444, 0x888888, 0xBBBBBB,
  0x996633, 0x663300, 0x006600, 0x00aa00,
  0x0099ff, 0x0000cc, 0x330099, 0xff0099,
  0xdd0000, 0xff6600, 0xffff00, 0xffffff
];
// 256 color
a=[0x000000,0x000033,0x000066,0x000099,0x0000cc,0x0000ff,0x003300,0x003333,0x003366,0x003399,0x0033cc,0x0033ff,0x006600,0x006633,0x006666,0x006699,0x0066cc,0x0066ff,0x009900,0x009933,0x009966,0x009999,0x0099cc,0x0099ff,0x00cc00,0x00cc33,0x00cc66,0x00cc99,0x00cccc,0x00ccff,0x00ff00,0x00ff33,0x00ff66,0x00ff99,0x00ffcc,0x00ffff,0x330000,0x330033,0x330066,0x330099,0x3300cc,0x3300ff,0x333300,0x333333,0x333366,0x333399,0x3333cc,0x3333ff,0x336600,0x336633,0x336666,0x336699,0x3366cc,0x3366ff,0x339900,0x339933,0x339966,0x339999,0x3399cc,0x3399ff,0x33cc00,0x33cc33,0x33cc66,0x33cc99,0x33cccc,0x33ccff,0x33ff00,0x33ff33,0x33ff66,0x33ff99,0x33ffcc,0x33ffff,0x660000,0x660033,0x660066,0x660099,0x6600cc,0x6600ff,0x663300,0x663333,0x663366,0x663399,0x6633cc,0x6633ff,0x666600,0x666633,0x666666,0x666699,0x6666cc,0x6666ff,0x669900,0x669933,0x669966,0x669999,0x6699cc,0x6699ff,0x66cc00,0x66cc33,0x66cc66,0x66cc99,0x66cccc,0x66ccff,0x66ff00,0x66ff33,0x66ff66,0x66ff99,0x66ffcc,0x66ffff,0x990000,0x990033,0x990066,0x990099,0x9900cc,0x9900ff,0x993300,0x993333,0x993366,0x993399,0x9933cc,0x9933ff,0x996600,0x996633,0x996666,0x996699,0x9966cc,0x9966ff,0x999900,0x999933,0x999966,0x999999,0x9999cc,0x9999ff,0x99cc00,0x99cc33,0x99cc66,0x99cc99,0x99cccc,0x99ccff,0x99ff00,0x99ff33,0x99ff66,0x99ff99,0x99ffcc,0x99ffff,0xcc0000,0xcc0033,0xcc0066,0xcc0099,0xcc00cc,0xcc00ff,0xcc3300,0xcc3333,0xcc3366,0xcc3399,0xcc33cc,0xcc33ff,0xcc6600,0xcc6633,0xcc6666,0xcc6699,0xcc66cc,0xcc66ff,0xcc9900,0xcc9933,0xcc9966,0xcc9999,0xcc99cc,0xcc99ff,0xcccc00,0xcccc33,0xcccc66,0xcccc99,0xcccccc,0xccccff,0xccff00,0xccff33,0xccff66,0xccff99,0xccffcc,0xccffff,0xff0000,0xff0033,0xff0066,0xff0099,0xff00cc,0xff00ff,0xff3300,0xff3333,0xff3366,0xff3399,0xff33cc,0xff33ff,0xff6600,0xff6633,0xff6666,0xff6699,0xff66cc,0xff66ff,0xff9900,0xff9933,0xff9966,0xff9999,0xff99cc,0xff99ff,0xffcc00,0xffcc33,0xffcc66,0xffcc99,0xffcccc,0xffccff,0xffff00,0xffff33,0xffff66,0xffff99,0xffffcc,0xffffff];
while(a.length<255)a.push(0);
a[255]=0xFFFFFF;
// 12 bit
print(a.map(function(rgb) {
  r = rgb>>16;
  g = (rgb>>8)&0xFF;
  b = rgb&0xFF;
  return ((r&0xF0)<<4) | (g&0xF0) | (b>>4);
}).map(x=>"0x"+x.toString(16)).join(","))
// 16 bit
 print(a.map(function(rgb) {
  r = rgb>>16;
  g = (rgb>>8)&0xFF;
  b = rgb&0xFF;
  return ((r&0xF8)<<8) | ((g&0xFc)<<3) | (b>>3);
}).map(x=>"0x"+x.toString(16)).join(","))
 */