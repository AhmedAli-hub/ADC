/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name:ADC_CONFIG.h
 *
 * Description: Private file for ADC Driver  compatible with AVR ATmega32  
 *
 * Author: Ahmed Ali
 *
 *******************************************************************************/


/*Preprocessor Guard*/
#ifndef ADC_PRIV_H 
#define ADC_PRIV_H 

/*Macro to define the maximum number of the Multiplexed ADC channels*/
#define ADC_u8_MAX_NO_ADC_CHANNELS   (u8)8

/*Macro to define the possible state of the ADC peripheral or the ADC interrupt*/
#define ADC_u8_ENABLE                0
#define ADC_u8_DISABLE               1

/*Macros to define the possible resolutions for the ADC value representation*/
#define ADC_u8_8BITS                 (u8)0
#define ADC_u8_10BITS				 (u8)1

/*Macros to define the available ADC prescaler*/
#define ADC_u8_PRESCALER_OVER_2      (u8)0
#define ADC_u8_PRESCALER_OVER_4      (u8)1
#define ADC_u8_PRESCALER_OVER_8      (u8)2
#define ADC_u8_PRESCALER_OVER_16     (u8)3
#define ADC_u8_PRESCALER_OVER_32     (u8)4
#define ADC_u8_PRESCALER_OVER_64     (u8)5
#define ADC_u8_PRESCALER_OVER_128    (u8)6

/*Macro to define the possible Voltage Reference Selections for ADC*/
#define ADC_u8_AREF                  (u8)0
#define ADC_u8_AVCC                  (u8)1
#define ADC_u8_INTERNAL_VREF         (u8)2

/*Macros to define the possible adjustment of the ADC result*/
#define ADC_u8_LEFT_ADJ                     (u8)0
#define ADC_u8_RIGHT_ADJ                    (u8)1

/* Macro to define the auto trigger sources */
#define      ADC_u8_FREE_RUNNING            (u8)0
#define	   	 ADC_u8_ANALOG_COMP             (u8)1
#define	   	 ADC_u8_EXT_INT0                (u8)2
#define	   	 ADC_u8_COMP_MATCH_TMR0         (u8)3
#define	   	 ADC_u8_OVERFLOW_TMR0           (u8)4
#define	   	 ADC_u8_COMP_MATCH_TMR1B        (u8)5
#define	   	 ADC_u8_OVERFLOW_TMR1           (u8)6
#define	   	 ADC_u8_TMR1_CAP_EVENT          (u8)7


#define  ADC_u8_ADC_CHAINING                (u8)0
#define  ADC_u8_USER_DEF_ISR                (u8)1

/*Macros to define the availabe Multiplexed ADC channels*/
#define     ADC_u8_CHANNEL0             (u8)0
#define	   	ADC_u8_CHANNEL1             (u8)1
#define	   	ADC_u8_CHANNEL2             (u8)2
#define		ADC_u8_CHANNEL3             (u8)3
#define		ADC_u8_CHANNEL4             (u8)4
#define		ADC_u8_CHANNEL5             (u8)5
#define		ADC_u8_CHANNEL6             (u8)6
#define		ADC_u8_CHANNEL7             (u8)7

/* Macros to define the triggering type for the ADC channel */
#define ADC_u8_SW_TRIGGER               (u8)0
#define ADC_u8_HW_TRIGGER               (u8)1

/*Array holding the Analog Channel and Gain Selection Bits should be assigned
to ADMUX according to each ADC channel*/
u8 ADC_Au8MuxPinSelect[ADC_u8_MAX_NO_ADC_CHANNELS] = {0,1,2,3,4,5,6,7};

/*The ISR of ADC Conversion Complete*/
void __vector_16 (void) __attribute__((signal));
/*==========================================================*/
/*                  ADC Registers                         */
/*==========================================================*/
#define ADC_ADMUX               ((Register*) 0x27) -> ByteAccess
#define ADC_ADCSRA              ((Register*) 0x26) -> ByteAccess
#define ADC_ADCH                ((Register*) 0x25) -> ByteAccess
#define ADC_ADCL                ((Register*) 0x24) -> ByteAccess
#define ADC_ADCVAL_10BITS       *((u16*) 0x24)
#define ADC_SFIOR                ((Register*) 0x50) -> ByteAccess

/*Defining bits in ADCSRA register*/
#define ADPS0	    (u8)0
#define ADPS1	    (u8)1
#define ADPS2	    (u8)2
#define ADIE	    (u8)3
#define ADIF        (u8)4
#define ADATE	    (u8)5
#define ADSC	    (u8)6
#define ADEN	    (u8)7

/*Defining bits in ADMUX register*/
#define MUX0		(u8)0
#define MUX1		(u8)1
#define MUX2		(u8)2
#define MUX3		(u8)3
#define MUX4		(u8)4
#define ADLAR		(u8)5
#define REFS0		(u8)6
#define REFS1		(u8)7

/*Defining bits in ADMUX register*/
#define ADTS0		(u8)5
#define ADTS1       (u8)6
#define ADTS2       (u8)7

/* Define max of Time Out For ADC */
#define maxOutTime     1000
/* Define Clear Mask for ADC_ADMUX */
#define ADMUXMask     31

#endif /* ADC_PRIV_H */ 
