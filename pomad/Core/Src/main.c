/*
 * main.c
 *
 *  Created on: 5 août 2017
 *      Author: Laurent
 */


#include "stm32f7xx.h"
#include "bsp.h"
//#define INPUTCAPTURE_PROG
#define PWM_PROG
#define BP_IT
uint16_t	TIM6_counter;
uint16_t	TIM6_UIF;
uint8_t 	timebase_irq = 0;

uint8_t	button_irq = 0;


void SystemClock_Config(void);
extern int my_printf	(const char *format, ...);
extern void BSP_DELAY_ms(uint32_t delay);
extern int BSP_DELAY_TIM_init();
extern int BSP_DELAY_TIM_ms();


void SystemClock_Config(void)
{

	  //HSI CONF to get 48MHZ using PLL  48=16/10*240/8/1/1

		uint32_t 	HSI_Status;
		uint32_t	PLL_Status;
		uint32_t	SW_Status;
		uint32_t	timeout = 0;

		timeout = 1000000;

		// Start HSI

		RCC->CR |= RCC_CR_HSION;


		do
			{
				HSI_Status = RCC->CR & RCC_CR_HSIRDY_Msk;
				timeout--;
			} while ((HSI_Status == 0) && (timeout > 0));


		// Main PLL Configuration PLLM/10 PLLNx240 PLLP/8


		//PLLM
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
		RCC->PLLCFGR |= (0xA <<RCC_PLLCFGR_PLLM_Pos);

		//PLLN
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
		RCC->PLLCFGR |= (0xF0 <<RCC_PLLCFGR_PLLN_Pos);

		//PLLP
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
		RCC->PLLCFGR |= (0x3 <<RCC_PLLCFGR_PLLP_Pos);

		// Main PLL activation

		RCC->CR |= RCC_CR_PLLON;
		do
				{
					PLL_Status = RCC->CR & RCC_CR_PLLRDY_Msk;
					timeout--;
				} while ((PLL_Status == 0) && (timeout > 0));


		//APB1 and AHB1 Conf /1 /1
		RCC->CFGR &= RCC_CFGR_PPRE1_Msk;
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

		RCC->CFGR &= RCC_CFGR_HPRE_Msk;
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		// Enable FLASH Prefetch Buffer and set Flash Latency
		FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY;
		// Wait until HSE is ready



		/* --- Until this point, MCU was still clocked by HSI at 8MHz ---*/
		/* --- Switching to PLL at 48MHz Now!  Fasten your seat belt! ---*/

		// Select the main PLL as system clock source
		RCC->CFGR &= ~RCC_CFGR_SW;
		RCC->CFGR |= RCC_CFGR_SW_PLL;
//
		// Wait until PLL becomes main switch input
		do
		{
			SW_Status = (RCC->CFGR & RCC_CFGR_SWS_Msk);
			timeout--;
		} while ((SW_Status != RCC_CFGR_SWS_PLL) && (timeout > 0));


//		/*--- Use PA8 as MCO output at 48/16 = 3MHz ---*/
//
//		// Set MCO source as SYSCLK (48MHz)
//		RCC->CFGR &= ~RCC_CFGR_MCO_Msk;
//		RCC->CFGR |=  RCC_CFGR_MCOSEL_SYSCLK;
//
//		// Set MCO prescaler to /16 -> 3MHz
//		RCC->CFGR &= ~RCC_CFGR_MCOPRE_Msk;
//		RCC->CFGR |=  RCC_CFGR_MCOPRE_DIV16;
//
//		// Enable GPIOA clock
//		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//
//		// Configure PA8 as Alternate function
//		GPIOA->MODER &= ~GPIO_MODER_MODER8_Msk;
//		GPIOA->MODER |= (0x02 <<GPIO_MODER_MODER8_Pos);
//
//		// Set to AF0 (MCO output)
//		GPIOA->AFR[1] &= ~(0x0000000F);
//		GPIOA->AFR[1] |=  (0x00000000);
//

//		// Update SystemCoreClock global variable
		SystemCoreClockUpdate();

}


// Main program

void main()
{
	uint8_t		rx_byte;

	// Configure System Clock
	SystemClock_Config();

	// Initialize Console
	BSP_Console_Init();
	my_printf("Console Ready!\r\n");

	// Main loop
	while(1)
	{
		// If there is something in USART RDR register
		if ( (USART3->ISR & USART_ISR_RXNE) == USART_ISR_RXNE )
		{
			// Read and report the content of RDR
			rx_byte = USART3->RDR;
			my_printf("You've hit the '%c' key\r\n", rx_byte);
		}
	}
}
