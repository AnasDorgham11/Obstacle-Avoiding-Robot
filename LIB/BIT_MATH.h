/*
 * BIT_MATH.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Anas Dorgham
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BIT) 	(VAR |= (1 << BIT))
#define CLEAR_BIT(VAR,BIT) 	(VAR &= (~(1 << BIT)))
#define TOG_BIT(VAR,BIT) 	(VAR ^= (1 << BIT))
#define GET_BIT(VAR,BIT) 	((VAR >> BIT) & 1)


#endif /* BIT_MATH_H_ */
