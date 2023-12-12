#include "stm32f429xx.h"

void delay(int dd);

int main(void)
{
	RCC->AHB1ENR |=0x40;
	GPIOG->MODER |=0x14000000;
	GPIOG->ODR=0x5000;
	while(1)
	{
	GPIOG->ODR=0x0000;
	delay(1200);
	GPIOG->ODR=0x5000;
	delay(12);
	}
	return 0;
}

void delay(int dd)
{
	for(;dd>0;dd--)
	{
		for(int j=0;j<30000;j++)
		{
			dd = dd*1;
		}	
	}
}
