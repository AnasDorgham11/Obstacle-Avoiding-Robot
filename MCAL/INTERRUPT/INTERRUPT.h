/*
 * INTERRUPT.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_H_
#define MCAL_INTERRUPT_INTERRUPT_H_

/* Registers Definition */
#define SREG		(*(volatile u8_t*)0x5F)

/* Flags Definition */
#define I			7


/********************************\
*********** Functions ************
\********************************/

void INTERRUPT_EnableGlobalInterrupt();
void INTERRUPT_DisableGlobalInterrupt();

/*
 * .-------------------------------.
 * | Explanation of each function  |
 * '-------------------------------'

 *	INTERRUPT_EnableGlobalInterrupt(void):
 * 				@brief	Enable global interrupts.
 *
 * 				@details
 * 						- Sets the I (Global Interrupt Enable) bit in the SREG (Status Register) to enable global interrupts.
 * 						- Allows the MCU to respond to interrupt requests.
 *
 *	____________________________________________________________________________________

 *	INTERRUPT_DisableGlobalInterrupt(void):
 * 				@brief	Disable global interrupts.
 *
 * 				@details
 * 						- Clears the I (Global Interrupt Enable) bit in the SREG (Status Register) to disable global interrupts.
 * 						- Prevents the MCU from responding to interrupt requests.
 *
 *	____________________________________________________________________________________

 */


#endif /* MCAL_INTERRUPT_INTERRUPT_H_ */
