
bool dead = false;
bool playing = false;

#include "headers/playerscript.h"
#include "headers/Game_hud.h"
#include "headers/a_good_name.h"
#include "enemy/fish.h"
#include "enemy/turtel.h"
#include "enemy/baby_shark.h"

#include "headers/when_death_is_true.h"
void gamescene(){
sleep(50);

	float bgvol=0;  
	int msictime=0;
int bgscounter=360;


int scrdraw=255;

	while(scene==2){

		clear_screen(make_color_rgb(4,4,10));
	
		msictime++;
		
		if( pl_lives<1 && bgvol<1 ) bgvol+=0.05;
		if( pl_lives>1 && bgvol>0 ) bgvol-=0.05;
		
		select_channel(1);
			set_channel_volume(bgvol);
		if(msictime==1)play_sound_in_channel(SndIntro,1);
		if(msictime>=1020)msictime=0;



		select_channel(0);
			set_channel_volume(0.5);
		if(bgscounter>=360){ play_sound_in_channel(SndBgs,0);bgscounter=0;}
		bgscounter++;
		

			playerscript();
		
			fish();
			turtle();
			shark();
			
			if(scorety<=5 && !dead)scorety++;
	
		bscroll(1);
			
			if(gamepad_button_a()>1 && !playing) playing=true;
			
	
			if(pl_lives<=0) dead = true;
			
		TffController();
		
			if(dead) death();
			
			vig_control()																														;

			TheHud();
	
	
			if(pl_outside){
				no();
			}
			
			if(scrdraw>0){ scrdraw--;
				
			set_multiply_color(make_color_rgba(255,255,255,scrdraw));
		select_texture(TexVig);
		set_drawing_scale( 360, 640 );
			select_region(1);
		draw_region_zoomed_at( 0, 0 );
			set_multiply_color(make_color_rgba(255,255,255,255));
			
			}
	
	
			end_frame();
	}
	
}


