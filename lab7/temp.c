#include "stm32f429xx.h"
#include "uart.h"
#include "RccConfig.h"

#define ARM_MATH_CM4

void GPIO_Init(void);
void TIM2_us_Delay(uint32_t delay); 																							


uint32_t static data;    //  vriable declaration etc.
double static time,dist;   //variable for collecting the distance, time etc.

void GPIO_Init (void) {									//Configuring PE4 for generating pulse sent to trig pin
	
	RCC->AHB1ENR |= (1<<4);				//Enable GPIOC/E clock
	RCC->AHB1ENR |= (1<<2);
	GPIOE->MODER = 0x100;			//Set the PE4 pin to output mode

	//Configuring output from echo pin to be sent to the board (PC6 pin)
	GPIOC->MODER = 0x0000;				//Set PC6 to input mode
}

void TIM2_us_Delay(uint32_t delay){
	while(delay--){
		RCC->APB1ENR |= 1; 								//Start the clock for the timer peripheral
		
		
		TIM2->ARR = 15; 									// Total period of the timer
		TIM2->CNT = 0;
		TIM2->CR1 |= 1;										//Start the Timer
		while(!(TIM2->SR & TIM_SR_UIF)){} //Polling the update interrupt flag
		TIM2->SR &= ~0x0001; 							//Reset the update interrupt flag
	}
}

int main(void){
	char buffer[30] ={0};       // initializing a buffer string that will be utilized for sending to UART for display
		
	SysClockConfig();
	UART1Config();
	RCC->CFGR |= 0<<10; 							// set APB1 = 16 MHz
	GPIO_Init();
		
	UART1_SendString("Ultrasonic");		// Setting trig pin to low to initialize the module
	
	while(1){
		//1. Sending 10us pulse to  PE4
		GPIOE->ODR = 0x0000; 			//PE4 is low
		TIM2_us_Delay(2);   //waiting just for 2 us
		GPIOE->ODR = 0x10;			//PE4 set to High
		TIM2_us_Delay(10);							// wait for 10us
		GPIOE->ODR = 0x0000;				// Make PE4 low again
		//double pulse_wid = 0;
		//2. Measure the pulse width of the pulse sent from the echo pin by polling IDR for port C
		TIM2->CNT = 0;
		while (((GPIOC->IDR)&(1<<6))){}
		data = TIM2->CNT;
		
		time = data*(0.0625*0.001);
		dist = time*17000;
		sprintf(buffer, "Distance = %f\r\n", dist);
		UART1_SendString(buffer);	
			
		
	}  
}  
