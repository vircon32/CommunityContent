
float intro_timer=0;
float intro_color_from_black=0;


void intro(){

	select_texture(0);
	select_region(region_logo);

	set_multiply_color(make_color_rgba(255,255,255,ease(intro_timer-1, SINE,SINE)*255 - ease(intro_timer-5, SINE,SINE)*255 ));

	clear_color=make_color_rgb(17*intro_color_from_black, 17*intro_color_from_black, 27*intro_color_from_black);

	if(intro_timer > 2 && intro_color_from_black <1) intro_color_from_black+=0.01;

	draw_region_at(320,180);



	intro_timer+=0.03;

	if(intro_timer>7){
		effect=0;
		set_multiply_color(0xFFFFFFFF);
		is_intro_over=true;
	}

}





float info_offset=0.0;
float title_timer=0.0;
int info_size;

bool info_open=false;

float button_timer=0;




void info(){

	select_texture(0);

	select_region(region_arrow);


	float title_off = 0.5;
	if(info_offset<0.5) draw_region_at(610, sin(button_timer-0.5)*5 - ease(info_offset, QUINT, BACK)*info_size + 300);

	select_region(region_button);
	if(info_offset<0.5) draw_region_at(610, sin(button_timer)*5 + 335 -ease(info_offset, QUINT, BACK)*info_size);

	button_timer+=0.04;

	textfont_print_from_right(&FontRetro_Gaming_11, 630, 10, "PRESS START\nTO REPLAY");



	if(info_open && info_offset < 1) info_offset+=0.02;
	if(!info_open && info_offset > 0) info_offset-=0.02;

	if(title_timer < effect) title_timer+=0.02;
	if(title_timer > effect) title_timer-=0.02;


	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer, NONE,BACK)*-400+10,
							 ease(title_timer+1, NONE,BACK)*50-40, "Effect 1: Offset.");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-1, NONE,BACK)*-400+10,
							 ease(title_timer, NONE,BACK)*50-40, "Effect 2: Simple ease.");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-2, NONE,BACK)*-450+10,
							 ease(title_timer-1, NONE,BACK)*50-40, "Effect 3: Different easing.");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-3, NONE,BACK)*-450+10,
							 ease(title_timer-2, NONE,BACK)*50-40,"Effect 4: Dual axis easing.");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-4, NONE,BACK)*-400+10,
							 ease(title_timer-3, NONE,BACK)*50-40, "Effect 5: Time offset");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-5, NONE,BACK)*-400+10,
							 ease(title_timer-4, NONE,BACK)*50-40, "Effect 6: Follow by offset");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-6, NONE,BACK)*-400+10,
							 ease(title_timer-5, NONE,BACK)*50-40, "Effect 7: Move only one");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-7, NONE,BACK)*-500+10,
							 ease(title_timer-6, NONE,BACK)*50-40, "Effect 8: Concatenate easings");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-8, NONE,BACK)*-400+10,
							 ease(title_timer-7, NONE,BACK)*50-40, "Effect 9: Scale");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-9, NONE,BACK)*-400+10,
							 ease(title_timer-8, NONE,BACK)*50-40, "Effect 10: Rotate");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-10, NONE,BACK)*-450+10,
							 ease(title_timer-9, NONE,BACK)*50-40, "Effect 11: Scale and rotate");

	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-11, NONE,BACK)*-400+10,
							 ease(title_timer-10, NONE,BACK)*50-40, "Effect 12: NONE type");


	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-12, NONE,BACK)*-450+10,
							 ease(title_timer-11, NONE,BACK)*50-40, "Effect 13: Two NONE types");


	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-13, NONE,BACK)*-400+10,
							 ease(title_timer-12, NONE,BACK)*50-40, "Effect 14: Speed control");


	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-14, NONE,BACK)*-510+10,
							 ease(title_timer-13, NONE,BACK)*50-40, "Effect 15: Multiple speed control");


	textfont_print_from_left(&FontUbuntuMono_B_30,
							 ease(title_timer-15, NONE,BACK)*-500+10,
							 ease(title_timer-14, NONE,BACK)*50-40, "Effect 16: Looped");


	switch(effect){

		case 0:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+435, "To offset any sprite, add a number to its position.\nMultiplying the number will make it move quicker.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (100 + t*20, 100 )");
			break;


		case 1:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+435, "The ease function enables us to simply create\npretty and smooth movements.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (100 + ease(t, SINE, SINE)*300, 100 );");
			break;


		case 2:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+435, "The ease function specifies two easing effects:\none for the first half and one for the second.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (100 + ease(t, QUINT, BACK)*300, 100 );");
			break;


		case 3:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+435, "The ease function can be used in both\nX and Y axis at the same time.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (100 + ease(t, BACK, BACK)*300, 100 + ease(t, SINE, SINE)*100 );");
			break;


		case 4:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+435, "By adding or subtracting t, the easing might\nbegin before or after a certain period.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (100 + ease(t-1, QUINT, QUINT)*300, 100 );");
			break;


		case 5:
			info_size=210;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "You can use timing offset to make various objects\n\"follow\" each other.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA:\n(100 + ease(t, QUINT, QUINT)*300, 60 );\n(100 + ease(t-0.2, QUINT, QUINT)*300, 110 );\n(100 + ease(t-0.4, QUINT, QUINT)*300, 160 );\n(100 + ease(t-0.6, QUINT, QUINT)*300, 210 );\n");
			break;


		case 6:
			info_size=230;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "If you subtract one easing to another with the same\namplitude, both will cancel.\napply it to various objects with different offsets.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+515,"FORMULA:\n(100, 100 + ease(t, QUINT, BACK)*50 - ease(t-1, BACK, QUINT)*50);\n(150, 100 + ease(t-1, QUINT, BACK)*50 - ease(t-2, BACK, QUINT)*50);\n(200, 100 + ease(t-2, QUINT, BACK)*50 - ease(t-3, BACK, QUINT)*50);\n(250, 100 + ease(t-3, QUINT, BACK)*50 - ease(t-4, BACK, QUINT)*50);");
			break;


		case 7:
			info_size=200;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Adding easings with temporal offset will result in\na variety of motions occurring one after the other.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA:\n(100 + ease(t, QUINT, BACK)*100 +\n            ease(t-1.5, SINE, SINE)*100 +\n            ease(t-3, BACK, BACK)*100, 60);");
			break;


		case 8:
			info_size=120;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Easings can be applied to scale property.");
			break;


		case 9:
			info_size=120;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Easings can be applied to rotation property.");
			break;


		case 10:
			info_size=140;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Easings can be applied to scale and roration\nproperties simultaneously.");
			break;



		case 11:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "NONE type can be used if you don't need\neasing in or easing out effect.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+505,"FORMULA: (ease(t, NONE, CUBIC), 100);");
			break;


		case 12:
			info_size=150;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Using NONE on both parts will result in an abrupt return.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+495,"FORMULA: (ease(t, NONE, NONE), 100);");
			break;


		case 13:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "Multiplying or dividing t will result in a\nspeed up or speed down.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+505,"FORMULA: (100 + ease(t/2, SINE, SINE)*300, 100);");
			break;


		case 14:
			info_size=200;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "A better demonstration of speed control.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+485,"FORMULA:\n(100 + ease(t/2, QUINT, QUINT)*300, 60);\n(100 + ease(t,     QUINT, QUINT)*300, 110);\n(100 + ease(t*2, QUINT, QUINT)*300, 160);\n(100 + ease(t*3, QUINT, QUINT)*300, 210);\n");
			break;


		case 15:
			info_size=160;

			print_at( 5, -ease(info_offset, QUINT, BACK)*info_size+440, "A triangular wave can cause an\ninfinite back and forth movement.");

			textfont_print_from_left(&FontRetro_Gaming_11, 5, -ease(info_offset, QUINT, BACK)*info_size+490,"FORMULA:\n(100 + ease( (asin( cos( t*2+pi ) ) + 1.5707963) / pi, QUINT, QUINT)*300, 100);");
			break;
	}

}






