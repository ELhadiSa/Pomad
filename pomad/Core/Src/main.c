/*
 * main.c
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */

#include "stm32f7xx.h"
#include "bsp.h"

// Static functions

static void SystemClock_Config(void);

// Main program

void main()
{
	// Configure System Clock
	SystemClock_Config();

	// Initialize LED pin
	BSP_LED_Init();

	// Initialize User-Button pin
	BSP_PB_Init();

	// Turn LED On
	BSP_LED_On();

	// Turn LED Off
	BSP_LED_Off();

	while(1)
	{
		// Turn LED On if User-Button is pushed down
		if (BSP_PB_GetState() == 1)
		{
			BSP_LED_On();
		}

		// Otherwise turn LED Off
		else
		{
			BSP_LED_Off();
		}
	}
}


void SystemClock_Config(void){

}
