#include "Seven_Segment.h"
#include "tm4c123gh6pm.h"

/****************************************************/   
/*
*  Hardware Connentions
*
* [PE0 - PE3] -> enable pins for each 7-Segments digit
* [PB0 - PB6] ->[A-G] pins of te 4 7-Segments unit
*  
****************************************************/
unsigned char digit1,digit2,digit3,digit4;//globale variables representing the value of the 4 7-Segments unit
//5ms delay between displaying each digit to maintain that the 4 digits will be displayed at the same time
void delay(void){
	unsigned long volatile time;
	time = 727240*200/91000; 		
	while(time){
	time--;
  }
}
void Init_Digits_Enable(){   
	SYSCTL_RCGCGPIO_R|= 0x10;  //Enable clock for Port E 
	while((SYSCTL_PRGPIO_R&0X10)==0){}	//Wait until clock is enabled 
	GPIO_PORTE_LOCK_R=0x4C4F434B;//Unlock the port
	GPIO_PORTE_CR_R = 0x0F;              
	GPIO_PORTE_AMSEL_R = 0x00; 
	GPIO_PORTE_AFSEL_R = 0x00;				
	GPIO_PORTE_PCTL_R = 0x00;
	GPIO_PORTE_DIR_R = 0x0F; 
	GPIO_PORTE_PUR_R = 0x00;          
	GPIO_PORTE_DEN_R = 0x0F;//Digital enable for [E0-E3]
}
void Init_Digits_Data(){				
	SYSCTL_RCGCGPIO_R |= 0x02; //Enable clock for Port B
  while((SYSCTL_PRGPIO_R&0X02)==0){}	//Wait until clock is enabled 
  GPIO_PORTB_LOCK_R=0x4C4F434B;//Unlock the port
	GPIO_PORTB_CR_R = 0x7F;            
	GPIO_PORTB_AMSEL_R = 0x00; 
	GPIO_PORTB_AFSEL_R = 0x00;		
	GPIO_PORTB_PCTL_R = 0x00;        
	GPIO_PORTB_DIR_R = 0x7F; 	
	GPIO_PORTB_PUR_R = 0x00;            
	GPIO_PORTB_DEN_R = 0x7F;//Digital enable for [B0-B6]
}
void Init_Seven_Segment(){//initialize tha data and enable functions
	Init_Digits_Data();
	Init_Digits_Enable();
}
//The show digit requires two parameters ,which digit is to be enabled and what is the value to be displayed
void show_Digit(unsigned char digit,unsigned char value){
	//the array holds the value which enabled the pins [B0-B6]==>[A-G] to show the correspoding passed value
	//This values are for a common cathode 4 digit 7-segment so we will invert them when we will be using them
	unsigned char values[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
	GPIO_PORTB_DATA_R = 0x00;//clear port B data register
	GPIO_PORTE_DATA_R = 0x00;//clear port E data register
	GPIO_PORTE_DATA_R = digit;//enable the corresponding digit
	GPIO_PORTB_DATA_R =~values[value];//save the value inside Port B data register 
	delay();
	 } 
void display_On(){//function to display the 4 digits
	show_Digit(First_Digit,digit1);
	show_Digit(Second_Digit,digit2);
	show_Digit(Third_Digit,digit3);	
	show_Digit(Fourth_Digit,digit4);
}
//Function to split any number into 4 digits
//In this case we will be using seconds and minutes and split each of them into two digits
//as their max value is 59
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
