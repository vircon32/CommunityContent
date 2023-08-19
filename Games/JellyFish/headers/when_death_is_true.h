
int deathtimer=0;
int defalpha=0;

void reset(){
	jumptempo=0;
	panima=0;
	pl_x=300;
	pl_y=100;
	pl_ax=0;
	pl_ay=1;
	pspr=0;
	pl_size=1;
	pl_hitd=false;
	pl_hittimer=51;
	pl_lives=3;
	dead=false;
	general_score=0;
	defalpha=0;

}


void death(){
	deathtimer++;


if(deathtimer>5){pspr=6;}
if(deathtimer>10){pspr=7;}
if(deathtimer>15){pspr=8;}
if(deathtimer>20){pspr=9;}
if(deathtimer>25){pspr=10;}
if(deathtimer>30){pspr=11;}

if(deathtimer>50){
	
	if(defalpha<255 && dead)defalpha+=3;
	
	
	set_multiply_color(make_color_rgba(255,255,255,defalpha));	
	
	select_texture(TexDefeat);
	select_region(RegDead);
	draw_region_at(320,180);
	
	select_region(RegS);
	draw_region_at(320,325);
	
	
	PrintScore(206,182,general_score/25);
	
	select_texture(TexDefeat);
	if(maxscore<=general_score){
	
		if(connec){
		select_region(RegNew);
		draw_region_at(122,210);
		
		maxscore=general_score;
		card_write_data( &maxscore, sizeof(sign), sizeof(maxscore) );	
		}else{
		select_region(RegNew);
		draw_region_at(122,212);
		
		maxscore=general_score;
			
		}
	}
	
	PrintScore(195,232,maxscore/25);	
	
	set_multiply_color(color_white);	
	
	if(gamepad_button_start()>1){reset();}
	
}
	if(scorety>-30)scorety--; 

}

