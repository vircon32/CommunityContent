// a library with some few useful functions (still really unfinished)

#define deg 0.0174532925199432957692369
#define rad 57.2957795130823208767982



float lerp(float a, float b, float f){
	return a * (1.0 - f) + (b * f);
}



int rand_btw(int min, int max){

	return rand() % (max + 1 - min) + min;
}



void print_int(int x,int y, int num){

	int[20] str;
	itoa(num,str,10);
	print_at(x, y, str);
}



