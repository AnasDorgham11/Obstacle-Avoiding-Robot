/*
 * H_BRIDGE.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef HAL_H_BRIDGE_L293_H_BRIDGE_H_
#define HAL_H_BRIDGE_L293_H_BRIDGE_H_

#define H_bridge_EN_PORT			PORT_D
#define H_bridge_A_PORT				PORT_C

#define H_EN1						PIN_4
#define H_EN2						PIN_5


#define H_A1						PIN_3
#define H_A2						PIN_4
#define H_A3						PIN_5
#define H_A4						PIN_6

void H_BRIDGE_L293_Motor_Init(u8_t EN, u8_t x, u8_t y);
void H_BRIDGE_L293_Motor_CW(u8_t EN, u8_t x, u8_t y);
void H_BRIDGE_L293_Motor_CCW(u8_t EN, u8_t x, u8_t y);
void H_BRIDGE_L293_Motor_FastStop(u8_t EN, u8_t x, u8_t y);
void H_BRIDGE_L293_Motor_FreeStop(u8_t EN);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	H_BRIDGE_L293_Motor_Init(u8_t EN, u8_t x, u8_t y):
 * 				@brief	Initialize the motor control pins for H-Bridge.
 *
 * 				@details
 * 						- Sets the enable pin and the motor control pins as outputs.
 *
 * 				@param EN: The enable pin.
 * 				@param x: First control pin (IN1 or IN3).
 * 				@param y: Second control pin (IN2 or IN4).
 *
 *	____________________________________________________________________________________

 *	H_BRIDGE_L293_Motor_CW(u8_t EN, u8_t x, u8_t y):
 * 				@brief	Rotate the motor in a clockwise direction.
 *
 * 				@details
 * 						- Activates the enable pin.
 * 						- Sets one control pin low and the other high to rotate the motor clockwise.
 *
 * 				@param EN: The enable pin.
 * 				@param x: First control pin (IN1 or IN3).
 * 				@param y: Second control pin (IN2 or IN4).
 *
 *	____________________________________________________________________________________

 *	H_BRIDGE_L293_Motor_CCW(u8_t EN, u8_t x, u8_t y):
 * 				@brief	Rotate the motor in a counterclockwise direction.
 *
 * 				@details
 * 						- Activates the enable pin.
 * 						- Sets one control pin high and the other low to rotate the motor counterclockwise.
 *
 * 				@param EN: The enable pin.
 * 				@param x: First control pin (IN1 or IN3).
 * 				@param y: Second control pin (IN2 or IN4).
 *
 *	____________________________________________________________________________________

 *	H_BRIDGE_L293_Motor_FastStop(u8_t EN, u8_t x, u8_t y):
 * 				@brief	Stop the motor quickly.
 *
 * 				@details
 * 						- Activates the enable pin.
 * 						- Sets both control pins low to brake the motor.
 *
 * 				@param EN: The enable pin.
 * 				@param x: First control pin (IN1 or IN3).
 * 				@param y: Second control pin (IN2 or IN4).
 *
 *	____________________________________________________________________________________

 *	H_BRIDGE_L293_Motor_FreeStop(u8_t EN):
 * 				@brief	Stop the motor freely (without braking).
 *
 * 				@details
 * 						- Deactivates the enable pin to allow the motor to coast to a stop.
 *
 * 				@param EN: The enable pin.
 *
 *	____________________________________________________________________________________

 */


#endif /* HAL_H_BRIDGE_L293_H_BRIDGE_H_ */
