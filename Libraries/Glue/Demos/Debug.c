#include "video.h"
#include "time.h"

#include "glue_debug.h"

int integer=0;
float fl=0;
bool boolean=false;

void main(void){

	while(true){
		clear_screen(color_black);
		
		
		integer++;
		fl+=0.1;
		
		
		if( integer>120  ){
			if( boolean ){ boolean=false; integer=0; }
				else{ boolean=true;integer=0;}
		}
		
		
		//magic:
		print_int(integer,15,integer);
		
		print_float(fl,30,fl);
		
		print_bool(boolean,45,boolean);
		

		end_frame();
		}
}