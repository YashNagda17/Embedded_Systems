//#include "stm32f4xx.h" 
#include "RccConfig.h"

#include<stdio.h>
#include<string.h>



void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		//Delay_us (1000); // delay of 1 ms
	}
}

void UART1Config (void)
{
		/******* STEPS FOLLOWED ********
	
	1. Enable the UART CLOCK and GPIO CLOCK
	2. Configure the UART PINs for ALternate Functions
	3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	4. Program the M bit in USART_CR1 to define the word length.
	5. Select the desired baud rate using the USART_BRR register.
	6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register

	********************************/
	
	// 1. Enable the UART1 CLOCK and GPIO CLOCK
	//RCC->APB1ENR |= (1<<14);  // Enable UART1 CLOCK
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHB1ENR |= (1<<0); // Enable GPIOA CLOCK
	
	//RCC->CFGR |=(4<<11);
	//RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	// 2. Configure the UART PINs for ALternate Functions
	GPIOA->MODER |= (1<<21);  // Bits (21:20)= 1:0 --> Alternate Function for Pin PA10
	GPIOA->MODER |= (1<<19);  // Bits (19:18)= 1:0 --> Alternate Function for Pin PA9
	
	//GPIOA->OSPEEDR |= (3<<19) | (3<<21);  // Bits (19:20)= 1:1 and Bits (21:21)= 1:1 --> High Speed for PIN PA9 and PA10
	
	GPIOA->AFR[1] |= (7<<4);  // Bytes (7:6:5:4) = 0:1:1:1  --> AF7 Alternate function for USART1 at Pin PA9
	GPIOA->AFR[1] |= (7<<8); // Bytes (11:10:9:8) = 0:1:1:1  --> AF7 Alternate function for USART1 at Pin PA10
	
	// 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USART1->CR1 = 0x00;  // clear all
	USART1->CR1 |= (1<<13);  // UE = 1... Enable USART
	
	// 4. Program the M bit in USART_CR1 to define the word length.
	USART1->CR1 &= ~(1<<12);  // M =0; 8 bit word length
	USART1->CR2 =0x00;
	// 5. Select the desired baud rate using the USART_BRR register.
	
	//USART1->CR3 &= ~USART_CR1_OVER8;
	
	USART1->BRR	 =9600; //115200 baud rate
	
	// 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
	USART1->CR1 |= (1<<2); // RE=1.. Enable the Receiver
	USART1->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}


void UART1_SendChar (uint8_t c)
{
		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
	
	USART1->DR = c; // load the data into DR register
	while (!(USART1->SR & (1<<7)));  // Wait for TC to SET.. This indicates that the data has been transmitted
	//USART1->DR = c;
}
	



void UART1_SendString (char *string)
{
	while (*string) UART1_SendChar (*string++);
}

uint8_t UART1_GetChar (void)
{
			/*********** STEPS FOLLOWED *************
	
	1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	2. Read the data from USART_DR  Register. This also clears the RXNE bit
	
	****************************************/

	uint8_t temp;
	
	while (!(USART1->SR & (1<<5)));  // wait for RXNE bit to set
	temp = USART1->DR;  // Read the data. This clears the RXNE also
	return temp;
}
	

