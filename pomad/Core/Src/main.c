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

	*(int *)0x40021014 |=  (0x01 <<17U);
	*(int *)0x48000000 &= ~(0xC00);
	*(int *)0x48000000 |=  (0x01 <<10U);

	while(1)
	{
		switch (state)
		{
			case 0:
			{
				*(int *)0x48000014 &= ~0x00000020U;
				i++;
				if (i>DELAY_OFF)
				{
					i = 0;
					j++;
					state = 1;
				}
				break;
			}
			case 1:
			{
				*(int *)0x48000014 |= 0x00000020U;
				i++;
				if (i>DELAY_ON)
				{
					i = 0;
					state = 0;
				}
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
