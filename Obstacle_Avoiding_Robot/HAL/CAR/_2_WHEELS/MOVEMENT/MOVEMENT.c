/*
 * MOVEMENT.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */
#include "../../../../LIB/STD_TYPES.h"
#include "../../../../LIB/BIT_MATH.h"
#include "../../../../MCAL/DIO/DIO.h"
#include "../../../../MCAL/TIMER/TIMER.h"
#include "../../../../HAL/LCD/LCD.h"
#include "../../../H_BRIDGE/L293/H_BRIDGE.h"
#include "MOVEMENT.h"

/* Variables */
u8_t DC_motors_speed_mode;
u8_t DC_motors_default_speed = 60;					// Initialize the default speed for both motors as 60%.
u8_t DC_motor1_default_speed = 60;					// Initialize the default speed for motor 1 as 60%.
u8_t DC_motor2_default_speed = 60;					// Initialize the default speed for motor 2 as 60%.


/********************************\
*********** Functions ************
\********************************/

void CAR_MOVEMENT_Motors_Init(CAR_motors_speed_mode mode){
	H_BRIDGE_L293_Motor_Init(H_EN1,H_A1,H_A2);
	H_BRIDGE_L293_Motor_Init(H_EN2,H_A3,H_A4);
	DC_motors_speed_mode = mode;
}

void CAR_MOVEMENT_Low(void){
	H_BRIDGE_L293_Motor_FastStop(H_EN1, H_A1, H_A2);
	H_BRIDGE_L293_Motor_FastStop(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Motor1_Low(void){
	H_BRIDGE_L293_Motor_FastStop(H_EN1, H_A1, H_A2);
}

void CAR_MOVEMENT_Motor2_Low(void){
	H_BRIDGE_L293_Motor_FastStop(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Stop(void){
	TIMER_Timer2_Stop();
	TIMER_Timer2_OC_DisableInterrupt();
	TIMER_Timer2_OV_DisableInterrupt();
	if (DC_motors_speed_mode == CAR_DC_MOTORS_DIFFERENT_SPEEDS){
		TIMER_Timer1_Stop();
		TIMER_Timer1_OCA_DisableInterrupt();
		TIMER_Timer1_IC_DisableInterrupt();
	}
	CAR_MOVEMENT_Low();
}


  /******************************************************************/
 /***************************** Speed ******************************/
/******************************************************************/

/* Controlling motors having the same speed */
void CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(double speed){
	OCR2 = (u8_t) ((speed * 256) / 100) - 1;
	TIMER_Timer2_OC_EnableInterrupt();
	TIMER_Timer2_OV_EnableInterrupt();
	TIMER_Timer2_Init(TIMER2_FAST_PWM, TIMER2_PRESCALER_64);
}

void CAR_MOVEMENT_SameSpeed_SetDefaultSpeedPercentage(double speed){
	DC_motors_default_speed = speed;
}

void CAR_MOVEMENT_SameSpeed_SetDirection_SetSpeedPercentage(CAR_directions direction, double speed){
	switch (direction){
	case CAR_FORWARD:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Forward_FullSpeed);
		break;
	case CAR_BACKWARD:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Backward_FullSpeed);
		break;
	case CAR_RIGHT:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Right_FullSpeed);
		break;
	case CAR_LEFT:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Left_FullSpeed);
		break;
	}
	CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(speed);
}

/* Controlling motors having different speeds */

void CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(double motor1_speed, double motor2_speed){
	TIMER_Timer1_ICR1_Set(255);											// Setting the top of Timer1 (ICR1) as 255 to be like Timer2 which is only 8-bits counter.
	TIMER_Timer1_OCR1A_Set((u8_t) ((motor1_speed * 256) / 100) - 1);
	TIMER_Timer2_OCR2_Set((u8_t) ((motor2_speed * 256) / 100) - 1);
	TIMER_Timer1_OCA_EnableInterrupt();
	TIMER_Timer1_IC_EnableInterrupt();
	TIMER_Timer2_OC_EnableInterrupt();
	TIMER_Timer2_OV_EnableInterrupt();
	TIMER_Timer1_Init(TIMER1_FAST_PWM_ICR1, TIMER1_PRESCALER_64);
	TIMER_Timer2_Init(TIMER2_FAST_PWM, TIMER2_PRESCALER_64);
}

void CAR_MOVEMENT_DifferentSpeeds_SetDefaultSpeedPercentages(double motor1_speed, double motor2_speed){
	DC_motor1_default_speed = motor1_speed;
	DC_motor2_default_speed = motor2_speed;
}

void CAR_MOVEMENT_DifferentSpeeds_SetDirection_SetSpeedPercentages(CAR_directions direction, double motor1_speed, double motor2_speed){
	switch (direction){
	case CAR_FORWARD:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Forward_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Forward_FullSpeed);
		break;
	case CAR_BACKWARD:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Backward_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Backward_FullSpeed);
		break;
	case CAR_RIGHT:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Right_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Right_FullSpeed);
		break;
	case CAR_LEFT:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Left_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Left_FullSpeed);
		break;
	}
	CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(motor1_speed, motor2_speed);
}


  /******************************************************************/
 /*************************** Direction ****************************/
/******************************************************************/

void CAR_MOVEMENT_Forward(void){
	switch (DC_motors_speed_mode){
	case CAR_DC_MOTORS_SAME_SPEED:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Forward_FullSpeed);
		CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(DC_motors_default_speed);
		break;
	case CAR_DC_MOTORS_DIFFERENT_SPEEDS:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Motor1_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Motor1_Forward_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Motor2_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Motor2_Forward_FullSpeed);
		CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(DC_motor1_default_speed, DC_motor2_default_speed);
		break;
	}
}

void CAR_MOVEMENT_Backward(void){
	switch (DC_motors_speed_mode){
	case CAR_DC_MOTORS_SAME_SPEED:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Backward_FullSpeed);
		CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(DC_motors_default_speed);
		break;
	case CAR_DC_MOTORS_DIFFERENT_SPEEDS:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Motor1_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Motor1_Backward_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Motor2_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Motor2_Backward_FullSpeed);
		CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(DC_motor1_default_speed, DC_motor2_default_speed);
		break;
	}
}

void CAR_MOVEMENT_Right(void){
	switch (DC_motors_speed_mode){
	case CAR_DC_MOTORS_SAME_SPEED:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Right_FullSpeed);
		CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(DC_motors_default_speed);
		break;
	case CAR_DC_MOTORS_DIFFERENT_SPEEDS:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Motor1_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Motor1_Right_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Motor2_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Motor2_Right_FullSpeed);
		CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(DC_motor1_default_speed, DC_motor2_default_speed);
		break;
	}
}

void CAR_MOVEMENT_Left(void){
	switch (DC_motors_speed_mode){
	case CAR_DC_MOTORS_SAME_SPEED:
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Left_FullSpeed);
		CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(DC_motors_default_speed);
		break;
	case CAR_DC_MOTORS_DIFFERENT_SPEEDS:
		TIMER_Timer1_OCA_SetCallBack(CAR_MOVEMENT_Motor1_Low);
		TIMER_Timer1_IC_SetCallBack(CAR_MOVEMENT_Motor1_Left_FullSpeed);
		TIMER_Timer2_OC_SetCallBack(CAR_MOVEMENT_Motor2_Low);
		TIMER_Timer2_OV_SetCallBack(CAR_MOVEMENT_Motor2_Left_FullSpeed);
		CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(DC_motor1_default_speed, DC_motor2_default_speed);
		break;
	}
}

void CAR_MOVEMENT_Forward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN1, H_A1, H_A2);
	H_BRIDGE_L293_Motor_CCW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Backward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN1, H_A1, H_A2);
	H_BRIDGE_L293_Motor_CW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Right_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN1, H_A1, H_A2);
	H_BRIDGE_L293_Motor_CCW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Left_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN1, H_A1, H_A2);
	H_BRIDGE_L293_Motor_CW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Motor1_Forward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN1, H_A1, H_A2);
}

void CAR_MOVEMENT_Motor1_Backward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN1, H_A1, H_A2);
}

void CAR_MOVEMENT_Motor1_Right_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN1, H_A1, H_A2);
}

void CAR_MOVEMENT_Motor1_Left_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN1, H_A1, H_A2);
}

void CAR_MOVEMENT_Motor2_Forward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Motor2_Backward_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Motor2_Right_FullSpeed(void){
	H_BRIDGE_L293_Motor_CCW(H_EN2, H_A3, H_A4);
}

void CAR_MOVEMENT_Motor2_Left_FullSpeed(void){
	H_BRIDGE_L293_Motor_CW(H_EN2, H_A3, H_A4);
}
