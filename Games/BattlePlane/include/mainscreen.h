
float sttimer=0;


int[4] ina = {-100,250,0,0};
void startup(){


	clear_screen(0xAF000000);

	select_texture(maintex);


	bg(600, r_tri);

	set_multiply_color(color_white);

	if(sttimer==40)play_sound_in_channel(s_advice, 0);

	if(sttimer>40){


		select_region(r_advice);
		set_drawing_scale( (1+sin(sttimer/20))/10+1, (1+cos(sttimer/20))/10+1 );
		draw_region_zoomed_at(320,140);




	}
	if(ina[4]<255)ina[4]++;


	if(sttimer <=150 && sttimer>80 ){
		ina[0]+=5;

		if(sttimer == 90) ina[2]=1;
		if(sttimer == 100) ina[2]=0;
		if(sttimer == 110) ina[2]=1;
		if(sttimer == 120) ina[2]=0;
		if(sttimer == 130) ina[2]=1;
		if(sttimer == 140) ina[2]=0;
		if(sttimer == 150) ina[2]=3;

	}

	if(sttimer ==160) ina[2]=2;
	if(sttimer ==200) ina[2]=4;
	if(sttimer ==210) ina[2]=5;
	if(sttimer ==220) ina[2]=6;

	if(sttimer >250 && sttimer <400){
		select_texture(introtex);
		select_region(8);
	
		set_drawing_scale(4,4);
		draw_region_zoomed_at(320,190);

	
	
	}if(sttimer>300 && sttimer < 400 ){
		select_texture(maintex);
		select_region(r_controller);
		draw_region_at(370,300);

	}



	select_texture(introtex);
	select_region(ina[2]);

	set_drawing_scale(5,5);
	
	if(sttimer<400)draw_region_zoomed_at(ina[0], ina[1] );

	for(int i=0;i<4;i++){

		select_gamepad(i);
		if(gamepad_button_a()>0 ||gamepad_button_b()>0 ||gamepad_button_start()>0 )scene=1;


	}

	select_texture(maintex);

	select_region(r_advgrad);
	set_multiply_color(make_color_rgba(ina[4],255,255,255));
	
	set_drawing_scale(640,3);
	draw_region_zoomed_at(0,163);


	set_multiply_color(0xFFFFFFFF);


	if(sttimer==500	)scene=1;


	sttimer++;
}















int titlepos;
int[3] missinttime={50,50,50};

	int maintimer=0;
	int gcom=192;
void mainscreen(){

	select_texture(maintex);



	if(titlepos>190)bg(600, r_sqr);



	bgcolor=make_color_rgb(194/gcom, 89/gcom, 37/gcom);

	if(maintimer>50 && gcom >1)gcom--;


	if(maintimer>100 && titlepos<=213)titlepos++;

	if(maintimer==0){stop_all_channels(); titlepos=50;}

	if(maintimer==1)play_sound_in_channel(s_insnd,0);


	if(titlepos>211)set_channel_loop(true);

    if(titlepos==212){stop_all_channels(); play_sound_in_channel(s_menu, 0); }

	set_multiply_color(color_white);


	select_region(r_title);
	draw_region_at(320,titlepos*3);

	players=0;



	

	set_multiply_color(0xFFFFFFFF);

	if(maintimer > 100){
		select_region(r_join);
		draw_region_at(320, 25+titlepos*3 -640);

		select_region(r_joinmenu);
		draw_region_at(320, 170+titlepos*3 -640);
		


		for(int i=0; i<4; i++){

			select_gamepad(i);

					if((gamepad_button_a()>0 ||gamepad_button_b()>0 ||gamepad_button_start()>0 ) && titlepos*3<640){
						
						


						titlepos=210;
					
						gcom=1;
					}

			if(gamepad_button_a()>1){
				
				if(playersjoided[i-1] || i==0){
					playersjoided[i]=true;
					p_alive[i]=true;

				}else{

					missinttime[i-1]=0;

				}
			}

			if((missinttime[i-1]>0 && missinttime[i-1]< 50) && i!=0){
				select_region(r_pjoin+4);
				draw_region_at(200, ((50+(i-1)*35)-50)+titlepos*3 -640);
			}

			if(playersjoided[i]){
			set_multiply_color(make_color_rgb( sin(i-0.1)*255, cos(-i-0.5)*255, asin(i/4)*1.4 ));
			
			select_region(r_pjoin+i);
			draw_region_at(200, ((50+i*35)-50)+titlepos*3 -640);




			players++;

			}

			

		}


		select_region(r_start);

		set_multiply_color(color_white);
		if(players!=1) draw_region_at(320, 310+titlepos*3 -640);



		for(int i=0; i<3; i++){
			missinttime[i]++;
		}

		set_multiply_color(0xFFFFFFFF);

		select_gamepad(0);



		if(gamepad_button_start()>0 && players>1){
			
			set_drawing_scale(gamepad_button_start()*5,5);
			
			select_texture(-1);
			select_region(256);

			draw_region_zoomed_at(320-gamepad_button_start()*2.5,330+titlepos*3 -640);
		
				if(gamepad_button_start()>60 )scene=2;
		
		
		}

	}
	maintimer++;
}