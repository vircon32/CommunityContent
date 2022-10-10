int rand_betw(int min, int max){
        return (rand() % (min - max + 1)) + min;}

float bgscroll;


void bscroll(float div){

	if(pl_lives>0)bgscroll--;
	
		select_texture(TexBackg);
		select_region(0);
		draw_region_at(bgscroll/div,0);
		draw_region_at((bgscroll/div)+640,0);

		if(bgscroll/div<=-640){bgscroll=0;}
}


int sqr_collision (int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
  if (x1 > x2 + w2 - 1 ||
      y1 > y2 + h2 - 1 ||
      x2 > x1 + w1 - 1 ||
      y2 > y1 + h1 - 1){
	  return false;
	  }else{
  return true;}
}


int vigalpha=0;
void vig_control(){

	if(pl_lives*84>vigalpha) vigalpha++; else{ vigalpha--;}
	if (vigalpha==0) vigalpha=1;
	
	select_texture(TexVig);
	select_region(0);
		set_blending_mode(21);

	set_multiply_color(make_color_rgba(0,0,0,-vigalpha));
	draw_region_at(0,0);
	set_multiply_color(color_white);
			set_blending_mode(20);
}


int tf_x=-50;
int tf_y=0;
int tftime=0;

void TffController(){

	if(pl_lives<3 && !dead){
		if(sqr_collision( pl_x-20, pl_y-7, 40, 91, tf_x, tf_y, 54, 29 ) ){
			pl_lives++;
			tf_x=-50;
		} 
		tf_x-=5;
		
		tftime++;
		
		if( (rand_betw(0,1000)>997 && tf_x<-30) && tftime>1800 ){
		
		tftime=0;
		
			tf_y=rand_betw(0,290);
			tf_x=640;
		}
		select_texture(TexTinyFuskingFish);	
		select_region(0);
		draw_region_at(tf_x, tf_y);
	}
	
}