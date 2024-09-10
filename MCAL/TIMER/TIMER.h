/*
 * TIMER.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

  /******************************************************************/
 /**************************** Timer0 ******************************/
/******************************************************************/

/* Timer0 Registers */
#define TCCR0		(*(volatile u8_t*)0x53)
#define TCNT0		(*(volatile u8_t*)0x52)
#define OCR0		(*(volatile u8_t*)0x5C)

/* TCCR0 */
#define	CS00	0
#define	CS01	1
#define	CS02	2
#define	WGM01	3
#define	COM00	4
#define	COM01	5
#define	WGM00	6
#define	FOC0	7

/* Timer0 - Modes of Operation */
typedef enum {
	TIMER0_NORMAL,
	TIMER0_PWM_PHASE_CORRECT,
	TIMER0_CTC,
	TIMER0_FAST_PWM
} TIMER0_mode_of_operation;

/* Timer0 - Prescalers */
typedef enum {
	TIMER0_STOP,
	TIMER0_NO_PRESCALER,
	TIMER0_PRESCALER_8,
	TIMER0_PRESCALER_64,
	TIMER0_PRESCALER_256,
	TIMER0_PRESCALER_1024,
	TIMER0_FALLING_EDGE,
	TIMER0_RISING_EDGE
} TIMER0_prescaler;

/* Timer0 - OC0 Pin Mode */
typedef enum{
	OC0_DISCONNECT,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING
} TIMER0_OC0_mode;



/********************************\
*********** Functions ************
\********************************/

void TIMER_Timer0_Init(TIMER0_mode_of_operation mode, TIMER0_prescaler prescaler);
void TIMER_Timer0_TCNT0_Set(u8_t value);
void TIMER_Timer0_OCR0_Set(u8_t value);
void TIMER_Timer0_OC0_Init(TIMER0_OC0_mode mode);
void TIMER_Timer0_OV_EnableInterrupt(void);
void TIMER_Timer0_OV_DisableInterrupt(void);
void TIMER_Timer0_OC_EnableInterrupt(void);
void TIMER_Timer0_OC_DisableInterrupt(void);
void TIMER_Timer0_OV_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer0_OC_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer0_OV_Polling_Wait(void);
void TIMER_Timer0_OC_Polling_Wait(void);
void TIMER_Timer0_Stop(void);

/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	TIMER_Timer0_Init(TIMER0_mode_of_operation mode, TIMER0_prescaler prescaler):
 * 				@brief	Initialize Timer0.
 *
 * 				@param mode: The mode of operation (Normal, CTC, FAST PWM or PWM Phase Correct).
 * 				@param prescaler: The value to divide the frequency of oscillator by to get more time between each machine cycle and the other (No, 8, 64, 256, 1024, or count on falling or rising edge).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_TCNT0_Set(u8_t value):
 *				@brief Set the value of Timer0's 8-bit counter.
 *
 *				@param value: The value to set TCNT0 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OCR0_Set(u8_t value):
 *				@brief Set the value of Timer0's Output Compare Register (OCR0).
 *
 *				@param value: The value to set OCR0 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OC0_Init(TIMER0_OC0_mode mode):
 *				@brief Initialize Timer0's OC0 (Output Compare) pin.
 *
 *				@details
 *						- OC0 pin has an advantage over any other general pin when working with Timer0 .
 *						- There are ready options that selects OC0 level on compare match or on reaching top without writing a code to set its levels.
 *
 *				@param mode: The mode of OC0 (Disconnected, Toggle, Non inverting or Inverting).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OV_EnableInterrupt(void):
 *				@brief Enable overflow interrupt for Timer0.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OV_DisableInterrupt(void):
 *				@brief Disable overflow interrupt for Timer0.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OC_EnableInterrupt(void):
 *				@brief Enable output compare match interrupt for Timer0.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OC_DisableInterrupt(void):
 *				@brief Disable output compare match interrupt for Timer0.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OV_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer0 overflow interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on overflow interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OC_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer0 output compare interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on output compare match interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OV_Polling_Wait(void):
 *				@brief Waiting Timer0 overflow by stucking in a while loop until TOV0 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_OC_Polling_Wait(void):
 *				@brief Waiting Timer0 output compare match by stucking in a while loop until OCF0 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer0_Stop(void):
 *				@brief Stop Timer0.
 *
 *	____________________________________________________________________________________

 */

  /******************************************************************/
 /**************************** Timer1 ******************************/
/******************************************************************/

/* Timer1 Registers */
#define TCCR1A		(*(volatile u8_t*)0x4F)
#define TCCR1B		(*(volatile u8_t*)0x4E)
#define TCNT1H		(*(volatile u8_t*)0x4D)
#define TCNT1L		(*(volatile u8_t*)0x4C)
#define OCR1AH		(*(volatile u8_t*)0x4B)
#define OCR1AL		(*(volatile u8_t*)0x4A)
#define OCR1BH		(*(volatile u8_t*)0x49)
#define OCR1BL		(*(volatile u8_t*)0x48)
#define ICR1H		(*(volatile u8_t*)0x47)
#define ICR1L		(*(volatile u8_t*)0x46)

/* TCCR1A */
#define	WGM10	0
#define	WGM11	1
#define	FOC1B	2
#define	FOC1A	3
#define	COM1B0	4
#define	COM1B1	5
#define	COM1A0	6
#define	COM1A1	7

/* TCCR1B */
#define	CS10	0
#define	CS11	1
#define	CS12	2
#define	WGM12	3
#define	WGM13	4
// Reserved		5
#define	ICES1	6
#define	ICNC1	7


/* Timer1 - Modes of Operation */
typedef enum {
	TIMER1_NORMAL,
	TIMER1_PWM_PHASE_CORRECT_8_BIT,
	TIMER1_PWM_PHASE_CORRECT_9_BIT,
	TIMER1_PWM_PHASE_CORRECT_10_BIT,
	TIMER1_CTC_OCR1,
	TIMER1_FAST_PWM_8_BIT,
	TIMER1_FAST_PWM_9_BIT,
	TIMER1_FAST_PWM_10_BIT,
	TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1,
	TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1,
	TIMER1_PWM_PHASE_CORRECT_ICR1,
	TIMER1_PWM_PHASE_CORRECT_OCR1,
	TIMER1_CTC_ICR1,
	TIMER1_FAST_PWM_ICR1,
	TIMER1_FAST_PWM_OCR1,
} TIMER1_mode_of_operation;

/* Timer1 - Prescalers */
typedef enum {
	TIMER1_STOP,
	TIMER1_NO_PRESCALER,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_FALLING_EDGE,
	TIMER1_RISING_EDGE
} TIMER1_prescaler;

/* Timer1 - OC1A/OC1B Pin Mode */
typedef enum{
	OC1_DISCONNECT,
	OC1_TOGGLE,
	OC1_NON_INVERTING,
	OC1_INVERTING
} TIMER1_OC1_mode;


void TIMER_Timer1_Init(TIMER1_mode_of_operation mode, TIMER1_prescaler  prescaler);
void TIMER_Timer1_TCNT1_Set(u16_t value);
void TIMER_Timer1_OCR1A_Set(u16_t value);
void TIMER_Timer1_OCR1B_Set(u16_t value);
void TIMER_Timer1_ICR1_Set(u16_t value);
void TIMER_Timer1_OC1A_Init(TIMER1_OC1_mode mode);
void TIMER_Timer1_OC1B_Init(TIMER1_OC1_mode mode);
void TIMER_Timer1_OV_EnableInterrupt(void);
void TIMER_Timer1_OV_DisableInterrupt(void);
void TIMER_Timer1_OCA_EnableInterrupt(void);
void TIMER_Timer1_OCA_DisableInterrupt(void);
void TIMER_Timer1_OCB_EnableInterrupt(void);
void TIMER_Timer1_OCB_DisableInterrupt(void);
void TIMER_Timer1_IC_EnableInterrupt(void);
void TIMER_Timer1_IC_DisableInterrupt(void);
void TIMER_Timer1_OV_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer1_OCA_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer1_OCB_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer1_IC_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer1_OV_Polling_Wait(void);
void TIMER_Timer1_OCA_Polling_Wait(void);
void TIMER_Timer1_OCB_Polling_Wait(void);
void TIMER_Timer1_IC_Polling_Wait(void);
void TIMER_Timer1_Stop(void);


/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	TIMER_Timer1_Init(TIMER1_mode_of_operation mode, TIMER1_prescaler prescaler):
 * 				@brief	Initialize Timer1.
 *
 * 				@param mode: The mode of operation (Normal, CTC with OCR1 as top, CTC with ICR1 as top, ...).
 * 				@param prescaler: The value to divide the frequency of oscillator by to get more time between each machine cycle and the other (No, 8, 64, 256, 1024, or count on falling or rising edge).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_TCNT1_Set(u16_t value):
 *				@brief Set the value of Timer1's 16-bit counter.
 *
 *				@param value: The value to set TCNT1 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCR1A_Set(u16_t value):
 *				@brief Set the value of Timer1's Output Compare Register A (OCR1A).
 *
 *				@param value: The value to set OCR1A to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCR1B_Set(u16_t value):
 *				@brief Set the value of Timer1's Output Compare Register B (OCR1B).
 *
 *				@param value: The value to set OCR1B to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_ICR1_Set(u16_t value):
 *				@brief Set the value of Timer1's Input Capture Register (ICR1).
 *
 *				@param value: The value to set ICR1 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OC1A_Init(TIMER1_OC1_mode mode):
 *				@brief Initialize Timer1's OC1A (Output Compare) pin.
 *
 *				@details
 * 						- OC1A pin has an advantage over any other general pin when working with Timer1 .
 *						- There are ready options that selects OC1A level on compare match (reaching OCR1A) or on reaching top without writing a code to set its levels.
 *
 *				@param mode: The mode of OC1A pin (Disconnect, Toggle, Non-Inverting, Inverting).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OC1B_Init(TIMER1_OC1_mode mode):
 *				@brief Initialize Timer1's OC1B (Output Compare) pin.
 *
 *				@details
 * 						- OC1B pin has an advantage over any other general pin when working with Timer1 .
 *						- There are ready options that selects OC1B level on compare match (reaching OCR1B) or on reaching top without writing a code to set its levels.
 *
 *				@param mode: The mode of OC1B pin (Disconnect, Toggle, Non-Inverting, Inverting).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OV_EnableInterrupt(void):
 *				@brief Enable overflow interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OV_DisableInterrupt(void):
 *				@brief Disable overflow interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCA_EnableInterrupt(void):
 *				@brief Enable output compare match A interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCA_DisableInterrupt(void):
 *				@brief Disable output compare match A interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCB_EnableInterrupt(void):
 *				@brief Enable output compare match B interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCB_DisableInterrupt(void):
 *				@brief Disable output compare match B interrupt for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_IC_EnableInterrupt(void):
 *				@brief Enable interrupt on capture event (reaching ICR1) for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_IC_DisableInterrupt(void):
 *				@brief Disable interrupt on capture event (reaching ICR1) for Timer1.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OV_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer1 overflow interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on overflow interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCA_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer1 output compare A interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on output compare match A interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCB_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer1 output compare B interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on output compare match B interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_IC_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer1 when reaching ICR1.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on capture event (reaching ICR1) interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OV_Polling_Wait(void):
 *				@brief Waiting Timer1 overflow by stucking in a while loop until TOV1 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCA_Polling_Wait(void):
 *				@brief Waiting Timer1 output compare match A by stucking in a while loop until OCF1A in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_OCB_Polling_Wait(void):
 *				@brief Waiting Timer1 output compare match A by stucking in a while loop until OCF1B in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_IC_Polling_Wait(void):
 *				@brief Waiting Timer1 input capture by stucking in a while loop until ICF1 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer1_Stop(void):
 *				@brief Stop Timer1.
 *
 *	____________________________________________________________________________________

 */

  /******************************************************************/
 /**************************** Timer2 ******************************/
/******************************************************************/

/* Timer2 Registers */
#define TCCR2		(*(volatile u8_t*)0x45)
#define TCNT2		(*(volatile u8_t*)0x44)
#define OCR2		(*(volatile u8_t*)0x43)

/* TCCR2 */
#define	CS20	0
#define	CS21	1
#define	CS22	2
#define	WGM21	3
#define	COM20	4
#define	COM21	5
#define	WGM20	6
#define	FOC2	7

/* Timer2 - Modes of Operation */
typedef enum {
	TIMER2_NORMAL,
	TIMER2_PWM_PHASE_CORRECT,
	TIMER2_CTC,
	TIMER2_FAST_PWM
} TIMER2_mode_of_operation;

/* Timer2 - Prescalers */
typedef enum {
	TIMER2_STOP,
	TIMER2_NO_PRESCALER,
	TIMER2_PRESCALER_8,
	TIMER2_PRESCALER_32,
	TIMER2_PRESCALER_64,
	TIMER2_PRESCALER_128,
	TIMER2_PRESCALER_256,
	TIMER2_PRESCALER_1024
} TIMER2_prescaler;

/* Timer2 - OC2 Pin Mode */
typedef enum{
	OC2_DISCONNECT,
	OC2_TOGGLE,
	OC2_NON_INVERTING,
	OC2_INVERTING
} TIMER2_OC2_mode;



/********************************\
*********** Functions ************
\********************************/

void TIMER_Timer2_Init(TIMER2_mode_of_operation mode, TIMER2_prescaler prescaler);
void TIMER_Timer2_TCNT2_Set(u8_t value);
void TIMER_Timer2_OCR2_Set(u8_t value);
void TIMER_Timer2_OC2_Init(TIMER2_OC2_mode mode);
void TIMER_Timer2_OV_EnableInterrupt(void);
void TIMER_Timer2_OV_DisableInterrupt(void);
void TIMER_Timer2_OC_EnableInterrupt(void);
void TIMER_Timer2_OC_DisableInterrupt(void);
void TIMER_Timer2_OV_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer2_OC_SetCallBack(void (*local_function_pointer) (void));
void TIMER_Timer2_OV_Polling_Wait(void);
void TIMER_Timer2_OC_Polling_Wait(void);
void TIMER_Timer2_Stop(void);


/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	TIMER_Timer2_Init(TIMER2_mode_of_operation mode, TIMER2_prescaler prescaler):
 * 				@brief	Initialize Timer2.
 *
 * 				@param mode: The mode of operation (Normal, CTC, FAST PWM or PWM Phase Correct).
 * 				@param prescaler: The value to divide the frequency of oscillator by to get more time between each machine cycle and the other (No, 8, 32, 64, 128, 256 or 1024).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_TCNT2_Set(u8_t value):
 *				@brief Set the value of Timer2's 8-bit counter.
 *
 *				@param value: The value to set TCNT2 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OCR2_Set(u8_t value):
 *				@brief Set the value of Timer2's Output Compare Register (OCR2).
 *
 *				@param value: The value to set OCR2 to.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OC2_Init(TIMER2_OC2_mode mode):
 *				@brief Initialize Timer2's OC2 (Output Compare) pin.
 *
 *				@details
 *						- OC2 pin has an advantage over any other general pin when working with Timer2.
 *						- There are ready options that selects OC2 level on compare match or on reaching top without writing a code to set its levels.
 *
 *				@param mode: The mode of OC2 (Disconnected, Toggle, Non inverting or Inverting).
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OV_EnableInterrupt(void):
 *				@brief Enable overflow interrupt for Timer2.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OV_DisableInterrupt(void):
 *				@brief Disable overflow interrupt for Timer2.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OC_EnableInterrupt(void):
 *				@brief Enable output compare match interrupt for Timer2.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OC_DisableInterrupt(void):
 *				@brief Disable output compare match interrupt for Timer2.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OV_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer2 overflow interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on overflow interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OC_SetCallBack(void (*local_function_pointer) (void)):
 *				@brief Set callback function for Timer2 output compare interrupt.
 *
 *				@param local_function_pointer: Pointer to the function that will be called on output compare match interrupt.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OV_Polling_Wait(void):
 *				@brief Waiting Timer2 overflow by stucking in a while loop until TOV2 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_OC_Polling_Wait(void):
 *				@brief Waiting Timer2 output compare match by stucking in a while loop until OCF2 in TIFR is set.
 *
 *	____________________________________________________________________________________
 *
 *	TIMER_Timer2_Stop(void):
 *				@brief Stop Timer2.
 *
 *	____________________________________________________________________________________

 */

  /******************************************************************/
 /************************ Timers Interrupt ************************/
/******************************************************************/

/* Timer Interrupt Registers */
#define TIMSK		(*(volatile u8_t*)0x59)
#define TIFR		(*(volatile u8_t*)0x58)

/* TIMSK */
#define	TOIE0	0
#define	OCIE0	1
#define	TOIE1	2
#define	OCIE1B	3
#define	OCIE1A	4
#define	TICIE1	5
#define	TOIE2	6
#define	OCIE2	7

/* TIFR */
#define	TOV0	0
#define	OCF0	1
#define	TOV1	2
#define	OCF1B	3
#define	OCF1A	4
#define	ICF1	5
#define	TOV2	6
#define	OCF2	7



/********************************\
*********** Functions ************
\********************************/

void TIMER_TIFR_ClearFlag(u8_t flag);


/*
 * .-----------------------------.
 * |Explanation of each function |
 * '-----------------------------'

 *	TIMER_TIFR_ClearFlag(u8_t flag):
 * 				@brief	Clear a flag in TIFR register.
 *
 * 				@param flag: The flag to be cleared it could be passed as its number of by its name since it is defined.
 *
 *	____________________________________________________________________________________

 */


#endif /* MCAL_TIMER_TIMER_H_ */
