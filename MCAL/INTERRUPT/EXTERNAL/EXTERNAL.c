/*
 * EXTERNAL_INTERRUPT.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include "../INTERRUPT.h"
#include "EXTERNAL.h"

/* Function Pointers */
void (*INT0_function_pointer) (void)=NULL;
void (*INT1_function_pointer) (void)=NULL;
void (*INT2_function_pointer) (void)=NULL;


/********************************\
*********** Functions ************
\********************************/

void INTERRUPT_EXTERNAL_INT0_EnableInterrupt(void){
	SET_BIT(GICR, INT0_FLAG);
}

void INTERRUPT_EXTERNAL_INT0_DisableInterrupt(void){
	CLEAR_BIT(GICR, INT0_FLAG);
}

void INTERRUPT_EXTERNAL_INT1_EnableInterrupt(void){
	SET_BIT(GICR, INT1_FLAG);
}

void INTERRUPT_EXTERNAL_INT1_DisableInterrupt(void){
	CLEAR_BIT(GICR, INT1_FLAG);
}

void INTERRUPT_EXTERNAL_INT2_EnableInterrupt(void){
	SET_BIT(GICR, INT2_FLAG);
}

void INTERRUPT_EXTERNAL_INT2_DisableInterrupt(void){
	CLEAR_BIT(GICR, INT2_FLAG);
}

void INTERRUPT_EXTERNAL_INT0_ControlSense(INT0_or_INT1_sense_control event){
	switch (event){
	case INT0_INT1_LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC00);
		CLEAR_BIT(MCUCR, ISC01);
		break;
	case INT0_INT1_ANY_CHANGE:
		SET_BIT(MCUCR, ISC00);
		CLEAR_BIT(MCUCR, ISC01);
		break;
	case INT0_INT1_FALLING_EDGE:
		CLEAR_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
		break;
	case INT0_INT1_RISING_EDGE:
		SET_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
		break;
	}
}
void INTERRUPT_EXTERNAL_INT1_ControlSense(INT0_or_INT1_sense_control event){
	switch (event){
	case INT0_INT1_LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC10);
		CLEAR_BIT(MCUCR, ISC11);
		break;
	case INT0_INT1_ANY_CHANGE:
		SET_BIT(MCUCR, ISC10);
		CLEAR_BIT(MCUCR, ISC11);
		break;
	case INT0_INT1_FALLING_EDGE:
		CLEAR_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
		break;
	case INT0_INT1_RISING_EDGE:
		SET_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
		break;
	}
}
void INTERRUPT_EXTERNAL_INT2_ControlSense(INT2_sense_control mode){
	switch (mode){
	case INT2_FALLING_EDGE:
		CLEAR_BIT(MCUCSR, ISC2);
		break;
	case INT2_RISING_EDGE:
		SET_BIT(MCUCSR, ISC2);
		break;
	}
}

void INTERRUPT_EXTERNAL_INT0_SetCallBack(void (*local_function_pointer) (void)){
	INT0_function_pointer = local_function_pointer;
}

void INTERRUPT_EXTERNAL_INT1_SetCallBack(void (*local_function_pointer) (void)){
	INT1_function_pointer = local_function_pointer;
}

void INTERRUPT_EXTERNAL_INT2_SetCallBack(void (*local_function_pointer) (void)){
	INT2_function_pointer = local_function_pointer;
}


/* ISR functions */

/*
 *
 * __vector_1(void) -> External Interrupt Request 0.
 * __vector_2(void) -> External Interrupt Request 1.
 * __vector_3(void) -> External Interrupt Request 2.
 *
 */

void __vector_1(void) __attribute__ ((signal, used, externally_visible));
void __vector_1 (void){
	INTERRUPT_DisableGlobalInterrupt();
	if (INT0_function_pointer){			// Check if the function pointer is not NULL
		INT0_function_pointer();		// Execute the function
	}
	INTERRUPT_EnableGlobalInterrupt();
}

void __vector_2(void) __attribute__ ((signal, used, externally_visible));
void __vector_2 (void){
	if (INT1_function_pointer){	// Check if the function pointer is not NULL
		INT1_function_pointer();		// Execute the function
	}
}

void __vector_3(void) __attribute__ ((signal, used, externally_visible));
void __vector_3 (void){
	if (INT2_function_pointer){	// Check if the function pointer is not NULL
		INT2_function_pointer();		// Execute the function
	}
}
