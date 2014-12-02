/*
 * gpio.c
 *
 *  Created on: Dec 7, 2013
 *      Author: Nathan
 */

#include "template_all.h"

void ConfigLED0()
{
	EALLOW;
	CLEARLED0();
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 1; 		//disable pull up
	EDIS;
}

void ConfigLED1()
{
	EALLOW;
	CLEARLED1();
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1; 		//disable pull up
	EDIS;
}

/*
void Config12V()
{
	EALLOW;
	CLEAR12V();
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1; 		//disable pull up
	EDIS;
}
*/


void ConfigGPButton()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;          // input
	GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0; 		//enable pull up
	EDIS;
}
