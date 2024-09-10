/*
 * MOVEMENT.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef HAL_CAR_MOVEMENT_MOVEMENT_H_
#define HAL_CAR_MOVEMENT_MOVEMENT_H_

typedef enum{
	CAR_DC_MOTORS_SAME_SPEED,
	CAR_DC_MOTORS_DIFFERENT_SPEEDS
} CAR_motors_speed_mode;

typedef enum{
	CAR_FORWARD,
	CAR_BACKWARD,
	CAR_RIGHT,
	CAR_LEFT
} CAR_directions;

void CAR_MOVEMENT_Motors_Init(CAR_motors_speed_mode mode);
void CAR_MOVEMENT_Low(void);
void CAR_MOVEMENT_Motor1_Low(void);
void CAR_MOVEMENT_Motor2_Low(void);
void CAR_MOVEMENT_Stop(void);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	CAR_MOVEMENT_Motors_Init(CAR_motors_speed_mode mode):
 * 				@brief	Initialize the motors for the car.
 *
 * 				@details
 * 						- Sets up the H-Bridge motor control pins and assigns the speed mode for the motors.
 *
 * 				@param mode: The speed mode for the car's DC motors (same or different speeds).
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Low(void):
 * 				@brief	Stop both DC motors quickly.
 *
 * 				@details
 * 						- Sets both motor control pins to fast stop mode.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor1_Low(void):
 * 				@brief	Stop motor 1 quickly.
 *
 * 				@details
 * 						- Sets the control pins for motor 1 to fast stop mode.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor2_Low(void):
 * 				@brief	Stop motor 2 quickly.
 *
 * 				@details
 * 						- Sets the control pins for motor 2 to fast stop mode.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Stop(void):
 * 				@brief	Stop the car's movement.
 *
 * 				@details
 * 						- Stops Timer2 and disables its interrupts.
 * 						- If using different speeds, stops also Timer1 and disables its interrupts.
 * 						- Calls CAR_MOVEMENT_Low() to stop both motors.
 *
 *	____________________________________________________________________________________

 */

  /******************************************************************/
 /***************************** Speed ******************************/
/******************************************************************/

 /* Controlling motors having the same speed */
void CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(double speed);
void CAR_MOVEMENT_SameSpeed_SetDefaultSpeedPercentage(double speed);
void CAR_MOVEMENT_SameSpeed_SetDirection_SetSpeedPercentage(CAR_directions direction, double speed_percentage);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	CAR_MOVEMENT_SameSpeed_SetSpeedPercentage(double speed):
 * 				@brief	Set the speed percentage for both motors when running at the same speed.
 *
 * 				@details
 * 						- Configures Timer2 for PWM to control the speed of both motors.
 * 						- Adjusts the speed based on the given percentage.
 *
 * 				@param speed: Desired speed percentage (0 to 100%).
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_SameSpeed_SetDefaultSpeedPercentage(double speed):
 * 				@brief	Set the default speed percentage for both motors when running at the same speed.
 *
 * 				@details
 * 						- Updates the default speed percentage used when no specific speed is set.
 *
 * 				@param speed: Default speed percentage (0 to 100%).
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_SameSpeed_SetDirection_SetSpeedPercentage(CAR_directions direction, double speed):
 * 				@brief	Set the direction and speed for both motors when running at the same speed.
 *
 * 				@details
 * 						- Configures Timer2 callbacks based on the direction.
 * 						- Sets the speed using the specified percentage.
 *
 * 				@param direction: Direction of movement (forward, backward, right, left).
 * 				@param speed: Desired speed percentage (0 to 100%).
 *
 *	____________________________________________________________________________________

 */

/* Controlling motors having different speeds */
void CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(double motor1_speed, double motor2_speed);
void CAR_MOVEMENT_DifferentSpeeds_SetDefaultSpeedPercentages(double motor1_speed, double motor2_speed);
void CAR_MOVEMENT_DifferentSpeeds_SetDirection_SetSpeedPercentages(CAR_directions direction, double motor1_speed, double motor2_speed);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	CAR_MOVEMENT_DifferentSpeeds_SetSpeedPercentages(double motor1_speed, double motor2_speed):
 * 				@brief	Set different speed percentages for each motor.
 *
 * 				@details
 * 						- Configures Timer1 and Timer2 for PWM to control the speed of each motor separately.
 * 						- Sets the top values for Timer1 and Timer2 to handle 8-bit PWM.
 *
 * 				@param motor1_speed: Speed percentage for motor 1 (0 to 100%).
 * 				@param motor2_speed: Speed percentage for motor 2 (0 to 100%).
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_DifferentSpeeds_SetDefaultSpeedPercentages(double motor1_speed, double motor2_speed):
 * 				@brief	Set the default speed percentages for each motor when using different speeds.
 *
 * 				@details
 * 						- Updates the default speed for each motor.
 *
 * 				@param motor1_speed: Default speed percentage for motor 1 (0 to 100%).
 * 				@param motor2_speed: Default speed percentage for motor 2 (0 to 100%).
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_DifferentSpeeds_SetDirection_SetSpeedPercentages(CAR_directions direction, double motor1_speed, double motor2_speed):
 * 				@brief	Set the direction and speed for each motor when running at different speeds.
 *
 * 				@details
 * 						- Configures Timer1 and Timer2 callbacks based on the direction.
 * 						- Sets the speed for each motor using the specified percentages.
 *
 * 				@param direction: Direction of movement (forward, backward, right, left).
 * 				@param motor1_speed: Speed percentage for motor 1 (0 to 100%).
 * 				@param motor2_speed: Speed percentage for motor 2 (0 to 100%).
 *
 *	____________________________________________________________________________________

 */

  /******************************************************************/
 /*************************** Direction ****************************/
/******************************************************************/

void CAR_MOVEMENT_Forward(void);
void CAR_MOVEMENT_Backward(void);
void CAR_MOVEMENT_Right(void);
void CAR_MOVEMENT_Left(void);
void CAR_MOVEMENT_Forward_FullSpeed(void);
void CAR_MOVEMENT_Backward_FullSpeed(void);
void CAR_MOVEMENT_Right_FullSpeed(void);
void CAR_MOVEMENT_Left_FullSpeed(void);
void CAR_MOVEMENT_Motor1_Forward_FullSpeed(void);
void CAR_MOVEMENT_Motor1_Backward_FullSpeed(void);
void CAR_MOVEMENT_Motor1_Right_FullSpeed(void);
void CAR_MOVEMENT_Motor1_Left_FullSpeed(void);
void CAR_MOVEMENT_Motor2_Forward_FullSpeed(void);
void CAR_MOVEMENT_Motor2_Backward_FullSpeed(void);
void CAR_MOVEMENT_Motor2_Right_FullSpeed(void);
void CAR_MOVEMENT_Motor2_Left_FullSpeed(void);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	CAR_MOVEMENT_Forward(void):
 * 				@brief	Move the car forward.
 *
 * 				@details
 * 						- Sets the PWM callbacks for Timer1 and Timer2 based on the speed mode and direction.
 * 						- Calls the appropriate function to move the car forward.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Backward(void):
 * 				@brief	Move the car backward.
 *
 * 				@details
 * 						- Sets the PWM callbacks for Timer1 and Timer2 based on the speed mode and direction.
 * 						- Calls the appropriate function to move the car backward.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Right(void):
 * 				@brief	Move the car to the right.
 *
 * 				@details
 * 						- Sets the PWM callbacks for Timer1 and Timer2 based on the speed mode and direction.
 * 						- Calls the appropriate function to turn the car right.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Left(void):
 * 				@brief	Move the car to the left.
 *
 * 				@details
 * 						- Sets the PWM callbacks for Timer1 and Timer2 based on the speed mode and direction.
 * 						- Calls the appropriate function to turn the car left.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Forward_FullSpeed(void):
 * 				@brief	Move the car forward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 clockwise and motor 2 counterclockwise for forward movement.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Backward_FullSpeed(void):
 * 				@brief	Move the car backward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 counterclockwise and motor 2 clockwise for backward movement.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Right_FullSpeed(void):
 * 				@brief	Move the car right at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate both motors counterclockwise for a right turn.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Left_FullSpeed(void):
 * 				@brief	Move the car left at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate both motors clockwise for a left turn.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor1_Forward_FullSpeed(void):
 * 				@brief	Move motor 1 forward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 clockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor1_Backward_FullSpeed(void):
 * 				@brief	Move motor 1 backward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 counterclockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor1_Right_FullSpeed(void):
 * 				@brief	Move motor 1 right at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 counterclockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor1_Left_FullSpeed(void):
 * 				@brief	Move motor 1 left at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 1 clockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor2_Forward_FullSpeed(void):
 * 				@brief	Move motor 2 forward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 2 counterclockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor2_Backward_FullSpeed(void):
 * 				@brief	Move motor 2 backward at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 2 clockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor2_Right_FullSpeed(void):
 * 				@brief	Move motor 2 right at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 2 counterclockwise.
 *
 *	____________________________________________________________________________________

 *	CAR_MOVEMENT_Motor2_Left_FullSpeed(void):
 * 				@brief	Move motor 2 left at full speed.
 *
 * 				@details
 * 						- Configures the H-Bridge to rotate motor 2 clockwise.
 *
 *	____________________________________________________________________________________

 */


#endif /* HAL_CAR_MOVEMENT_MOVEMENT_H_ */
