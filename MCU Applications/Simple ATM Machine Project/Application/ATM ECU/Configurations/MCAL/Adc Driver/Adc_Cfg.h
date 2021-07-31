/*
 * Adc_Cfg.h
 *
 * Created: 24-Jul-21 10:26:08 PM
 *  Author: Megz
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/* CONSTANTS */

/* user set the number of channles used in the project */

#define ADC_USED_CHANNELS_NUM   1

#define ADC0_ID				0
#define ADC1_ID				1
#define ADC2_ID				2
#define ADC3_ID				3
#define ADC4_ID				4
#define ADC5_ID				5
#define ADC6_ID				6
#define ADC7_ID				7

/* if External_Vref is chosen, you can't use internal or Adc Vcc for other channles */
#define External_Vref		0
#define AdcVcc_Vref			1
#define InternalVref		2
 
 /* enter Vref value in volts */
#define Vref				(float32_t)5

/* choose whether you want to disable auto trigger or choose trigger source */
#define DisableAutoTrigger	0

#define TriggerSource_ExternalInterrupt0	1
#define TriggerSource_AnalogComparator		2
#define TriggerSource_Timer0CompareMatch	3
#define TriggerSource_Timer0Overflow		4
#define TriggerSource_Timer1CompareMatch	5
#define TriggerSource_Timer1Overflow0		6
#define TriggerSource_Timer1CaptureEvent	7


#define AutoTriggerState			DisableAutoTrigger
#endif /* ADC_CFG_H_ */