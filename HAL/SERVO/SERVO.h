/*
 * SERVO.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Abdullah Etman
 */

#ifndef SERVO_SERVO_H_
#define SERVO_SERVO_H_

#define SERVO_PORT 							PORT_D
#define SERVO_PIN 							PIN_7

/* Servo Motor Values */
/*
 * NOTE:
 * 		I calculated the values that I should use according to the datasheet, but they did not work for me.
 * 		I got these values by trial and error.
 * 		These values worked for my servo motor. You may need to change it in your case.
 * 		Try until you get the best results!
 *
 */
#define SERVO_CENTER_PULSE_PRESCALER_256 	93   	// Pulse width for center position.
#define SERVO_90_CW_PULSE_PRESCALER_256 	30    	// Pulse width for 90° clockwise position.
#define SERVO_90_CCW_PULSE_PRESCALER_256 	150  	// Pulse width for 90° counterclockwise position.
#define SERVO_TOP_VALUE_PRESCALER_256 		1249    // Value for ICR1 in Timer1 (top value).
#define SERVO_DELAY_MS_ 					1700   	// Delay time for servo movement.
#define SERVO_WAIT_MS_ 						500     // Delay after stopping the servo.


/********************************\
*********** Functions ************
\********************************/

void SERVO_Init(void);
void SERVO_Center(void);
void SERVO_90_CW(void);
void SERVO_90_CCW(void);
void SERVO_High(void);
void SERVO_Low(void);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	SERVO_Init(void):
 * 				@brief	Initialize the servo motor
 *
 * 				@details
 * 						- Set the servo pin as an output.
 * 						- Set the ICR1 register to define the PWM period.
 * 						- Enable interrupts to handle rising and falling edges of the pulse.
 * 						- Set the timer in Fast PWM mode with a prescaler of 256.
 *
 *	____________________________________________________________________________________

 *	SERVO_Center(void):
 * 				@brief	Move the servo to the center position (0 degrees).
 *
 * 				@details
 * 						- Initializes the servo.
 * 						- Sets OCR1A to 93, which corresponds to the center position.
 * 						- Stops the timer after a delay to hold the servo in position.
 *
 *	____________________________________________________________________________________

 *	SERVO_90_CCW(void):
 * 				@brief	Move the servo to 90 degrees counterclockwise.
 *
 * 				@details
 * 						- Initializes the servo.
 * 						- Sets OCR1A to 150 to rotate 90 degrees counterclockwise.
 * 						- Stops the timer after a delay to hold the servo in position.
 *
 *	____________________________________________________________________________________

 *	SERVO_90_CW(void):
 * 				@brief	Move the servo to 90 degrees clockwise.
 *
 * 				@details
 * 						- Initializes the servo.
 * 						- Sets OCR1A to 30 to rotate 90 degrees clockwise.
 * 						- Stops the timer after a delay to hold the servo in position.
 *
 *	____________________________________________________________________________________

 *	SERVO_High(void):
 * 				@brief	Set the servo pin to high (5V).
 *
 *	____________________________________________________________________________________

 *	SERVO_Low(void):
 * 				@brief	Set the servo pin to low (0V).
 *
 *	____________________________________________________________________________________

 */


#endif /* SERVO_SERVO_H_ */
