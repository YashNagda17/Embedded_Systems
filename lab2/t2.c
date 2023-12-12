#include "stm32f429xx.h"
#include "RccConfig.h"
#include "uart.h"


void delay(int dd);
void UART2Config (void);
void UART2_SendString(char* s);
void UART2_SendChar (uint8_t c);
uint8_t UART2_GetChar (void);

void UART2Config (void)
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

void delay (int dd)
{
	int i;
	for (;dd>0;dd--)
	{
		for(i=0;i<30000;i++);
	}
}


void UART2_SendString(char* s){
	for (int i=0;i<11;i++){
	UART2_SendChar(s[i]);
	if(s[i]=='p'){
		RCC->AHB1ENR |=0x40;
		GPIOG->MODER |=0x10000000;
		GPIOG->ODR=0x4000;
		delay(10);
	}
	}
}

void UART2_SendChar (uint8_t c)
{
	USART1->DR = c; 
	while (!(USART1->SR & (1<<7))); 
}

uint8_t UART2_GetChar (void)
{

uint8_t temp;
while (!(USART1->SR & (1<<5))); 
temp = USART1->DR;
return temp;
}
 
int main(void)
{
	SysClockConfig();
	UART2Config ();
	char *s = "IIT Jodhpur";
	UART2_SendString(s);

}