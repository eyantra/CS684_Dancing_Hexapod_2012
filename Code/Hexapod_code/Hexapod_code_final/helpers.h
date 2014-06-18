#ifndef HELPERS_H
#define HELPERS_H 0

#include "globals.h"

void buzzer_on (void)
{
 PORTC = PORTC | 0x08;
}

void buzzer_off (void)
{
 PORTC = PORTC & 0xF7;
}

void delay_25ms(void)
{
 delay_count = 0;
 while(delay_count < 10);
}

void delay_xms(unsigned int x){
delay_count = 0;
while(delay_count<2*(x/5));
}

void delay_50ms(void)
{
 delay_count = 0;
 while(delay_count < 20);
}

void delay_100ms(void)
{
 delay_count = 0;
 while(delay_count < 40);
}

void delay_250ms(void)
{
 delay_count = 0;
 while(delay_count < 100);
}

void delay_500ms(void)
{
 delay_count = 0;
 while(delay_count < 200);
}

void delay_1s(void)
{
 delay_count = 0;
 while(delay_count < 400);
}

#endif