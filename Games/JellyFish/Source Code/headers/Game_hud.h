
//i'm too lazy to write this
void PrintScore( int LeftX, int TopY, int Number ){


    int CurrentDigitBase = 1000000000;
    

    while( CurrentDigitBase > 1 ){
        if( Number >= CurrentDigitBase )
          break;
        
        CurrentDigitBase /= 10;
    }
	    while( CurrentDigitBase > 0 )
    {
        int Digit = (Number / CurrentDigitBase) % 10;
        select_texture(Sfont);
		select_region( FRegSfont + Digit );
        draw_region_at( LeftX, TopY );
        
        // advance to the right for next digit
        CurrentDigitBase /= 10;
        LeftX += 19;
    }
	
}


int scorety=5;

void TheHud(){
int livereg=0;
int livereglast=0;

if(pl_lives>0 && playing)general_score++;

if(general_score<0)general_score=0;

if(pspr==5){livereglast=2;}
if(pspr==4){livereglast=1;}
if( !(pspr==5) && !(pspr==4) ){livereglast=0;}


/*this is the print score function, i can't find it*/ PrintScore(10,scorety,general_score/25);


	for(int i=pl_lives;i>0;i--){
		select_texture(TexLives);
		
			select_region(livereglast);
		if(!(i==pl_lives) && pl_hittimer){
			select_region(livereg);}

		draw_region_at(i*50-50,314);


	}
}