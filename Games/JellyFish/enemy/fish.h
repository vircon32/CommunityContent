
#define maxfish 7
	int fspr;
	int[maxfish] fishx;
	int[maxfish] fishy;	
	int fget;
	int ftimeline;
void fish(){

	if(ftimeline>15){fspr=1;}
	if(ftimeline>30){fspr=0;}
	if(ftimeline>45){fspr=2;}
	if(ftimeline>60){fspr=0;ftimeline=0;}

	ftimeline++;
	fget++;
		
	for( int i=maxfish-1; i>=0; i-- ){

//is collision time

	if(!fishy[i]==0){
		
	if( sqr_collision(	pl_x-20, pl_y-7,
						40,31,
						fishx[i]+13,
						fishy[i]+15,65,20 ) &&pl_hittimer>120){
		pl_hitd=true;
		pl_hittimer=0;
	}

		select_texture(TexFish);	
		select_region(fspr+FRegFish);
		draw_region_at(fishx[i],fishy[i]);
		
	}	
		
		fishx[i]--;
		if(dead){fishx[i]--;}
		if(rand_betw(0,1000)>990 && fishx[i]<-100 && fget>80){
			fishx[i]=650;
			fishy[i]=rand_betw(1,300);
			fget=0;
		}
	}
}