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
