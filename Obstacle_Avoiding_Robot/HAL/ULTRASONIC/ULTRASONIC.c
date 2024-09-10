/*
 * ULTRASONIC.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/INTERRUPT/EXTERNAL/EXTERNAL.h"
#include "ULTRASONIC.h"
#include <util/delay.h>

/* Variables */
u8_t ultrasonic_state = ULTRASONIC_OFF;
u8_t ultrasonic_edge = ULTRASONIC_RISING_EDGE;
u16_t ultrasonic_overflow_counter = 0;
u16_t ultrasonic_maximum_overflow = (u16_t) 2 * (F_CPU * (ULTRASONIC_MAXIMUM_LENGTH_CM_ / ((double) SOUND_VELOCITY_CM_PER_S_ * 64)) / 256);


/********************************\
*********** Functions ************
\********************************/

void ULTRASONIC_Init(void){
	DIO_SetPinDirection(ULTRASONIC_PORT, TRIG, PIN_OUTPUT);
	DIO_SetPinDirection(ULTRASONIC_PORT, ECHO, PIN_INPUT);
	DIO_EnablePinPullup(ULTRASONIC_PORT, ECHO);
	INTERRUPT_EXTERNAL_INT1_EnableInterrupt();
	INTERRUPT_EXTERNAL_INT1_ControlSense(INT0_INT1_ANY_CHANGE);
	INTERRUPT_EXTERNAL_INT1_SetCallBack(ULTRASONIC_ECHO_InterruptHandler);
	TIMER_Timer0_OV_SetCallBack(ULTRASONIC_Timer_OverflowHandler);
}

void ULTRASONIC_TRIG_Send(void){
	if (ultrasonic_state == ULTRASONIC_OFF){
		TIMER_Timer0_OV_EnableInterrupt();
		DIO_SetPinValue(ULTRASONIC_PORT, TRIG, PIN_HIGH);
		_delay_us(15);
		DIO_SetPinValue(ULTRASONIC_PORT, TRIG, PIN_LOW);
		ultrasonic_state = ULTRASONIC_ON;
		TIMER_Timer0_Init(TIMER0_NORMAL, TIMER0_PRESCALER_64);
		_delay_ms(30);
	}
}

void ULTRASONIC_ECHO_InterruptHandler(void){
	if (ultrasonic_state == ULTRASONIC_ON){
		if (ultrasonic_edge == ULTRASONIC_FALLING_EDGE){
			TIMER_Timer0_OV_DisableInterrupt();
			ultrasonic_distance = ((ultrasonic_overflow_counter * 256 + TCNT0) * ((double) SOUND_VELOCITY_CM_PER_S_ * 64 / F_CPU))/2;
			TIMER_Timer0_Stop();
			ultrasonic_overflow_counter = 0;
			ultrasonic_edge = ULTRASONIC_RISING_EDGE;
			ultrasonic_state = ULTRASONIC_OFF;
		}
		else{
			TCNT0 = 0;
			ultrasonic_overflow_counter = 0;
			ultrasonic_edge = ULTRASONIC_FALLING_EDGE;
		}
	}
}

void ULTRASONIC_Timer_OverflowHandler(void){
	ultrasonic_overflow_counter++;
	if(ultrasonic_overflow_counter > ultrasonic_maximum_overflow){
		ultrasonic_distance = ULTRASONIC_MAXIMUM_LENGTH_CM_;
		TCNT0 = 0;
		ultrasonic_state = ULTRASONIC_OFF;
		ultrasonic_edge = ULTRASONIC_RISING_EDGE;
		ultrasonic_overflow_counter = 0;
	}
}

u16_t ULTRASONIC_GetDistance_cm_(void){
	return ultrasonic_distance;
}
