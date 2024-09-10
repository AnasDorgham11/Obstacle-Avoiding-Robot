/*
 * main.c
 *
 *  Created on: Sep 10, 2024
 *      Authors: Abdullah Etman & Anas Dorgham
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/LCD/LCD.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/INTERRUPT/INTERRUPT.h"
#include "../HAL/ULTRASONIC/ULTRASONIC.h"
#include "../HAL/SERVO/SERVO.h"
#include "../HAL/CAR/_2_WHEELS/MOVEMENT/MOVEMENT.h"
#include <util/delay.h>

/* Macros Definition */
#define FORWARD						0
#define NON_FORWARD					1
#define OBSTACLE_THRESHOLD_CM_ 		45

/* Variables */
u8_t direction = FORWARD;


/********************************\
*********** Functions ************
\********************************/

void PrintDirection(CAR_directions direction){
	LCD_GoToPosition(UPPER_ROW,5);
	switch (direction){
	case CAR_FORWARD:
		LCD_SendString("Forward");
		break;
	case CAR_BACKWARD:
		LCD_SendString("Backward");
		break;
	case CAR_RIGHT:
		LCD_SendString("Right   ");
		break;
	case CAR_LEFT:
		LCD_SendString("Left    ");
		break;
	}
	/*
	 * NOTE:
	 * 		Spaces after "Right" and "Left" are written to remove any left characters from "Forward" and "Backward" if existed.
	 *
	 */
}

void PrintDistance(void){
	LCD_GoToPosition(LOWER_ROW, 6);
	LCD_SendNumber((u16_t) ULTRASONIC_GetDistance_cm_());
	if (ULTRASONIC_GetDistance_cm_() < 10){			// 1-digit distance
		LCD_GoToPosition(LOWER_ROW, 7);
		LCD_SendString("  ");						// Write 2 spaces after the distance to remove the last 2 digits from a past distance if existed.
	}
	else if (ULTRASONIC_GetDistance_cm_() < 100){	// 2-digits distance
		LCD_GoToPosition(LOWER_ROW, 8);
		LCD_SendChar(' ');							// Write one space after the distance to remove the last digit from a past distance if existed.
	}
}

int main(){
	INTERRUPT_EnableGlobalInterrupt();
	LCD_Init(_4bits);													// Initialize LCD as 4-bits.
	LCD_SendString("Dir: ");											// To indicate the directory.

	// Write "Dist=    cm" in the second line of LCD.
	LCD_GoToPosition(LOWER_ROW, 0);
	LCD_SendString("Dist= ");
	LCD_GoToPosition(LOWER_ROW, 9);
	LCD_SendString("cm");

	CAR_MOVEMENT_Motors_Init(CAR_DC_MOTORS_DIFFERENT_SPEEDS);			// Both motors are working with the same speed.
	CAR_MOVEMENT_DifferentSpeeds_SetDefaultSpeedPercentages(54,50);		// Motors speed are 54, 50%.
	ULTRASONIC_Init();
	SERVO_Center();														// Ensure the servo motor is centered.
	direction = NON_FORWARD;
	while(1){
		ULTRASONIC_TRIG_Send();											// Send an ultrasonic trigger (with a delay inside to wait the echo).
		PrintDistance();												// Print distance on LCD after the echo gets a response.
		if (ULTRASONIC_GetDistance_cm_() > OBSTACLE_THRESHOLD_CM_){

			// Checking if direction was not set as forward, to call the next lines when only needed.
			if (direction != FORWARD){
				PrintDirection(CAR_FORWARD);							// Print the direction as "Forward".
				CAR_MOVEMENT_Forward();									// Move the car in forward direction.
				direction = FORWARD;									// Change the direction to be forward to avoid calling the previous 2 function again.
			}

			_delay_ms(100);
			continue;													// Skip the rest of the code and enter the loop again.
		}

		// Checking if the direction is non-forward and if the distance is greater than 35cm, to ensure calling CAR_MOVEMENT_Forward() when only needed.
		CAR_MOVEMENT_Stop();
		direction = NON_FORWARD;										// Change the direction to be non-forward.
		LCD_GoToPosition(UPPER_ROW,5);
		LCD_SendString("Stopped  ");									// Print the direction as "Stopped".
		SERVO_90_CW();													// Rotate the servo motor into the right of the car.
		ULTRASONIC_TRIG_Send();											// Send an ultrasonic trigger (with a delay inside to wait the echo).
		PrintDistance();												// Print the distance on LCD.
		if (ULTRASONIC_GetDistance_cm_() > OBSTACLE_THRESHOLD_CM_){
			PrintDirection(CAR_RIGHT);									// Print the direction as "Right".
			CAR_MOVEMENT_Right();										// Rotate the car to the right.
			_delay_ms(450);												// The rotation takes 450ms to rotate by 90 degrees to the right.
		}
		// If the distance read for the right of the car is greater than 15, ...
		else{
			SERVO_90_CCW();												// Rotate the servo motor into the left of the car.
			ULTRASONIC_TRIG_Send();										// Send an ultrasonic trigger (with a delay inside to wait the echo).
			PrintDistance();											// Print the distance on LCD.
			if (ULTRASONIC_GetDistance_cm_() > OBSTACLE_THRESHOLD_CM_){
				PrintDirection(CAR_LEFT);								// Print the direction as "Left".
				CAR_MOVEMENT_Left();									// Rotate the car to the left.
				_delay_ms(430);											// The rotation takes 430ms to rotate by 90 degrees to the left.
			}
			// Rotate car to the right by 180 degrees (Turnabout)
			else{
				CAR_MOVEMENT_Right();									// Rotate the car to the right.
				_delay_ms(790);											// The rotation takes 790ms to rotate by 180 degrees to the right.
			}
		}
		CAR_MOVEMENT_Stop();											// Stop the car.
		SERVO_Center();													// Center the servo motor.
	}
}

