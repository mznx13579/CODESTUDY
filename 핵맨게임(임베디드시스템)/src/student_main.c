//-------| src/main.c |-------//
#include "main.h"


/* 채울 것 */ 


int main(int argc, char* argv[]) {
	
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED, PROT_WRITE);
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = /* 채울 것 */ 
	}
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = /* 채울 것 */ 
	}
	clcd_cmd  = /* 채울 것 */ 
	clcd_data = /* 채울 것 */ 
	keypad_out  = /* 채울 것 */ 
	keypad_in = /* 채울 것 */ 
	
	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
	init_keypad(keypad_out, keypad_in);
	
	sel.all = 0;
	while( logic() == TRUE ) {	}
	
	unmapper();
	close(fd);
	return 0;
}

short * mapper(off_t offset, int prot) {
	map_data[map_counter] = mmap(NULL, sizeof(short), prot, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

/* 채울 것 */ 

truth_t logic() {
	if( sel.all == 0 ) { select_mode(); }
	else if( sel.exit == 1 ) { return FALSE; }
	else { input_mode(); }
	return TRUE;
}

void select_mode() {
	int i;  char buf[100];
	char clcd_str[20] = "";
	
	led_clear();
	dot_clear();
	fnd_clear();
	clcd_clear_display();
	
	printf("\n");
	printf("*********** Select device **********\n");
	printf("*   l (LED)       d (Dot Matrix)   *\n");
	printf("*   f (FND)       c (CLCD)         *\n");
	printf("*   a (All devices)                *\n");
	printf("*       press 'e' to exit program  *\n");
	printf("************************************\n\n");
	scanf("%s", buf);
	
	for( i=0; i<strlen(buf); i++ ) {
		if( buf[i] == 'l' ) { sel.led = 1; }
		else if( buf[i] == 'd' ) { sel.dot  = 1; }
		else if( buf[i] == 'f' ) { sel.fnd  = 1; }
		else if( buf[i] == 'c' ) { sel.clcd = 1; }
		else if( buf[i] == 'e' ) { sel.exit = 1;  break; }
		else if( buf[i] == 'a' ) { 
			sel.all = 0xFF;  sel.exit = 0;  break;
		}
	}
	
	if( sel.led  == 1 ) { strcat(clcd_str, "LED "); }
	if( sel.dot  == 1 ) { /* 채울 것 */  }
	if( sel.fnd  == 1 ) { /* 채울 것 */  }
	if( sel.clcd == 1 ) { /* 채울 것 */  }
	clcd_write_string(clcd_str);
}

void input_mode() {
	int key_count, key_value;
	char clcd_str[20];
	key_count = keypad_read(&key_value);
	
	if( key_count == 1 ) {
		if( sel.led  == 1 ) { /* 채울 것 */ }
		if( sel.dot  == 1 ) { /* 채울 것 */ }
		if( sel.fnd  == 1 ) { /* 채울 것 */ }
		if( sel.clcd == 1 ) { 
			sprintf(clcd_str, "%#04x            ", key_value);
			clcd_set_DDRAM(0x40);
			clcd_write_string(clcd_str);
		}
	}
	else if( key_count > 1 ) { sel.all = 0; }
}

