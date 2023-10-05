/*PORTF PF0 and PF4 fall edge interrupt example*/
/*This GPIO interrupt example code controls green LED with switches SW1 and SW2 external interrupts */

#include "TM4C123.h"                    // Device header
#define BLUE (1<<2)
void Time1A_1sec_delay(void);
int main(void)
{
    SYSCTL->RCC2 = 38000000UL; // set frequence to 38mhz
	  /*Iniitialize PF3 as a digital output pin */  	 
   SYSCTL->RCGCGPIO |= 0x20; // turn on bus clock for GPIOF
   GPIOF->DIR       |= BLUE; // set blue pin as a digital output pin
   GPIOF->DEN       |= BLUE;  // Enable PF2 pin as a digital pin
   Time1A_1sec_delay();
	while(1)
	{
		// do nothing wait for the interrupt to occur
	}
}

/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */
void TIMER1A_Handler(void)
{	
  if (TIMER1->MIS & 0x01) /* check if interrupt causes by PF4/SW1*/
    GPIOF->DATA ^= BLUE;
	TIMER1->ICR = (1<<0);
}
void Time1A_1sec_delay(void)
{
	SYSCTL->RCGCTIMER |= 1<<1; // enable timer A
	TIMER1->CTL =0; // DISABLE TIMERA DURING CONFIG
	TIMER1->CFG= (0); // 32-BITS CONFIG; 0x04 for 16 bits. then need to use prescaler
	TIMER1->TAMR = (1<<1) ; // PERIODIC MODE
	//TIMER1->TAPR = 250U-1U; // PRESCALER 250
	TIMER1->TAILR = 38000000U-1; // INTERVAL LOAD 16MHZ/250
	TIMER1->ICR= (1<<0); // CLEAR INTERRUPT FLAG
	TIMER1->IMR |= (1<<0); // ENABLE TIMEOUT INTERRUPT MASK
	TIMER1->CTL |= (1<<0); // ENABLE TIMER A
	NVIC->ISER[0]|= (1<<21); // ENABLE IRQ 21
}

	
