#include "video.h"
#include "time.h"
#include "input.h"

#define glue_AnimLimit 5
#include "glue_animator.h"

//unnecessary function, I don't want to repeat the code so much

void fast(int type){
	glue_move_edit(0, type);
	glue_move_edit(1, type);
	glue_move_edit(2, type);
	glue_move_edit(3, type);
	glue_move_edit(4, type);
	glue_move_edit(5, type);
}

void main(void){
	int ein=50;
	int eout=50;
	int einout=50;
	int bin=50;
	int bout=50;
	int binout=50;

	glue_move_start();

	while(true){
		
		clear_screen(color_black);

	ein=glue_move(0, ein, 360, 0.5, ease_in);
	eout=glue_move(1, eout, 360, 0.5, ease_out);
	einout=glue_move(2, ein, 360, 0.5, ease_inout);
		bin=glue_move(3, bin, 360, 0.5, back_in);
		bout=glue_move(4, bout, 360, 0.5, back_out);
		binout=glue_move(5, binout, 360, 0.5, back_inout);

		
		if(gamepad_button_a()>0) fast(go_start);
		if(gamepad_button_b()>0) fast(go_end);
		if(gamepad_button_x()>0) fast(go_pause);
		if(gamepad_button_y()>0) fast(go_continue);
		if(gamepad_button_start()>0) fast(delete_key);


	print_at(ein,10,"ease in");
	print_at(eout,25,"ease out");
	print_at(einout,40,"ease in-out");
	print_at(bin,55,"back in");
	print_at(bout,70,"back out");
	print_at(binout,85,"back in-out");	


		print_at(50,100,"i");
				print_at(360,100,"i");
		end_frame();
		}
}