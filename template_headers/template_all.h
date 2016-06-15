/*
 * all.h
 *
 *  Created on: Oct 29, 2013
 *      Author: Nathan
 */

#ifndef ALL_H_
#define ALL_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "stopwatch_template.h"
#include "sys_op.h"
#include "sys_data.h"
#include "Init_template.h"
#include "can_template.h"
#include "SensorCov_template.h"
#include "boot_template.h"
#include "PowerDown_template.h"
#include "common_template.h"
#include "clock_template.h"
#include <stdlib.h>
#include "adc_template.h"
#include "gpio_template.h"
#include "EMA_template.h"

extern sys_ops_struct sys_ops;
extern sys_data_struct sys_data;

#define CPU_FREQ_MHZ	60

#endif /* ALL_H_ */
