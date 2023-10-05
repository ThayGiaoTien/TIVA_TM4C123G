#include "TM4C123.h"                    // Device header
int main()
{
	//SYSCTL->RCC2 = 32000000UL;
  SYSCTL->RCGCGPIO |= 0x20; // turn on bus clock for GPIOF
  GPIOF->DIR       |= 0x04; //set BLUE pin as a digital output pin
  GPIOF->DEN       |= 0x04;  // Enable PF3 pin as a digital pin
	
	SysTick->LOAD = 15999999; // one second delay relaod value
	SysTick->CTRL = 0b0111; ; // enable counter, interrupt enable and select system bus clock 
	SysTick->VAL  = 0; //initialize current value register 
	
	while (1)
	{
		
	}
}	
	
void SysTick_Handler(void)
{
	GPIOF->DATA ^= 0x04; 
}

