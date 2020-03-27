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

	// Initialize LED pin
	BSP_LED_Init();

	// Turn LED On
	BSP_LED_On();

	// Turn LED Off
	BSP_LED_Off();
int32_t i=0;
	while(1)
	{


		i++;
		if (i==800000000)
		{
			// Toggle LED state
			BSP_LED_Toggle();
			i=0;
		}
	}
}


