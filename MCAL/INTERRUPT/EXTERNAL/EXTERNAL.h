/*
 * EXTERNAL_INTERRUPT.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef MCAL_INTERRUPT_EXTERNAL_EXTERNAL_H_
#define MCAL_INTERRUPT_EXTERNAL_EXTERNAL_H_

#define GICR		(*(volatile u8_t*)0x5B)
#define MCUCR		(*(volatile u8_t*)0x55)
#define MCUCSR		(*(volatile u8_t*)0x54)

/* GICR */
/*
 * NOTE:
 * 		"_FLAG" are added to the names of the flags, since INT0, INT1 and INT2 are names for pins in LIB/PIN_CONFIG.h. So, no conflicts occur.
 *
 */
#define INT2_FLAG	5
#define INT0_FLAG	6
#define INT1_FLAG	7

/* MCUCR */
#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3

/* MCUCSR */
#define ISC2		6

typedef enum{
	INT0_INT1_LOW_LEVEL,
	INT0_INT1_ANY_CHANGE,
	INT0_INT1_FALLING_EDGE,
	INT0_INT1_RISING_EDGE
} INT0_or_INT1_sense_control;

typedef enum{
	INT2_FALLING_EDGE,
	INT2_RISING_EDGE
} INT2_sense_control;


/********************************\
*********** Functions ************
\********************************/

void INTERRUPT_EXTERNAL_INT0_EnableInterrupt(void);
void INTERRUPT_EXTERNAL_INT0_DisableInterrupt(void);
void INTERRUPT_EXTERNAL_INT1_EnableInterrupt(void);
void INTERRUPT_EXTERNAL_INT1_DisableInterrupt(void);
void INTERRUPT_EXTERNAL_INT2_EnableInterrupt(void);
void INTERRUPT_EXTERNAL_INT2_DisableInterrupt(void);
void INTERRUPT_EXTERNAL_INT0_ControlSense(INT0_or_INT1_sense_control event);
void INTERRUPT_EXTERNAL_INT1_ControlSense(INT0_or_INT1_sense_control event);
void INTERRUPT_EXTERNAL_INT2_ControlSense(INT2_sense_control mode);
void INTERRUPT_EXTERNAL_INT0_SetCallBack(void (*local_function_pointer) (void));
void INTERRUPT_EXTERNAL_INT1_SetCallBack(void (*local_function_pointer) (void));
void INTERRUPT_EXTERNAL_INT2_SetCallBack(void (*local_function_pointer) (void));

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	INTERRUPT_EXTERNAL_INT0_EnableInterrupt(void):
 * 				@brief	Enable external interrupt on pin INT0.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT0_DisableInterrupt(void):
 * 				@brief	Disable external interrupt on pin INT0.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT1_EnableInterrupt(void):
 * 				@brief	Enable external interrupt on pin INT1.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT1_DisableInterrupt(void):
 * 				@brief	Disable external interrupt on pin INT1.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT2_EnableInterrupt(void):
 * 				@brief	Enable external interrupt on pin INT2.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT2_DisableInterrupt(void):
 * 				@brief	Disable external interrupt on pin INT2.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT0_ControlSense(INT0_or_INT1_sense_control event):
 * 				@brief	Select what event on INT0 to cause interrupt request.
 *
 *				@param mode: Selected event to cause interrupt request (Low Level, Any Change, Falling Edge, or Rising Edge).
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT1_ControlSense(INT0_or_INT1_sense_control event):
 * 				@brief	Select what event on INT1 to cause interrupt request.
 *
 *				@param mode: Selected event to cause interrupt request (Low Level, Any Change, Falling Edge, or Rising Edge).
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT2_ControlSense(INT2_sense_control event):
 * 				@brief	Select what event on INT2 to cause interrupt request.
 *
 *				@param mode: Selected event to cause interrupt request (Falling Edge or Rising Edge).
 *
 *	____________________________________________________________________________________
 *
 * 	INTERRUPT_EXTERNAL_INT0_SetCallBack(void (*local_function_pointer) (void));
 *				@brief Set callback function for external interrupt request 0.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on interrupt.
 *
 *	____________________________________________________________________________________
 *
 * 	INTERRUPT_EXTERNAL_INT1_SetCallBack(void (*local_function_pointer) (void));
 *				@brief Set callback function for external interrupt request 1.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	INTERRUPT_EXTERNAL_INT2_SetCallBack(void (*local_function_pointer) (void));
 *				@brief Set callback function for external interrupt request 2.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on interrupt.
 *
 *	____________________________________________________________________________________

 */

#endif /* MCAL_INTERRUPT_EXTERNAL_EXTERNAL_H_ */
