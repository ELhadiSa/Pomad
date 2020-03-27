/*
 * main.c
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */


#include "stm32f7xx.h"
#include "bsp.h"



// Main program

void main(void)
{
	uint8_t	i, sent;

	// Configure System Clock
	//SystemClock_Config();

	// Initialize LED & Button pin
	BSP_LED_Init();
	BSP_PB_Init();

	// Initialize Debug Console
	BSP_Console_Init();

	// Main loop
	while(1)
	{
		// If User-Button is pushed down
		if (BSP_PB_GetState() == 1)
		{
			BSP_LED_On();	// Keep LED On

			// Send '#' only once
			if (sent == 0)
			{
				while ((USART3->ISR & USART_ISR_TC) != USART_ISR_TC);
				USART3->TDR = '#';
				sent = 1;
			}
		}

		// If User-Button is released
		else
		{
			BSP_LED_Off();	// Keep LED Off
			sent = 0;
		}
	}
}


void SystemClock_Config(void){

}
