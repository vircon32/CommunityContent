
#include "string.h" // i know i shouldn't include extra libraries but ITOA and FTOA are big functions.




#define deg 		0.0174532925199432957692369
#define rad 		57.2957795130823208767982

#define tau			1.57079632679489661923132
#define euler		2.71828182845904523536029
#define golden		1.61803398874989484820459
#define pythagoras	1.41421356237309504880169




//
// BEGIN MATH FUNCTIONS
//

int wrap(int index, int range) {
	return ((index % range) + range) % range;
}





float lerp(float a, float b, float f){
	return a * (1.0 - f) + (b * f);
}





float clamp(float value, float min, float max){
	if (value < min) return min;
	else if( value > max) return max;
	else return value;

}




int rand_between(int min, int max){
	int random=0;
	asm{"in R0, RNG_CurrentValue" "mov {random}, R0"}

	return random % (max + 1 - min) + min;
}






///
/// COLLISION
///

bool point_in_circle(int px, int py, int cx, int cy, int radius){


	int x = px-cx;
	int y = py-cy;

	// radius squared is faster than getting a square root.
	return ( x*x + y*y < radius*radius);
}





bool circle_in_circle(int circle_1_x, int circle_1_y, int circle_1_radius, int circle_2_x, int circle_2_y, int circle_2_radius){

	float d =	(circle_2_x - circle_1_x) * (circle_2_x - circle_1_x) +
				(circle_2_y - circle_1_y) * (circle_2_y - circle_1_y);

	return (d < (circle_1_radius + circle_2_radius)*(circle_1_radius + circle_2_radius));
}




int point_in_box(float px, float py, float bx, float by, float w, float h) {
	return (
		px >= bx 		&&
		px <= bx + w 	&&
		py >= by 		&&
		py <= by + h
	);
}





int box_in_box (int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){

	// i guess this algorithm was called AABB

	return !(
			x1 > x2 + w2 - 1 ||
			y1 > y2 + h2 - 1 ||
			x2 > x1 + w1 - 1 ||
			y2 > y1 + h1 - 1
			);

}





//
// PRINTING NUMBERS IN THE SCREEN
//

void print_int(int x,int y, int num, int base){

	//convert string into an string (stored into "str" array)
	int[33] str = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	itoa(num, str, base);


	int texture;
	asm{
		"in R0, GPU_SelectedTexture"
		"mov {texture}, R0"
		"mov R0, -1"
		"out GPU_SelectedTexture, R0"
	}


	for(int i=0; i<33; i++){
		int char = str[i];

		asm{
			"mov R0, {char}"
			"out GPU_SelectedRegion, R0"

			"mov R0, 10"

			"mov R1, {x}"
			"iadd R0, R1"	//the assembler says second operand can't be from memory

			"mov R1, {i}"
			"imul R0, R1"


			"out GPU_DrawingPointX, R0"
			"mov R0, {y}"
			"out GPU_DrawingPointY, R0"

			"out GPU_Command, GPUCommand_DrawRegion"
		}

	}
	asm{
		"mov R0, {texture}"
		"out GPU_SelectedTexture, R0"
	}

}





void print_float(int x,int y, float num){

	int[33] str = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ftoa(num, str);

	int texture;
	asm{
		"in R0, GPU_SelectedTexture"
		"mov {texture}, R0"
		"mov R0, -1"
		"out GPU_SelectedTexture, R0"
	}


	for(int i=0; i<33; i++){
		int char = str[i];

		asm{
			"mov R0, {char}"
			"out GPU_SelectedRegion, R0"

			"mov R0, 10"

			"mov R1, {x}"
			"iadd R0, R1"	//the assembler says second operand can't be from memory

			"mov R1, {i}"
			"imul R0, R1"


			"out GPU_DrawingPointX, R0"
			"mov R0, {y}"
			"out GPU_DrawingPointY, R0"

			"out GPU_Command, GPUCommand_DrawRegion"
		}

	}
	asm{
		"mov R0, {texture}"
		"out GPU_SelectedTexture, R0"
	}



}





///
/// BITWISE TASKS
///

// turn bit number k into "1"
void setbit(int *n, int k){
	*n = (*n | (1 << k));
}

// turn bit number k into "0"
void clearbit(int *n, int k){
	*n = (*n & (~(1 << k)));
}

// toggles bit number k state
void togglebit(int *n, int k){
	*n = (*n ^ (1 << k));
}

// set bit number k into 1 or 0
void modifybit(int *n, int k, int p){
	*n = (*n | (p << k));
}

// returns the state of bit number N
bool findbit(int n, int k){
	return ((n >> k) & 1);
}
