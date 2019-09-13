//-------| src/dot.c |-------//
#include "dot.h"


static unsigned short dot_hexadecimal[16][MAX_DOT] = {
	{0x7F, 0x41, 0x41, 0x41, 0x7F}, // 0
	{0x00, 0x00, 0x7F, 0x00, 0x00}, // 1
	{0x4F, 0x49, 0x49, 0x49, 0x79}, // 2
	{0x49, 0x49, 0x49, 0x49, 0x7F}, // 3
	{0x78, 0x08, 0x08, 0x7F, 0x08}, // 4
	{0x79, 0x49, 0x49, 0x49, 0x4F}, // 5
	{0x7F, 0x49, 0x49, 0x49, 0x4F}, // 6
	{0x40, 0x40, 0x40, 0x40, 0x7F}, // 7
	{0x7F, 0x49, 0x49, 0x49, 0x7F}, // 8
	{0x78, 0x48, 0x48, 0x48, 0x7F}, // 9
	/* 채울 것 */ 
};

/* 채울 것 */ 
