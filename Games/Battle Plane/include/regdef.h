#define s_advice 0
#define s_insnd 1
#define s_menu 2
#define s_gaming 3
#define s_death 4
#define s_bullet 5


#define maintex 0
#define scoretex 1
#define introtex 2


#define r_player 0
#define r_bullet 1
#define r_start  2
#define r_pjoin  4
#define r_joinmenu  9
#define r_join 10
#define r_leave 11
#define r_pmissing 12
#define r_tri 13
#define r_sqr 14
#define r_title 15
#define r_advice 16
#define r_advgrad 17
#define r_controller 18



void defreg(int reg, int x1, int y1, int x2, int y2, int type){

    select_region(reg);
    switch(type){

        case(0): define_region_topleft(x1,y1,x2,y2);
            break;

        case(1): define_region_center(x1,y1,x2,y2);
            break;
    }

}


void define_regions(){

    select_texture(maintex);

        defreg(r_player, 0,0, 31,31, 0);
        defreg(r_bullet, 33,0, 47,14, 1);

        defreg(r_start, 0,33, 320,61, 1);
        define_region_matrix(r_pjoin, 0,93, 247,121, 0,0, 1, 5,1);

        defreg(r_joinmenu, 249,93, 638,318, 1);

        defreg(r_join, 0,63, 121,91, 1);

        defreg(r_tri, 0,243, 45,288, 1);
        defreg(r_sqr, 47,243, 92,288, 1);

        defreg(r_title, 2,290, 224,331, 1);
        defreg(r_advice, 2,333, 284,376, 1);
        defreg(r_advgrad, 0,290, 0,453, 0);
        defreg(r_controller, 286,320, 389,364, 1);


    
    select_texture(introtex);
        define_region_matrix(0, 0,0, 18,17, 0,0, 9, 1, 0);


    select_texture(scoretex);
    select_region(0);
    define_region_matrix(0, 0,0, 43,59, 0,0, 12, 1,0);

}

