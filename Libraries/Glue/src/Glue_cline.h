

//	||>>>>>>>>>>>>>>>>>>>>||
//		glue cline
//	
//		like the penguin
//	||<<<<<<<<<<<<<<<<<<<<||

// this library is an experiment, it is not recommended to use in a serious project

#ifndef GLUE_CLINE_H
#define GLUE_Cline_H

#include "misc.h"

#define txt_scx 66
#define txt_scy 18

	int[txt_scx+1][txt_scy+1] screen;


void txtplay(){
		int x=0;
		int y=0;			
		
    asm{ "out GPU_SelectedTexture, -1" }

	for(int i=0;i < sizeof(screen); ++i ){

		if(i==sizeof(screen)-1) memset( screen, 0, sizeof(screen) );

		x++;

			if(x==txt_scx-1){
				y++;
				x=0;
			}
			
			select_region(screen[x][y]);

			draw_region_at(x*10-10, y*20-20);
	
	}
	
}

	void screen_draw(int x, int y, int val){
		
		if( !(x<1) && !(y<1) && !(x>txt_scx) && !(y>txt_scy) ) screen[x][y]=val;
	}


void txt_draw(int x, int y, int* text){

	for( int i = 0; i < strlen( text ); ++i ){

		screen_draw( x+i, y, text[i] );

	}

}

void txt_rect( int x, int y, int w, int h , bool fill, int val){

	int px=0;
	int py=0;
	
	
	for(int i = 1; i <= w*h; i++){
	
		if( px>=w ){
	
			px=0;
			py++;
			
		}
			
		px++;
		
		if(fill){
			screen_draw(x+px-1, y+py, val);
	
		}else{
			
			if( ( i<=w || i>w*h-w ) ||
			    ( px==1 || px==w )){					
				screen_draw(x+px-1, y+py, val);
			}

			
		}
		
	}

}

void txt_rline( int x,int y, int w, int orientation, int val){


	for(int i = 0; i <= w; i++){
		
		switch(orientation){
		case(0):screen_draw(x+i, y, val); break;
		
		case(1):screen_draw(x, y+i, val); break;
		
		case(2):screen_draw(x-i, y, val); break;
		
		case(3):screen_draw(x, y-i, val); break;
		}
	}
	
}

#endif