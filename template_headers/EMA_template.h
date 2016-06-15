/*
 * EMA.h
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

#ifndef EMA_FILTER
#define EMA_FILTER

#include "template_all.h"
#include "IQmathLib.h"

typedef struct filter filter;

struct filter
{
	_iq _input;
	int16 _sampleRate;
	int32 _lastSampleTime;
	_iq _alpha;
	_iq _filteredOutput;
	filter *_nextFilter;
};

//This function initializes the variables listed above
//Takes in 2 parameters, one being the structure while the other being the sample rate
//The alpha value is calculated using this sample rate

void EMA_Filter_Init(filter *f, Uint32 sampleRate, Uint32 clockPeriod);

//This function updates the last input throttle and time elapsed to calculate the new throttle output

void EMA_Filter_Update(void);

//This function sets the input variable in the filter structure

float EMA_Filter_NewInput(filter *f, float input);

//This function returns the throttle output value

float EMA_Filter_GetFilteredOutput(filter *f);

#endif
