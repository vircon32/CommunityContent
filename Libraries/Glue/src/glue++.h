
//	||>>>>>>>>>>>>>>>>>>>>>>>>>>>||
//		glue++
//	
//	 	big brain time
//	||<<<<<<<<<<<<<<<<<<<<<<<<<<<||



#ifndef GLUE_PLUSPLUS
#define GLUE_PLUSPLUS

#include "math.h"
#include "misc.h"
int rand_betw(int min, int max){
        return (rand() % (min - max + 1)) + min;}


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


#endif
