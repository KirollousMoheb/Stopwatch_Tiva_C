#include "Leds_Switches.h"
#include "tm4c123gh6pm.h"


void InitPortF(){
	SYSCTL_RCGCGPIO_R|= 0x20;//enable clock for port F
	while((SYSCTL_PRGPIO_R&0X20)==0){}//wait until clock is enabled
	GPIO_PORTF_LOCK_R=0x4C4F434B;//open lock for port F
	GPIO_PORTF_CR_R |= 0x1F;//enable changes for bits [0-4] which is the 3 ledds and the 2 switchess         
	GPIO_PORTF_AMSEL_R = 0x00; //disable analog functions
	GPIO_PORTF_AFSEL_R = 0x00;	//disable alternate function select we will be using the pins as GPIO pins			
	GPIO_PORTF_PCTL_R = 0x00;    
	GPIO_PORTF_DIR_R |= 0x0E;   //the 3 leds are putput and the 2 switches are input      
	GPIO_PORTF_PUR_R = 0x11;    //enable the pull up resistors for the two swiches [F1,F4]       
	GPIO_PORTF_DEN_R |= 0x1F;		//Digital enable for all 5 pins
}
void LedOn(unsigned char led){//Turn a specific led on
	GPIO_PORTF_DATA_R|= led;	
}
void LedOff(unsigned char led){//Turn a specific led off
	GPIO_PORTF_DATA_R&=~ led;	
}
unsigned char readSwitch(unsigned char sw){//Read switch value 
	return !(GPIO_PORTF_DATA_R & sw);
}
void clearSwitch(unsigned char sw){//Disable switch if pressed before
	GPIO_PORTF_DATA_R&=~ sw;	
}
