//-------| lib/main.h |-------//
#ifndef	MAIN_H
#define	MAIN_H 


#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t , usleep()
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>		// strlen()
//각 함수를 사용하기 위한 헤더파일 호출

#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "clcd.h"
#include "keypad.h"
//프로그램 실행에 필요한 헤더파일 호출


typedef enum {	//truth_t자료형 정의
	FALSE = 0,
	TRUE  = 1
} truth_t;

typedef enum {	//error_t자료형 정의
	ERROR	= -1,
	SUCCESS	= 0
} error_t;

typedef union {	//구조체의 비트필드 seclection_t 정의
	unsigned char all;
	struct {					
		unsigned char  led : 1;	
		unsigned char  dot : 1;
		unsigned char  fnd : 1;
		unsigned char clcd : 1;
		unsigned char exit : 1;
	};
} seclection_t;
//|							all(char형 1byte)										|
//| 빈공간 | 빈공간 | 빈공간 | exit(1bit) | clcd(1bit) | fnd(1bit) | dot(1bit) | led(1bit) |
//all을 bit단위로 쪼개어 각 비트마다 멤버를 선언(선언하는 순서대로 하위비트부터 채워진다)

int main();
short * mapper(off_t offset, int prot);
void unmapper();
void emergency_closer();

truth_t logic();
void select_mode();
void input_mode_small();
void input_mode_big();
//void playgame();

#endif
