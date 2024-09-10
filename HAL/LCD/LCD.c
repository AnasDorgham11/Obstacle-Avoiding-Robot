/*
 * LCD.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include <avr/delay.h>
#include "LCD.h"

/* Variables */
u8_t mode_of_operation;


/********************************\
*********** Functions ************
\********************************/

void LCD_Init(LCD_modes_of_operation mode){
	mode_of_operation = mode;						// Mode is saved in a variable.
	DIO_SetPinDirection(Control_Port, E, PIN_OUTPUT);
	DIO_SetPinDirection(Control_Port, RS, PIN_OUTPUT);
	DIO_SetPinDirection(Control_Port, RW, PIN_OUTPUT);
	switch (mode){
	case _4bits:									// When dealing with 4 bits, only 4 pins are output.
		DIO_SetPinDirection(Data_Port, D4, PIN_OUTPUT);
		DIO_SetPinDirection(Data_Port, D5, PIN_OUTPUT);
		DIO_SetPinDirection(Data_Port, D6, PIN_OUTPUT);
		DIO_SetPinDirection(Data_Port, D7, PIN_OUTPUT);
		break;

	case _8bits:
		DIO_SetPortDirection(Data_Port, PORT_OUTPUT);// When dealing with 8 bits, the whole port is output.
		break;
	}
	_delay_ms(50);
	LCD_ReturnHome();
	LCD_EntryModeSet(INCREMENT,SHIFT_OFF);							// Increment the addresses 1 when writing into or reading from them. No display shifting.
	LCD_DisplayControl(DISPLAY_ON, CURSOR_OFF, CURSOR_BLINK_OFF);	// Display is on. No cursor. No cursor blinking (when needed).
	LCD_FunctionSet(mode, _2_LINES, _5x8_DOTS);					// Mode is taken as an argument. 2 lines mode. 5*10 dots.
	LCD_Clear();
}

void LCD_SendInstruction(u8_t instruction){
	DIO_SetPinValue(Control_Port, RS, PIN_LOW);
	DIO_SetPinValue(Control_Port, RW, PIN_LOW);
	switch (mode_of_operation){
	case _4bits:
		/* Sending the upper nibble */
		DIO_SetPinValue(Data_Port, D7, GET_BIT(instruction, 7));
		DIO_SetPinValue(Data_Port, D6, GET_BIT(instruction, 6));
		DIO_SetPinValue(Data_Port, D5, GET_BIT(instruction, 5));
		DIO_SetPinValue(Data_Port, D4, GET_BIT(instruction, 4));
		LCD_EnablePulse();
		LCD_DisablePulse();
		_delay_ms(100);
		/* Sending the lower nibble */
		DIO_SetPinValue(Data_Port, D7, GET_BIT(instruction, 3));
		DIO_SetPinValue(Data_Port, D6, GET_BIT(instruction, 2));
		DIO_SetPinValue(Data_Port, D5, GET_BIT(instruction, 1));
		DIO_SetPinValue(Data_Port, D4, GET_BIT(instruction, 0));
		LCD_EnablePulse();
		LCD_DisablePulse();
		break;

	case _8bits:
		/* Sending the whole instruction in one stage */
		LCD_EnablePulse();
		DIO_SetPortValue(Data_Port, instruction);
		LCD_DisablePulse();
		break;
	}
	_delay_us(50);

}

void LCD_SendChar(unsigned char character){
	DIO_SetPinValue(Control_Port, RS, PIN_HIGH);
	DIO_SetPinValue(Control_Port, RW, PIN_LOW);
	switch (mode_of_operation){
	case _4bits:
		/* Sending the upper nibble */
		DIO_SetPinValue(Data_Port, D7, GET_BIT(character, 7));
		DIO_SetPinValue(Data_Port, D6, GET_BIT(character, 6));
		DIO_SetPinValue(Data_Port, D5, GET_BIT(character, 5));
		DIO_SetPinValue(Data_Port, D4, GET_BIT(character, 4));
		LCD_EnablePulse();
		LCD_DisablePulse();
		/* Sending the lower nibble */
		DIO_SetPinValue(Data_Port, D7, GET_BIT(character, 3));
		DIO_SetPinValue(Data_Port, D6, GET_BIT(character, 2));
		DIO_SetPinValue(Data_Port, D5, GET_BIT(character, 1));
		DIO_SetPinValue(Data_Port, D4, GET_BIT(character, 0));
		LCD_EnablePulse();
		LCD_DisablePulse();
		break;
	case _8bits:
		LCD_EnablePulse();
		DIO_SetPortValue(Data_Port, character);
		LCD_DisablePulse();
		break;
	}
}

void LCD_SendString(char* c){
	for (u8_t i = 0; c[i]; i++){	// Iterates until c[i] is false meaning that it is a null operator '\0'
		LCD_SendChar(c[i]);
	}
}

void LCD_SendNumber(double num){
	u32_t truncated = (u32_t) num;
	u8_t counter = 0;
	if (truncated == num){
		u32_t copy_truncated = truncated;
		u8_t int_list [10];
		if (copy_truncated == 0) {
			LCD_SendChar('0');
		}
		while(copy_truncated){
			int_list[counter] = copy_truncated % 10 + '0';
			copy_truncated /= 10;
			counter ++;
		}
		for (u8_t i = counter; i > 0; i--){
			LCD_SendChar(int_list[i-1]);
		}
	}
	else{
		LCD_SendNumber(truncated);
		u8_t fractional_list [4];
		double fractional = num - truncated + 0.00001;
		counter = 0;
		do{
			fractional *= 10;
			truncated = (u8_t) fractional;
			fractional_list[counter] = truncated + '0';
			fractional -= truncated;
			counter ++;
		}
		while(fractional != 0 && counter < 4);
		LCD_SendChar('.');				// Print the decimal point
		while (fractional_list [counter - 1] == '0'){
			counter--;
		}
		for (u8_t i = 0; i < counter; i++){
			LCD_SendChar(fractional_list[i]);
		}
	}
}

void LCD_GoToPosition(LCD_rows row, u8_t col){
	switch (row){
	// Upper row positions ranges from 0x00 (col = 0) to 0x0f (col = 15)
	case UPPER_ROW:
		LCD_SetDDRAMAddress(col);
		break;
	// Upper row positions ranges from 0x40 (col = 0) to 0x4f (col = 15)
	case LOWER_ROW:
		LCD_SetDDRAMAddress(0x40 + col);
		break;
	}
}

void LCD_Clear(void){
	LCD_SendInstruction(1<<D0);
}

void LCD_ReturnHome(void){
	LCD_SendInstruction(1<<D1);
	// The maximum execution time is 1520us for 270KHz f(OSC), So it is converted to match our 16MHz f(OSC).
	_delay_us(1520*(float)(270/16000));
}

void LCD_EntryModeSet(u8_t cursor_move, u8_t display_shift){
	LCD_SendInstruction((1 << D2) | ((1 & cursor_move) << D1) | ((1 & display_shift) << D0));
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_DisplayControl(u8_t display_mode, u8_t cursor_display, u8_t cursor_blink){
	LCD_SendInstruction((1 << D3) | ((1 & display_mode) << D2) | ((1 & cursor_display) << D1) | ((1 & cursor_blink) << D0));
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_CursorOrDisplayShift(u8_t cursor_or_display, u8_t right_or_left){
	LCD_SendInstruction((1 << D4) | ((1 & cursor_or_display) << D3) | ((1 & right_or_left) << D2));
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_FunctionSet(u8_t data_length, u8_t display_lines_num, u8_t char_font){
	LCD_SendInstruction((1 << D5) | ((1 & data_length) << D4) | ((1 & display_lines_num) << D3) | ((1 & char_font) << D2));
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_SetCGRAMAddress(u8_t address){
	address &= 0b00111111; // Address is ANDed with 0b111111 to ensure it is in the range(0:31)
	LCD_SendInstruction((1 << D6) | address);
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_SetDDRAMAddress(u8_t address){
	address &= 0b01111111; // Address is ANDed with 0b111111 to ensure it is in the range(0:63)
	LCD_SendInstruction((1 << D7) | address);
	// The maximum execution time is in nanoseconds for our 16MHz f(OSC), so it could be approximated to be 1us.
	_delay_us(1);
}

void LCD_EnablePulse(void){
	DIO_SetPinValue(Control_Port, E, PIN_HIGH);
	_delay_ms(1);
}

void LCD_DisablePulse(void){
	DIO_SetPinValue(Control_Port, E ,PIN_LOW);
	_delay_ms(1);
}
