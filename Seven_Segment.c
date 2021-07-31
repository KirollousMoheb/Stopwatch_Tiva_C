#include "Seven_Segment.h"
#include "tm4c123gh6pm.h"
unsigned char digit1,digit2,digit3,digit4;

void delay(void){
	unsigned long volatile time;
	time = 727240*200/91000; 		
	while(time){
	time--;
  }
}
void Init_Digits_Enable(){ //Port E     
	SYSCTL_RCGCGPIO_R|= 0x10;   
	while((SYSCTL_PRGPIO_R&0X10)==0){}	
	GPIO_PORTE_LOCK_R=0x4C4F434B;
	GPIO_PORTE_CR_R = 0x0F;              
	GPIO_PORTE_AMSEL_R = 0x00; 
	GPIO_PORTE_AFSEL_R = 0x00;				
	GPIO_PORTE_PCTL_R = 0x00;
	GPIO_PORTE_DIR_R = 0x0F; 
	GPIO_PORTE_PUR_R = 0x00;          
	GPIO_PORTE_DEN_R = 0x0F;
}
void Init_Digits_Data(){//Port B				
	SYSCTL_RCGCGPIO_R |= 0x02; 
  while((SYSCTL_PRGPIO_R&0X02)==0){}	
  GPIO_PORTB_LOCK_R=0x4C4F434B;
	GPIO_PORTB_CR_R = 0x7F;            
	GPIO_PORTB_AMSEL_R = 0x00; 
	GPIO_PORTB_AFSEL_R = 0x00;		
	GPIO_PORTB_PCTL_R = 0x00;        
	GPIO_PORTB_DIR_R = 0x7F; 	
	GPIO_PORTB_PUR_R = 0x00;            
	GPIO_PORTB_DEN_R = 0x7F;
}
void Init_Seven_Segment(){
	Init_Digits_Data();
	Init_Digits_Enable();
}
void show_Digit(unsigned char digit,unsigned char value){
	unsigned char values[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
	GPIO_PORTB_DATA_R = 0x00;
	GPIO_PORTE_DATA_R = 0x00;
	GPIO_PORTE_DATA_R = digit;
	GPIO_PORTB_DATA_R =~values[value];
	delay();
	 } 
void display_On(){
	show_Digit(First_Digit,digit1);
	show_Digit(Second_Digit,digit2);
	show_Digit(Third_Digit,digit3);	
	show_Digit(Fourth_Digit,digit4);
}
void SplitTime(unsigned char seconds,unsigned char minutes){
	digit1 = seconds % 10;	
	seconds /= 10;		
	digit2 = seconds % 10;              
	seconds /= 10;
	digit3 = minutes % 10;
	minutes /= 10;
	digit4 = minutes % 10;
	minutes/= 10;
}
