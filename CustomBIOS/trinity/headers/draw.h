#define white_pixel 256
#define v_matrix 257
#define w_matrix 267
#define biostexture -1 // used for testing

void define_regions(){

	select_texture(biostexture);

	define_region_matrix(0,  0,0,  9,19,  1,1,  32,8,  0);

	define_region_matrix(257,  0,161,  52,215,  26,188,  6,1,  1);


	//we chose a random white pixel on the texture
	select_region(white_pixel);
	define_region_topleft(150,0,150,0);


	// 32
	select_region(263);
	define_region_center(0,217,79,272);

	// request cart text
	select_region( 264 );
	define_region_center(81,217, 301,237);

	// vircon console
	select_region( 265 );
	define_region_center(321,59, 372,93);

	// vircon cartridge
	select_region( 266 );
	define_region_center(374,59, 389,75);

	// define region matrices
	define_region_matrix( w_matrix, 321,0,  368,57,  345,30,  4,1,  1 );



}






void draw3d(int x, int y, int tall){



	for( float i = 1; i < tall+1; i++){

		if(i<tall) set_multiply_color(make_gray(i*3));
		else set_multiply_color(0xFFFFFFFF);


		draw_region_at((x+i*(x*5)/640)+320,y-i);

	}


}



void print_hex(int x, int y, int value){
	// borrowed and adapted some parts from carra's original bios

	int[ 17 ] hex_characters = "0123456789ABCDEF";
	int[ 9 ] hex_string;

	for( int Digit = 7; Digit >= 0; Digit-- )
	{
		hex_string[ Digit ] = hex_characters[ value & 15 ];
		value >>= 4;
	}

	hex_string[ 8 ] = 0;

	// join all text parts
	int[ 11 ] text;
	strcpy( text, "0x" );
	strcat( text, hex_string );

	// print the text
	print_at( x, y, text );
}



float rc_timer;
void request_cart(){

	set_multiply_color(0xFFFFFFFF);


	select_region(264);

	draw_region_at(320, -(ease( rc_timer, NONE, BACK)*60)+380 );

	select_region(265);

	// fancy animations made with ease-studio!


	draw_region_at(680+ease(((rc_timer-1)*1.5), NONE, CIRC)*-88+ease(((rc_timer-5)*1), BACK, NONE)*88,280+ease(((rc_timer-3.5)*1.5), NONE, CIRC)*5+ease(((rc_timer-4.2)*1.5), QUINT, QUINT)*-5);

	select_region(266);

	set_drawing_angle(0+ease(((rc_timer-1.5)*0.9), NONE, BACK)*6.28319+ease(((rc_timer-2.7)*2.4), NONE, CUBIC)*0.5+ease(((rc_timer-3.2)*2), SINE, SINE)*-0.5);
	set_drawing_scale(1,1);
	draw_region_rotated_at(680+ease(((rc_timer-1.5)*1), NONE, CIRC)*-88+ease(((rc_timer-2.7)*1.5), NONE, NONE)*-3+ease(((rc_timer-5)*1), BACK, NONE)*88,180+ease(((rc_timer-2.7)*2.1), NONE, QUINT)*-15+ease(((rc_timer-3.2)*1.5), QUINT, CIRC)*109+ease(((rc_timer-4.2)*1.5), QUINT, QUINT)*-5);




	rc_timer += 0.016666666666666666;




}
