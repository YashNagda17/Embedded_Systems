#include "stm32f4xx.h"

int main(void)
{
	unsigned short a,b,c;
	a = 0x1B;
	b = 0x0B;
	RCC-> AHB1ENR |= 1;
	GPIOA -> MODER |= 0x5555;
	GPIOA->ODR=0x00;
	c = a+b;
	GPIOA->ODR=a;
	
	
	
	return 0;
}