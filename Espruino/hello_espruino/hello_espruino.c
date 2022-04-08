/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

int main() {
	char c;
    stdio_init_all();
	sleep_ms(20000);
	printf("hello Juergen\n");
    while (true) {
		printf("soso\n");
        sleep_ms(1000);
    }
    return 0;
}
