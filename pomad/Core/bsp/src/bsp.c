/*
 * bsp.c
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */

#include "bsp.h"

/*
 * BSP_LED_Init()
 * Initialize LED pin (PB7) as a High-Speed Push-Pull output
 * Set LED initial state to OFF
 */

void BSP_LED_Init()
{
	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Configure PB7 as output
	GPIOB->MODER &= ~GPIO_MODER_MODER7_Msk;
	GPIOB->MODER |= (0x01 <<GPIO_MODER_MODER7_Pos);

	// Configure PB7 as Push-Pull output
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_7;

	// Configure PB7 as High-Speed Output
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR7_Msk;
	GPIOB->OSPEEDR |= (0x03 <<GPIO_OSPEEDR_OSPEEDR7_Pos);

	// Disable PA5 Pull-up/Pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7_Msk;

	// Set Initial State OFF
	GPIOB->BSRR |= GPIO_BSRR_BR_7;
}


/*
 * BSP_LED_On()
 * Turn ON LED on PB7
 */

void BSP_LED_On()
{
	GPIOB->BSRR = GPIO_BSRR_BS_7;
}

/*
 * BSP_LED_Off()
 * Turn OFF LED on PB7
 */

void BSP_LED_Off()
{
	GPIOB->BSRR = GPIO_BSRR_BR_7;
}

/*
 * BSP_LED_Toggle()
 * Toggle LED on PB7
 */

void BSP_LED_Toggle()
{
	GPIOB->ODR ^= GPIO_ODR_ODR_7;
}




/*
 * BSP_PB_Init()
 * Initialize Push-Button pin (PC13) as input without Pull-up/Pull-down
 */

void BSP_PB_Init()
{
	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure PC13 as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
	GPIOC->MODER |= (0x00 <<GPIO_MODER_MODER13_Pos);

	// Disable PC13 Pull-up/Pull-down
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_Msk;
}

/*
 * BSP_PB_GetState()
 * Returns the state of the button (0=released, 1=pressed)
 */

uint8_t BSP_PB_GetState()
{
	uint8_t state;

	if ((GPIOC->IDR & GPIO_IDR_ID13) == GPIO_IDR_ID13)
	{
		state = 1;
	}
	else
	{
		state = 0;
	}

	return state;
}
