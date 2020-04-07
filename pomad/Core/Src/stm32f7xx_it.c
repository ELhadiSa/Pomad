
/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * This function handles EXTI line 13 interrupt request.
  */
#include "STM32F746xx.h"
extern uint8_t	console_rx_byte;
extern uint8_t	console_rx_irq;

extern int my_printf(const char *format, ...);



extern uint8_t button_irq;

void EXTI15_10_IRQHandler()
{
	// Test for line 13 pending interrupt
	if ((EXTI->PR & EXTI_PR_PR13_Msk) != 0)
	{
		// Clear pending bit 13 by writing a '1'
		EXTI->PR = EXTI_PR_PR13;

		// Do what you need
		button_irq++;
	}
}

/*
 * This function handles TIM6 interrupts
 */

extern uint8_t timebase_irq;

void TIM6_DAC_IRQHandler()
{
	// Test for TIM6 update pending interrupt
	if ((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		// Clear pending interrupt flag
		TIM6->SR &= ~TIM_SR_UIF;

		// Do what you need
		timebase_irq = 1;
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */


void USART3_IRQHandler()
{
	// Test for RXNE pending interrupt
	if ((USART3->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
	{
		// RXNE flags automatically clears when reading RDR.

		// Store incoming byte
		console_rx_byte = USART3->RDR;
		console_rx_irq = 1;
	}

}
void SysTick_Handler(void)
{
  // HAL_IncTick();
}
