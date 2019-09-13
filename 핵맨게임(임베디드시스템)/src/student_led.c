//-------| src/led.c |-------//
#include "led.h"

/* 채울 것 */ 

void led_bit(int number) {
	*led = (short)~(number << /* 채울 것 */ );
}
