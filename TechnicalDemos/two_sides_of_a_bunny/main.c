//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//
//         TWO SIDES OF A BUNN DEMO
//     This demo shows a method to draw
// a texture only on one side of the screen.
//
//  Keypoints:
//    - line 34: variables.
//    - line 80: drawing the awesome bunny on the left side.
//    - line 95: drawing the good bunny on the right side.
//
// I actually made this effect thinking on split screen games :p
//
//    MADE WITH SOME BRAINCELLS BY @Palta, 2026
//
//´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´´



#include "video.h"
#include "input.h"
#include "math.h"
#include "time.h"

// taken from PGoodies library, only function needed.
float clamp(float value, float min, float max){
	if (value < min) return min;
	else if( value > max) return max;
	else return value;

}


#define region_squared_size 255

int x = 0;					// X position of our bunny
int middle_line = 320;		// Separatory line

bool draw_awesome = 1;
bool draw_good = 1;

int timer=0; // used only for bunny movement


void main(void){


	while(1){
		timer++;
		clear_screen(0xFF0F0F0F);

		set_multiply_color(0xAAFFFFFF);

		// left to right movement, controls, nothing important

		x=sin(timer/64.0)*180+320-region_squared_size/2;

		if(gamepad_button_a() == 1){
			if(draw_awesome) draw_awesome = 0;
			else draw_awesome = 1;

		}

		if(gamepad_button_b() == 1){
			if(draw_good) draw_good= 0;
			else draw_good = 1;

		}

		if(gamepad_left()>0) middle_line--;
		if(gamepad_right()>0) middle_line++;




		select_texture(0);
		select_region(0);

		// awesome bun (left side)
		if(draw_awesome){
			print_at(middle_line-115,30,"Awesome bun");


			// redefines the texture so it never draws past middle_line.

			define_region_topleft(0, 0, clamp(middle_line-x, 0, region_squared_size), region_squared_size );

			if(x<middle_line)
				draw_region_at(x, 55);
		}



		// good bun (right side)
		if(draw_good){
			print_at(middle_line+10,30,"Good bun");


			// this one is harder.
			// it moves the first point X position so it follows the texture and middle_line positions.
			// and moves it so it never gets drawn behind middle_line

			define_region_topleft( clamp(middle_line-x + region_squared_size, region_squared_size, region_squared_size*2), 0, region_squared_size*2, region_squared_size);

			if(x>middle_line-region_squared_size)
				draw_region_at(clamp(x, middle_line, 640), 55);
		}



		select_texture(-1);
		select_region(256);

		// draw a vertical line in the middle, not important.
		set_drawing_scale(2,281);
		draw_region_zoomed_at(middle_line,30);

		print_at(230,0,"Two sides of a bunn");


		print_at(10,320,"Press A and B to hide bunns\nLEFT and RIGHT to move division line");

		end_frame();
	}
}
