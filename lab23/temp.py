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




#include "stm32f429xx.h"

void delay(int dd);

int main(void)
{
	RCC->AHB1ENR |=0x40;
	GPIOG->MODER |=0x14000000;
	GPIOG->ODR=0x6000;
	short int a = 0;
	while(1)
	{
		//GPIOG->ODR = 0x
		if (a)
		{
			GPIOG->ODR=0x0000;
			delay(12);
			GPIOG->ODR=0x4000;
			delay(12);
			a = 0;
		}
		else
		{
			GPIOG->ODR=0x0000;
			delay(12);
			GPIOG->ODR=0x2000;
			delay(12);
			a = 1;
		}
	
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


#include "stm32f429xx.h"

void delay(int dd);

int main(void)
{
	RCC->AHB1ENR |=0x41;
	GPIOA->IDR = 0x1;
	GPIOG->MODER |=0x14000000;
	GPIOA->MODER |=0x0;
	GPIOG->ODR=0x0000;
	short int a = 0;
	while(1)
	{
		
		if (a)
		{
			
			GPIOG->ODR=0x4000;
			delay(12);
		}
		if ((GPIOA->IDR) & 1)
		{
			a = 1;
		}
		
	
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




