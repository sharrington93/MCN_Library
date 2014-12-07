

#ifndef ADC_H_
#define ADC_H_

/**
 * ADC initialization statements for a MCN
 */
void adcinit();


typedef struct
{
	unsigned int size;
	unsigned int index;
	int outputValue;
	int *previousValues;
} DSPfilter;


/**
 * DSP filter initialization.
 */
void initDSPfilter(DSPfilter filter, unsigned int frequency);

/**
 * Update DPS output variables.
 */
void updateDSPfilter(DSPfilter filter, unsigned int newValue);

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

#define ONEK					1000
#define TENK					10000


#endif /* 12V_H_ */

