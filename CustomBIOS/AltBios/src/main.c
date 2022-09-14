// include headers
#include "audio.h"
#include "video.h"
#include "time.h"
#include "misc.h"

// ---------------------------------------------------------
//     SUPPORT FUNCTIONS
// ---------------------------------------------------------
#define first_region_font	0
#define i_hate_white_pixel	256
#define region_logo_line	257
#define region_subtitle		258
#define region_grad			259
#define region_alphabg		260
#define region_blt			261
#define region_grad_alt		262
#define region_cart_plz		263
#define region_cart_rez		264
#define region_cart			265
#define region_logo_letters	266

bool cartridge_connected()
{
    asm{ "in R0, CAR_Connected" }
}

void run_cartridge()
{
	stop_channel(0);
	asm{ "jmp 0x20000000" }
}

int rand_betw(int min, int max){
	        int num = (rand() % max- min + 1) + min;
return num;
}

#include "err.h"
// ---------------------------------------------------------
//     MAIN FUNCTION
// ---------------------------------------------------------
int ever=1;
int evera=0;
int ha=0;
void magik(){
	int[64] bltx;
	int[64] blty;
int bstart=0;
	
	play_sound_in_channel(-1,0);
while(true){

	ha++;

	// redefine region, darker pixel
	if(ha>150){ever+=evera; evera++;
		select_region(region_alphabg);
		define_region_topleft(326,22, 326,22);
	}

		if(ha>65){
			for(int i=0;i<64;i++){
			
				if(bstart<64){
					blty[i]=rand_betw(0,360);
					bltx[i]=rand_betw(0,640);
					bstart+=1;
				}
			
				if(ha<120){
					if(blty[i]>360){
						bltx[i]=rand_betw(1,640);
						blty[i]=-7;
					}
				}
				
				blty[i]+=rand_betw(2,12);
				select_region(region_blt);
			
				set_drawing_scale(3,2);
				draw_region_zoomed_at(bltx[i], blty[i] );

			}
				
			select_region(region_grad);
			set_drawing_scale(700,2);
			draw_region_zoomed_at(0,-(ever));

		}

	//bg dont dounch
		select_region(region_alphabg);
		set_drawing_scale(700,400);
		draw_region_zoomed_at(0,0);

	if(ha>35){
		select_region(region_logo_letters);
		draw_region_at(640/2,ever+(360/2));
	}
		

	if(ha>45){
		select_region(region_logo_line);
		draw_region_at(640/2,ever+(360/2));
	}

	if(ha>55){
		select_region(region_subtitle);
		draw_region_at(640/2,ever+(360/1.5));
	}


	if(ha>230){
		if( cartridge_connected() )
			run_cartridge();
		else{
			request_cartridge();
		}
	}

	end_frame();
	}
}


void main( void )
{
	
	// <region>
	select_texture(-1);
	    // all characters of the text font
    define_region_matrix( first_region_font,  1,22,  10,41,  1,22,  32,8,  0 );
  
	// logo letters
    select_region( i_hate_white_pixel );
    define_region_topleft( 316,183, 316,183 );
  
    // logo letters
    select_region( region_logo_letters );
    define_region( 1,183,  278,238,  140,238 );
    
    // logo line
    select_region( region_logo_line );
    define_region( 1,240,  278,247,  140,232 );
    
    // subtitle
    select_region( region_subtitle );
    define_region( 1,1,  440,20,  221,20 );
	
	    // topgrad
    select_region( region_grad );
    define_region_topleft( 322,24,322,181 );

	    // those dots
    select_region( region_blt );
    define_region_topleft( 324,22,324,27 );
	
		    // bg with aphla
    select_region( region_alphabg );
    define_region_topleft( 322,22,322,22 );
	
	    // topgrad request_cartridge
    select_region( region_grad_alt );
    define_region_topleft( 324,29,324,186 );

	    // please reset
    select_region( region_cart_plz );
    define_region_center( 1,249,225,267 );
	
		    // cart please
    select_region( region_cart_rez );
    define_region_center( 1,269,197,283 );
	
	    // "sample text"
    select_region( region_cart );
    define_region_center( 280,183,314,209 );

	// </region>

	magik(); // alias the main function 2

}
