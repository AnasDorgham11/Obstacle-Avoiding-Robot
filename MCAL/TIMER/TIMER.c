/*
 * TIMER.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#define F_CPU		16000000UL
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/PIN_CONFIG.h"
#include "../../MCAL/DIO/DIO.h"
#include "TIMER.h"




  /******************************************************************/
 /**************************** Timer0 ******************************/
/******************************************************************/

/* Function Pointers */
void (*Timer0_OVF_function_pointer) (void)=NULL;
void (*Timer0_COMP_function_pointer) (void)=NULL;


/********************************\
*********** Functions ************
\********************************/

void TIMER_Timer0_Init(TIMER0_mode_of_operation mode, TIMER0_prescaler prescaler){
	switch (mode){
	case TIMER0_NORMAL:
		CLEAR_BIT(TCCR0, WGM00);
		CLEAR_BIT(TCCR0, WGM01);
		break;
	case TIMER0_PWM_PHASE_CORRECT:
		SET_BIT(TCCR0, WGM00);
		CLEAR_BIT(TCCR0, WGM01);
		break;
	case TIMER0_CTC:
		CLEAR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
		break;
	case TIMER0_FAST_PWM:
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
		break;
	}

	/*
	 * NOTE:
	 * 		The flags responsible of setting prescaler (CS00, CS01 and CS02) are the least 3 significant bits in TCCR0.
	 * 		Prescalers definitions are arranged from 0 (Stop) to 7.
	 * 		Therefore, It is easier to just make TCCR0 &= 0b11111000 then TCCR0 =| prescaler to set the chosen prescaler.
	 * 		However, it is often better to avoid using magic numbers or depend on the location of flags, so "SET_BIT" and "CLEAR_BIT" are used below.
	 *
	 */
	switch (prescaler){
	case TIMER0_STOP:
		CLEAR_BIT(TCCR0, CS00);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS02);
		break;
	case TIMER0_NO_PRESCALER:
		SET_BIT(TCCR0, CS00);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS02);
		break;
	case TIMER0_PRESCALER_8:
		CLEAR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS02);
		break;
	case TIMER0_PRESCALER_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS02);
		break;
	case TIMER0_PRESCALER_256:
		CLEAR_BIT(TCCR0, CS00);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
	case TIMER0_PRESCALER_1024:
		SET_BIT(TCCR0, CS00);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
	case TIMER0_FALLING_EDGE:
		CLEAR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
	case TIMER0_RISING_EDGE:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
	}
//	TIMER_TIFR_ClearFlag(TOV0);
//	TIMER_TIFR_ClearFlag(OCF0);
	TCNT0 = 0;
}

void TIMER_Timer0_TCNT0_Set(u8_t value){
	TCNT0 = value;
}

void TIMER_Timer0_OCR0_Set(u8_t value){
	OCR0 = value;
}

void TIMER_Timer0_OC0_Init(TIMER0_OC0_mode mode){
	DIO_SetPinDirection(OC0_PORT, OC0, PIN_OUTPUT);
	switch (mode){
	case OC0_DISCONNECT:
		CLEAR_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
		break;
	case OC0_TOGGLE:
		SET_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
		break;
	case OC0_NON_INVERTING:
		CLEAR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;
	case OC0_INVERTING:
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;
	}
}

void TIMER_Timer0_OV_EnableInterrupt(void){
	SET_BIT(TIMSK, TOIE0);
}

void TIMER_Timer0_OV_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, TOIE0);
}

void TIMER_Timer0_OC_EnableInterrupt(void){
	SET_BIT(TIMSK, OCIE0);
}

void TIMER_Timer0_OC_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, OCIE0);
}

void TIMER_Timer0_OV_SetCallBack(void (*local_function_pointer) (void)){
	Timer0_OVF_function_pointer = local_function_pointer;
}
void TIMER_Timer0_OC_SetCallBack(void (*local_function_pointer) (void)){
	Timer0_COMP_function_pointer = local_function_pointer;
}

void TIMER_Timer0_OV_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(TOV0);			// Clear TOV0 initially.
	while(!GET_BIT(TIFR, TOV0));		// While TOV0 flag is 0 (Overflow hasn't been reached yet), stay here.
}

void TIMER_Timer0_OC_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(OCF0);			// Clear OCF0 initially.
	while(!GET_BIT(TIFR, OCF0));		// While OCF0 flag is 0 (TCNT0 has not matched OCR0 yet), stay here.
}

void TIMER_Timer0_Stop(void){
	CLEAR_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
}

/* ISR functions */

/*
 *
 * __vector_10(void) -> Timer 0 Compare Match Interrupt.
 * __vector_11(void) -> Timer 0 Overflow Interrupt.
 *
 */

void __vector_10(void) __attribute__ ((signal, used, externally_visible));
void __vector_10 (void){
	if (Timer0_COMP_function_pointer){	// Check if the function pointer is not NULL
		Timer0_COMP_function_pointer();	// Execute the function
	}
}

void __vector_11(void) __attribute__ ((signal, used, externally_visible));
void __vector_11 (void){
	if (Timer0_OVF_function_pointer){	// Check if the function pointer is not NULL
		Timer0_OVF_function_pointer();	// Execute the function
	}
}


  /******************************************************************/
 /**************************** Timer1 ******************************/
/******************************************************************/

/* Function Pointers */
void (*Timer1_OVF_function_pointer) (void)=NULL;
void (*Timer1_COMPA_function_pointer) (void)=NULL;
void (*Timer1_COMPB_function_pointer) (void)=NULL;
void (*Timer1_CAPT_function_pointer) (void)=NULL;


/********************************\
*********** Functions ************
\********************************/

void TIMER_Timer1_Init(TIMER1_mode_of_operation mode, TIMER1_prescaler  prescaler){
	switch (mode){
	case TIMER1_NORMAL:
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_CORRECT_8_BIT:
		SET_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_CORRECT_9_BIT:
		CLEAR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_CORRECT_10_BIT:
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_CTC_OCR1:
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_FAST_PWM_8_BIT:
		SET_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_FAST_PWM_9_BIT:
		CLEAR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_FAST_PWM_10_BIT:
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		CLEAR_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1:
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1:
		SET_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_CORRECT_ICR1:
		CLEAR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_PWM_PHASE_CORRECT_OCR1:
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		CLEAR_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_CTC_ICR1:
		CLEAR_BIT(TCCR1A, WGM10);
		CLEAR_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_FAST_PWM_ICR1:
		CLEAR_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	case TIMER1_FAST_PWM_OCR1:
		SET_BIT(TCCR1A, WGM10);
		SET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		SET_BIT(TCCR1B, WGM13);
		break;
	}

	/*
	 * NOTE:
	 * 		The flags responsible of setting prescaler (CS00, CS01 and CS02) are the least 3 significant bits in TCCR0.
	 * 		Prescalers definitions are arranged from 0 (Stop) to 7.
	 * 		Therefore, It is easier to just make TCCR0 &= 0b11111000 then TCCR0 =| prescaler to set the chosen prescaler.
	 * 		However, it is often better to avoid using magic numbers or depend on the location of flags, so "SET_BIT" and "CLEAR_BIT" are used below.
	 *
	 */
	switch (prescaler){
	case TIMER1_STOP:
		CLEAR_BIT(TCCR1B, CS10);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS12);
		break;
	case TIMER1_NO_PRESCALER:
		SET_BIT(TCCR1B, CS10);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS12);
		break;
	case TIMER1_PRESCALER_8:
		CLEAR_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS12);
		break;
	case TIMER1_PRESCALER_64:
		SET_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS12);
		break;
	case TIMER1_PRESCALER_256:
		CLEAR_BIT(TCCR1B, CS10);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
	case TIMER1_PRESCALER_1024:
		SET_BIT(TCCR1B, CS10);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
	case TIMER1_FALLING_EDGE:
		CLEAR_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
	case TIMER1_RISING_EDGE:
		SET_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
	}
	TIMER_Timer1_TCNT1_Set(0);
}

void TIMER_Timer1_TCNT1_Set(u16_t value){
	// Setting TCNT1L as the least significant 8 bits of the 16 bits value by ANDing the value with only the right 8 bits high and assigning the result to TCNTL.
	TCNT1L = value & 0x00ff;
	// Setting TCNT1H as the most significant 8 bits of the 16 bits value by shifting it 8 bits to the right and assigning the result to TCNTH.
	TCNT1H = value >> 8;
}

void TIMER_Timer1_OCR1A_Set(u16_t value){
	// Setting OCR1AL as the least significant 8 bits of the 16 bits value by ANDing the value with only the right 8 bits high and assigning the result to OCR1AL.
	OCR1AL = value & 0x00ff;
	// Setting OCR1AH as the most significant 8 bits of the 16 bits value by shifting it 8 bits to the right and assigning the result to OCR1AH.
	OCR1AH = value >> 8;
}
void TIMER_Timer1_OCR1B_Set(u16_t value){
	// Setting OCR1BL as the least significant 8 bits of the 16 bits value by ANDing the value with only the right 8 bits high and assigning the result to OCR1BL.
	OCR1BL = value & 0x00ff;
	// Setting OCR1BH as the most significant 8 bits of the 16 bits value by shifting it 8 bits to the right and assigning the result to OCR1BH.
	OCR1BH = value >> 8;
}

void TIMER_Timer1_ICR1_Set(u16_t value){
	// Setting ICR1L as the least significant 8 bits of the 16 bits value by ANDing the value with only the right 8 bits high and assigning the result to ICR1L.
	ICR1L = value & 0x00ff;
	// Setting ICR1H as the most significant 8 bits of the 16 bits value by shifting it 8 bits to the right and assigning the result to ICR1H.
	ICR1H = value >> 8;
}

void TIMER_Timer1_OC1A_Init(TIMER1_OC1_mode mode){
	DIO_SetPinDirection(OC1A_PORT, OC1A, PIN_OUTPUT);
	switch (mode){
	case OC1_DISCONNECT:
		CLEAR_BIT(TCCR1A, COM1A0);
		CLEAR_BIT(TCCR1A, COM1A1);
		break;
	case OC1_TOGGLE:
		SET_BIT(TCCR1A, COM1A0);
		CLEAR_BIT(TCCR1A, COM1A1);
		break;
	case OC1_NON_INVERTING:
		CLEAR_BIT(TCCR1A, COM1A0);
		SET_BIT(TCCR1A, COM1A1);
		break;
	case OC1_INVERTING:
		SET_BIT(TCCR1A, COM1A0);
		SET_BIT(TCCR1A, COM1A1);
		break;
	}
}

void TIMER_Timer1_OC1B_Init(TIMER1_OC1_mode mode){
	DIO_SetPinDirection(OC1B_PORT, OC1B, PIN_OUTPUT);
	switch (mode){
	case OC1_DISCONNECT:
		CLEAR_BIT(TCCR1A, COM1B0);
		CLEAR_BIT(TCCR1A, COM1B1);
		break;
	case OC1_TOGGLE:
		SET_BIT(TCCR1A, COM1B0);
		CLEAR_BIT(TCCR1A, COM1B1);
		break;
	case OC1_NON_INVERTING:
		CLEAR_BIT(TCCR1A, COM1B0);
		SET_BIT(TCCR1A, COM1B1);
		break;
	case OC1_INVERTING:
		SET_BIT(TCCR1A, COM1B0);
		SET_BIT(TCCR1A, COM1B1);
		break;
	}
}

void TIMER_Timer1_OV_EnableInterrupt(void){
	SET_BIT(TIMSK, TOIE1);
}

void TIMER_Timer1_OV_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, TOIE1);
}

void TIMER_Timer1_OCA_EnableInterrupt(void){
	SET_BIT(TIMSK, OCIE1A);
}

void TIMER_Timer1_OCA_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, OCIE1A);
}

void TIMER_Timer1_OCB_EnableInterrupt(void){
	SET_BIT(TIMSK, OCIE1B);
}

void TIMER_Timer1_OCB_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, OCIE1B);
}

void TIMER_Timer1_IC_EnableInterrupt(void){
	SET_BIT(TIMSK, TICIE1);
}

void TIMER_Timer1_IC_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, TICIE1);
}

void TIMER_Timer1_OV_SetCallBack(void (*local_function_pointer) (void)){
	Timer1_OVF_function_pointer = local_function_pointer;
}

void TIMER_Timer1_OCA_SetCallBack(void (*local_function_pointer) (void)){
	Timer1_COMPA_function_pointer = local_function_pointer;
}

void TIMER_Timer1_OCB_SetCallBack(void (*local_function_pointer) (void)){
	Timer1_COMPB_function_pointer = local_function_pointer;
}

void TIMER_Timer1_IC_SetCallBack(void (*local_function_pointer) (void)){
	Timer1_CAPT_function_pointer = local_function_pointer;
}

void TIMER_Timer1_OV_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(TOV1);		// Clear TOV1 initially.
	while(!GET_BIT(TIFR, TOV1));	// While TOV1 flag is 0 (Overflow hasn't been reached yet), stay here.
}

void TIMER_Timer1_OCA_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(OCF1A);	// Clear OCF1A initially.
	while(!GET_BIT(TIFR, OCF1A));	// While OCF1A flag is 0 (TCNT1 has not matched OCR1A yet), stay here.
}

void TIMER_Timer1_OCB_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(OCF1B);	// Clear OCF1B initially.
	while(!GET_BIT(TIFR, OCF1B));	// While OCF1B flag is 0 (TCNT1 has not matched OCR1B yet), stay here.
}

void TIMER_Timer1_IC_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(ICF1);		// Clear ICF1 initially.
	while(!GET_BIT(TIFR, ICF1));	// While ICF1 flag is 0 (TCNT1 has not matched OCR1B yet), stay here.
}

void TIMER_Timer1_Stop(void){
	CLEAR_BIT(TCCR1B, CS10);
	CLEAR_BIT(TCCR1B, CS11);
	CLEAR_BIT(TCCR1B, CS12);
}

/* ISR functions */

/*
 *
 * __vector_6(void)  -> Timer 1 Capture Event Interrupt.
 * __vector_7(void)  -> Timer 1 Compare Match A Interrupt.
 * __vector_8(void)  -> Timer 1 Compare Match B Interrupt.
 * __vector_9(void) -> Timer 1 Overflow Interrupt.
 *
 */

void __vector_6(void) __attribute__ ((signal, used, externally_visible));
void __vector_6 (void){
	if (Timer1_CAPT_function_pointer){		// Check if the function pointer is not NULL
		Timer1_CAPT_function_pointer();		// Execute the function
	}
}

void __vector_7(void) __attribute__ ((signal, used, externally_visible));
void __vector_7 (void){
	if (Timer1_COMPA_function_pointer){		// Check if the function pointer is not NULL
		Timer1_COMPA_function_pointer();	// Execute the function
	}
}

void __vector_8(void) __attribute__ ((signal, used, externally_visible));
void __vector_8 (void){
	if (Timer1_COMPB_function_pointer){		// Check if the function pointer is not NULL
		Timer1_COMPB_function_pointer();	// Execute the function
	}
}

void __vector_9(void) __attribute__ ((signal, used, externally_visible));
void __vector_9 (void){
	if (Timer1_OVF_function_pointer){		// Check if the function pointer is not NULL
		Timer1_OVF_function_pointer();		// Execute the function
	}
}



  /******************************************************************/
 /**************************** Timer2 ******************************/
/******************************************************************/

/* Function Pointers */
void (*Timer2_OVF_function_pointer) (void)=NULL;
void (*Timer2_COMP_function_pointer) (void)=NULL;


/********************************\
*********** Functions ************
\********************************/

void TIMER_Timer2_Init(TIMER2_mode_of_operation mode, TIMER2_prescaler prescaler){
	switch (mode){
	case TIMER2_NORMAL:
		CLEAR_BIT(TCCR2, WGM20);
		CLEAR_BIT(TCCR2, WGM21);
		break;
	case TIMER2_PWM_PHASE_CORRECT:
		SET_BIT(TCCR2, WGM20);
		CLEAR_BIT(TCCR2, WGM21);
		break;
	case TIMER2_CTC:
		CLEAR_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);
		break;
	case TIMER2_FAST_PWM:
		SET_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);
		break;
	}

	/*
	 * NOTE:
	 * 		The flags responsible of setting prescaler (CS20, CS21 and CS22) are the least 3 significant bits in TCCR2.
	 * 		Prescalers definitions are arranged from 0 (Stop) to 7.
	 * 		Therefore, It is easier to just make TCCR2 &= 0b11111000 then TCCR2 =| prescaler to set the chosen prescaler.
	 * 		However, it is often better to avoid using magic numbers or depend on the location of flags, so "SET_BIT" and "CLEAR_BIT" are used below.
	 *
	 */
	switch (prescaler){
	case TIMER2_STOP:
		CLEAR_BIT(TCCR2, CS20);
		CLEAR_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS22);
		break;
	case TIMER2_NO_PRESCALER:
		SET_BIT(TCCR2, CS20);
		CLEAR_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_8:
		CLEAR_BIT(TCCR2, CS20);
		SET_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_32:
		SET_BIT(TCCR2, CS20);
		SET_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_64:
		CLEAR_BIT(TCCR2, CS20);
		CLEAR_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_128:
		SET_BIT(TCCR2, CS20);
		CLEAR_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_256:
		CLEAR_BIT(TCCR2, CS20);
		SET_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS22);
		break;
	case TIMER2_PRESCALER_1024:
		SET_BIT(TCCR2, CS20);
		SET_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS22);
		break;
	}
	TCNT2 = 0;
}


void TIMER_Timer2_TCNT2_Set(u8_t value){
	TCNT2 = value;
}

void TIMER_Timer2_OCR2_Set(u8_t value){
	OCR2 = value;
}

void TIMER_Timer2_OC2_Init(TIMER2_OC2_mode mode){
	DIO_SetPinDirection(OC2_PORT, OC2, PIN_OUTPUT);
	switch (mode){
	case OC2_DISCONNECT:
		CLEAR_BIT(TCCR2, COM20);
		CLEAR_BIT(TCCR2, COM21);
		break;
	case OC2_TOGGLE:
		SET_BIT(TCCR2, COM20);
		CLEAR_BIT(TCCR2, COM21);
		break;
	case OC2_NON_INVERTING:
		CLEAR_BIT(TCCR2, COM20);
		SET_BIT(TCCR2, COM21);
		break;
	case OC2_INVERTING:
		SET_BIT(TCCR2, COM20);
		SET_BIT(TCCR2, COM21);
		break;
	}
}

void TIMER_Timer2_OV_EnableInterrupt(void){
	SET_BIT(TIMSK, TOIE2);
}

void TIMER_Timer2_OV_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, TOIE2);
}

void TIMER_Timer2_OC_EnableInterrupt(void){
	SET_BIT(TIMSK, OCIE2);
}

void TIMER_Timer2_OC_DisableInterrupt(void){
	CLEAR_BIT(TIMSK, OCIE2);
}

void TIMER_Timer2_OV_SetCallBack(void (*local_function_pointer) (void)){
	Timer2_OVF_function_pointer = local_function_pointer;
}
void TIMER_Timer2_OC_SetCallBack(void (*local_function_pointer) (void)){
	Timer2_COMP_function_pointer = local_function_pointer;
}

void TIMER_Timer2_OV_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(TOV2);		// Clear TOV2 initially.
	while(!GET_BIT(TIFR, TOV2));	// While TOV2 flag is 0 (Overflow hasn't been reached yet), stay here.=
}

void TIMER_Timer2_OC_Polling_Wait(void){
	TIMER_TIFR_ClearFlag(OCF2);		// Clear OCF2 initially.
	while(!GET_BIT(TIFR, OCF2));	// While OCF2 flag is 0 (TCNT2 has not matched OCR2 yet), stay here.
}

void TIMER_Timer2_Stop(void){
	CLEAR_BIT(TCCR2, CS20);
	CLEAR_BIT(TCCR2, CS21);
	CLEAR_BIT(TCCR2, CS22);
}

/* ISR functions */

/*
 *
 * __vector_4(void) -> Timer 2 Compare Match Interrupt.
 * __vector_5(void) -> Timer 2 Overflow Interrupt.
 *
 */

void __vector_4(void) __attribute__ ((signal, used, externally_visible));
void __vector_4 (void){
	if (Timer2_COMP_function_pointer){		// Check if the function pointer is not NULL
		Timer2_COMP_function_pointer();		// Execute the function
	}
}

void __vector_5(void) __attribute__ ((signal, used, externally_visible));
void __vector_5 (void){
	if (Timer2_OVF_function_pointer){		// Check if the function pointer is not NULL
		Timer2_OVF_function_pointer();		// Execute the function
	}
}



  /******************************************************************/
 /************************ Timers Interrupt ************************/
/******************************************************************/


/********************************\
*********** Functions ************
\********************************/

void TIMER_TIFR_ClearFlag(u8_t flag){
	SET_BIT(TIFR, flag);			// According to the datasheet, to clear any flag in TIFR, write a logic one to it.
}


