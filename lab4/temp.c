#include "stm32f429xx.h"
#include "RccConfig.h"

void SysClockconfig(void)
{
	RCC->AHB1ENR = RCC_APB2ENR_USART1EN;
	RCC->AHB1ENR |=(1<<0);
	
	GPIOA->MODER |= (1<<3);
	GPIOA->AFR[1] = (7<<10);
	USART1->CR1 |=(1<<13);
	
	
	
}

int main(void)
{
	while(1){
		
	}
	return 0;
	
}