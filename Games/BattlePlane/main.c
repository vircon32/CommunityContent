/*
    BATTLE PLANE 
    a battle game made for the second vircon32 jam
    THEME: scoring ( easy one, thanks carra :D )


*/




#include "time.h"
#include "video.h"
#include "audio.h"
#include "math.h"
#include "input.h"
#include "misc.h"
#include "string.h"

#include "include/debug.h"
#include "include/glue_basic++.h"


int scene=0;
int[4] playersjoided={true, false, false, false};
bool[4] p_alive={true, false, false, false};
int players=1;

int bgcolor;
#include "include/regdef.h"
#include "include/bgs.h"
#include "include/mainscreen.h"
#include "include/scene1.h"



void main(void){

    define_regions();
    


    while(1){
        clear_screen(bgcolor);
    
        if(scene==0)startup();
        if(scene==1)mainscreen();
        if(scene==2)gamescene();
        end_frame();
    }

}