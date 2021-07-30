#include "StopWatch.h"
#include "tm4c123gh6pm.h"
#include "Systick_Timer.h"
#include "Seven_Segment.h"
#include "Leds_Switches.h"

unsigned char seconds=0;
unsigned char minutes=0;
unsigned char flag=0;



void SysTick_Handler(){
		seconds++;
		SplitTime(seconds,minutes);
	if(seconds>=59){
		seconds=0;
		minutes++;
	}
	if(minutes>=59){
	minutes=0;
	seconds=0;
	}
	
	
	while(flag){
		if(readSwitch(sw_2)){
			flag=0;
			LedOff(red_led);
			LedOn(green_led);
		}
	display_On();	
	}					
}


void StopWatch_On(){
	Sys_tick_Init();
	InitPortF();
	Init_Seven_Segment();
	while(1){
		display_On();
		LedOn(green_led);	
		if(readSwitch(sw_1)){
		flag=1;
		LedOff(green_led);
		LedOn(red_led);
		}
	
	}
}

