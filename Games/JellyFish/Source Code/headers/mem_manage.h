
int[20] sign="jelly_fish_game____";
int connec=false;
void memanagement(){
	int bars=0;
	int barsap=0;
	
	
	int timer=0;
	
	int make=0;
	
		if(card_is_connected()){
			card_read_data( &maxscore, sizeof(sign), maxscore );
			connec=true;

			if(card_is_empty())card_write_signature(&sign);
			
		}
			
			
			
	while(scene==0){
	
	if(!card_is_connected() ||  !card_signature_matches(&sign)){
	
	
	clear_screen(make_color_rgb(4,1,2));
	
	if(make==0){barsap=glue_move(9,barsap,255,1,ease_inout); timer++;}
	if(timer==100) make=1;
	
	if(make==1) bars=glue_move(10,bars,300,1,ease_inout);
	
	if( (gamepad_button_a()>0 || gamepad_button_start()>0) && (timer<200 && timer>=100 ) ){ make=2; timer=200;
	glue_move_edit(9,go_end); glue_move_edit(10,go_end);
	}
	
	if(make==2){
		timer++;
		bars=glue_move(11,bars,0,1,ease_inout);
		

		if(timer>300) barsap=glue_move(12,barsap,0,2,ease_inout);
	

	}
	
	if(timer>400)scene=1;
	
	select_texture(TexMem);
	
		if(timer>=100 && timer<=300){
		select_region(0);
		draw_region_at(320,110);

		select_region(2);
		draw_region_at(320,250);
		}
	
	set_multiply_color(make_color_rgba(255,255,255,barsap));	
	select_region(1);
	set_drawing_scale(3,9);
	draw_region_zoomed_at(0-bars,0);

	set_drawing_scale(-3,9);
	draw_region_zoomed_at(640+bars,0);
	set_multiply_color(make_color_rgb(255,255,255));
	
	
	
	}else{scene=1;}
	
	end_frame();
	}
	
}
