
void introduction(){

	int jellyy=180;
	int op=1;
	
	int todraw=1;
	int intimer=0;
	
	int bgop=0;
	float bgscr=0;
	float bgspd=1;
	
	int rott=0;
	float rot=00;
	
	int starty=400;
	float startsc=1000;
	int startop=1;
	float bgvol=0;
	
	int stime=0;
	int salig=0;
	int msictime=0;
	
	
	while(scene==1){
	clear_screen(color_black);
	
		msictime++;
		
		if( (intimer>30 && bgvol<1) && stime==0) bgvol+=0.1;
		select_channel(1);
			set_channel_volume(bgvol);
		if(msictime==1)play_sound_in_channel(SndIntro,1);
		if(msictime>=1020)msictime=0;
		

	
	
		if(intimer<500)intimer++;
		bgscr-=bgspd;
		
		if(bgscr<=-640)bgscr=0;
		
		if(intimer>30) op=glue_move(0,op,250,1,ease_inout); 
	
		if(intimer>150) op=glue_move(1,op,0,1,ease_inout);
	
		if(intimer>240) op=glue_move(2,op,250,1,ease_inout);
	
		if(intimer>240 && intimer<400){ todraw=0; bgop=glue_move(3,bgop,250,0.5,ease_inout); }
	
		if(intimer>340){ jellyy=glue_move(4,jellyy,101,1.5,ease_inout);}
	
		if(intimer>370)rott++;
		if(rott>00 && rott<=200){ rot=glue_move(5,rot,2,0.5,ease_inout); glue_move_edit(6,delete_key); }

		if(rott>200 && rott<=400){ rot=glue_move(6,rot,-1,0.5,ease_inout); glue_move_edit(5,delete_key); }
	
		if(intimer>400){ starty=glue_move(7,starty,250,1,back_out);}
	
		if(rott>400)rott=0;

		if(intimer>440){startop-=2;startsc++;}
		if(startop<=0){startop=200;startsc=1000;}
	
		if(gamepad_button_start()>0 && intimer<240){intimer=240; glue_move_edit(0,go_end); glue_move_edit(1,go_end);}

		if( gamepad_button_start()>0 && stime==0 && intimer>440 )stime=1;
	
		if(stime>0)stime++;
		if(stime>30){ salig=glue_move(8,salig,500,1,ease_in);  bgvol-=0.01;}
		if(stime>50 && stime<130 && bgop>0){ bgspd+=0.1; bgop-=3; glue_move_edit(3,delete_key);}

		if(stime>140){scene=2; stop_channel(1); }
	
		set_multiply_color(make_color_rgba(255,255,255,op));
	
		select_texture(TexIntro);
	
		set_drawing_angle(rot/10);
		select_region(todraw);
		draw_region_rotated_at(320 -salig ,jellyy);
			set_multiply_color(make_color_rgba(255,255,255,255));
	
	
			set_drawing_scale(startsc/1000,startsc/1000);
			select_region(2);
		draw_region_zoomed_at(320 -salig ,starty);
	
			set_multiply_color(make_color_rgba(255,255,255,startop));
		set_drawing_scale( startsc/900 ,startsc/900 );
			select_region(2);
		draw_region_zoomed_at(320 -salig ,starty);
			set_multiply_color(make_color_rgba(255,255,255,255));

	
			set_multiply_color(make_color_rgba(255,255,255,bgop));
		select_texture(TexBackg);
		select_region(0);
		draw_region_at(bgscr, 0);
		draw_region_at(bgscr+640, 0);
		set_multiply_color(make_color_rgba(255,255,255,255));
	
		select_texture(TexVig);
		select_region(0);
		draw_region_at(0,0);


		end_frame();
	}
	
}