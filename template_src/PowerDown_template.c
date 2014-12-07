/*
 * PowerDown_template.c
 *
 *  Created on: May 17, 2014
 *      Author: Sean
 */

#include "template_all.h"

extern DSPfilter A0filter;
extern DSPfilter A1filter;
extern DSPfilter A2filter;
extern DSPfilter A3filter;
extern DSPfilter A4filter;
extern DSPfilter A5filter;
extern DSPfilter B0filter;
extern DSPfilter B1filter;
extern DSPfilter B2filter;
extern DSPfilter B3filter;
extern DSPfilter B4filter;
extern DSPfilter B5filter;
extern DSPfilter B6filter;
extern DSPfilter B7filter;

void SystemPowerDown()
{
	while(isPowerOn() == 0) {}
	EALLOW;
	SysCtrlRegs.WDCR = 0x0028;               // Enable watchdog module
	SysCtrlRegs.WDKEY = 0x00;                // wrong key should restart
	SysCtrlRegs.WDKEY = 0x00;
	EDIS;

	// Free memory allocated for DSP filters
	free(A0filter.previousValues);
	free(A1filter.previousValues);
	free(A2filter.previousValues);
	free(A3filter.previousValues);
	free(A4filter.previousValues);
	free(A5filter.previousValues);
	free(B0filter.previousValues);
	free(B1filter.previousValues);
	free(B2filter.previousValues);
	free(B3filter.previousValues);
	free(B4filter.previousValues);
	free(B5filter.previousValues);
	free(B6filter.previousValues);
	free(B7filter.previousValues);

	while(1){}
}

char isPowerOn()
{
	return !Comp3Regs.COMPSTS.bit.COMPSTS; 	// 1 means cause interrupt = no power
}

void PowerDownISRSetup()
{
	InitComp3Gpio();

	EALLOW;
	AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;

	Comp3Regs.DACVAL.bit.DACVAL = (Uint16)(COMPVOLTAGE*1023.0)/(VDDA-VSSA);
	Comp3Regs.COMPCTL.bit.CMPINV = 1; //invert comp signal
	Comp3Regs.COMPCTL.bit.COMPDACEN = 1;

	EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP3OUT;
	EPwm1Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;
	EPwm1Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;
	EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_SYNC;
	EPwm1Regs.TZCLR.all = 0xFFFF;
	EPwm1Regs.TZEINT.bit.DCAEVT2 = 1;
	EPwm1Regs.TZCTL.bit.DCAEVT2 = TZ_NO_CHANGE;


	PieCtrlRegs.PIEIER2.bit.INTx1 = 1;

	IFR &= ~M_INT2;
	IER |= M_INT2;

	EDIS;
}

void StartPowerDownInt()
{
	EALLOW;
	EPwm1Regs.TZCLR.all = 0xFFFF;
	EDIS;
}

// INT2.1
__interrupt void EPWM1_TZINT_ISR(void)    // EPWM-1
{

	// To receive more interrupts from this PIE group, acknowledge this interrupt
	sys_ops.State = STATE_POWER_DOWN;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

}
