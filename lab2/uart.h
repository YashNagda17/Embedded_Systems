#include "stm32f4xx.h" 
#include<stdio.h>
#include<string.h>
#include <stdint.h>

void UART1Config (void);
void UART1_SendChar (uint8_t c);
uint8_t UART1_GetChar (void);