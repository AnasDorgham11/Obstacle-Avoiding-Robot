/*
 * DIO.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_


/* Registers Definition */
#define PORTA	(*(volatile u8_t*)0x3B)
#define DDRA	(*(volatile u8_t*)0x3A)
#define PINA	(*(volatile u8_t*)0x39)

#define PORTB	(*(volatile u8_t*)0x38)
#define DDRB	(*(volatile u8_t*)0x37)
#define PINB	(*(volatile u8_t*)0x36)

#define PORTC	(*(volatile u8_t*)0x35)
#define DDRC	(*(volatile u8_t*)0x34)
#define PINC	(*(volatile u8_t*)0x33)

#define PORTD	(*(volatile u8_t*)0x32)
#define DDRD	(*(volatile u8_t*)0x31)
#define PIND	(*(volatile u8_t*)0x30)


  /******************************************************************/
 /***************************** Ports ******************************/
/******************************************************************/

/* Ports */
#define PORT_A   0
#define PORT_B   1
#define PORT_C   2
#define PORT_D   3

/* Port - Direction */
#define PORT_INPUT 		0x00		// 0x00 = 0b00000000
#define PORT_OUTPUT		0xff 	 	// 0xff = 0b11111111

/* Port - Value */
#define PORT_LOW    	0x00		// 0x00 = 0b00000000
#define PORT_HIGH   	0xff		// 0xff = 0b11111111


/********************************\
*********** Functions ************
\********************************/

/* Dealing with the whole port */
void DIO_SetPortDirection(u8_t port, u8_t direction);
void DIO_SetPortValue(u8_t port, u8_t value);
void DIO_TogglePort(u8_t port);
u8_t DIO_GetPortValue(u8_t port);


/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'
 *	DIO_SetPortDirection(u8_t port, u8_t direction):
 * 				@brief	Set the direction of a whole port.
 *
 * 				@param port		: The port whose direction is to be set (PORT_A, PORT_B, PORT_C, or PORT_D)
 * 				@param direction: The direction of the port (PORT_INPUT, PORT_OUTPUT, or any value between them).
 *
 *	____________________________________________________________________________________
 *
 *	DIO_SetPortValue(u8_t port, u8_t value):
 * 				@brief	Set the value of a whole port.
 *
 * 				@param port		: The port whose value is to be set (PORT_A, PORT_B, PORT_C, or PORT_D)
 * 				@param value	: The value of the port (PORT_LOW, PORT_HIGH, or any value between them).
 *
 *	____________________________________________________________________________________
 *
 *	DIO_TogglePort(u8_t port):
 * 				@brief	Toggle the value of a whole port.
 *
 *				@param port		: The port whose value is to be toggled (PORT_A, PORT_B, PORT_C, or PORT_D)
 *
 *	____________________________________________________________________________________
 *
 *	DIO_GetPortValue(u8_t port):
 * 				@brief	Get (Read) the value of a whole port.
 *
 *				@param port		: The port whose value is to be get (PORT_A, PORT_B, PORT_C, or PORT_D)
 *
 *				@return u8_t
 *
 *	____________________________________________________________________________________

 */


  /******************************************************************/
 /****************************** Pins ******************************/
/******************************************************************/

/* Pins */
#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7

/* Pin - Directions */
#define PIN_INPUT 		0
#define PIN_OUTPUT		1

/* Pin - Values */
#define PIN_LOW    		0
#define PIN_HIGH   		1
#define PIN_TOGGLE 		2


/********************************\
*********** Functions ************
\********************************/

/* Dealing with pins */
void DIO_SetPinDirection(u8_t port, u8_t pin, u8_t direction);
void DIO_SetPinValue(u8_t port, u8_t pin, u8_t value);
u8_t DIO_GetPinValue(u8_t port, u8_t pin);
void DIO_EnablePinPullup(u8_t port, u8_t pin);


/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'
 *	DIO_SetPinDirection(u8_t port, u8_t pin, u8_t direction):
 * 				@brief	Set the direction of a pin.
 *
 * 				@param port		: The port containing the pin (PORT_A, PORT_B, PORT_C, or PORT_D).
 * 				@param pin		: The pin whose direction is to be set (PIN_0, PIN_1,..., PIN_6, or PIN_7).
 * 				@param direction: The direction of the port (PIN_INPUT or PIN_OUTPUT).
 *
 *	____________________________________________________________________________________
 *
 *	DIO_SetPinValue(u8_t port, u8_t pin, u8_t value):
 * 				@brief	Set the value of a pin.
 *
 * 				@param port		: The port containing the pin (PORT_A, PORT_B, PORT_C, or PORT_D).
 * 				@param pin		: The pin whose value is to be set (PIN_0, PIN_1,..., PIN_6, or PIN_7).
 * 				@param value	: The value of the pin (PIN_LOW, PIN_HIGH, or PIN_TOGGLE).
 *
 *	____________________________________________________________________________________
 *
 *	DIO_GetPinValue(u8_t port, u8_t pin):
 * 				@brief	Get (Read) the value of a pin in the case it is input.
 *
 *				@param port		: The port containing the pin (PORT_A, PORT_B, PORT_C, or PORT_D)
 *				@param pin		: The pin whose value is to be get (PIN_0, PIN_1,..., PIN_6, or PIN_7).
 *
 *				@return u8_t
 *
 *	____________________________________________________________________________________
 *
 *	DIO_EnablePinPullup(u8_t port, u8_t pin):
 * 				@brief	Enable the feature of pull-up resistor in a pin.
 *
 * 				@details
 * 						- Pull-up prevents the floating pin problem.
 * 						- When the input component connected to the pin is pressed, the input voltage becomes 0V (Ground).
 * 						- Otherwise, the input voltage is always high (not 0).
 *						- Instead of installing pull-up resistor by hardware, each pin in the MCU is connected to a pull-up resistor inside.
 *						- To enable the pull-up resistor, set the pin in the PORT register as high although it is input.
 *
 * 				@param port		: The port containing the pin (PORT_A, PORT_B, PORT_C, or PORT_D).
 * 				@param pin		: The pin to enable pull-up resistor for (PIN_0, PIN_1,..., PIN_6, or PIN_7).
 *
 *	____________________________________________________________________________________
 *
 */


#endif /* MCAL_DIO_DIO_H_ */
