#include "StopWatch.h"
#include "tm4c123gh6pm.h"
#include "Systick_Timer.h"
#include "Seven_Segment.h"
#include "Leds_Switches.h"
//Red led indicates the stopwatch is paused
//Green led indicates the stop watch is running



unsigned char paused=0;
unsigned char seconds=0;
unsigned char minutes=0;
void SysTick_Handler(){
	
	//increment seconds each time the reload register goes down to zero
	seconds++;
	//split the seconds and minutes into 2 digits each
	SplitTime(seconds,minutes);
	
	if(seconds>=59){//if seconds reach 59 increment minutes and clear seconds
	seconds=0;
	minutes++;
	}
	if(minutes>=59){//if minutes reach 59 clear all
	minutes=0;
	seconds=0;
	}
	
	while(paused){//if paused=1(when switch 1 is pressed)
	display_On();//keep displaying the last reached time but no increment happens
	if(readSwitch(sw_2)){//if switch 2 is pressed paused=0 and break the loop
		clearSwitch(sw_2);
		paused=0;
		LedOff(red_led);
		LedOn(green_led);
	}		
	}					
}
void StopWatch_On(){
	Sys_tick_Init(100);
	InitPortF();
	Init_Seven_Segment();
	while(1){
	display_On();
	LedOn(green_led);	
	if(readSwitch(sw_1)){
	clearSwitch(sw_1);
	paused=1;
	LedOff(green_led);
	LedOn(red_led);
	}
	
	}
}

