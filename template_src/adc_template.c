#include "template_all.h"
#include <math.h>

int datatest[] = {1, 5, 7, 2, 6, 7, 8, 2, 2, 7, 8, 3, 7, 3, 7, 3, 15, 6};

DSPfilter A0filter;
DSPfilter A1filter;
DSPfilter A2filter;
DSPfilter A3filter;
DSPfilter A4filter;
DSPfilter A5filter;
DSPfilter A6filter;
DSPfilter A7filter;

extern DSPfilter GPIO19filter;
extern DSPfilter GPIO26filter;

DSPfilter B0filter;
DSPfilter B1filter;
DSPfilter B2filter;
DSPfilter B3filter;
DSPfilter B4filter;
DSPfilter B5filter;
DSPfilter B6filter;
DSPfilter B7filter;


extern Uint32 GPIO19_FREQ, GPIO26_FREQ;
extern Uint32 GPIO19_COUNTER, GPIO26_COUNTER;

int count = 0;

Uint64 one_fixed_point = ((Uint32)1 << 16);

void adcinit()
{
	InitAdc();  // Init the ADC

	EALLOW;

	// Comment out other unwanted lines.
	GpioCtrlRegs.AIODIR.all = 0x0000;

	GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;    // Configure AIO2 for A2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO4 = 2;    // Configure AIO4 for A4 (analog input) operation
	//GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;    // Configure AIO6 for A6 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // Configure AIO10 for B2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   // Configure AIO12 for B4 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   // Configure AIO14 for B6 (analog input) operation


	//solve first conversion problem:
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;
	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;

	AdcRegs.ADCSOC0CTL.bit.CHSEL  = 0; // SOC0 TO A0
	AdcRegs.ADCSOC1CTL.bit.CHSEL  = 1; // SOC1 TO A1
	AdcRegs.ADCSOC2CTL.bit.CHSEL  = 2; // SOC2 TO A2
	AdcRegs.ADCSOC3CTL.bit.CHSEL  = 3; // SOC3 TO A3
	AdcRegs.ADCSOC4CTL.bit.CHSEL  = 4; // SOC4 TO A4
	AdcRegs.ADCSOC5CTL.bit.CHSEL  = 5; // SOC5 TO A5
	AdcRegs.ADCSOC6CTL.bit.CHSEL  = 6; // SOC6 TO A6
	AdcRegs.ADCSOC7CTL.bit.CHSEL  = 7; // SOC7 TO A7

	AdcRegs.ADCSOC8CTL.bit.CHSEL  = 8; // SOC8 TO B0
	AdcRegs.ADCSOC9CTL.bit.CHSEL  = 9; // SOC9 TO B1
	AdcRegs.ADCSOC10CTL.bit.CHSEL  = 10; // SOC10 TO B2
	AdcRegs.ADCSOC11CTL.bit.CHSEL  = 11; // SOC11 TO B3
	AdcRegs.ADCSOC12CTL.bit.CHSEL  = 12; // SOC12 TO B4
	AdcRegs.ADCSOC13CTL.bit.CHSEL  = 13; // SOC13 TO B5
	AdcRegs.ADCSOC14CTL.bit.CHSEL  = 14; // SOC14 TO B6
	AdcRegs.ADCSOC15CTL.bit.CHSEL  = 15; // SOC15 TO B7

	AdcRegs.ADCSOC0CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC0 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC1CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC1 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC2CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC2 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC3CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC3 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC4CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC4 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC5CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC5 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC6CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC6 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC7CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC7 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC8CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC8 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC9CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC9 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC10CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC10 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC11CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC11 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC12CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC12 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC13CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC13 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC14CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC14 acquisition period to DEFINED PERIOD
	AdcRegs.ADCSOC15CTL.bit.ACQPS  = ACQPS_VALUE; //Set SOC15 acquisition period to DEFINED PERIOD

	AdcRegs.INTSEL1N2.bit.INT1SEL = 15; //Connect ADCINT1 to SOC15 (last conversion)
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1; //ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1E  =  1; //Enable ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT = 0; //Disable ADCINT1 Continuous mode

	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 7;	//set SOC0  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 7;	//set SOC1  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 7;	//set SOC2  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL 	= 7;	//set SOC3  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL 	= 7;	//set SOC4  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC5CTL.bit.TRIGSEL 	= 7;	//set SOC5  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL 	= 7;	//set SOC6  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC7CTL.bit.TRIGSEL 	= 7;	//set SOC7  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL 	= 7;	//set SOC8  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL 	= 7;	//set SOC9  start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 7;	//set SOC10 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 7;	//set SOC11 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC12CTL.bit.TRIGSEL = 7;	//set SOC12 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC13CTL.bit.TRIGSEL = 7;	//set SOC13 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC14CTL.bit.TRIGSEL = 7;	//set SOC14 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...
	AdcRegs.ADCSOC15CTL.bit.TRIGSEL = 7;	//set SOC15 start trigger on EPWM2A, due to round-robin SOC0 converts first then SOC1, then SOC2, etc...

	AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      //Select internal reference mode
	AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;     //Select VREFLO internal connection on B5
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80;    //Apply artificial offset (+80) to account for a negative offset that may reside in the ADC core

	// Assumes ePWM2 clock is already enabled in InitSysCtrl();
	EPwm2Regs.ETSEL.bit.SOCAEN	= 1;		// Enable SOC on A group
	EPwm2Regs.ETSEL.bit.SOCASEL	= 4;		// Select SOC from CPMA on upcount
	EPwm2Regs.ETPS.bit.SOCAPRD 	= 1;		// Generate pulse on 1st event

	/*
	EPwm2Regs.ETSEL.bit.INTEN = 1;			// Generate PWM2 Interrupt
	EPwm2Regs.ETSEL.bit.INTSEL = 4;			// Toggle interrupt from CPMA on upcount
	EPwm2Regs.ETPS.bit.INTPRD = 1;			// Toggle interrupt on 1st event
	*/

	EPwm2Regs.CMPA.half.CMPA 	= 0x0BB7;	// Set compare A value
	EPwm2Regs.TBPRD 			= 0x0BB7;	// Set period for ePWM2
	EPwm2Regs.TBCTL.bit.CTRMODE	= 0;		// count up and start
	//EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;

	//PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	PieCtrlRegs.PIEIER10.bit.INTx1 = 1;

	//IER |= M_INT1;
	IER |= M_INT3;
	IER |= M_INT10;
	EDIS;
}

/*
 * alpha = (1.0 - exp(-2.0 * PI * (CANFrequency / samplingFrequency))) * 2^16;
 */
void initDSPfilter(DSPfilter *filter, Uint32 alpha)
{
	filter->alpha = alpha;
	filter->outputValue = 0;
	filter->isOn = 0;
}

void updateDSPfilter(DSPfilter *filter, Uint32 newValue)
{
	if (!filter->isOn) {
		filter->outputValue = newValue;
	} else {
		filter->outputValue =  ((filter->alpha * newValue) + (((one_fixed_point - filter->alpha) * filter->outputValue) >> 16));
		filter->filtered_value = filter->outputValue >> 16;
	}
}

#pragma CODE_SECTION (updateAllFilters, "ramfuncs")

void updateAllFilters()
{
		A0filter.outputValue =  ((A0filter.alpha * AdcResult.ADCRESULT0) + (((one_fixed_point - A0filter.alpha) * A0filter.outputValue) >> 16));
		A0filter.filtered_value = A0filter.outputValue >> 16;

		A1filter.outputValue =  ((A1filter.alpha * AdcResult.ADCRESULT1) + (((one_fixed_point - A1filter.alpha) * A1filter.outputValue) >> 16));
		A1filter.filtered_value = A1filter.outputValue >> 16;

		A2filter.outputValue =  ((A2filter.alpha * AdcResult.ADCRESULT2) + (((one_fixed_point - A2filter.alpha) * A2filter.outputValue) >> 16));
		A2filter.filtered_value = A2filter.outputValue >> 16;

		A3filter.outputValue =  ((A3filter.alpha * AdcResult.ADCRESULT3) + (((one_fixed_point - A3filter.alpha) * A3filter.outputValue) >> 16));
		A3filter.filtered_value = A3filter.outputValue >> 16;

		A4filter.outputValue =  ((A4filter.alpha * AdcResult.ADCRESULT4) + (((one_fixed_point - A4filter.alpha) * A4filter.outputValue) >> 16));
		A4filter.filtered_value = A4filter.outputValue >> 16;

		A5filter.outputValue =  ((A5filter.alpha * AdcResult.ADCRESULT5) + (((one_fixed_point - A5filter.alpha) * A5filter.outputValue) >> 16));
		A5filter.filtered_value = A5filter.outputValue >> 16;

		A6filter.outputValue =  ((A6filter.alpha * AdcResult.ADCRESULT6) + (((one_fixed_point - A6filter.alpha) * A6filter.outputValue) >> 16));
		A6filter.filtered_value = A6filter.outputValue >> 16;

		A7filter.outputValue =  ((A7filter.alpha * AdcResult.ADCRESULT7) + (((one_fixed_point - A7filter.alpha) * A7filter.outputValue) >> 16));
		A7filter.filtered_value = A7filter.outputValue >> 16;

		B0filter.outputValue =  ((B0filter.alpha * AdcResult.ADCRESULT8) + (((one_fixed_point - B0filter.alpha) * B0filter.outputValue) >> 16));
		B0filter.filtered_value = B0filter.outputValue >> 16;

		B1filter.outputValue =  ((B1filter.alpha * AdcResult.ADCRESULT9) + (((one_fixed_point - B1filter.alpha) * B1filter.outputValue) >> 16));
		B1filter.filtered_value = B1filter.outputValue >> 16;

		B2filter.outputValue =  ((B2filter.alpha * AdcResult.ADCRESULT10) + (((one_fixed_point - B2filter.alpha) * B2filter.outputValue) >> 16));
		B2filter.filtered_value = B2filter.outputValue >> 16;

		B3filter.outputValue =  ((B3filter.alpha * AdcResult.ADCRESULT11) + (((one_fixed_point - B3filter.alpha) * B3filter.outputValue) >> 16));
		B3filter.filtered_value = B3filter.outputValue >> 16;

		B4filter.outputValue =  ((B4filter.alpha * AdcResult.ADCRESULT12) + (((one_fixed_point - B4filter.alpha) * B4filter.outputValue) >> 16));
		B4filter.filtered_value = B4filter.outputValue >> 16;

		B5filter.outputValue =  ((B5filter.alpha * AdcResult.ADCRESULT13) + (((one_fixed_point - B5filter.alpha) * B5filter.outputValue) >> 16));
		B5filter.filtered_value = B5filter.outputValue >> 16;

		B6filter.outputValue =  ((B6filter.alpha * AdcResult.ADCRESULT14) + (((one_fixed_point - B6filter.alpha) * B6filter.outputValue) >> 16));
		B6filter.filtered_value = B6filter.outputValue >> 16;

		B7filter.outputValue =  ((B7filter.alpha * AdcResult.ADCRESULT15) + (((one_fixed_point - B7filter.alpha) * B7filter.outputValue) >> 16));
		B7filter.filtered_value = B7filter.outputValue >> 16;

		if(count >= 100)
		{

			GPIO19filter.outputValue = ((GPIO19filter.alpha * GPIO19_COUNTER) + (((one_fixed_point - GPIO19filter.alpha) * GPIO19filter.outputValue) >> 16));
			GPIO19filter.filtered_value = (float)((GPIO19filter.outputValue  * GPIO19_FREQ) >> 16)/100.0;
			GPIO19_COUNTER = 0;

			GPIO26filter.outputValue = ((GPIO26filter.alpha * GPIO26_COUNTER) + (((one_fixed_point - GPIO26filter.alpha) * GPIO26filter.outputValue) >> 16));
			GPIO26filter.filtered_value = (float)((GPIO26filter.outputValue * GPIO26_FREQ) >> 16)/100.0; //Sample Freq / 100
			GPIO26_COUNTER = 0;
			count = 0;
		}
		else
		{
			count++;
		}

}

// INT1.1
__interrupt void ADCINT1_ISR(void)   // ADC  (Can also be ISR for INT10.1 when enabled)
{
	// Insert ISR Code here
	EALLOW;
	AdcRegs.ADCOFFTRIM.bit.OFFTRIM = AdcRegs.ADCOFFTRIM.bit.OFFTRIM - AdcResult.ADCRESULT13;  //Set offtrim register with new value (i.e remove artical offset (+80) and create a two's compliment of the offset error)
	EDIS;

	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

	EINT;
	// Update DSP filters
	updateAllFilters();
	EMA_Filter_Update();

	DINT;
}
