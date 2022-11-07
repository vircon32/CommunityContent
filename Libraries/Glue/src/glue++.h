
//	||>>>>>>>>>>>>>>>>>>>>>>>>>>>||
//		glue++
//	
//		big brain time
//	||<<<<<<<<<<<<<<<<<<<<<<<<<<<||



#ifndef GLUE_PLUSPLUS
#define GLUE_PLUSPLUS

#include "math.h"
#include "misc.h"



int rand_betw(int min, int max){
        
	return (rand() % (min - max + 1)) + min;
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

int in_scuare(int x, int y, int w, int h, int inx, int iny){
	
	if( ((inx >= x) && (inx <= x+w)) &&
		((iny <= y+h) && (iny >= y)) )
		return true;
	else return false;
	
}

float lerp(float a, float b, float t) {
  return (1 - t) * a + t * b;
}

void draw_dot(int x, int y){
	
	asm{
		
		"out GPU_SelectedTexture, -1"
		"out GPU_SelectedRegion, 256"
		
		"mov R0, {x}"
        "out GPU_DrawingPointX, R0"
        "mov R0, {y}"
        "out GPU_DrawingPointY, R0"
        "out GPU_Command, GPUCommand_DrawRegion"
	}
	
}




bool get_key(int key){
	#define  k_left		0
	#define  k_right	1
	#define  k_up		2
	#define  k_down		3
	#define  k_a		4
	#define  k_b		5
	#define  k_x		6
	#define  k_y		7
	#define  k_l		8
	#define  k_r		9
	#define  k_start	10
	

	int key_left;
	int key_right;
	int key_up;
	int key_down;
	int key_a;
	int key_b;
	int key_x;
	int key_y;
	int key_l;
	int key_r;
	int key_start;
	
		asm{
			
			"in R0, INP_GamepadLeft"
			"mov {key_left}, R0"
			
			"in R0, INP_GamepadRight"
			"mov {key_right}, R0"

			"in R0, INP_GamepadUp"
			"mov {key_up}, R0"		

			"in R0, INP_GamepadDown"
			"mov {key_down}, R0"
			
			"in R0, INP_GamepadButtonA"
			"mov {key_a}, R0"
			
			"in R0, INP_GamepadButtonB"
			"mov {key_b}, R0"
			
			"in R0, INP_GamepadButtonX"
			"mov {key_x}, R0"
			
			"in R0, INP_GamepadButtonY"
			"mov {key_y}, R0"
			
			"in R0, INP_GamepadButtonL"
			"mov {key_l}, R0"

			"in R0, INP_GamepadButtonR"
			"mov {key_r}, R0"
			
			"in R0, INP_GamepadButtonStart"
			"mov {key_start}, R0"
			}
	
	
	switch(key){
		
		case(k_left): if(key_left>0)return true; else return false; break;
		
		case(k_right): if(key_right>0)return true; else return false; break;
		
		case(k_up): if(key_up>0)return true; else return false; break;
		
		case(k_down): if(key_down>0)return true; else return false; break;
		
		case(k_a): if(key_a>0)return true; else return false; break;
		
		case(k_b): if(key_b>0)return true; else return false; break;
		
		case(k_x): if(key_x>0)return true; else return false; break;
		
		case(k_y): if(key_y>0)return true; else return false; break;
		
		case(k_l): if(key_l>0)return true; else return false; break;

		case(k_r): if(key_r>0)return true; else return false; break;
		
		case(k_start): if(key_start>0)return true; else return false; break;
		
		
	}
	
}


#endif