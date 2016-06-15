/*
 * EMA.c
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

//#include "../RC Headers/all.h"
#include "EMA_template.h"

static filter *currentFilter = NULL;
static filter *headFilter = NULL;

static int counter = 0;
static int16 mClockPeriod = 0;

static float testInput = 0;
static float test = 0;
static float testOutput = 0;

void EMA_Filter_Init(filter *f, Uint32 sampleRate, Uint32 clockPeriod)
{
	mClockPeriod = clockPeriod;
	f->_input = 0;
	f->_sampleRate = sampleRate;
	f->_lastSampleTime = 0;
	//alpha = (1.0 - exp(-2.0 * PI * (CANFrequency / samplingFrequency)))
	f->_alpha = _IQ(1.0) - _IQexp(_IQmpy(_IQ(-6.28), _IQdiv(_IQ(mClockPeriod), _IQ(sampleRate))));
	float alpha = _IQtoF(f->_alpha);

	f->_filteredOutput = 0;

	if (headFilter == NULL){

		headFilter = f;
		headFilter->_nextFilter = NULL;
	}
	else {
		currentFilter = headFilter;
		while(currentFilter->_nextFilter != NULL)
		{
			currentFilter = currentFilter->_nextFilter;
		}
		currentFilter->_nextFilter = f;
	}
}

void EMA_Filter_Update(void)
{
	/*
	counter++;
	int32 currentTime = counter * mClockPeriod;

	currentFilter = headFilter;
	while(currentFilter != NULL)
	{
		if( currentTime - currentFilter->_lastSampleTime >= currentFilter->_sampleRate)
		{

			currentFilter->_lastSampleTime = currentTime;

			_iq newScale = _IQmpy(currentFilter->_alpha, currentFilter->_input);
			_iq oldScale = _IQmpy((_IQ(1.0) - currentFilter->_alpha), currentFilter->_filteredOutput);

			currentFilter->_filteredOutput = newScale + oldScale;
		}
		currentFilter = currentFilter->_nextFilter;
	}
	*/
	currentFilter = headFilter;
	while(currentFilter != NULL)
	{
		_iq newScale = _IQmpy(currentFilter->_alpha, currentFilter->_input);
		_iq oldScale = _IQmpy((_IQ(1.0) - currentFilter->_alpha), currentFilter->_filteredOutput);
		currentFilter->_filteredOutput = newScale + oldScale;

		currentFilter = currentFilter->_nextFilter;
	}
}

float EMA_Filter_NewInput(filter *f, float input)
{
	return f->_input = _IQ(input);
	//return testInput = input;
}

float EMA_Filter_GetFilteredOutput(filter *f)
{
	return _IQtoF(f->_filteredOutput);
	//return testOutput;
}


