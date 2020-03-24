/*
 * main.c
 */

#define DELAY_ON	20000
#define DELAY_OFF	100000

static void 	reset_handler 		(void);
static void 	default_handler		(void);
int 			main 			(void);

/* Minimal vector table */
__attribute__ ((section(".isr_vector")))
void (* const table_interrupt_vector[])(void) =
{
	(void *)0x20000800, 	// 0 - stack
	reset_handler, 	 	// 1 - reset handler
	default_handler, 	// 2 - NMI handler
	default_handler, 	// 3 - Hardfault handler
};

/* Main program */
int main(void)
{
    int i = 0, j = 0;
    unsigned char state = 0;

//	*(int *)0x40021014 |=  (0x01 <<17U);
//	*(int *)0x48000000 &= ~(0xC00);
//	*(int *)0x48000000 |=  (0x01 <<10U);

    //AHB
    *(int *)0x40023830 |=  (0x01 <<1U);
    //gpio output MODER

    *(int *)0x40020400 |=  (0x00 <<29U);
    *(int *)0x40020400 |=  (0x01 <<28U);
    //gpio mode OTYPER
    *(int *)0x40020404 |=  (0x00 <<14U);

    //gpio speed GPIOx_OSPEEDR
    *(int *)0x40020408 |=  (0x00 <<29U);
    *(int *)0x40020408 |=  (0x00 <<28U);
    //gpio intial PUPDR
    *(int *)0x4002040c |=  (0x00 <<29U);
    *(int *)0x4002040c |=  (0x01 <<28U);

    //gpio intial PUPDR
    *(int *)0x40020414 |=  (0x01 <<14U);

    while(1)
	{
		switch (state)
		{
			case 0:
			{
//				*(int *)0x48000014 &= ~0x00000020U;
//				i++;
//				if (i>DELAY_OFF)
//				{
//					i = 0;
//					j++;
//					state = 1;
//				}
				break;
			}
			case 1:
			{
//				*(int *)0x48000014 |= 0x00000020U;
//				i++;
//				if (i>DELAY_ON)
//				{
//					i = 0;
//					state = 0;
//				}
				break;
			}
		}
	}
}

/* Reset handler */
void reset_handler (void)
{
	main();
}

/* Default handler */
void default_handler(void)
{
	for(;;);
}
