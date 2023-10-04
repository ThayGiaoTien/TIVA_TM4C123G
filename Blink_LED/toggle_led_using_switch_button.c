#include <stdint.h>
#include "C:\ti\TivaWare_C_Series-2.2.0.295\inc\tm4c123gh6pm.h"
/**
 * main.c
 */
#define GPIO_PORTF_DATA_RD4  (*(( volatile unsigned long *)0x40025040))  // PF4
//#define GPIO_PORTF_DATA_RD0  &GPIO_PORTF_DATA_BITS_R + 0x04 // PF0

#define GPIO_PORTF_DATA_RW3  (*(( volatile unsigned long *)0x40025020)) // PF3 (led green)
//#define GPIO_PORTF_DATA_RW1  (*(( volatile unsigned long *)(&GPIO_PORTF_DATA_BITS_R + 0x08)) // PF1(led red)

# define SYSTEM_CLOC_FREQUENCY  16000000

#define DELAY_DEBOUNCE					SYSTEM_CLOC_FREQUENCY/1000
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	for(i = 0; i<counter; i++);	
}
int main(void)
{
   unsigned int state=0;
   SYSCTL_RCGCGPIO_R |= 0b100000;  // A B C D E F  enable clock for port F
   GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Write 0x4C4F434B unlocks commit register for write acess.if write other value, CR will reapply for lock. 
   GPIO_PORTF_CR_R = 0xFF;           // Enable CR for all GPIO pin. 0x01 works as well.
   GPIO_PORTF_DEN_R  = 0x18;    // enable pf4 and pf3 as digital pins
   GPIO_PORTF_DIR_R  = 0x08;    // pf3 as output
   GPIO_PORTF_DIR_R &= ~0x10; // pf4 as input
   
   GPIO_PORTF_PUR_R = 0x10; // Set pf4 as pull up register.
   while(1){
     if(GPIO_PORTF_DATA_RD4 == 0 )
     {
       Delay(DELAY_DEBOUNCE);
       if(GPIO_PORTF_DATA_RD4==0x00 && state==0)
       {
         GPIO_PORTF_DATA_RW3 ^= 0x08;
         state =1;
       }
     } 
     else 
       state=0;
       
   }
    return 0;
}


void SystemInit(void)
{
    NVIC_CPAC_R |= 0x00F00000;
}
