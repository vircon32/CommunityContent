#include "math.h"
#include "string.h"

#ifndef GLUE_ANIMATOR_H
#define GLUE_ANIAMTOR_H


#define ease_in 0
#define ease_out 1
#define ease_inout 2
#define back_in 3
#define back_out 4
#define back_inout 5


float[glue_AnimLimit+1] key_timer;
float[glue_AnimLimit+1] key_init;

//only one function lol

/*
			Template
	case(insert_type) return key_init[key]+ "instert math" *end;
*/

// float↓
float glue_move(int key, float init, float finish, float velocity, int type){
	
	key_timer[key]+=velocity/100;
	int end=finish-key_init[key];
		
	if( key_timer[key]>=1)key_timer[key]=1;

	if( key_init[key]==0 )key_init[key]=init;

	int c1 = 1.70158;
	int c2 = c1 * 1.525;
	int c3 = c1 + 1;
//	where the fuck in my c4	
	
	
	//look at this (stoled) math

//like the ones in my house
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

//no
#endif