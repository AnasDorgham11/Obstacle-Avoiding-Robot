/*
 * SERVO.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Abdullah Etman
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include"../../MCAL/DIO/DIO.h"
#include"../../MCAL/TIMER/TIMER.h"
#include"../../MCAL/INTERRUPT/INTERRUPT.h"
#include "../LCD/LCD.h"
#include"SERVO.h"
#include<util/delay.h>


/********************************\
*********** Functions ************
\********************************/

void SERVO_Init(void)
{
	DIO_SetPinDirection(SERVO_PORT, SERVO_PIN, PIN_OUTPUT);
	TIMER_Timer1_ICR1_Set(SERVO_TOP_VALUE_PRESCALER_256);
	SERVO_High();								// Initialize the pulse as high.
	TIMER_Timer1_OCA_EnableInterrupt();			// Enable output compare match interrupt.
	TIMER_Timer1_IC_EnableInterrupt();			// Enable input capture interrupt.
	TIMER_Timer1_OCA_SetCallBack(SERVO_Low);	// When TCNT1 = OCR1A, generate 0v for the servo motor.
	TIMER_Timer1_IC_SetCallBack(SERVO_High);	// When reaching the top (ICR1), generate 5v for the servo motor.
	TIMER_Timer1_Init(TIMER1_FAST_PWM_ICR1, TIMER1_PRESCALER_256);
}

/* Move the servo to the center position (1.5ms pulse) */
void SERVO_Center(void)
{
    SERVO_Init();  // Initialize the servo motor.
    TIMER_Timer1_OCR1A_Set(SERVO_CENTER_PULSE_PRESCALER_256);  // Set the pulse width for the center position.
    _delay_ms(SERVO_DELAY_MS_);                                // Wait for the servo to reach the position.
    TIMER_Timer1_Stop();                                       // Stop Timer1 after the movement.
    TIMER_Timer1_OCA_DisableInterrupt();                       // Disable output compare match interrupt.
    TIMER_Timer1_IC_DisableInterrupt();                        // Disable input capture interrupt.
    _delay_ms(SERVO_WAIT_MS_);                                 // Wait before executing the next operation.
}

/* Move the servo to 90 degrees counterclockwise (CCW) */
void SERVO_90_CCW(void)
{
    SERVO_Init();  // Initialize the servo motor.
    TIMER_Timer1_OCR1A_Set(SERVO_90_CCW_PULSE_PRESCALER_256);  // Set the pulse width for 90 degrees CCW.
    _delay_ms(SERVO_DELAY_MS_);                                // Wait for the servo to reach the position.
    TIMER_Timer1_Stop();                                       // Stop Timer1 after the movement.
    TIMER_Timer1_OCA_DisableInterrupt();                       // Disable output compare match interrupt.
    TIMER_Timer1_IC_DisableInterrupt();                        // Disable input capture interrupt.
    _delay_ms(SERVO_WAIT_MS_);                                 // Wait before executing the next operation.
}

/* Move the servo to 90 degrees clockwise (CW)*/
void SERVO_90_CW(void)
{
    SERVO_Init();  // Initialize the servo motor.
    TIMER_Timer1_OCR1A_Set(SERVO_90_CW_PULSE_PRESCALER_256);  // Set the pulse width for 90 degrees CW.
    _delay_ms(SERVO_DELAY_MS_);                               // Wait for the servo to reach the position.
    TIMER_Timer1_Stop();                                      // Stop Timer1 after the movement.
    TIMER_Timer1_OCA_DisableInterrupt();                      // Disable output compare match interrupt.
    TIMER_Timer1_IC_DisableInterrupt();                       // Disable input capture interrupt.
    _delay_ms(SERVO_WAIT_MS_);                                // Wait before executing the next operation.
}

/* Set the servo pin to high (5V) to generate the rising edge of the pulse */
void SERVO_High(void)
{
    DIO_SetPinValue(SERVO_PORT, SERVO_PIN, PIN_HIGH);  // Set the servo pin to high.
}

/* Set the servo pin to low (0V) to generate the falling edge of the pulse */
void SERVO_Low(void)
{
    DIO_SetPinValue(SERVO_PORT, SERVO_PIN, PIN_LOW);   // Set the servo pin to low.
}
