/*
 * LCD.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "../../LIB/STD_TYPES.h"


/* Modes of Operation*/
typedef enum{
	_4bits,
	_8bits
} LCD_modes_of_operation;

/* Ports Carrying LCD Pins*/
#define Control_Port	PORT_B
#define Data_Port		PORT_A

/* Control Pins */
#define RS				PIN_1
#define RW				PIN_2
#define E				PIN_3

/* Data Pins */
#define D0				PIN_0
#define D1				PIN_1
#define D2				PIN_2
#define D3				PIN_3
#define D4				PIN_4
#define D5				PIN_5
#define D6				PIN_6
#define D7				PIN_7

/* Rows */
typedef enum{
	UPPER_ROW,
	LOWER_ROW
} LCD_rows;

/* Entry Mode Parameters */
#define DECREMENT		0
#define INCREMENT		1
#define SHIFT_OFF		0
#define SHIFT_ON		1

/* Display On/Off Control */
#define	DISPLAY_OFF			0
#define	DISPLAY_ON			1
#define	CURSOR_OFF			0
#define	CURSOR_ON			1
#define CURSOR_BLINK_OFF	0
#define CURSOR_BLINK_ON		1

/* Cursor or Display Shift */
#define CURSOR_MOVE			0
#define DISPLAY_SHIFT		1
#define LEFT_SHIFT			0
#define RIGHT_SHIFT			1

/* Function Set */
#define _4_BITS_DATA_LENGTH	0
#define _8_BITS_DATA_LENGTH	1
#define _1_LINE				0
#define _2_LINES			1
#define _5x8_DOTS			0
#define _5x10_DOTS			1




 /********************************\
 *********** Functions ************
 \********************************/

void LCD_Init(LCD_modes_of_operation mode);
void LCD_SendInstruction(u8_t instruction);
void LCD_SendChar(unsigned char character);
void LCD_SendString(char* c);
void LCD_SendNumber(double num);
void LCD_GoToPosition(u8_t row, u8_t col);
void LCD_Clear(void);
void LCD_ReturnHome(void);
void LCD_EntryModeSet(u8_t cursor_move, u8_t display_shift);
void LCD_DisplayControl(u8_t display_mode, u8_t cursor_display, u8_t cursor_blink);
void LCD_CursorOrDisplayShift(u8_t cursor_or_display, u8_t right_or_left);
void LCD_FunctionSet(u8_t data_length, u8_t display_lines_num, u8_t char_font);
void LCD_SetCGRAMAddress(u8_t address);
void LCD_SetDDRAMAddress(u8_t address);
void LCD_EnablePulse(void);
void LCD_DisablePulse(void);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	LCD_Init(u8_t mode):
 * 				@brief	Initialize the LCD
 *
 * 				@details
 * 						- Set control pins as outputs.
 * 						- If the input mode is 4 bits, only pins (D4-D7) are set as output pins.
 * 						- If the input mode is 8 bits, all the pins are set as output pins.
 *
 * 				@param mode: The mode of operation which is 4 bits or 8 bits.
 *
 *	____________________________________________________________________________________

 *	LCD_SendInstruction(u8_t instruction):
 *				@brief Send an instruction.
 *
 *				@param instruction: The instruction to be sent.
 *
 *	____________________________________________________________________________________

 *	LCD_SendChar(unsigned char character);
 *				@brief Print a character into the LCD.
 *
 *				@param character: The character to be sent.
 *
 *	____________________________________________________________________________________

 *	LCD_SendString(char* str);
 *				@brief Print a string into the LCD.
 *
 *				@param str: Pointer to the null-terminated string to be sent.
 *
 *	____________________________________________________________________________________

 *	LCD_SendNumber(double num);
 *				@brief Print a number into the LCD.
 *
 *				@param num: The number to be sent.
 *
 *	____________________________________________________________________________________

 *	LCD_GoToPosition(u8_t row, u8_t col);
 *				@brief Go to specific position in LCD.
 *
 *				@param row: The row to be in (UPPER_ROW, LOWER_ROW).
 *				@param col: The column to be in (0, 1, 2, ..., 14, or 15).
 *
 *	____________________________________________________________________________________

 *	LCD_Clear(void);
 *				@brief Clear the LCD display.
 *
 *	____________________________________________________________________________________

 *	LCD_ReturnHome(void);
 *				@brief Return the LCD cursor to the home position.
 *
 *	____________________________________________________________________________________

 *	LCD_EntryModeSet(u8_t cursor_move, u8_t display_shift);
 *				@brief Set the entry mode of the LCD.
 *
 *				@details
 *						- It controls the cursor move and display shift.
 *						- If cursor is on and its move is set as INCREMENT, it would move to right when typing a new character.
 *						- If cursor is on and its move is set as DECREMENT, it would move to left when typing a new character.
 *						- If shift is on, the display shifts when printing a new character.
 *						- If shif is off, the display does not shift when printing any character.
 *
 *				@param cursor_move: Cursor move direction (INCREMENT or DECREMENT).
 *				@param display_shift: Display shift mode (SHIFT_OFF or SHIFT_ON).
 *
 *	____________________________________________________________________________________

 *	LCD_DisplayControl(u8_t display_mode, u8_t cursor_display, u8_t cursor_blink);
 *				@brief Control the display settings of the LCD.
 *
 *				@param display_mode: Display on/off (DISPLAY_ON or DISPLAY_OFF).
 *				@param cursor_display: Cursor on/off (CURSOR_ON or CURSOR_OFF).
 *				@param cursor_blink: Cursor blink on/off (CURSOR_BLINK_ON or CURSOR_BLINK_OFF).
 *
 *	____________________________________________________________________________________

 *	LCD_CursorOrDisplayShift(u8_t cursor_or_display, u8_t right_or_left);
 *				@brief Shift the cursor or display of the LCD without writing or reading display data.
 *
 *				@details
 *						- In a 2-line display, the cursor moves to the second line when it passes the 40th digit of the first line.
 *
 *				@param cursor_or_display: Cursor or display shift (CURSOR_MOVE or DISPLAY_SHIFT).
 *				@param right_or_left: Shift direction (RIGHT_SHIFT or LEFT_SHIFT).
 *
 *	____________________________________________________________________________________

 *	LCD_FunctionSet(u8_t data_length, u8_t display_lines_num, u8_t char_font);
 *				@brief Set the function settings of the LCD.
 *
 *				@param data_length: Data length (4-bit or 8-bit mode).
 *				@param display_lines_num: Number of display lines (1 line or 2 lines).
 *				@param char_font: Character font (5x8 dots or 5x10 dots).
 *
 *	____________________________________________________________________________________

 *	LCD_SetCGRAMAddress(u8_t address);
 *				@brief Set the CGRAM (Character Generator RAM) address of the LCD.
 *
 *				@param address: Address value for CGRAM.
 *
 *	____________________________________________________________________________________

 *	LCD_SetDDRAMAddress(u8_t address);
 *				@brief Set the DDRAM (Display Data RAM) address of the LCD.
 *
 *				@param address: Address value for DDRAM.
 *
 *	____________________________________________________________________________________

 *	LCD_EnablePulse(void);
 *				@brief Enable the pulse for data transfer to the LCD.
 *
 *	____________________________________________________________________________________

 *	LCD_DisablePulse(void);
 *				@brief Disable the pulse for data transfer to the LCD.
 *
 *	____________________________________________________________________________________

 */

#endif /* HAL_LCD_LCD_H_ */
