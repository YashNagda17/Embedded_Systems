#include "stm32f4xx.h" 
#include<stdio.h>
#include<string.h>
#include <stdint.h>

void UART1Config (void);
void UART1_SendChar (uint8_t c);
void UART1_SendString (char *string);
uint8_t UART1_GetChar (void);
void delay(int d);
