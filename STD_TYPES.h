
/* Description: This header file is dedicated for defining fixed    */
/* size data types which are realable to be used                    */
/* Embedded System development.                                     */                               
/********************************************************************/

/*
This header file is dedicated for defining fixed size data types which are realable to be used
Embedded System development.
*/

#ifndef STD_TYPES
#define STD_TYPES

/* unsigned 8 bit type */
typedef unsigned char      u8   ;

/* signed 8 bit type */
typedef signed char        s8   ;

/* unsigned 16 bit type */
typedef unsigned short int u16  ;

/* signed 16 bit type */
typedef signed short int   s16  ;

/* unsigned 32 bit type */
typedef unsigned long int  u32  ;

/* signed 32 bit type */
typedef signed long int    s32  ;

/* floating type 32 bit */
typedef float              f32  ;

/* floating type 64 bit */
typedef double             f64  ;

/* Register 8 bit */
typedef union {
	struct
	{
		u8 Bit0 : 1;
		u8 Bit1 : 1;
		u8 Bit2 : 1;
		u8 Bit3 : 1;
		u8 Bit4 : 1;
		u8 Bit5 : 1;
		u8 Bit6 : 1;
		u8 Bit7 : 1;
	}BitAccess;
	u8 ByteAccess;
} Register;

/* Error status */
#define ERROR_NOK (u8)1
#define ERROR_OK  (u8)0

#define UNSIGNED_MIN 0

/* Macro for NULL */
#define NULL ((void*)0)

#endif
