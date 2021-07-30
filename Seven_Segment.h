#ifndef _SevenSegment_
#define _SevenSegment_
#define First_Digit 8
#define Second_Digit 4
#define Third_Digit 2
#define Fourth_Digit 1
void delay(void);
void Init_Digits_Enable(void);
void Init_Digits_Data(void);
void Init_Seven_Segment(void);
void show_Digit(unsigned char,unsigned char);
void display_On(void);
void SplitTime(unsigned char,unsigned char);
#endif
