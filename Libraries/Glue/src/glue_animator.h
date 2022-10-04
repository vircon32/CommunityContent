#include "math.h"

#ifndef GLUE_ANIMATOR_H
#define GLUE_ANIAMTOR_H


#define ease_in 0
#define ease_out 1
#define ease_inout 2
#define back_in 3
#define back_out 4
#define back_inout 5

#define go_start 0
#define go_end 1
#define go_pause 2
#define go_continue 3
#define delete_key 4


float[glue_AnimLimit+1] key_timer;
float[glue_AnimLimit+1] key_init;
bool [glue_AnimLimit+1] key_active;

/*
			Template
	case(insert_type) return key_init[key]+ "instert math" *end;
*/

// float↓

void glue_move_start(){
	for(int i=glue_AnimLimit; i>=0;i--){
		key_timer[i]=0;
		key_init[i]=0;
		key_active[i]=true;
	}
	
}

float glue_move(int key, float init, float finish, float velocity, int type){

if(key_active[key]){	
	key_timer[key]+=velocity/100;

		
	if( key_timer[key]>=1){ key_timer[key]=1; key_active[key]=false; }

	if( key_init[key]==0 )key_init[key]=init;

}
	int end=finish-key_init[key];
	int c1 = 1.70158;
	int c2 = c1 * 1.525;
	int c3 = c1 + 1;
//	where the fuck in my c4	
	
	
	//look at this (stoled) math

//like the ones at home
switch(type){

////////////////////|-- ease functions --|////////////////////

	case(ease_in): return key_init[key]+(1 - cos((key_timer[key] * pi) / 2)) *end ; break;
	
	case(ease_out): return key_init[key]+ (sin((key_timer[key] * pi) / 2)) *end; break;
	
	case(ease_inout): return key_init[key]+ (-(cos(pi * key_timer[key]) - 1) / 2) *end; break;
	
	
	
////////////////////|-- back functions --|////////////////////

	case(back_in): return key_init[key]+ (c3 * key_timer[key] * key_timer[key] * key_timer[key] - c1 * key_timer[key] * key_timer[key]) *end ; break;
	
	case(back_out): return key_init[key]+ (1 + c3 * pow(key_timer[key] - 1, 3) + c1 * pow(key_timer[key] - 1, 2)) *end; break;
	
	case(back_inout):	if(key_timer[key] < 0.5){
		return key_init[key]+(pow(2 * key_timer[key], 2) * ((c2 + 1) * 2 * key_timer[key] - c2)) / 2*end; break;
	}else{
		return key_init[key]+(pow(2 * key_timer[key] - 2, 2) * ((c2 + 1) * (key_timer[key] * 2 - 2) + c2) + 2) / 2*end; break;
	}
	}

}

void glue_move_edit(int key, int type){

	switch(type){
		
		case(go_start): key_timer[key]=0; key_active[key]=true; break;

		case(go_end): key_timer[key]=1; break;
		
		case(go_pause): key_active[key]=false; break;
		
		case(go_continue): key_active[key]=true; break;

		case(delete_key): key_active[key]=true; key_init[key]=0; key_timer[key]=0; break;

	}

}
//no
#endif
