
#define maxturtle 5
	int tspr;
	int[maxturtle] turtx;
	float[maxturtle] turty;
	float[maxturtle] turtay;

	int tget;
	int ttimeline;
void turtle(){

	if(ttimeline>15){tspr=1;}
	if(ttimeline>30){tspr=0;}
	if(ttimeline>45){tspr=2;}
	if(ttimeline>60){tspr=0;ttimeline=0;}

	ttimeline++;
	tget++;
		
		int tlimit=20;
	for( int i=maxturtle-1; i>=0; i-- ){

//is collision time

	if(!turty[i]==0){
	
	if( sqr_collision(	pl_x-20, pl_y-7, 40, 31, turtx[i]+26, turty[i]+6, 106, 34 ) &&pl_hittimer>120){
		pl_hitd=true;
		pl_hittimer=0;
	}
	
		select_texture(TexTurtle);	
		select_region(tspr+FRegTurtle);
		draw_region_at(turtx[i],turty[i]);
	}
		//turtle logic
		turty[i]+=turtay[i];
		
		if(pl_x<turtx[i]+50){
		if(pl_y+tlimit>turty[i]) turtay[i]+=0.05;
		if(pl_y-tlimit<turty[i]) turtay[i]-=0.05;	

		}
		else{
			if(turtay[i]>0)turtay[i]-=0.1;
			else if(turtay[i]<0) turtay[i]+=0.1;
			turtx[i]--;
		}
		
		if(turtay[i]>1.5) turtay[i]=1.5;
		if(turtay[i]<-1.5) turtay[i]=-1.5;
		
		turtx[i]--;
		// end turtle logic

		if(dead){turtx[i]--;}
		if(rand_betw(0,1000)>995 && turtx[i]<-100 && tget>150){
			turtx[i]=650;
			turty[i]=rand_betw(1,310);
			tget=0;
		}
	}
}