/*---------------------------------------------------------------------------------------/
/| TEXTURE REGION DEFINITIONS
/---------------------------------------------------------------------------------------*/

// Definitions for Assets:
#define rSky          0
#define rPlateaus     1
#define rTrees        2
#define rCacti        3
#define rGrass        4

#define rPRun1       10
#define rPRun2       11
#define rPRun3       12
#define rPRun4       13
#define rPJump       14
#define rPFall       15
#define rPSlide      16

#define rBlock       20
#define rSpike       21

// Definitions for Foreground:
#define rFGGrass      0
#define rFGTree       1

// Definitions for Death:
#define rDScreen      0
#define rDText        1

// Definitions for Start:
#define rSScreen      0
#define rSText        1

/*---------------------------------------------------------------------------------------/
/| SOUND DEFINITIONS
/---------------------------------------------------------------------------------------*/

#define sSavanna      0
#define sText         1
#define sGrass        2
#define sMetal        3
#define sDead         4

/*---------------------------------------------------------------------------------------/
/| TEXTURE REGION FUNCTIONS
/---------------------------------------------------------------------------------------*/

// Defines all the texture regions.
void defineTextureRegions( ) {
    
    // Defines the Assets.
    select_texture( 0 );
    select_region( rSky );
    define_region_topleft( 0,0, 639,304 );    
    select_region( rPlateaus );
    define_region( 0,305, 639,490, 0,490 );    
    select_region( rTrees );
    define_region( 0,491, 639,660, 0,660 );    
    select_region( rCacti );
    define_region( 0,661, 639,791, 0,791 );    
    select_region( rGrass );
    define_region( 0,792, 639,862, 0,862 );    

    define_region_matrix( rPRun1, 0,863, 49,922, 0,922, 7,1, 0 );

    define_region_matrix( rBlock, 0,923, 63,986, 0,986, 2,1, 0 );
    
    // Defines the Foreground.
    select_texture( 1 );
    select_region( rFGGrass );
    define_region( 0,0, 639,86, 0,86 );    
    select_region( rFGTree );
    define_region( 0,87, 639,446, 0,446 );    
    
    // Defines the Death.
    select_texture( 2 );
    select_region( rDScreen );
    define_region_topleft( 0,0, 639,359 );    
    select_region( rDText );
    define_region_center( 0,360, 271,375 );    
    
    // Defines the Start.
    select_texture( 3 );
    select_region( rSScreen );
    define_region_topleft( 0,0, 639,359 );    
    select_region( rSText );
    define_region( 0,360, 133,384, 133,384 );    
    
    // Resets the select_texture to the main one.
    select_texture( 0 );
}
