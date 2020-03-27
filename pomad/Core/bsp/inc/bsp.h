/*
 * bsp.h
 *
 *  Created on: 27 mars 2020
 *      Author: pc
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

void	BSP_Console_Init	(void);
/*
 * LED driver functions
 */

void	BSP_LED_Init	(void);
void	BSP_LED_On	(void);
void	BSP_LED_Off	(void);
void	BSP_LED_Toggle	(void);


/*
 * Push-Button driver functions
 */

void		BSP_PB_Init		(void);
uint8_t	BSP_PB_GetState	(void);



#endif /* BSP_BSP_H_ */
