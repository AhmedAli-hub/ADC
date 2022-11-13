/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name:ADC_CONFIG.h
 *
 * Description: Configuration file for ADC Driver compatible with AVR ATmega32 
 *
 * Author: Ahmed Ali
 *
 *******************************************************************************/


#ifndef ADC_CONFIG_H 
#define ADC_CONFIG_H 

/****************************************************************/
/*                 ADC Initial configurations                   */
/****************************************************************/
/*
Macro to define the initial ADC state
Range:   ADC_u8_ENABLE
	   	 ADC_u8_DISABLE
*/
#define ADC_u8_INIT_STATE      ADC_u8_ENABLE

/*
Macro to select the ADC resolution
Range:     ADC_u8_8BITS
	   	   ADC_u8_10BITS
 */
#define ADC_u8_RESOLUTION      ADC_u8_8BITS

/*
Macros for the prescaler of ADC
Range:   ADC_u8_PRESCALER_OVER_2
	   	 ADC_u8_PRESCALER_OVER_4
	   	 ADC_u8_PRESCALER_OVER_8
		 ADC_u8_PRESCALER_OVER_16
		 ADC_u8_PRESCALER_OVER_32
		 ADC_u8_PRESCALER_OVER_64
		 ADC_u8_PRESCALER_OVER_128
*/
#define ADC_u8_PRESCALER	  ADC_u8_PRESCALER_OVER_2

/*
Macros for the select the Vref of the ADC peripheral
Range:   ADC_u8_AREF
	   	 ADC_u8_AVCC
	   	 ADC_u8_INTERNAL_VREF
*/
#define ADC_u8_VREF_SELECT	   ADC_u8_AVCC

/*
Macro to select the Adjacement
Range:   ADC_u8_LEFT_ADJ
	   	 ADC_u8_RIGHT_ADJ
*/
#define ADC_u8_ADJACEMENT       ADC_u8_LEFT_ADJ

/*
Macro to select the ADC interrupt initial state
Range:   ADC_u8_ENABLE
	   	 ADC_u8_DISABLE
*/
#define ADC_u8_INIT_INT	    ADC_u8_ENABLE

/*
Macro to select the ISR running mode whether it will run to measure a sequence of
ADC channels or run a user defined ISR
Range:		    ADC_u8_ADC_CHAINING
			    ADC_u8_USER_DEF_ISR
*/
#define ADC_u8_INT_MODE			ADC_u8_ADC_CHAINING

/*
Macro to select the ADC auto trigger state
Range:   ADC_u8_ENABLE
	   	   ADC_u8_DISABLE
*/
#define ADC_u8_AUTO_TRIGGER_STATE   ADC_u8_DISABLE

/*
Macro to select the auto trigger source
Range:   ADC_u8_FREE_RUNNING
	   	 ADC_u8_ANALOG_COMP
	   	 ADC_u8_EXT_INT0
	   	 ADC_u8_COMP_MATCH_TMR0
	   	 ADC_u8_OVERFLOW_TMR0
	   	 ADC_u8_COMP_MATCH_TMR1B
	   	 ADC_u8_OVERFLOW_TMR1
	   	 ADC_u8_TMR1_CAP_EVENT
*/
#define ADC_u8_AUTO_TRIGGER_TYPE     ADC_u8_FREE_RUNNING

/****************************************************************/
/*            ADC Channels Initial configurations               */
/****************************************************************/
/* Macro to specify the number of ADC channel group needed in the system */
#define ADC_u8_NO_OF_GRPS                1

/* Macro to specify the number of channels for ADC group 1 */
#define ADC_u8_GRP1_CH_NO                3

/* Definition of a ADC group structure which should be filled with:
 * (1) The triggering type of the group ADc channels (ADC_u8_SW_TRIGGER/ADC_u8_HW_TRIGGER)
 * (2) The number of ADC channel required for the group
 * (3) A pointer to the Group array filled with the channels needed to be assigned for the group
 * (4) Array which is supposed to hold the coming ADC value for each channel in the group
 * (5) Pointer to an index variable needed in the conversion chaining process (should be defined and initialized by zero at first)
 */
typedef struct
{
	u8 SwOrHwTrigger;
	u8 NoOfChannels;
	u8* ChannelNumber;
	u16* ADC_Values;
	u8* Index;
}ADC_GroupStruct_t;

u8  Grp1_Arr[ADC_u8_GRP1_CH_NO] = {ADC_u8_CHANNEL0,ADC_u8_CHANNEL1,ADC_u8_CHANNEL2};
u16 Grp1_ADCValue[ADC_u8_GRP1_CH_NO];
u8  Grp1_Index = 0;



ADC_GroupStruct_t ADC_Groups[ADC_u8_NO_OF_GRPS]= {{ADC_u8_SW_TRIGGER,ADC_u8_GRP1_CH_NO,Grp1_Arr,Grp1_ADCValue,&Grp1_Index}};

#endif /* ADC_CONFIG_H */ 

