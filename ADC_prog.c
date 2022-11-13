/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name:ADC_CONFIG.h
 *
 * Description: 
 *
 * Author: Ahmed Ali
 *
 *******************************************************************************/
/* Description: Program file for ADC Driver compatible with AVR ATmega32     */
/*****************************************************************************/

#include "STD_TYPES.h" 
#include "BIT_CALC.h" 
#include "ADC_interface.h" 
#include "ADC_priv.h" 
#include "ADC_config.h" 

/*pointer to the callback function which  which will run as ISR on ADC conversion complete*/
static void (*PVCallBack) (void) = NULL;

/*Static global Variable holding the Result of ADC which get in ISR on ADC conversion complete */
static u16 *ADC_APu8Result;

/*Static global array holding the refresh finish flag for each ADC group*/
static u8 ADC_Au8RefreshFlag[ADC_u8_NO_OF_GRPS];

/*Static global array holding the current channel index for each ADC group*/
static u8 ADC_Au8ChannelIndex[ADC_u8_NO_OF_GRPS];

/*Static global variable holding the current group number selected by Refresh function*/
static u8 ADC_u8GroupNumber;

/*Static global array of pointer to the base address of ADC array for each channel*/
static u16* ADC_Pu16UpdatedVal[ADC_u8_NO_OF_GRPS];

/*
 * Description: Function to initialize the ADC driver
 * Inputs: none
 * Output: void
 */
void ADC_vInit (void)
{
	#if (ADC_u8_INIT_STATE == ADC_u8_ENABLE)
	{
		switch (ADC_u8_PRESCALER)
		{
			case ADC_u8_PRESCALER_OVER_4:
			{

				SET_BIT(ADC_ADCSRA,ADPS1);
				break;
			}
			case ADC_u8_PRESCALER_OVER_8:
			{
				SET_BIT(ADC_ADCSRA,ADPS0);
				SET_BIT(ADC_ADCSRA,ADPS1);
				break;
			}
			case ADC_u8_PRESCALER_OVER_16:
			{
				SET_BIT(ADC_ADCSRA,ADPS2);
				break;
			}
			case ADC_u8_PRESCALER_OVER_32:
			{
				SET_BIT(ADC_ADCSRA,ADPS0);
				SET_BIT(ADC_ADCSRA,ADPS2);
				break;
			}
			case ADC_u8_PRESCALER_OVER_64:
			{
				SET_BIT(ADC_ADCSRA,ADPS0);
				SET_BIT(ADC_ADCSRA,ADPS1);
				break;
			}
			case ADC_u8_PRESCALER_OVER_128:
			{

				SET_BIT(ADC_ADCSRA,ADPS1);
				SET_BIT(ADC_ADCSRA,ADPS2);
				break;
			}
		}

		if (ADC_u8_VREF_SELECT == ADC_u8_AVCC)
		{
			SET_BIT(ADC_ADMUX,REFS0);
		}
		else if (ADC_u8_VREF_SELECT == ADC_u8_INTERNAL_VREF)
		{
			SET_BIT(ADC_ADMUX,REFS0);
			SET_BIT(ADC_ADMUX,REFS1);
		}

		if (ADC_u8_ADJACEMENT == ADC_u8_LEFT_ADJ)
			SET_BIT(ADC_ADMUX,ADLAR);

		if (ADC_u8_INIT_INT == ADC_u8_ENABLE)
			SET_BIT(ADC_ADCSRA,ADIE);

		if (ADC_u8_AUTO_TRIGGER_STATE == ADC_u8_ENABLE)
		{
			SET_BIT(ADC_ADCSRA,ADATE);
			
			switch (ADC_u8_AUTO_TRIGGER_TYPE)
			{
				case ADC_u8_ANALOG_COMP:
				{
					SET_BIT(ADC_SFIOR,ADPS0);
					break;
				}
				case ADC_u8_EXT_INT0:
				{
					SET_BIT(ADC_SFIOR,ADPS1);
					break;
				}
				case ADC_u8_COMP_MATCH_TMR0:
				{
					SET_BIT(ADC_SFIOR,ADPS0);
					SET_BIT(ADC_SFIOR,ADPS1);
					break;
				}
				case ADC_u8_OVERFLOW_TMR0:
				{
					SET_BIT(ADC_SFIOR,ADPS2);
					break;
				}
				case ADC_u8_COMP_MATCH_TMR1B:
				{
					SET_BIT(ADC_SFIOR,ADPS0);
					SET_BIT(ADC_SFIOR,ADPS2);
					break;
				}
				case ADC_u8_OVERFLOW_TMR1:
				{
					SET_BIT(ADC_SFIOR,ADPS1);
					SET_BIT(ADC_SFIOR,ADPS2);
					break;
				}
				case ADC_u8_TMR1_CAP_EVENT:
				{
					SET_BIT(ADC_SFIOR,ADPS0);
					SET_BIT(ADC_SFIOR,ADPS1);
					SET_BIT(ADC_SFIOR,ADPS2);
					break;
				}
			}
		}

		SET_BIT(ADC_ADCSRA,ADEN);
	}
	#endif
	return;
}


u8 ADC_u8GetADCSync (u8 Copy_u8ChannelNb,u16* Copy_Pu16ADCValue)
{
	/*Local Variable holding the error state*/
	 u8 Local_u8Error = ERROR_OK;
	 u16 TimeOutCounter = 0;
	 
	if (Copy_u8ChannelNb < ADC_u8_MAX_NO_ADC_CHANNELS && Copy_Pu16ADCValue != NULL)
	{
		/* Clear the ADC Mux selection Bits */
		ADC_ADMUX & = ~( ADMUXMask << 0 );
		
		/*Select the Mux selection bit according to the required ADC channel*/
		ADC_ADMUX |= ADC_Au8MuxPinSelect[Copy_u8ChannelNb];

		/*Start ADC conversion*/
		SET_BIT(ADC_ADCSRA,ADSC);
        /* ADC Enable */
		CLEAR_BIT(ADC_ADCSRA,ADIE);
		while(GET_BIT(ADC_ADCSRA,ADIF) == 0 && TimeOutCounter < maxOutTime)
		{
			TimeOutCounter++;
		}   	/*wait until the conversion ends */
		if(TimeOutCounter >= maxOutTime )
		{
			Local_u8Error = ERROR_NOK;
			
		}
		SET_BIT(ADC_ADCSRA,ADIF);  /* The End of ADC conversion flag is cleared by writing one on it */
		SET_BIT(ADC_ADCSRA,ADIE);

		if (ADC_u8_RESOLUTION == ADC_u8_8BITS)
			*Copy_Pu16ADCValue = ADC_ADCH;
		else
			*Copy_Pu16ADCValue = ADC_ADCVAL_10BITS;
	}
	
	else
	{
		Local_u8Error = ERROR_NOK;
	}
	
	
	return Local_u8Error;
}

u8 ADC_u8GetADCAsyn (u8 Copy_u8ChannelNb,u16* Copy_Pu16ADCValue,void(*Copy_PVCallBack)(void));
{
	/*Local Variable holding the error state*/
	u8 Local_u8Error = ERROR_OK;
	
	if (Copy_u8ChannelNb < ADC_u8_MAX_NO_ADC_CHANNELS && Copy_pu16ADCValue != NULL &&ADC_u8_INIT_INT == ADC_u8_ENABLE)
	{
		ADC_APu8Result=&Copy_Pu16ADCValue;
		
		PVCallBack = Copy_PVCallBack;
		/* Clear the ADC Mux selection Bits */
		ADC_ADMUX &= ~(ADMUXMask<<0);
		
		/*Select the Mux selection bit according to the required ADC channel*/
		ADC_ADMUX |= ADC_Au8MuxPinSelect[Copy_u8ChannelNb];

		/*Start ADC conversion*/
		SET_BIT(ADC_ADCSRA,ADSC);
        /* ADC Enable */
		CLEAR_BIT(ADC_ADCSRA,ADIE);

	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}
	
	
	return Local_u8Error;
}

/*
 * Description: Function to start the process of ADC conversion from multiple number of ADC channels
 * It is an Asynchronous function which initiates a series of ISRs
 * Inputs: the group number
 * Output: void
 */
u8 ADC_u8ADCRefresh (u8 Copy_u8GroupNumber)
{
	/*Local Variable holding the error state*/
	u8 Local_u8Error = ERROR_OK;

	if (Copy_u8GroupNumber < ADC_u8_NO_OF_GRPS && ADC_Au8RefreshFlag[Copy_u8GroupNumber] == 0)
	{
		if (ADC_Groups[Copy_u8GroupNumber].SwOrHwTrigger == ADC_u8_SW_TRIGGER ||
				(ADC_Groups[Copy_u8GroupNumber].SwOrHwTrigger == ADC_u8_HW_TRIGGER && ADC_u8_AUTO_TRIGGER_TYPE == ADC_u8_FREE_RUNNING))
		{
			ADC_u8GroupNumber = Copy_u8GroupNumber;
			ADC_Au8RefreshFlag[Copy_u8GroupNumber] = 1;

		    /*Select the Mux selection bit according to the Starting channel in the chain*/
		    ADC_ADMUX |= ADC_Au8MuxPinSelect[ADC_Groups[Copy_u8GroupNumber].ChannelNumber[0]];

		    /*Start ADC conversion*/
		    SET_BIT(ADC_ADCSRA,ADSC);
		}
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}
	return Local_u8Error;
}

/*
 * Description: Function to get the ADC of a certain ADC channel in case of applying ADC Chaining process
 * on multiple number of ADC channels
 * Inputs: The ADC group number + the required ADC channel in this group + the Pointer to the variable supposed to hold the ADC variable
 * Output: Error state
 */
u8 ADC_u8GetADCValue (u8 Copy_u8GroupNumber,u8 Copy_u8ChannelNbInChain,u16* Copy_Pu16ADCValue)
{
	//Local Variable holding the error state
	u8 Local_u8Error = ERROR_OK;
	
	if (Copy_u8GroupNumber < ADC_u8_NO_OF_GRPS &&
		Copy_u8ChannelNbInChain < ADC_Groups[Copy_u8GroupNumber].NoOfChannels &&
		Copy_Pu16ADCValue != NULL)
	{
		*Copy_Pu16ADCValue = *(ADC_Pu16UpdatedVal[ADC_u8GroupNumber]+Copy_u8ChannelNbInChain);
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}
	/*Function return*/
	return Local_u8Error;
}



void __vector_16 (void)
{
	u8 Local_u8ChannelIndex;
	u8 Local_u8CurrentChannel;

	if (PVCallBack != NULL)
	{
		if (ADC_u8_INT_MODE == ADC_u8_ADC_CHAINING)
		{
			Local_u8ChannelIndex = *(ADC_Groups[ADC_u8GroupNumber].Index);
			if (ADC_u8_RESOLUTION == ADC_u8_8BITS)
				ADC_Groups[ADC_u8GroupNumber].ADC_Values[Local_u8ChannelIndex] = ADC_ADCH;
			else
				ADC_Groups[ADC_u8GroupNumber].ADC_Values[Local_u8ChannelIndex] = ADC_ADCVAL_10BITS;
			(*(ADC_Groups[ADC_u8GroupNumber].Index))++;

			/* Checking if the index a reached the chain limit */
			if (*(ADC_Groups[ADC_u8GroupNumber].Index) == ADC_Groups[ADC_u8GroupNumber].NoOfChannels)
			{

				/* After finishing the conversion of each ADC channel in the chain, now it's time for the pointer
				 * to point to the array of the ADc chain */
				ADC_Pu16UpdatedVal[ADC_u8GroupNumber] = ADC_Groups[ADC_u8GroupNumber].ADC_Values;
				*(ADC_Groups[ADC_u8GroupNumber].Index) = 0;
				ADC_Au8RefreshFlag[ADC_u8GroupNumber] = 0;
				PVCallBack();
			}
			/* if there is remaining channels in the chain haven't been filled yet */
			else
			{
				ADC_Au8ChannelIndex[ADC_u8GroupNumber]++;
				Local_u8CurrentChannel = ADC_Au8ChannelIndex[ADC_u8GroupNumber];
				/* Clear the ADC Mux selection Bits */
				ADC_ADMUX &= ~(ADMUXMask<<0);
				/*Select the Mux selection bit according to the required ADC channel for the assigned recent group*/
				ADC_ADMUX |= ADC_Au8MuxPinSelect[ADC_Groups[ADC_u8GroupNumber].ChannelNumber[Local_u8CurrentChannel]];
				/*Start ADC conversion*/
				SET_BIT(ADC_ADCSRA,ADSC);
			}
		}
		else
			PVCallBack();
	}
}
