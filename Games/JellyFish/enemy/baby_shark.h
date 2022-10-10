
	int sspr;
	int sharkx;
	int sharky;	
	int sget;
	int stimeline;
	float sharka=1;
	

	
	bool issharkopen=false;

	int bittimeline=100;

void shark(){

	bool Csharkclose= (sqr_collision(pl_x-20, pl_y-7,40,31, sharkx+36,sharky+31,196,52 ) &&pl_hittimer>120);
	bool Csharkopen= (sqr_collision(pl_x-20, pl_y-7,40,31, sharkx+20,sharky+15,196,62 ) &&pl_hittimer>120);

	if(stimeline>15){sspr=1;}
	if(stimeline>30){sspr=0;}
	if(stimeline>45){sspr=2;}
	if(stimeline>60){sspr=0;stimeline=0;}

	if(!issharkopen) stimeline++;
	sget++;
	bittimeline++;


	//is collision time

	if( (Csharkopen && issharkopen) || (!issharkopen && Csharkclose) ){
		pl_hitd=true;
		pl_hittimer=0;
	}


	//time to shark pog ö
	
	if( pl_x>sharkx-200 && pl_x<sharkx && pl_y>sharky && pl_y<sharky+85 && bittimeline>150){
		
		bittimeline=0; 
		issharkopen=true;
	}

	if(bittimeline<65){
		stimeline=0;
		if(bittimeline>0 && bittimeline<30){ sspr=3; issharkopen=true; }
		if(bittimeline>30 && bittimeline<35)sharka=5;
		if(bittimeline==30) play_sound_in_channel(SndShark,5); 
		if(bittimeline>35 ) sspr=4;
		if(bittimeline>50 ){ sspr=5; issharkopen=false; }
	}
	
	//end (shark pogger ö)
	
		if(!sharky==0){
	if(sharka>1) sharka-=0.05; else sharka=1;

		select_texture(TexShark);	
		select_region(sspr);
		draw_region_at(sharkx,sharky);
		
		}
		
		sharkx-=sharka;
		if(dead)sharkx-=sharka;
		if(rand_betw(0,1000)>995 && sharkx<-200 && sget>300 ){
			sharkx=650;
			sharky=rand_betw(1,220);
			sget=0;
		}
	
}