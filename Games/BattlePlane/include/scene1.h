#define maxbullets 150


int[4] p_x={5, 601, 304, 304};     //players X position
int[4] p_y={160, 160, 4, 320};     //players Y position
float[4] p_ax;  //player acceleration X
float[4] p_ay;  //player acceleration Y
int[4] p_score ={0,0,0,0}; //players score
int[4] p_pup;   //players powerup


int[maxbullets] bullet_x;       //i need more bullets
int[maxbullets] bullet_y;       //i need more bullets
int[maxbullets] bullet_a;       //i need more bullets
int[maxbullets] bullet_owner;   //i need more bullets



float gametimer=0;
int deathtimer=0;

bool gaming=false;

#include "players.h"


void restart(){

        
        for(int i=0; i<players; i++){
                
                p_ax[i]=0;
                p_ay[i]=0;
                p_alive[i]=true;
                p_pup[i]=0;
        }

        for(int i=0; i<maxbullets; i++){
                bullet_x[i]=NULL;
                bullet_y[i]=NULL;
                bullet_a[i]=NULL;
                bullet_owner[i]=NULL;
        }


        p_x[0]=5;
        p_x[1]=601;
        p_x[2]=304;
        p_x[3]=304;

        p_y[0]=160;
        p_y[1]=160;
        p_y[2]=4;
        p_y[3]=320;

        gaming=false;
        gametimer=0;
        deathtimer=0;

}







void gamescene(){

        bgcolor=0xFF2f4FAF;
        
        gametimer++;
        playersmovement();

        bg(600, r_tri);


        playersdraw();

        if(gametimer<150) stop_all_channels();

        select_channel(0);
        set_channel_loop(true);

        if(gametimer==150){
                
                play_sound_in_channel(s_gaming,0);
 
        
        }


        if(whosleft()!=0){
                
                deathtimer++;
                


                if(deathtimer>100){

                        p_score[whosleft()-1]++;
                        restart();
                }
        }
}