#include "LPC43xx.h"
#include "system_LPC43xx.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_gpio.h"
#include "lpc43xx_cgu.h"

volatile uint32_t msTicks = 0; // counter for 1ms SysTicks

#define LED1_BIT			7 //LEDUSB
#define LED1_PORT			0x7


void SysTick_Handler (void) ;

//====================================================================================
void main()
{
	volatile uint32_t i;
	uint32_t timer_mark;
	//while(1);
	
	SystemInit();
	CGU_Init();

	scu_pinmux(0xE ,7 , MD_PDN, FUNC4); 	// P8.1 : USB0_IND1 LED

	GPIO_SetDir(LED1_PORT,(1<<LED1_BIT), 1);

	GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));

	// M3Frequency is automatically set when SetClock(BASE_M3_CLK... was called.
	SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);  				// Generate interrupt @ 1000 Hz
	
	for(;;)
	{
		GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));
		for(i = 0; i < 200000; i++);
		GPIO_SetValue(LED1_PORT,(1<<LED1_BIT));
		for(i = 0; i < 200000; i++);
	}

	while (1)
	{                           					// Loop forever
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		GPIO_ClearValue(LED1_PORT,(1<<LED1_BIT));				// Turn the LED off
	
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		GPIO_SetValue(LED1_PORT,(1<<LED1_BIT));				// Turn the LED on
	}

	/*
	
	// Init on-board LED as output
	GPIO1->FIODIR |= 1 << 18;
	
	// Init SysTick
	SysTick_Config(SystemFrequency / 1000);		// Generate interrupt every 1 ms
	
	for (;;)
	{
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		GPIO1->FIOCLR = 1 << 18;				// Turn the LED off
	
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		GPIO1->FIOSET = 1 << 18;				// Turn the LED on
	}*/
}

//====================================================================================
void SysTick_Handler(void)
{
	GPIO_SetValue(LED1_PORT,(1<<LED1_BIT));
	msTicks++;
}
