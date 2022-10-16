#include "video.h"
#include "time.h"
#include "input.h"
#include "glue_debug.h"
#include "math.h"

#include "Glue++.h"
#include "Glue_cline.h"

void main(void){
	int plx=10;
	int ply=10;
	int cy=0;
	int todraw=14;
	

	while(true){
	clear_screen(make_color_rgb(2,0,15));

	txtplay();

	cy++;

	
	if(cy>25)todraw=15;
	if(cy>50){ todraw=14; cy=0; }
	
	



	txt_rect(plx-1, ply-1, 3, 3, true, 17);
	
		txt_rect(40, 12, 6, 6, false, 19+todraw-16);
		txt_rect(40, 3, 6, 6, true, 19+todraw-15);
		
		
	txt_rline(21, 10, plx, 0, 14);
	txt_rline(20, 11, plx, 1, 14);
	txt_rline(19, 10, plx, 2, 14);
	txt_rline(20, 9, plx, 3, 14);
	
		txt_draw(5,12,"burguer cheese");
		txt_draw(5,13,"cheese");
		txt_draw(5,14,"burguer");
	
	screen_draw(plx,ply,todraw);

	txt_draw(plx-3,ply-3,"player");
	

	
	screen_draw(plx,ply-2,86 );
	

	
	
	if(gamepad_up()>1)ply--;
	if(gamepad_down()>1)ply++;
	
	if(gamepad_left()>1)plx--;
	if(gamepad_right()>1)plx++;
	

	end_frame();
	}	
}