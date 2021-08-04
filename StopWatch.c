#include "StopWatch.h"
#include "tm4c123gh6pm.h"
#include "Systick_Timer.h"
#include "Seven_Segment.h"
#include "Leds_Switches.h"
//Red led indicates the stopwatch is paused
//Green led indicates the stop watch is running



unsigned char paused=0;
unsigned char pause=0;
unsigned char resume=0;
unsigned char seconds=0;
unsigned char minutes=0;
void SysTick_Handler(){
	if(!paused){
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
			if(readSwitch(sw_2)){
	clearSwitch(sw_2);

	resume++;
		if(resume-pause>=5){
		Sys_tick_Init(1000);
												}
							}
			}	
}
void StopWatch_On(){
	Sys_tick_Init(100);
	InitPortF();
	Init_Seven_Segment();
	
	while(1){
	display_On();
	if(paused){
		LedOn(red_led);
		LedOff(green_led);
	}else{
		LedOn(green_led);
		LedOff(red_led);
	}
	if(readSwitch(sw_1)){
	clearSwitch(sw_1);
	pause++;
	paused=1;	
	}
	if(readSwitch(sw_2)){
	clearSwitch(sw_2);
	pause++;
	paused=0;
	}
	
	}
}

