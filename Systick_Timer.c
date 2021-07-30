#include "Systick_Timer.h"
#include "tm4c123gh6pm.h"


void Sys_tick_Init(){
	NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R=1599999;  

	//NVIC_ST_RELOAD_R=15999999;  
	NVIC_ST_CTRL_R=7; 
	__enable_irq();
}

