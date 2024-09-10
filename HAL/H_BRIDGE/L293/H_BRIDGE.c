/*
 * H_BRIDGE.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
#include "../../../MCAL/DIO/DIO.h"
#include "../../../MCAL/TIMER/TIMER.h"
#include "../../../HAL/LCD/LCD.h"
#include "H_BRIDGE.h"

void H_BRIDGE_L293_Motor_Init(u8_t EN, u8_t x, u8_t y){
	DIO_SetPinDirection(H_bridge_EN_PORT, EN, PIN_OUTPUT);
	DIO_SetPinDirection(H_bridge_A_PORT, x, PIN_OUTPUT);
	DIO_SetPinDirection(H_bridge_A_PORT, y, PIN_OUTPUT);
}
void H_BRIDGE_L293_Motor_CW(u8_t EN, u8_t x, u8_t y){
	DIO_SetPinValue(H_bridge_EN_PORT, EN, PIN_HIGH);
	DIO_SetPinValue(H_bridge_A_PORT, x, PIN_LOW);
	DIO_SetPinValue(H_bridge_A_PORT, y, PIN_HIGH);
}

void H_BRIDGE_L293_Motor_CCW(u8_t EN, u8_t x, u8_t y){
	DIO_SetPinValue(H_bridge_EN_PORT, EN, PIN_HIGH);
	DIO_SetPinValue(H_bridge_A_PORT, x, PIN_HIGH);
	DIO_SetPinValue(H_bridge_A_PORT, y, PIN_LOW);
}

void H_BRIDGE_L293_Motor_FastStop(u8_t EN, u8_t x, u8_t y){
	DIO_SetPinValue(H_bridge_EN_PORT, EN, PIN_HIGH);
	DIO_SetPinValue(H_bridge_A_PORT, x, PIN_LOW);
	DIO_SetPinValue(H_bridge_A_PORT, y, PIN_LOW);
}

// This function takes the enabler as the only argument, since if it is low, the motor does free stop.
void H_BRIDGE_L293_Motor_FreeStop(u8_t EN){
	DIO_SetPinValue(H_bridge_EN_PORT, EN, PIN_LOW);
}
