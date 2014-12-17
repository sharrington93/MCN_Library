/*
 * gpio.c
 *
 *  Created on: Dec 7, 2013
 *      Author: Nathan
 */

#include "template_all.h"

DSPfilter GPIO19filter;
DSPfilter GPIO26filter;

float GPIO19_PERIOD, GPIO26_PERIOD;
unsigned int GPIO19_COUNTER, GPIO26_COUNTER;
stopwatch_struct* GPIO19_watch, GPIO26_watch;

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

void ConfigGPIOSensor(float CAN_Frequency, float Sample_Frequency, int pin, Uint16 GPAPUD, Uint16 xint_polarity)
{
	EALLOW;

	// Determine alpha and store

	if(pin == 19)
	{
		GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;	//GPIO
		GpioCtrlRegs.GPADIR.bit.GPIO19 = 0; 	//input
		GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0;	//Synch to SYSCLKOUT only
		GpioCtrlRegs.GPAPUD.bit.GPIO19 = GPAPUD;		//enable pull up

		//Setup interrupt
		IER |= M_INT35;
		PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
		GpioIntRegs.GPIOXINT1SEL = 19;
		XIntruptRegs.XINT1CR.bit.POLARITY = xint_polarity;
		XIntruptRegs.XINT1CR.bit.ENABLE = 1;
		initDSPfilter(GPIO19filter, ONEK, TENK);

		GPIO19_COUNTER = 0;
		GPIO19_PERIOD = 1.0/Sample_Frequency;
		GPIO19_watch = StartStopWatch((1.0/Sample_Frequency)*500000);
	}
	else if(pin == 26)
	{
		GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;	//GPIO
		GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;		//input
		GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;	//Synch to SYSCLKOUT only
		GpioCtrlRegs.GPAPUD.bit.GPIO26 = GPAPUD;

		//Setup interrupt
		IER |= M_INT36;
		PieCtrlRegs.PIEIER1.bit.INTx5 = 1;
		GpioIntRegs.GPIOXINT2SEL = 26;
		XIntruptRegs.XINT2CR.bit.POLARITY = xint_polarity;
		XIntruptRegs.XINT2CR.bit.ENABLE = 1;
		initDSPfilter(GPIO26filter, ONEK, TENK);

		GPIO26_COUNTER = 0;
		GPIO26_PERIOD = 1.0/Sample_Frequency;
		GPIO26_watch = StartStopWatch((1.0/Sample_Frequency)*500000); // change freq to period, convert to us, divide by 2
	}
	else  // Only two valid GPIO sensors on RW-3 revision
	{
		//Stop program.. you did something wrong..
		__asm ("      ESTOP0");
		for(;;);
	}
	EDIS;
}

// INT1.3 - Reserved
__interrupt void XINT1_ISR(void)
{
	// Insert ISR Code here
	if (isStopWatchComplete(GPIO19_watch) == 1)
	{

	}
	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

// INT1.5
__interrupt void  XINT2_ISR(void)
{
	// Insert ISR Code here
	if(isStopWatchComplete(GPIO26_watch) == 1)
	{

		//GPIO26_COUNTER / GPIO26_PERIOD;
	}
	else
	{
		GPIO26_COUNTER++;
	}
	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;



}
