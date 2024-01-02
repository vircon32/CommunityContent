void PrintScore( int LeftX, int TopY, int Number){


    int CurrentDigitBase = 100;
    

        int[ 5 ] st;
    itoa( Number, st, 10 );
    

    int num_length = strlen( st )*22;



    while( CurrentDigitBase > 1 ){
        if( Number >= CurrentDigitBase )
          break;
        
        CurrentDigitBase /= 10;
    }
	    while( CurrentDigitBase > 0 ){
        int Digit = (Number / CurrentDigitBase) % 10;


		select_region( Digit );
        draw_region_at( LeftX -num_length/2, TopY-22 );
        
        // advance to the right for next digit
        CurrentDigitBase /= 10;
        LeftX += 45;
    }
	
}





int lastbullet=1;

void create_bullet(int x, int y, int a, int own){


    play_sound(s_bullet);


    if(lastbullet>=maxbullets-1){
        lastbullet=1;
    }else{

        lastbullet++;
    }

        bullet_x[lastbullet]=x;
        bullet_y[lastbullet]=y;
        bullet_a[lastbullet]=a;
        bullet_owner[lastbullet]=own;


}




#define p_maxspeed 5


void playersmovement(){



    for(int i=0; i<players; i++){
        
        select_gamepad(i);
        
        if(p_alive[i] && gaming){
            if(p_ax[i]< p_maxspeed && gamepad_left()>0){ p_ax[i]--; }    else if(p_ax[i]<0){p_ax[i]++;}
            if(p_ax[i]> -p_maxspeed && gamepad_right()>0){ p_ax[i]++; } else if(p_ax[i]>0){p_ax[i]--;}

            if(p_ay[i]< p_maxspeed && gamepad_up()>0){ p_ay[i]--; }     else if(p_ay[i]<0){p_ay[i]++;}  
            if(p_ay[i]> -p_maxspeed && gamepad_down()>0){ p_ay[i]++; }  else if(p_ay[i]>0){p_ay[i]--;}

            if(gamepad_button_a()==1) {  create_bullet(p_x[i]+15, p_y[i]+15, 2, i);  }
            if(gamepad_button_b()==1) {  create_bullet(p_x[i]+15, p_y[i]+15, 3, i);  }
            if(gamepad_button_x()==1) {  create_bullet(p_x[i]+15, p_y[i]+15, 0, i);  }
            if(gamepad_button_y()==1) {  create_bullet(p_x[i]+15, p_y[i]+15, 1, i);  }

            p_x[i]+=p_ax[i]/2.5;
            p_y[i]+=p_ay[i]/2.5;



            if(p_x[i]<0){ p_ax[i]=1; p_x[i]=0; }
            if(p_y[i]<0){ p_ay[i]=1; p_y[i]=0; }

            if(p_x[i]>609){ p_ax[i]=-1; p_x[i]=609; }
            if(p_y[i]>329){ p_ay[i]=-1; p_y[i]=329; }


            for(int e=0; e<maxbullets-1; e++){

                if(in_scuare(p_x[i], p_y[i], 31, 31, bullet_x[e], bullet_y[e]) && bullet_owner[e]!=i && deathtimer==0){
                    stop_channel(15);
                    play_sound_in_channel(s_death,15);
                    p_alive[i]=false;

                }

            }
        
        }

    }



    for(int i=0; i<maxbullets-1; i++){


        
        if(bullet_a[i]==0) bullet_y[i]-=5;
        if(bullet_a[i]==1) bullet_x[i]-=5;
        if(bullet_a[i]==2) bullet_x[i]+=5;
        if(bullet_a[i]==3) bullet_y[i]+=5;

    }



}


void playersdraw(){

    
    for(int i=0; i<players; i++){
    
        select_texture(maintex);
        set_multiply_color(make_color_rgb( sin(i-0.1)*255, cos(-i-0.5)*255, asin(i/4) ));

        
        int scorepos;
        if(players==4) scorepos=65;
        if(players==3) scorepos=100;
        if(players==2) scorepos=130;

        
        for(int e=0; e<maxbullets-1; e++){
            
            if(bullet_owner[e]==i){
                select_region(r_bullet);
                draw_region_at(bullet_x[e], bullet_y[e]);
            }

        }

            if(p_alive[i]){
                select_region(r_player);
                draw_region_at(p_x[i], p_y[i]);

                if(gametimer<150){
                    select_texture(-1);
                    select_region(256);

                     
                    set_multiply_color(make_color_rgba(0, 0, 0, 255-gametimer*1.7));
                    set_drawing_scale(640,360);
                    draw_region_zoomed_at(0,0);

                    set_multiply_color(make_color_rgba( sin(i-0.1)*255, cos(-i-0.5)*255, asin(i/4) ,255));
                    
                    select_texture(scoretex);

                 
                    PrintScore(sin((gametimer/20)+i)*30+320, i*70+scorepos, p_score[i]);
                
                }else if(gametimer == 150) gaming=true;
            }


    }
}






int whosleft(){

    int p_left=0;



    for(int i=0; i<players;i++){
        if(!p_alive[i])p_left++;
    }

    if(p_left>=players-1){

        if(p_alive[0]) return 1;
        if(p_alive[1]) return 2;
        if(p_alive[2]) return 3;
        if(p_alive[3]) return 4;

    }

}