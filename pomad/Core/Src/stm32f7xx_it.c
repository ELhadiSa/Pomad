
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

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  // HAL_IncTick();
}
