/*
 * PIN_CONFIG.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef LIB_PIN_CONFIG_H_
#define LIB_PIN_CONFIG_H_

#include "../MCAL/DIO/DIO.h"

/*
 *
 * This file contains the definitions for the unique pins on the ATmega32 microcontroller.
 * Each pin is assigned a specific function beyond its basic I/O capability, such as analog-to-digital conversion (ADC),
 * timer output compare, or other specialized functions. These alternate function names (e.g., ADC0, T0, OC1A)
 * are used throughout the project to ensure consistency and clarity.
 *
 */

  /******************************************************************/
 /***************************** PORT A *****************************/
/******************************************************************/

/* Pins */
#define	ADC0		PIN_0
#define	ADC1		PIN_1
#define	ADC2		PIN_2
#define	ADC3		PIN_3
#define	ADC4		PIN_4
#define	ADC5		PIN_5
#define	ADC6		PIN_6
#define	ADC7		PIN_7

/* Port */
/*
 * NOTE:
 * 		All ADC pins are on PORT A, and it only contains ADC pins, so no need to define the port for each pin.
 *		The name is just "ADC_PORT"
 */
#define ADC_PORT	PORT_A


  /******************************************************************/
 /***************************** PORT B *****************************/
/******************************************************************/

/* Pins */
#define	XCK			PIN_0
#define	T0			PIN_0
#define	T1			PIN_1
#define	INT2		PIN_2
#define	AIN0		PIN_2
#define	OC0			PIN_3
#define	AIN1		PIN_3
#define	SS			PIN_4
#define	MOSI		PIN_5
#define	MISO		PIN_6
#define	SCK			PIN_7

/* Port */
#define	XCK_PORT	PORT_B
#define	T0_PORT		PORT_B
#define	T1_PORT		PORT_B
#define	INT2_PORT	PORT_B
#define	AIN0_PORT	PORT_B
#define	OC0_PORT	PORT_B
#define	AIN1_PORT	PORT_B
#define	SS_PORT		PORT_B
#define	MOSI_PORT	PORT_B
#define	MISO_PORT	PORT_B
#define	SCK_PORT	PORT_B


  /******************************************************************/
 /***************************** PORT C *****************************/
/******************************************************************/

/* Pins */
#define	SCL		PIN_0
#define	SDA		PIN_1
#define	TCK		PIN_2
#define	TMS		PIN_3
#define	TDO		PIN_4
#define	TDI		PIN_5
#define	TOSC1	PIN_6
#define	TOSC2	PIN_7

/* Port */
#define	SCL_PORT	PORT_C
#define	SDA_PORT	PORT_C
#define	TCK_PORT	PORT_C
#define	TMS_PORT	PORT_C
#define	TDO_PORT	PORT_C
#define	TDI_PORT	PORT_C
#define	TOSC1_PORT	PORT_C
#define	TOSC2_PORT	PORT_C


  /******************************************************************/
 /***************************** PORT D *****************************/
/******************************************************************/
/* Pins */
#define	RXD		PIN_0
#define	TXD		PIN_1
#define	INT0	PIN_2
#define	INT1	PIN_3
#define	OC1B	PIN_4
#define	OC1A	PIN_5
#define	ICP		PIN_6
#define	OC2		PIN_7

/* Port */
#define	RXD_PORT	PORT_D
#define	TXD_PORT	PORT_D
#define	INT0_PORT	PORT_D
#define	INT1_PORT	PORT_D
#define	OC1B_PORT	PORT_D
#define	OC1A_PORT	PORT_D
#define	ICP_PORT	PORT_D
#define	OC2_PORT	PORT_D


#endif /* LIB_PIN_CONFIG_H_ */
