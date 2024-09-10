/*
 * DIO.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO.h"



/********************************\
*********** Functions ************
\********************************/

  /******************************************************************/
 /***************************** Ports ******************************/
/******************************************************************/

/* Dealing with the whole port */
void DIO_SetPortDirection(u8_t port, u8_t direction){
	switch (port){
	case PORT_A:
		DDRA = direction;
		break;
	case PORT_B:
		DDRB = direction;
		break;
	case PORT_C:
		DDRC = direction;
		break;
	case PORT_D:
		DDRD = direction;
		break;
	}
}

void DIO_SetPortValue(u8_t port, u8_t value){
	switch (port){
	case PORT_A:
		PORTA = value;
		break;
	case PORT_B:
		PORTB = value;
		break;
	case PORT_C:
		PORTC = value;
		break;
	case PORT_D:
		PORTD = value;
		break;
	}
}

void DIO_TogglePort(u8_t port){
	switch (port){
	case PORT_A:
		PORTA ^= PORT_HIGH;
		break;
	case PORT_B:
		PORTB ^= PORT_HIGH;
		break;
	case PORT_C:
		PORTC ^= PORT_HIGH;
		break;
	case PORT_D:
		PORTD ^= PORT_HIGH;
		break;
	}
}

u8_t DIO_GetPortValue(u8_t port){
	u8_t get_port;
	switch(port){
	case PORT_A:
		get_port = PORTA;
		break;
	case PORT_B:
		get_port = PORTB;
		break;
	case PORT_C:
		get_port = PORTC;
		break;
	case PORT_D:
		get_port = PORTD;
		break;
	}
	return get_port;
}


/******************************************************************/
/****************************** Pins ******************************/
/******************************************************************/

/* Dealing with pins */
void DIO_SetPinDirection(u8_t port, u8_t pin, u8_t direction){
	switch (direction){
	case PIN_INPUT:
		switch (port){
		case PORT_A:
			CLEAR_BIT(DDRA, pin);
			break;
		case PORT_B:
			CLEAR_BIT(DDRB, pin);
			break;
		case PORT_C:
			CLEAR_BIT(DDRC, pin);
			break;
		case PORT_D:
			CLEAR_BIT(DDRD, pin);
			break;
		}
		break;
		case PIN_OUTPUT:
			switch (port){
			case PORT_A:
				SET_BIT(DDRA, pin);
				break;
			case PORT_B:
				SET_BIT(DDRB, pin);
				break;
			case PORT_C:
				SET_BIT(DDRC, pin);
				break;
			case PORT_D:
				SET_BIT(DDRD, pin);
				break;
			}
	}
}

void DIO_SetPinValue(u8_t port, u8_t pin, u8_t value){
	switch (value){
	case PIN_LOW:
		switch (port){
		case PORT_A:
			CLEAR_BIT(PORTA, pin);
			break;
		case PORT_B:
			CLEAR_BIT(PORTB, pin);
			break;
		case PORT_C:
			CLEAR_BIT(PORTC, pin);
			break;
		case PORT_D:
			CLEAR_BIT(PORTD, pin);
			break;
		}
		break;
	case PIN_HIGH:
		switch (port){
		case PORT_A:
			SET_BIT(PORTA, pin);
			break;
		case PORT_B:
			SET_BIT(PORTB, pin);
			break;
		case PORT_C:
			SET_BIT(PORTC, pin);
			break;
		case PORT_D:
			SET_BIT(PORTD, pin);
			break;
		}
		break;
	case PIN_TOGGLE:
		switch (port){
		case PORT_A:
			TOG_BIT(PORTA, pin);
			break;
		case PORT_B:
			TOG_BIT(PORTB, pin);
			break;
		case PORT_C:
			TOG_BIT(PORTC, pin);
			break;
		case PORT_D:
			TOG_BIT(PORTD, pin);
			break;
		}
	}
}

u8_t DIO_GetPinValue(u8_t port, u8_t pin){
	u8_t get_pin;
	switch(port){
	case PORT_A:
		get_pin = GET_BIT(PINA, pin);
		break;
	case PORT_B:
		get_pin = GET_BIT(PINB, pin);
		break;
	case PORT_C:
		get_pin = GET_BIT(PINC, pin);
		break;
	case PORT_D:
		get_pin = GET_BIT(PIND, pin);
		break;
	}
	return get_pin;
}

void DIO_EnablePinPullup(u8_t port, u8_t pin){
	switch (port){
	case PORT_A:
		SET_BIT(PORTA, pin);
		break;
	case PORT_B:
		SET_BIT(PORTB, pin);
		break;
	case PORT_C:
		SET_BIT(PORTC, pin);
		break;
	case PORT_D:
		SET_BIT(PORTD, pin);
		break;
	}
}



