
#include "video.h"
#include "audio.h"
#include "input.h"
#include "math.h"
#include "string.h"
#include "time.h"
// #include "memcard.h"
#include "misc.h"


#include "headers/easings.h"
#include "headers/draw.h"
#include "headers/pgoodies.h" //  <-- pre-beta future library of mine .p
#include "biosutils.h" // <-- check this too.



int timer=0;
int x=64;
int y=180;
int shake=0;

void main( void ){

	set_defaults();
	clear_screen(color_black);
	sleep(15);


	define_regions();

	select_texture(biostexture);
	set_multiply_color( color_white );


	play_sound_in_channel( -1, 1);

	while(1){

		clear_screen(color_black);


		timer++;


		select_region(v_matrix); // draw V
		draw3d(
			(-120+x) + rand_btw(-shake, shake),
			y + rand_btw(-shake, shake),
			ease((timer-15)/64.0, NONE, BACK)*32.0
		);

		select_region(v_matrix + 1); // draw i
		draw3d(
			(-100+x) + rand_btw(-shake, shake),
			y + rand_btw(-shake, shake),
			ease((timer-30)/64.0, NONE, BACK)*32.0
		);

		select_region(v_matrix + 2); // draw r
		draw3d(
			(-90+x) + rand_btw(-shake, shake),
			y + rand_btw(-shake, shake),
			ease((timer-45)/64.0, NONE, BACK)*32.0
		);

		select_region(v_matrix + 3); // draw c
		draw3d(
			(-65+x) + rand_btw(-shake, shake),
			y + rand_btw(-shake, shake),
			ease((timer-60)/64.0, NONE, BACK)*32.0
		);

		select_region(v_matrix + 4); // draw o
		draw3d(
			(-40+x) + rand_btw(-shake, shake),
			   y + rand_btw(-shake, shake),
			   ease((timer-75)/64.0, NONE, BACK)*32.0
		);

		select_region(v_matrix + 5); // draw n
		draw3d(
			(-11+x) + rand_btw(-shake, shake),
			y + rand_btw(-shake, shake),
			ease((timer-90)/64.0, NONE, BACK)*32.0
		);

		//print_int(timer,10,10);


		select_region(v_matrix + 6); // draw 32
		draw3d(
			(66-x) + rand_btw(-shake, shake),
			(y+50) + rand_btw(-shake, shake),
			ease((timer-144)/64.0, NONE, BACK)*24.0
		);



		select_region(256);
		set_drawing_scale(640,360);

		set_multiply_color(make_color_rgba(255,255,255, (timer >= 144) * 100.0 * pow(0.97, timer - 144) ));

		draw_region_zoomed_at(0,0);

		shake = (timer >= 144.0) * 5.0 * pow(0.987, timer - 144.0);



	if(!cartridge_connected() && timer > 380)
		request_cart();


	if(timer> 500) pause_channel(1);	// pauses the sound after asking for a cartridge


	if(cartridge_connected()){


		if(timer > 320){
			x= 64 - ease((timer-320)/50.0, CUBIC, NONE)*420;

			stop_channel(1);
			if(timer == 400) run_cartridge();
		}


		if( gamepad_button_start() > 1 ){
			stop_channel(1);
			run_cartridge();

		}

	}


		end_frame();
	}

}
