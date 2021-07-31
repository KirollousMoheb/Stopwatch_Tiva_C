#ifndef _Led_Switches_
#define _Led_Switches_
#define red_led 0x02
#define blue_led 0x04
#define green_led 0x08
#define sw_1 0x10
#define sw_2 0x01



void InitPortF(void);
void LedOn(unsigned char);
void LedOff(unsigned char);
unsigned char readSwitch(unsigned char);
void clearSwitch(unsigned char);



#endif
