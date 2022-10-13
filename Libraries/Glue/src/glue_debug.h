
//	||>>>>>>>>>>>>>>>>>>>>>>>>>>>||
//		glue debug
//	
//		just try printing an float
//	||<<<<<<<<<<<<<<<<<<<<<<<<<<<||



#ifndef GLUE_DEBUG_H_H
#define GLUE_DEBUG_H


#include "string.h"

void print_int(int posx,int posy, float num){
	
	int[20] hlt;
	itoa(num,hlt,10);
	print_at(posx,posy,hlt);
}

void print_float(int px,int py,float flnum){
	
	int[20] text;
	ftoa(flnum,text);
	print_at(px,py,text);
}

void print_bool(int posx,int posy, bool val){
	if(val){
		print_at(posx,posy,"true");
	}else{
		print_at(posx,posy,"false");
	}	
	
}

#endif