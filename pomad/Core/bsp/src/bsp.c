/*
 * bsp.c
 *
 *  Created on: 27 mars 2020
 *      Author: pc
 */

#include "stm32f7xx.h"


#include "bsp.h"
#define BP_IT
#define TIMER_IT

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
#ifndef BP_IT
	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure PC13 as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
	GPIOC->MODER |= (0x00 <<GPIO_MODER_MODER13_Pos);

	// Disable PC13 Pull-up/Pull-down
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_Msk;
#else
	// Enable GPIOC clock
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

		// Configure PC13 as input
		GPIOC->MODER &= ~GPIO_MODER_MODER13_Msk;
		GPIOC->MODER |= (0x00 <<GPIO_MODER_MODER13_Pos);

		// Disable PC13 Pull-up/Pull-down
		GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_Msk;

		// Enable SYSCFG clock
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

		// Select Port C as interrupt source for EXTI line 13
		SYSCFG->EXTICR[3] &= ~ SYSCFG_EXTICR4_EXTI13_Msk;
		SYSCFG->EXTICR[3] |=   SYSCFG_EXTICR4_EXTI13_PC;

		// Enable EXTI line 13
		EXTI->IMR |= EXTI_IMR_IM13;

		// Disable Rising / Enable Falling trigger
		EXTI->RTSR &= ~EXTI_RTSR_TR13;
		EXTI->FTSR |=  EXTI_FTSR_TR13;
#endif
}
/*
 * BSP_NVIC_Init()
 * Setup NVIC controller for desired interrupts
 */

void BSP_NVIC_Init()
{
	// Set maximum priority for EXTI line 4 to 15 interrupts
	NVIC_SetPriority(EXTI15_10_IRQn, 0);

	// Enable EXTI line 4 to 15 (user button on line 13) interrupts
	NVIC_EnableIRQ(EXTI15_10_IRQn);
#ifdef TIMER_IT

		// Set maximum priority for EXTI line 4 to 15 interrupts
		NVIC_SetPriority(EXTI15_10_IRQn, 0);

		// Enable EXTI line 4 to 15 (user button on line 13) interrupts
		NVIC_EnableIRQ(EXTI15_10_IRQn);

		// Set priority level 1 for TIM6 interrupt
		NVIC_SetPriority(TIM6_DAC_IRQn, 1);

		// Enable TIM6 interrupts
		NVIC_EnableIRQ(TIM6_DAC_IRQn);

		// Set priority level 1 for USART2 interrupt
		NVIC_SetPriority(USART3_IRQn, 1);

		// Enable USART2 interrupts
		NVIC_EnableIRQ(USART3_IRQn);

#endif
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
/*
 * BSP_Console_Init()
 * USART2 @ 115200 Full Duplex
 * 1 start - 8-bit - 1 stop
 * TX -> PD8 (AF7)
 * RX -> PD9 (AF7)
 */

void BSP_Console_Init()
{
	// Enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

//	// Configure PD8 and PD9 as Alternate function
	GPIOD->MODER &= ~(GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk);
	GPIOD->MODER |= (0x02 <<GPIO_MODER_MODER8_Pos) | (0x02 <<GPIO_MODER_MODER9_Pos);

//	// Set PD8 and PD9 to AF7 (USART3)
	GPIOD->AFR[1] &=  ~(0x000000FF);
	GPIOD->AFR[1] |=   (0x00000077);
//
	// Enable USART3 clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
//
	// Clear USART2 configuration (reset state)
	// 8-bit, 1 start, 1 stop, CTS/RTS disabled
	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;
//
	// Select PCLK (APB1) as clock source
	// PCLK -> 48 MHz
	RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_USART3SEL_Msk;

//
	// Baud Rate = 115200
	// With OVER8=0 and Fck=48MHz, USARTDIV =   48E6/115200 = 416.6666
	// BRR = 417 -> Baud Rate = 115107.9137 -> 0.08% error
	//
	// With OVER8=1 and Fck=48MHz, USARTDIV = 2*48E6/115200 = 833.3333
	// BRR = 833 -> Baud Rate = 115246.0984 -> 0.04% error (better)
//
	USART3->CR1 |= USART_CR1_OVER8;
	USART3->BRR = 833;

	// Enable both Transmitter and Receiver
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// Enable interrupt on RXNE event
		USART3->CR1 |= USART_CR1_RXNEIE;
	// Enable USART3
	USART3->CR1 |= USART_CR1_UE;
}



/*
 * ADC_Init()
 * Initialize ADC for a single channel conversion
 * on channel 9 -> pin PF3
 */

void BSP_ADC_Init()
{
	// Enable GPIOF clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

	// Configure pin PF3 as analog
	GPIOF->MODER &= ~GPIO_MODER_MODER3_Msk;
	GPIOF->MODER |= (0x03 <<GPIO_MODER_MODER3_Pos);

	//configure PINF3
	// Enable ADC clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;

//	ADC3->CR1 = 0x00000000;
//	ADC3->CR2 = 0x00000000;
//	ADC3->SQR2 = 0x00000000;
//	ADC3->SMPR2 = 0x00000000;
//	ADC->CCR = 0x00000000;


//
	// Enable continuous conversion mode
	ADC3->CR2 |= (0b1 << ADC_CR2_CONT_Pos);
//
//	// 12-bit resolution
	ADC3->CR1 |= (0b00<< ADC_CR1_RES_Pos);
	//
	// Select PCLK/2 as ADC clock
	ADC->CCR |= (0x00 <<ADC_CCR_ADCPRE_Pos);
//
//	// Set sampling time to 28.5 ADC clock cycles
	ADC3->SMPR2 |= ( 0b010 << ADC_SMPR2_SMP9_Pos );


///	// Select channel 9 (write the channel number on the first sequence)

	ADC3->SQR3 |= (9 << ADC_SQR3_SQ1_Pos);

//	// Enable ADC
	ADC3->CR2 |= (0b1 << ADC_CR2_ADON_Pos);
//
//	// Start conversion
	ADC3->CR2 |=  (0b1 <<ADC_CR2_SWSTART_Pos);

	// Reset ADC configuration

}



/*
 * BSP_TIMER_Timebase_Init()
 * TIM6 at 48MHz
 * Prescaler   = 48000 -> Counting period = 1ms
 * Auto-reload = 1000  -> Update period   = 1s
 * ####################  OR  ########################
 *when TIMER_IT is #def
  *
 * BSP_TIMER_Timebase_Init()
 * TIM6 at 48MHz
 * Prescaler   = 48000 -> Counting period = 1ms
 * Auto-reload = 200   -> Update period   = 200ms
 */

void BSP_TIMER_Timebase_Init()
{
#ifndef TIMER_IT

	// Enable TIM6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	// Reset TIM6 configuration
	TIM6->CR1 = 0x0000;
	TIM6->CR2 = 0x0000;

	// Set TIM6 prescaler
	// Fck = 48MHz -> /48000 = 1KHz counting frequency
	TIM6->PSC = (uint16_t) 48000 -1;

	// Set TIM6 auto-reload register for 1s
	TIM6->ARR = (uint16_t) 1000 -1;

	// Enable auto-reload preload
	TIM6->CR1 |= TIM_CR1_ARPE;

	// Start TIM6 counter
	TIM6->CR1 |= TIM_CR1_CEN;
#else
	// Enable TIM6 clock
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

		// Reset TIM6 configuration
		TIM6->CR1 = 0x0000;
		TIM6->CR2 = 0x0000;

		// Set TIM6 prescaler
		// Fck = 48MHz -> /48 = 1kHz counting frequency
		TIM6->PSC = (uint16_t) 48000 -1;

		// Set TIM6 auto-reload register for 200ms
		TIM6->ARR = (uint16_t) 200 -1;

		// Enable auto-reload preload
		TIM6->CR1 |= TIM_CR1_ARPE;

		// Enable Interrupt upon Update Event
		TIM6->DIER |= TIM_DIER_UIE;

		// Start TIM6 counter
		TIM6->CR1 |= TIM_CR1_CEN;
#endif
}


/*
 * BSP_TIMER_IC_Init()
 * TIM3 as Input Capture
 * Channel 1 -> PC6 (AF2)
 */

void BSP_TIMER_IC_Init()
{
	// Enable GPIOC clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure PC6 as Alternate function
	GPIOC->MODER &= ~(GPIO_MODER_MODER6_Msk);
	GPIOC->MODER |=  (0x02 <<GPIO_MODER_MODER6_Pos);

	// Set PC6 to AF2 (TIM3_CH1)
	GPIOC->AFR[0] &= (0000<<GPIO_AFRL_AFRL6_Pos);
	GPIOC->AFR[0] |= (0b0010<<GPIO_AFRL_AFRL6_Pos);

	// Enable TIM3 clock
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	// Reset TIM3 configuration
	TIM3->CR1  = 0x0000;
	TIM3->CR2  = 0x0000;
	TIM3->CCER = 0x0000;

	// Set TIM3 prescaler
	// Fck = 48MHz -> /48000 = 1KHz counting frequency
	TIM3->PSC = (uint16_t) 48000 -1;

	// Set Auto-Reload to maximum value
	TIM3->ARR = (uint16_t) 0xFFFF;


	//3.1. Single edge capture

//	// Reset Input Capture configuration
//	TIM3->CCMR1 = 0x0000;
//	TIM3->CCMR2 = 0x0000;
//
//	// Set Channel 1 input on TI1
//	TIM3->CCMR1 |= (0x01 <<TIM_CCMR1_CC1S_Pos);
//
//	// Filter with N=8
//	TIM3->CCMR1 |= (0x03 <<TIM_CCMR1_IC1F_Pos);
//
//	// Select falling edge for channel 1
//	TIM3->CCER |= (0x00 <<TIM_CCER_CC1NP_Pos) | (0x01 <<TIM_CCER_CC1P_Pos);
//
//	// Enable capture on channel 1
//	TIM3->CCER |= (0x01 <<TIM_CCER_CC1E_Pos);
//
//	// Enable TIM3
//	TIM3->CR1 |= TIM_CR1_CEN;



	//3.2. Dual edges capture
	// Setup Input Capture
//		TIM3->CCMR1 = 0x0000;
//		TIM3->CCMR2 = 0x0000;
//
//		// Channel 1 input on TI1
//		TIM3->CCMR1 |= (0x01 <<TIM_CCMR1_CC1S_Pos);
//
//		// Channel 2 input also on TI1
//		TIM3->CCMR1 |= (0x02 <<TIM_CCMR1_CC2S_Pos);
//
//		// Filter both channels with N=8
//		TIM3->CCMR1 |= (0x03 <<TIM_CCMR1_IC1F_Pos) | (0x03 <<TIM_CCMR1_IC2F_Pos);
//
//		// Select falling edge for channel 1
//		TIM3->CCER |= (0x00 <<TIM_CCER_CC1NP_Pos) | (0x01 <<TIM_CCER_CC1P_Pos);
//
//		// Select rising edge for channel 2
//		TIM3->CCER |= (0x00 <<TIM_CCER_CC2NP_Pos) | (0x00 <<TIM_CCER_CC2P_Pos);
//
//		// Enable capture on channel 1 & channel 2
//		TIM3->CCER |= (0x01 <<TIM_CCER_CC1E_Pos) | (0x01 <<TIM_CCER_CC2E_Pos);
//
//		// Enable TIM3
//		TIM3->CR1 |= TIM_CR1_CEN;
//
//
		//3.3. Dual edges capture with slave reset

	// Setup Input Capture
		TIM3->CCMR1 = 0x0000;
		TIM3->CCMR2 = 0x0000;

		// Channel 1 input on TI1
		TIM3->CCMR1 |= (0x01 <<TIM_CCMR1_CC1S_Pos);

		// Channel 2 input also on TI1
		TIM3->CCMR1 |= (0x02 <<TIM_CCMR1_CC2S_Pos);

		// Filter with N=8
		TIM3->CCMR1 |= (0x03 <<TIM_CCMR1_IC1F_Pos) | (0x03 <<TIM_CCMR1_IC2F_Pos);

		// Select falling edge for channel 1
		TIM3->CCER |= (0x00 <<TIM_CCER_CC1NP_Pos) | (0x01 <<TIM_CCER_CC1P_Pos);

		// Select rising edge for channel 2
		TIM3->CCER |= (0x00 <<TIM_CCER_CC2NP_Pos) | (0x00 <<TIM_CCER_CC2P_Pos);

		// Enable capture on channel 1 & channel 2
		TIM3->CCER |= (0x01 <<TIM_CCER_CC1E_Pos) | (0x01 <<TIM_CCER_CC2E_Pos);

		// Choose Channel 1 as trigger input
		TIM3->SMCR |= (0x05 <<TIM_SMCR_TS_Pos);

		// Slave mode -> Resets counter when trigger occurs
		TIM3->SMCR |= (0x4 <<TIM_SMCR_SMS_Pos);

		// Enable TIM3
		TIM3->CR1 |= TIM_CR1_CEN;
}



/*
 * BSP_TIMER_PWM_Init()
 * TIM1 as Output Compare PWM mode
 * Channel 1 -> PE9 (AF2)
 * Channel 2 -> PE11 (AF2)
 */

void BSP_TIMER_PWM_Init()
{
	// Enable GPIOE clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

	// Configure PE9 and PE11 as Alternate Function
	GPIOE->MODER &= ~(GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER11_Msk);
	GPIOE->MODER |=  (0x02 <<GPIO_MODER_MODER9_Pos) | (0x02 <<GPIO_MODER_MODER11_Pos);

	// Set PE9 and PE11 to AF1 (TIM1)
	GPIOE->AFR[1] |= (0b0001<<GPIO_AFRH_AFRH1_Pos);
	GPIOE->AFR[1] |= (0b0001<<GPIO_AFRH_AFRH3_Pos);


	// Enable TIM1 clock
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Reset TIM1 configuration
	TIM1->CR1  = 0x0000;
	TIM1->CR2  = 0x0000;
	TIM1->CCER = 0x0000;

	// Set TIM1 prescaler
	// Fck = 48MHz -> /48 = 1MHz counting frequency (1µs resolution)
	TIM1->PSC = (uint16_t) 48 -1;

	// Set Auto-Reload to period = 11ms
	TIM1->ARR = (uint16_t) 11000;

	// Enable Auto-Reload Preload register
	TIM1->CR1 |= TIM_CR1_ARPE;

	// Setup Input Capture
	TIM1->CCMR1 = 0x0000;
	TIM1->CCMR2 = 0x0000;

	// Setup PWM mode 1 output
	TIM1->CCMR1 |= (0x06 <<TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE;
	TIM1->CCMR1 |= (0x06 <<TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE;

	// Set default PWM values
	TIM1->CCR1 = 1500;
	TIM1->CCR2 = 1500;

	// Enable Outputs
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;

	// Enable Main output
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Enable TIM1
	TIM1->CR1 |= TIM_CR1_CEN;
}




