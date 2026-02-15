
/*--------------------------------------┐
|                                       |
|             BIOS UTILS                |
|  Basic util functions to make a bios  |
|                                       |
|     Functions:                        |
|         - cartridge check             |
|         - jump to cartridge           |
|         - error handler               |
|                                       |
└--------------------------------------*/


#ifndef BIOSUTILS_H
#define BIOSUTILS_H

#define error_memory_read       0
#define error_memory_write      1
#define error_port_read         2
#define error_port_write        3
#define error_stack_overflow    4
#define error_stack_underflow   5
#define error_division          6
#define error_arc_cosine        7
#define error_arc_tangent_2     8
#define error_logarithm         9
#define error_power            10
#define error_unknown          11



//====================================
// Check if a cartridge is connected
//====================================

bool cartridge_connected(){
	asm{ "in R0, CAR_Connected" }
}



//========================
// Jump to the cartridge
//========================

void run_cartridge(){

	asm{

	"mov R0, 1"
	"out GPU_DrawingScaleY, R0"

	"mov R0, 1"
	"out GPU_DrawingScaleX, R0"

	"mov R0, 0xFFFFFFFF"
    "out GPU_MultiplyColor, R0"

	"mov R0, 0"
	"out GPU_DrawingPointX, R0"
	"out GPU_DrawingPointY, R0"

	"out GPU_DrawingAngle, R0"

	"out GPU_SelectedRegion, R0"
	"jmp 0x20000000"

	}
}

void set_defaults(){

	asm{

		"mov R0, 1"
		"out GPU_DrawingScaleY, R0"

		"mov R0, 1"
		"out GPU_DrawingScaleX, R0"

		"mov R0, 0xFFFFFFFF"
		"out GPU_MultiplyColor, R0"

		"mov R0, 0"
		"out GPU_DrawingPointX, R0"
		"out GPU_DrawingPointY, R0"

		"out GPU_DrawingAngle, R0"

	}
}



//==================
// Error handeling
//==================

void error_handler() {
	// do not initialize!

	int error_code;
	int instruction_pointer;
	int instruction;
	int immediate_value;

	// save registers to variables
	asm{
		"mov {error_code}, R0"
		"mov {instruction_pointer}, R1"
		"mov {instruction}, R2"
		"mov {immediate_value}, R3"
	}

	int* error_title = NULL;
	int* error_message = NULL;


	int timer=0;
	int woops_scroll=0;

	select_texture(biostexture);
	select_region(256);

	for(int i=0; i<360; i++){

		set_multiply_color(make_color_rgba(i/205, i/202, i/43, 230 ));
		set_drawing_scale(640,1);
		draw_region_zoomed_at(0,i);


	}


	select_channel(1);

	assign_channel_sound(1,-1);

	play_channel(1);


	// at the moment, set_channel_position function seems broken.
	// so we do this to skip to the sound effect.

	set_channel_speed(128);
	set_channel_volume(0);

	sleep(4);

	set_channel_speed(1);
	set_channel_volume(1);



	while(1){

		timer++;

		woops_scroll = -100 + ease(timer/64.0, NONE, BACK) * 70 ;



		switch(error_code){


			case error_memory_read:

				error_title = "MEMORY READ ERROR";
				error_message = "A write-only device or nonexistent memory\nwas attempted to be read by the program.";

				break;


			case error_memory_write:

				error_title = "MEMORY WRITE ERROR";
				error_message = "A read-only device or nonexistent memory\nwas attempted to be written by the program.";

				break;


			case error_port_read:

				error_title = "INVALID PORT READ";
				error_message = "An invalid or write-only port \n was attemped to be read by the program.";

				break;


			case error_port_write:

				error_title = "INVALID PORT WRITE";
				error_message = "An write-only port was attemped \nto be read by the program.";

				break;


			case error_stack_overflow:

				error_title = "STACK OVERFLOW";
				error_message = "Pushed too many values into an filled up stack.";

				break;


			case error_stack_underflow:

				error_title = "STACK UNDERFLOW";
				error_message = "Tried to pop values from an empty stack.";

				break;


			case error_division:

				error_title = "DIVISION BY ZERO";
				error_message = "Tried to divide or modulate by zero.";

				break;


			case error_arc_cosine:

				error_title = "ARC COSINE OUT OF RANGE";
				error_message = "Tried to perform arc cosine operation\n with numbers outside the range (-1, 1).";

				break;


			case error_arc_tangent_2:

				error_title = "ARC TANGENT NOT DEFINED";
				error_message = "Tried to perform arc tangent operation\n with undefined result.";

				break;


			case error_logarithm:

				error_title = "LOGARITHM OUT OF RANGE";
				error_message = "Tried to perform a logarithm\nwith negative number.";

				break;

			case error_power:

				error_title = "POWER HAS NO REAL SOLUTION";
				error_message = "Tried to perform a power operation\nwith negative base and decimal exponent.";

				break;


			case error_unknown:

				error_title = "UNKNOWN";
				error_message = "How did we get here?";

				break;

		}

		// drawing routine

		select_region(256);

set_multiply_color(0x3F000000);
		set_drawing_scale(640,100);

		draw_region_zoomed_at(0, woops_scroll+4);


		// draw W O O P S letters

		set_multiply_color(0xFFFFFFFF);
		select_region(w_matrix);
		draw_region_at(205 + sin( (timer)/32.0 ) * 15, 70+woops_scroll);

		select_region(w_matrix+1);

		draw_region_at(265 + sin( (timer+16)/32.0 ) * 15, 70+woops_scroll);

		// letter "O" is duplicated
		draw_region_at(325 + sin( (timer+32)/32.0 ) * 15, 70+woops_scroll);

		select_region(w_matrix+2);
		draw_region_at(385 + sin( (timer+48)/32.0 ) * 15, 70+woops_scroll);

		select_region(w_matrix+3);
		draw_region_at(445 + sin( (timer+64)/32.0 ) * 15, 70+woops_scroll);


		print_at(100,100, error_message);


		// draw error codes
		if(timer>55){
			set_multiply_color(0x12232DD3);
			print_at(150, 200, "ERROR:");
			print_at(350,200, error_title);

			set_multiply_color(0x12D38D23);
			print_at(150, 230, "WHERE:");
			print_hex(350,230, instruction_pointer);

			set_multiply_color(0x1223D3CD);
			print_at(150, 260, "INSTRUCTION:");
			print_hex(350,260, instruction);

			set_multiply_color(0x124AD323);
			print_at(150, 290, "IMMEDIATE VALUE:");
			print_hex(350,290, immediate_value);
		}



		end_frame();
	}


}

#endif
