#include "stm32f4xx.h"

void GPIO_init(void)
{
	RCC->AHB1ENR=RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER &= ~(3UL << 16); // Clear bit 17 and bit 16 
	GPIOE->MODER |= (2UL << 16);
	GPIOE->AFR[1] &= ~(0xF);  //CLEAR AFR[1]
	GPIOE->AFR[1] |= 1UL; 
	GPIOE->PUPDR &= ~(3UL<<16);
}

void TIMl_Init(void)
{
//II Enable TIMER 1 clock
	RCC->APB2ENR = RCC_APB2ENR_TIM1EN; //0x01
	TIM1->CR1 &= ~TIM_CR1_DIR;//0x00 //Select up-counting-0, down-counting-1
//II PrescaLer, slow down the input clock by a factor of (1 + prescaLer) 
	TIM1->PSC = 1599;  
//II Auto-reload
	TIM1->ARR =  999; //I
//II Clear output compare mode bits for channel 1 
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;
//II Select PWM Mode 1 output on channel 1 (OC1M = 110)
	TIM1->CCMR1|= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
//Output 1 preload enable
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
//II Select output polarity: 0 = Active high, 1 = Active Low
	TIM1->CCER &= ~TIM_CCER_CC1NP; //II OC1N = OCREF + CC1NP
//II Enable complementary output of channel 1 (CH1N) 
	TIM1->CCER |= TIM_CCER_CC1NE;
//II Main output enable (MOE): 0 = Disable, 1 Enable 
	TIM1->BDTR |= TIM_BDTR_MOE;
//II Output Compare Register for channel 1 
	TIM1->CCR1 = 500; //II Initial duty cycle 50%
//II Enable counter
	TIM1->CR1|= TIM_CR1_CEN;//0x01
}

int main(void)
{
	uint32_t c,i;
	c = 0;
	GPIO_init();
	TIMl_Init();
	
	while(1)
	{
		TIM1->CCR1 = c;
		c = (c+10)%1000;
		for(i=0;i<50000;i++){}
		
	}
	
	return 0;
}



