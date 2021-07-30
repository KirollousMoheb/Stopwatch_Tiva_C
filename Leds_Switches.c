#include "Leds_Switches.h"
#include "tm4c123gh6pm.h"


void InitPortF(){
	SYSCTL_RCGCGPIO_R|= 0x20;
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x1F;                 
	GPIO_PORTF_AMSEL_R = 0x00;        
	GPIO_PORTF_PCTL_R = 0x00;    
	GPIO_PORTF_DIR_R |= 0x0E;         
	GPIO_PORTF_PUR_R = 0x11;                
	GPIO_PORTF_DEN_R |= 0x1F;
//	GPIO_PORTF_IBE_R&=0X11;
//		GPIO_PORTF_IS_R&=0X11;
//	GPIO_PORTF_IEV_R&=0X11;
//	GPIO_PORTF_ICR_R=0X11;
//	GPIO_PORTF_IM_R|=0X11;
//	NVIC_PRI7_R=(NVIC_PRI7_R&0XFF00FFFF)|(0X00400000);
//	NVIC_EN0_R=0X40000000;
//	__enable_irq();
	
}



void LedOn(unsigned char led){
	GPIO_PORTF_DATA_R|= led;	
}
void LedOff(unsigned char led){
	GPIO_PORTF_DATA_R&=~ led;	
}
unsigned char readSwitch(unsigned char sw){
	return !(GPIO_PORTF_DATA_R & sw);
}