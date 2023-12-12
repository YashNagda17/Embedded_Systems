#include "encoder.h"
#include "SysClockConfig.h"
#include "TM1637.h"

uint32_t current,previous;
#define rate 1000
int tog=1;
int main(void)

{
SysClockConfig();
systick_init();
//encoder_init(9999);
tm1637Init();

while(1)
{

	
	
current=get_encoder_value();
	
	for(int i=0;i<10000;i++)
	tm1637DisplayDecimal(i,tog);
	


	
if(millis()-previous>1000){tog=!tog; previous=millis();}

	
}


}


