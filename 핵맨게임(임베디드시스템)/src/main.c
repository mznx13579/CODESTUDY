//-------| src/main.c |-------//
#include "main.h"
#include <string.h>
static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};
static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};
	
static int fd;
static int map_counter = 0;
static void * map_data[100];
static seclection_t sel; 
int round;
int count_char;
int temp_count;
int main(int argc, char* argv[]) {
	
	int check[8]={2,};
	char clcd_str_fin[20]="GAME RESURT";
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	round = 0;
	count_char=0;
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED, PROT_WRITE);
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = mapper(IEB_DOT[i], PROT_WRITE);
	}
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = mapper(IEB_FND[i], PROT_WRITE);
	}
	clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
	clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE);
	keypad_out  = mapper(IEB_KEY_W, PROT_WRITE);
	keypad_in = mapper(IEB_KEY_R, PROT_READ);
	
	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
	init_keypad(keypad_out, keypad_in);
	
	led_all();
	
	sel.all = 0;

	while( logic(check) == TRUE ) {		}
	printf
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

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

truth_t logic(int check[]) {
	int key_value;
	char buf[8];
	char clcd_str[20]="";

	if( sel.all == 0 ) { select_mode(buf); }
	else if( sel.exit == 1 ) { return FALSE; }
	else {
		if( checker() == TRUE){
			input_mode_big(buf,check);
			if(count_char>=8){ 
				clcd_clear_display();
				sprintf(clcd_str,"      RESULT");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "SUCCESS :)");
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				return FALSE;
			}
			else if(round>=8){ 
				clcd_clear_display();
				sprintf(clcd_str,"     RESULT");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "FAIL :(");
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				return FALSE;
			}
		}
		else{
			input_mode_small(buf, check, count_char);
			
			if(count_char>=8){ 
				clcd_clear_display();
				sprintf(clcd_str,"     RESULT");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "SUCCESS :)");
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				return FALSE;
			}
			else if(round>=8){ 
				clcd_clear_display();
				sprintf(clcd_str,"     RESULT");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "FAIL :(");
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				return FALSE;
			}
		}
	}

	return TRUE;
}



void select_mode(char buf[]) {
	int i, key_value;  
	char clcd_str[20]="";
	temp_count=0;
	led_clear();
	dot_clear();
	fnd_clear();
	clcd_clear_display();
	
	printf("\n");
	printf("*********** Select device **********\n");
	printf("*******     MAX SIZE 8     *********\n");
	printf("*******     ONLY CAPITAL    ********\n");
	printf("*******     WRITE YOUR WORD ********\n");
	printf("************************************\n\n");
	scanf("%s", buf);
	for(i=0; buf[i]!=0;i++){
		temp_count++;
	}
	count_char=8-temp_count;
	
	sel.all=0xFF; sel.exit=0;
	strcat(clcd_str, "HACK MAN GAME");
	clcd_write_string(clcd_str);
	/*for( i=0; i<strlen(buf); i++ ) {
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
	if( sel.dot  == 1 ) { strcat(clcd_str, "Dot "); }
	if( sel.fnd  == 1 ) { strcat(clcd_str, "FND "); }
	if( sel.clcd == 1 ) { strcat(clcd_str, "CLCD"); }
	clcd_write_string(clcd_str);*/
}

void input_mode_small(char buf[], int check[]) {
	int key_count, key_value;
	char clcd_str[20]="";
	key_count = keypad_read(&key_value);
	int t, u;
	int exist=0;
	if(key_count == 1){
		round=round+1;
		for(t=0; t<8;t++){
			if(buf[t]==key_value+65){
				check[t]=1;
				count_char=count_char+1;
				exist=1;
			}
		}
		if( sel.led ==1){led_clear(); led_round(round);}
		if( sel.dot ==1){dot_clear(); dot_write(key_value);}
		if( sel.fnd ==1){
			for(u=0;u<8;u++){
				if(check[u]==1){
					fnd_write(1,7-u);
				}
				else{
					fnd_write(0,7-u);
				}
				// else if 3
			}
		}
		if( sel.clcd==1){
			if(exist==1){
				clcd_clear_display();
				sprintf(clcd_str,"HACK MAN");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "%c exists",(key_value+65));
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				exist=0;
			}
			else if (exist==0){
				clcd_clear_display();
				sprintf(clcd_str,"HACK MAN");
				clcd_set_DDRAM(0x00);
				clcd_write_string(clcd_str);
				sprintf(clcd_str, "%c not exists",(key_value+65));
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				exist=0;
			}
		}
	}
	else if(key_count>1){
		sel.all=0;
	}
}

void input_mode_big(char buf[], int check[]) {
	int key_count, key_value;
	char clcd_str[20]="";
	key_count = keypad_read(&key_value);
	int  t, u;
	int exist=0;

	if(key_count == 1){
		round=round+1;
		for(t=0; t<8;t++){
			if(buf[t]==key_value+77){
				check[t]=1;
				count_char=count_char+1;
				exist=1;
			}
		}
		if( sel.led ==1){led_clear(); led_round(round);}
		if( sel.dot ==1){dot_clear(); dot_write(key_value+12);}
		if( sel.fnd ==1){
			for(u=0;u<8;u++){
				if(check[u]){
					fnd_write(1,7-u);
				}
				else{
					fnd_write(0,7-u);
				}
				// else if 3
			}
		}
		if( sel.clcd==1){
			if(exist==1){
				clcd_clear_display();
				sprintf(clcd_str,"HANG MAN");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "%c exists",(key_value+77));
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				exist=0;
			}
			else if (exist==0){
				clcd_clear_display();
				sprintf(clcd_str,"HANG MAN");
				clcd_set_DDRAM(0x00);

				clcd_write_string(clcd_str);
				sprintf(clcd_str, "%c not exists",(key_value+77));
				clcd_set_DDRAM(0x40);
				clcd_write_string(clcd_str);
				exist=0;
			}
		}
	}
	
	else if(key_count>1){
		sel.all=0;
	}
}



