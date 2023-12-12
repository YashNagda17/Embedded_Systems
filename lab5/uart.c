#include "stm32f4xx.h"
#include "RccConfig.h"
#include "uart.h"

void UART1Config (void)
{

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		RCC->AHB1ENR |= (1<<0); 
		GPIOA->MODER |= (1<<21); 
	  GPIOA->MODER |= (1<<19);
		GPIOA->AFR[1] |= (7<<4);
		GPIOA->AFR[1] |= (7<<8);
		USART1->CR1 = 0x00; 
	  USART1->CR1 |= (1<<13);

		USART1->CR1 &= ~(1<<12); 
		USART1->CR2 =0x00;

		USART1->BRR =0x249F; 

		USART1->CR1 |= (1<<2); 
		USART1->CR1 |= (1<<3);
}

void UART1_SendString(char* s){
		for (int i=0;i<strlen(s);i++){
			UART1_SendChar(s[i]);
				if(s[i]=='P'){
					RCC->AHB1ENR |=0x40;
					GPIOG->MODER |=0x4000000;
					GPIOG->ODR=0x2000;
				}
		}
}

void UART1_SendChar (uint8_t c)
{ 
		USART1->DR = c; 
		while (!(USART1->SR & (1<<7)));
}


uint8_t UART1_GetChar (void)
{
		uint8_t temp;
		while (!(USART1->SR & (1<<5)));
		temp = USART1->DR;
		return temp;
}

int main()
{
	SysClockConfig();
	UART1Config ();
	char *s = "IIT JODHPUR";
	UART1_SendString(s);
}