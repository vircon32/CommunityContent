	int jumptempo=0;
	int panima=0;
	
		//player variables
	float pl_x=300;
	float pl_y=100;
	float pl_ax=0;
	float pl_ay=1;
	int pspr=0;
	float pl_size=1;
	bool pl_hitd;
	int pl_hittimer=130;
	int pl_lives=3;
	bool pl_sndget=false;
	
	bool pl_outside=true; //only disable on debug please
void playerscript(){

	float desac= 0.02;

if(pl_lives>0){

	pl_ay++;
	jumptempo++;
	pl_y+=pl_ay/20;
	pl_x+=pl_ax;

	
	
	if(!pl_hitd){
		
	if(gamepad_right()>1){ pl_ax+=0.2; pl_size=1;}
	
	if(gamepad_left()>1){ pl_ax-=0.2; pl_size=-1;}
	
	if(gamepad_button_a()>1){jumptempo=0;}
	
	if(gamepad_button_a()>1 && jumptempo<5){
		pspr=2; panima=0;
	}else{ 
		if(jumptempo>5 && jumptempo<20 && pl_y>10){
			pl_ay=-35; 
			pspr=3; 
			panima=0;
		} 
	}
	
	}
		//sound controller
		//i'm going to play a sound when jumptempo==1
		
		if(jumptempo==1 && pl_sndget)play_sound_in_channel(SndBubbles,2);else
		if(jumptempo==1 && !pl_sndget)play_sound_in_channel(SndBubbles,3);	
		
		if(jumptempo>20){
		//player idle
		if(panima<20){
			pspr=1;
		}
			
		if(panima>=20){
			pspr=0;
		}
	if(panima>=40 ){
		panima=0;
	}else{panima++;}
		}
	
	//speed limits
	if(pl_ay>25){pl_ay=25;}

	if(pl_ax<-3){pl_ax=-3;}
	if(pl_ax>3){pl_ax=3;}
	
	if( gamepad_left()<0 || gamepad_right()<0 ){
		if(pl_ax<0){
			pl_ax+=desac;
			}else{
			pl_ax-=desac;
			}
		
	}
	//collision == {enemy}.h

	pl_hittimer++;

	if(pl_hitd && pl_hittimer <=80){
		
		panima=0;
		if(pl_hittimer>0 && pl_hittimer<3 && pl_lives>1)general_score-=350;
		if(pl_hittimer>0 && pl_hittimer<10){pspr=4;pl_ay=-50;}
		if(pl_hittimer>10){pspr=5;}
		if(pl_hittimer>20){pspr=4;}
		if(pl_hittimer>30){pspr=5;}
		if(pl_hittimer>40){pspr=4;}
		if(pl_hittimer>50){pspr=5;pl_hitd=false;}
	

	}
		if(pl_hittimer==1)play_sound_in_channel(SndHit,4);
	
		if(pl_hittimer==50){pl_lives--;}
	
	if(pl_hittimer>60 && pl_hittimer<70 ){pspr=13;}
	if(pl_hittimer>80 && pl_hittimer<90 ){pspr=13;}
	if(pl_hittimer>100 && pl_hittimer<110 ){pspr=13;}
	//end collision entity
}

	int Panim= FRegPlayer + pspr;	
	select_texture(TexPlayer);	
			select_region(Panim);
			

			set_drawing_scale(pl_size,1);
	draw_region_zoomed_at(pl_x, pl_y);


}

void no(){
	if(pl_y>300){pl_ay-=2;}
	if(pl_y<10){pl_ay+=3;}

	if(pl_x>600){pl_ax-=0.5;}
	if(pl_x<40){pl_ax+=0.5;}
}