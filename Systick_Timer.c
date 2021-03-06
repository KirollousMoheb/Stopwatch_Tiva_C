#include "Systick_Timer.h"
#include "tm4c123gh6pm.h"
#include <Math.h>

void Sys_tick_Init(unsigned int time){
	
	NVIC_ST_CTRL_R = 0;//Disable systick timer
	NVIC_ST_RELOAD_R=((time*pow(10,-3))/(62.5*pow(10,-9)))-1; //value inside the reload register is controled by time parameter
	NVIC_ST_CTRL_R=7; //enable clock,timer and systick intterupt 
	__enable_irq();//enable global interrupts
}

