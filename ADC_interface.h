/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name:ADC_interface.h
 *
 * Description: Interface file for ADC Driver compatible with AVR ATmega32
 *
 * Author: Ahmed Ali
 *
 *******************************************************************************/


#ifndef ADC_INTERFACE_H 
#define ADC_INTERFACE_H 

/*Macro to define the availabe Multiplexed ADC channels*/
#define ADC_u8ADC0_SEL     (u8)0
#define ADC_u8ADC1_SEL     (u8)1
#define ADC_u8ADC2_SEL     (u8)2
#define ADC_u8ADC3_SEL     (u8)3
#define ADC_u8ADC4_SEL     (u8)4
#define ADC_u8ADC5_SEL     (u8)5
#define ADC_u8ADC6_SEL     (u8)6
#define ADC_u8ADC7_SEL     (u8)7


void ADC_vInit (void);
 
u8 ADC_u8GetADCSync (u8 Copy_u8ChannelNb,u16* Copy_Pu16ADCValue);

u8 ADC_u8GetADCAsyn (u8 Copy_u8ChannelNb,u16* Copy_Pu16ADCValue,void(*Copy_PVCallBack)(void));

/*
 * Description: Function to start the process of ADC conversion from multiple number of ADC channels
 * Inputs: the group number
 * Output: Error state
 */
u8 ADC_vADCRefresh (u8 Copy_u8GroupNumber);

/*
 * Description: Function to get the ADC of a certain ADC channel in case of applying ADC Chaining process
 * on multiple number of ADC channels
 * Inputs: The ADC group number + the required ADC channel in this group + the Pointer to the variable supposed to hold the ADC variable
 * Output: Error state
 */
u8 ADC_u8GetADCValue (u8 Copy_u8GroupNumber,u8 Copy_u8ChannelNbInChain,u16* Copy_Pu16ADCValue);



#endif /* ADC_INTERFACE_H */ 
