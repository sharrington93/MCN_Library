

#ifndef ADC_H_
#define ADC_H_

/**
 * ADC initialization statements for a MCN
 */
void adcinit();

/**
 * Reads ADC output until the ADC interrupt triggers.
 */
void readADC();

typedef struct {
	int size;
	int index;
	int outputValue;
	int *previousValues;
} DSPfilter;

DSPfilter A0filter;
DSPfilter A1filter;
DSPfilter A2filter;
DSPfilter A3filter;
DSPfilter A4filter;
DSPfilter A5filter;
DSPfilter B0filter;
DSPfilter B1filter;
DSPfilter B2filter;
DSPfilter B3filter;
DSPfilter B4filter;
DSPfilter B5filter;
DSPfilter B6filter;
DSPfilter B7filter;

/**
 * DSP filter initialization.
 */
void initDSPfilter(DSPfilter filter, int frequency);

/**
 * Update DPS output variables.
 */
void updateDSPfilter(DSPfilter filter);

#define ACQPS_VALUE				20
#define ADC_RATIO				10

#define A0RESULT				A0filter.outputValue
#define A1RESULT				A1filter.outputValue
#define A2RESULT				A2filter.outputValue
#define A3RESULT				A3filter.outputValue
#define A4RESULT				A4filter.outputValue
#define A5RESULT				A5filter.outputValue
#define B0RESULT				B0filter.outputValue
#define B1RESULT				B1filter.outputValue
#define B2RESULT				B2filter.outputValue
#define B3RESULT				B3filter.outputValue
#define B4RESULT				B4filter.outputValue
#define B5RESULT				B5filter.outputValue
#define B6RESULT				B6filter.outputValue
#define B7RESULT				B7filter.outputValue


#endif /* 12V_H_ */

