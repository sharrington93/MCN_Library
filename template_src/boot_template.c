/*
 * Boot.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 *      Updated on Nov. 29, Julia
 *
 */



#include "boot_template.h"

// Internal Functions

#define BOOT_MODE_ADDR	(0x7FC)
#define BOOT_KEY_WORD1	(0x4142)
#define BOOT_KEY_WORD2	(0x4B53)
#define BOOT_KEY_WORD3	(0x5543)
#define BOOT_KEY_WORD4	(0x4B53)

void SetupBootload(void) {
	int * modeAddr = (int *) 0x7fc;

	*modeAddr++ = 0x4142;
	*modeAddr++ = 0x4b53;
	*modeAddr++ = 0x5543;
	*modeAddr++ = 0x4b53;
}
