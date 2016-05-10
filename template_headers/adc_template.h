

#ifndef ADC_H_
#define ADC_H_

/**
 * ADC initialization statements for a MCN
 */
void adcinit();


typedef struct
{
	Uint32 alpha;
	Uint32 outputValue;
	float filtered_value;
	char isOn;
} DSPfilter;


/**
 * DSP filter initialization.
 */
void initDSPfilter(DSPfilter *filter, Uint32 alpha);

/**
 * Update DPS output variables.
 */
void updateDSPfilter(DSPfilter *filter, Uint32 newValue);
void updateAllFilters();

#define ACQPS_VALUE				20
#define ADC_RATIO				10

#define A0RESULT				A0filter.filtered_value
#define A1RESULT				A1filter.filtered_value
#define A2RESULT				A2filter.filtered_value
#define A3RESULT				A3filter.filtered_value
#define A4RESULT				A4filter.filtered_value
#define A5RESULT				A5filter.filtered_value
#define A6RESULT				A6filter.filtered_value
#define A7RESULT				A7filter.filtered_value
#define B0RESULT				B0filter.filtered_value
#define B1RESULT				B1filter.filtered_value
#define B2RESULT				B2filter.filtered_value
#define B3RESULT				B3filter.filtered_value
#define B4RESULT				B4filter.filtered_value
#define B5RESULT				B5filter.filtered_value
#define B6RESULT				B6filter.filtered_value
#define B7RESULT				B7filter.filtered_value

#define ONEK					1000.0
#define TENK					10000.0

#define PI						3.14159265358979323846

/*
 * alpha = (1.0 - exp(-2.0 * PI * (CANFrequency / samplingFrequency))) * 2^16;
 */
#define ALPHA_SYS				818

#endif /* 12V_H_ */

