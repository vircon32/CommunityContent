#include "video.h"
#include "audio.h"
#include "time.h"

#include "memcard.h"
#include "input.h"
#include "misc.h"
#include "math.h"
#include "headers/glue_debug.h"

#define glue_AnimLimit 15
#include "headers/glue_animator.h"

#include "headers/TexDef.h"

int scene=0;
int general_score=0;
int maxscore=0;

	#include "headers/mem_manage.h"
	#include "headers/intro.h"
	#include "headers/gamescene.h"	

	
/*scene
0= memcheck
1= intro
2= gamescene
*/
 
 //about the sound:
 /*
 channel  0 = background sound
 channel  1 = background music
 channel  2,3,4 = jellyfish sounds
 channel  5 = shark exclusive (and death sfx)
 */


void main(void){
glue_move_start();	
	
	TexDefine();
		memanagement();
	introduction();
	gamescene();

}