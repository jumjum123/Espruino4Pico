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
#ifndef JSHARDWARETOOLS_H_
#define JSHARDWARETOOLS_H_

uint32_t getIrqMask();
void print_buf(const uint8_t *buf, size_t len);

void rpiTest();

#endif /* JSHARDWARETOOLS_H_ */