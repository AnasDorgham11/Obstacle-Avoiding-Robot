/*
 * ULTRASONIC.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

/* PORTS */
#define ULTRASONIC_PORT		PORT_D


/* PINS */
/*
 * NOTE:
 * 		INT0 is defined in LIB/PIN_CONFIG.h as PIN_2.
 * 		INT0_PORT is defined in LIB/PIN_CONFIG as PORT_D which is ULTRASONIC_PORT here.
 *
 */
#define TRIG							PIN_1
#define ECHO							PIN_3

#define ULTRASONIC_OFF					0
#define ULTRASONIC_ON					1

#define ULTRASONIC_FALLING_EDGE			0
#define ULTRASONIC_RISING_EDGE			1

#define SOUND_VELOCITY_CM_PER_S_		34300
#define ULTRASONIC_MAXIMUM_LENGTH_CM_	400

double ultrasonic_distance;


/********************************\
*********** Functions ************
\********************************/

void ULTRASONIC_Init(void);
void ULTRASONIC_TRIG_Send(void);
void ULTRASONIC_TRIG_EnableAutoSend(u32_t delay_in_ms);
void ULTRASONIC_TRIG_DisableAutoSend(void);
void ULTRASONIC_ECHO_InterruptHandler(void);
void ULTRASONIC_Timer_OverflowHandler(void);
u16_t ULTRASONIC_GetDistance_cm_(void);

/*
 * .-----------------------------.
 * | Explanation of each function |
 * '-----------------------------'

 * ULTRASONIC_Init(void):
 *				@brief	Initialize the ultrasonic sensor.
 *
 *				@details
 *						- Sets the TRIG pin as output and the ECHO pin as input.
 *						- Enables pull-up resistor for the ECHO pin.
 *						- Configures external interrupt for echo detection.
 *						- Registers callback functions for the interrupt and timer overflow handling.
 *
 * ____________________________________________________________________________________

 * ULTRASONIC_TRIG_Send(void):
 *				@brief	Send a trigger pulse to start the measurement.
 *
 *				@details
 *						- Sends a 15us high pulse on the TRIG pin to initiate the sensor.
 *						- Starts Timer0 and enables timer overflow interrupt to measure the echo duration.
 *
 * ____________________________________________________________________________________

 * ULTRASONIC_ECHO_InterruptHandler(void):
 *				@brief	Handle the external interrupt caused by the echo signal.
 *
 *				@details
 *						- On the rising edge, starts the timer to count the echo pulse duration.
 *						- On the falling edge, calculates the distance based on the timer value and stops the timer.
 *
 * ____________________________________________________________________________________

 * ULTRASONIC_Timer_OverflowHandler(void):
 *				@brief	Handle the timer overflow during echo signal measurement.
 *
 *				@details
 *						- Increments the overflow counter.
 *						- If the counter exceeds the maximum allowable overflow, sets the distance to the maximum measurable value.
 *
 * ____________________________________________________________________________________

 * ULTRASONIC_GetDistance_cm_(void):
 *				@brief	Returns the calculated distance in centimeters.
 *
 *				@return	Returns the last measured distance in cm.
 *
 * ____________________________________________________________________________________

 */


#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
