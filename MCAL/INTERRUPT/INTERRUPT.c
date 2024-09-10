/*
 * INTERRUPT.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "INTERRUPT.h"


/********************************\
*********** Functions ************
\********************************/

void INTERRUPT_EnableGlobalInterrupt(){
	SET_BIT(SREG, I);
}

void INTERRUPT_DisableGlobalInterrupt(){
	CLEAR_BIT(SREG, I);
}
