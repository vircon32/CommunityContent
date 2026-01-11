
#include "video.h"
#include "audio.h"
#include "input.h"
#include "math.h"
#include "string.h"
#include "time.h"
#include "misc.h"

#include "libs/easings.h"
#include "libs/textfont.h"

#include "libs/UbuntuMono_B_30.h"
#include "libs/Retro_Gaming_11.h"


#define number_of_effects 15

#define region_logo		0
#define region_ball		1
#define region_button	2
#define region_arrow	3
#define region_controls	4


int effect=-1;

float timer=0;

int clear_color=0xEA1b1111;



#include "effects.h"

bool is_intro_over=false; //set to true if you want to skip into (might not be a good idea)
bool show_controls=true;
#include "ui.h"

void main(void){

	setupFontUbuntuMono_B_30();
	setupFontRetro_Gaming_11();
	select_texture(0);

	select_region( region_logo );
	define_region_center(0,0, 137,93);

	select_region( region_ball );
	define_region_center(139,0, 186,47);

	select_region( region_button );
	define_region_center(188,0, 215,27);

	select_region( region_arrow );
	define_region_center(139,49, 177,82);

	select_region( region_controls );
	define_region_topleft(217,0, 264,47);



	while(1){

		clear_screen(clear_color);

		if(!is_intro_over) intro();
		else{

			if(gamepad_button_start()==1) timer = 0.0;

			if(gamepad_button_a()==1 && !info_open) info_open=true;
			else if(gamepad_button_a()==1 && info_open) info_open=false;

			if(gamepad_left()==1 && effect>0){
			effect--; timer=0;
			}

			if(gamepad_right()==1 && effect<number_of_effects){
				effect++; timer=0; show_controls=false;
			}



			if(show_controls){
				select_texture( 0 );

				select_region(region_controls);
				set_multiply_color(make_gray( (sin(timer*3)*64)+192 ));
				draw_region_at(10, 200);

				textfont_print_from_left(&FontRetro_Gaming_11, 68, 210, "Use left and right\nto navigate");
				set_multiply_color(0xFFFFFFFF);
			}

			select_texture( 0 );
			select_region( region_ball );


			switch(effect){

				case 0: effect_offset(timer); break;

				case 1: effect_simple_ease(timer); break;

				case 2: effect_different_ease(timer); break;

				case 3: effect_two_axis_ease(timer); break;

				case 4: effect_time_offset(timer); break;

				case 5: effect_follow_by_offset(timer); break;

				case 6: effect_only_one_offset(timer); break;

				case 7: effect_concatenate(timer); break;

				case 8: effect_scale(timer); break;

				case 9: effect_rotation(timer); break;

				case 10: effect_rotozoomed(timer); break;

				case 11: effect_none(timer); break;

				case 12: effect_dual_none(timer); break;

				case 13: effect_speed(timer); break;

				case 14: effect_multiple_speed(timer); break;

				case 15: effect_repeat(timer); break;


			}

			info();


			timer+=0.01;

		}
		end_frame();

	}

}
