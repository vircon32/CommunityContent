/*---------------------------------------------------------------------------------------/
| VIRCON32 LIBRARY AND HEADER FILE INCLUSIONS
/---------------------------------------------------------------------------------------*/

// Includes Vircon32 libraries.
#include "audio.h"
#include "input.h"
#include "math.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"

// Includes external header files.
#include "definitions.h"

/*---------------------------------------------------------------------------------------/
| PLAYER AND OBSTACLE INFRASTRUCTURE
/---------------------------------------------------------------------------------------*/

// Player Structure
struct Player {

    // Positional Variables.
    int posX;
    int posY;
    int speed;
    int accel;
    
    // State Flags.
    int animFrame;
    bool isJumping;
    bool isSliding;
    bool isDead;
};

// Obstacle Structure
struct Obstacle {

    // Object Data.
    bool isSpike;
    int posX;
    int posY;

    // Pointers for List Traversal.
    Obstacle* next;
    Obstacle* prev;    
};

// Foreground Element Structure
struct Foreground {

    // Object Data.
    int posX;
    bool isTree;

    // Pointers for List Traversal.
    Foreground* next;
    Foreground* prev;
};

// List Structures
struct ListObs {

    // Pointers for List Traversal and Notation.
    Obstacle* BP;
    Obstacle* EP;

    // Additional Properties for Easier Computation.
    int size;
};

struct ListFG {

    // Pointers for List Traversal and Notation.
    Foreground* BP;
    Foreground* EP;

    // Additional Properties for Easier Computation.
    int size;
};

// Queue Structure
struct Queue {

    // Pointers for Queue Interactions.
    ListFG* data;
    Foreground* top;
    Foreground* rear;
};

// Global Pointers
Player* P1 = NULL;
Queue* foreground = NULL;
ListObs* patArr = NULL;

/*---------------------------------------------------------------------------------------/
| QUEUE MANAGEMENT FUNCTIONS 
/---------------------------------------------------------------------------------------*/

// Appends a Foreground element onto a specified List.
void appendFG( Foreground* fg, ListFG** list ) {
    if( (*list)->size == 0 ) {
        (*list)->BP = fg;
        (*list)->EP = fg;
        fg->prev = NULL;
        fg->next = NULL;
    } else {
        (*list)->BP->prev = fg;
        fg->next = (*list)->BP;
        fg->prev = NULL;
        (*list)->BP = fg;
    } 
    fg = NULL;
    (*list)->size += 1;
}

// Removes a Foreground element from the current list it resides in.
Foreground* removeFG( ListFG** list ) {
    Foreground* tempP = NULL;
    if( (*list)->BP != NULL ) {
        tempP = (*list)->EP;
        if( (*list)->size > 1 ) {
            tempP->prev->next = NULL;
            (*list)->EP = tempP->prev;
            tempP->prev = NULL;
        } else {
            (*list)->BP = NULL;
            (*list)->EP = NULL;
        }
        (*list)->size -= 1;
        return tempP;
    }
}

// Pushes the Selected Foreground element into the Selected Queue.
void push( Foreground* fg, Queue* queue ) {
    appendFG( fg, &(queue->data) );
    queue->rear = queue->data->BP;
}

// Pops the Top Foreground element from the Selected Queue into cardP.
Foreground* pop( Queue* queue ) {
    Foreground* tempP = NULL;
    if( queue->data->size > 0 ) {
        tempP = removeFG( &(queue->data) );
        queue->top = queue->data->EP;
    }
    return tempP;
}

// Appends an Obstacle onto a specified List.
void appendObs( Obstacle* obs, ListObs* list ) {
    if( list->size == 0 ) {
        list->BP = obs;
        list->EP = obs;
        obs->prev = NULL;
        obs->next = NULL;
    } else {
        list->EP->next = obs;
        obs->prev = list->EP;
        obs->next = NULL;
        list->EP = obs;
    } 
    obs = NULL;
    list->size += 1;
}

/*---------------------------------------------------------------------------------------/
| SOUND INITIALIZATION AND PLAYBACK FUNCTIONS
/---------------------------------------------------------------------------------------*/

// Initializes the Background Ambiance.
void initializeBackgroundSound( ) {
    select_channel( 0 );
    assign_channel_sound( 0, sSavanna );
    set_channel_loop( true );
    set_global_volume( 2 );
    play_channel( 0 );
}

// Player Walking Noises.
void playPlayerWalkingOnGrass( ) {
    if( ((get_frame_counter() % 14) == 0) && (P1->isSliding == false) ) { 
        play_sound( sGrass ); 
    }
}

void playPlayerWalkingOnBlock( ) {
    if( ((get_frame_counter() % 14) == 0) && (P1->isSliding == false) ) { 
        play_sound( sMetal ); 
    }
}

/*---------------------------------------------------------------------------------------/
| OBJECT INITIALIZATION FUNCTIONS 
/---------------------------------------------------------------------------------------*/

// Generates and Initializes the Player.
void initializePlayer( ) {

    // Allocates the needed memory.
    P1 = ( Player* ) malloc( sizeof( Player ) );

    // Initializes the Player with starting data.
    P1->posX = 100; 
    P1->posY = 302; 
    P1->speed = 0; 
    P1->accel = 1; 
    P1->animFrame = 0; 
    P1->isJumping = false; 
    P1->isSliding = false; 
    P1->isDead = false; 
}

// Generates and Initializes the Foreground Queue.
void initializeForeground( ) {

    // Allocates the needed memory.
    foreground = ( Queue* ) malloc( sizeof( Queue ) );

    // Initializes the Foreground with data.
    foreground->data = ( ListFG* ) malloc( sizeof( ListFG ) );
    foreground->top = NULL;
    foreground->rear = NULL;

    Foreground* tempP = NULL;
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Foreground* ) malloc( sizeof( Foreground ) );
        tempP->posX = index * 640;
        if( index == 2 ) { tempP->isTree = true; }
        else { tempP->isTree = false; }
        push( tempP, foreground );         
    }
    foreground->top = foreground->data->EP;
}

// Generates and Initializes the Obstacle Patterns.
void initializePatterns( ) {

    // Allocates the needed memory.
    patArr = ( ListObs* ) malloc( sizeof( ListObs ) * 7 );

    // Initializes the 7 Patterns with default data.
    for( int index = 0; index < 7; index++ ) {
        (patArr+index)->BP = NULL;
        (patArr+index)->EP = NULL;
        (patArr+index)->size = 0;
    }
}

// Populates the Platform pattern.
void populatePatternPlatform( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645 + (64 * index);
        tempP->posY = 302;
        appendObs( tempP, patArr );         
    }
    tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
    tempP->isSpike = true;
    tempP->posX = 773;
    tempP->posY = 238;         
    appendObs( tempP, patArr );         
}

// Populates the Overhang pattern.
void populatePatternOverhang( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645;
        tempP->posY = 14 + (64 * index);
        appendObs( tempP, (patArr+1) );         
    }    
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 709 + (64 * index);
        tempP->posY = 270;
        appendObs( tempP, (patArr+1) );         
    }    
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 1029;
        tempP->posY = 14 + (64 * index);
        appendObs( tempP, (patArr+1) );         
    }    
}

// Populates the Pit pattern.
void populatePatternPit( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645 + (64 * index);
        tempP->posY = 46;
        appendObs( tempP, (patArr+2) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645;
        tempP->posY = 302 - (64 * index);
        appendObs( tempP, (patArr+2) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = true;
        tempP->posX = 709 + (64 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+2) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 901;
        tempP->posY = 302 - (64 * index);
        appendObs( tempP, (patArr+2) );         
    }
}

// Populates the Weave pattern.
void populatePatternWeave( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645;
        tempP->posY = 14 + (64 * index);
        appendObs( tempP, (patArr+3) );         
    }
    tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
    tempP->isSpike = false;
    tempP->posX = 781;
    tempP->posY = 302;
    appendObs( tempP, (patArr+3) );         
    tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
    tempP->isSpike = true;
    tempP->posX = 781;
    tempP->posY = 238;
    appendObs( tempP, (patArr+3) );         
}

// Populates the Stairs pattern.
void populatePatternStairs( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 7; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        if( index > 3 ) { tempP->isSpike = true; }
        else { tempP->isSpike = false; }
        tempP->posX = 645 + (64 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+4) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 709 + (64 * index);
        tempP->posY = 238;
        appendObs( tempP, (patArr+4) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 773 + (64 * index);
        tempP->posY = 174;
        appendObs( tempP, (patArr+4) );         
    }
    tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
    tempP->isSpike = false;
    tempP->posX = 837;
    tempP->posY = 110;
    appendObs( tempP, (patArr+4) );         
}

// Populates the Mound pattern.
void populatePatternMound( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = true;
        tempP->posX = 645 + (192 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+5) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = true;
        tempP->posX = 677 + (128 * index);
        tempP->posY = 238;
        appendObs( tempP, (patArr+5) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 677 + (64 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+5) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 709 + (64 * index);
        tempP->posY = 238;
        appendObs( tempP, (patArr+5) );         
    }
}

// Populates the Castle pattern.
void populatePatternCastle( ) {
    Obstacle* tempP = NULL;
    for( int index = 0; index < 5; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = true;
        tempP->posX = 645 + (128 * index);
        tempP->posY = 46;
        appendObs( tempP, (patArr+6) );         
    }
    for( int index = 0; index < 3; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = true;
        tempP->posX = 773 + (128 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+6) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 1093 + (64 * index);
        tempP->posY = 302;
        appendObs( tempP, (patArr+6) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 1093 + (64 * index);
        tempP->posY = 238;
        appendObs( tempP, (patArr+6) );         
    }
    for( int index = 0; index < 2; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645;
        tempP->posY = 238 - (64 * index);
        appendObs( tempP, (patArr+6) );         
    }
    tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
    tempP->isSpike = false;
    tempP->posX = 1157;
    tempP->posY = 142;
    appendObs( tempP, (patArr+6) );         
    for( int index = 0; index < 9; index++ ) {
        tempP = ( Obstacle* ) malloc( sizeof( Obstacle ) );
        tempP->isSpike = false;
        tempP->posX = 645 + (64 * index);
        tempP->posY = 110;
        appendObs( tempP, (patArr+6) );         
    }
}

// Creates the Obstacles.
void createObstaclePatterns( ) {
    initializePatterns();
    populatePatternPlatform();
    populatePatternOverhang();
    populatePatternPit();
    populatePatternWeave();
    populatePatternStairs();
    populatePatternMound();
    populatePatternCastle();
} 

/*---------------------------------------------------------------------------------------/
| OBJECT RESET FUNCTIONS
/---------------------------------------------------------------------------------------*/

// Resets the Player.
void resetPlayer( ) {
    P1->posX = 100; 
    P1->posY = 302; 
    P1->speed = 0; 
    P1->accel = 1; 
    P1->animFrame = 0; 
    P1->isJumping = false; 
    P1->isSliding = false; 
    P1->isDead = false; 
}

// Resets the Platform Pattern.
void resetPatternPlatform( ) {
    Obstacle* tempP = patArr->BP;
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 645 + (64 * index);
        tempP->posY = 302;
        tempP = tempP->next;         
    }
    tempP->isSpike = true;
    tempP->posX = 773;
    tempP->posY = 238;         
}

// Resets the Overhang Pattern.
void resetPatternOverhang( ) {
    Obstacle* tempP = (patArr+1)->BP;
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 645;
        tempP->posY = 14 + (64 * index);
        tempP = tempP->next;
    }    
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 709 + (64 * index);
        tempP->posY = 270;
        tempP = tempP->next;
    }    
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 1029;
        tempP->posY = 14 + (64 * index);
        tempP = tempP->next;
    }    
}

// Resets the Pit Pattern.
void resetPatternPit( ) {
    Obstacle* tempP = (patArr+2)->BP;
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 645 + (64 * index);
        tempP->posY = 46;
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 645;
        tempP->posY = 302 - (64 * index);
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 709 + (64 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 901;
        tempP->posY = 302 - (64 * index);
        tempP = tempP->next;
    }
}

// Resets the Weave Pattern.
void resetPatternWeave( ) {
    Obstacle* tempP = (patArr+3)->BP;
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 645;
        tempP->posY = 14 + (64 * index);
        tempP = tempP->next;
    }
    tempP->posX = 781;
    tempP->posY = 302;
    tempP = tempP->next;
    tempP->posX = 781;
    tempP->posY = 238;
}

// Resets the Stairs Pattern.
void resetPatternStairs( ) {
    Obstacle* tempP = (patArr+4)->BP;
    for( int index = 0; index < 7; index++ ) {
        tempP->posX = 645 + (64 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 709 + (64 * index);
        tempP->posY = 238;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 773 + (64 * index);
        tempP->posY = 174;
        tempP = tempP->next;
    }
    tempP->posX = 837;
    tempP->posY = 110;
}

// Resets the Mound Pattern.
void resetPatternMound( ) {
    Obstacle* tempP = (patArr+5)->BP;
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 645 + (192 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 677 + (128 * index);
        tempP->posY = 238;
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 677 + (64 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 709 + (64 * index);
        tempP->posY = 238;
        tempP = tempP->next;
    }
}

// Resets the Castle Pattern.
void resetPatternCastle( ) {
    Obstacle* tempP = (patArr+6)->BP;
    for( int index = 0; index < 5; index++ ) {
        tempP->posX = 645 + (128 * index);
        tempP->posY = 46;
        tempP = tempP->next;
    }
    for( int index = 0; index < 3; index++ ) {
        tempP->posX = 773 + (128 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 1093 + (64 * index);
        tempP->posY = 302;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 1093 + (64 * index);
        tempP->posY = 238;
        tempP = tempP->next;
    }
    for( int index = 0; index < 2; index++ ) {
        tempP->posX = 645;
        tempP->posY = 238 - (64 * index);
        tempP = tempP->next;
    }
    tempP->posX = 1157;
    tempP->posY = 142;
    tempP = tempP->next;
    for( int index = 0; index < 9; index++ ) {
        tempP->posX = 645 + (64 * index);
        tempP->posY = 110;
        tempP = tempP->next;
    }
}

// Resets all Obstacles.
void resetAllObstacles( int* obsState ) {
    *obsState = 0;
    resetPatternPlatform();
    resetPatternOverhang();
    resetPatternPit();
    resetPatternWeave();
    resetPatternStairs();
    resetPatternMound();
    resetPatternCastle();
}

/*---------------------------------------------------------------------------------------/
| OBSTACLE SPAWNING AND MOVEMENT FUNCTIONS 
/---------------------------------------------------------------------------------------*/

// Spawns an obstacle if one isn't already present.
void spawnObstacle( int* obsState, int* probArr ) {
    
    // Checks if an Obstacle isn't already present.
    if( *obsState == 0 ) {

        // Selects the Pattern.
        int currPattern = rand() % 33;
// debug: int currPattern = 31;    // 0, 6, 11, 15, 20, 25, 31
        *obsState = *(probArr+currPattern);
    }
}

// Shifts the Obstacle leftward.
void moveObstacle( int* obsType ) {
    
    // Checks if an Obstacle exists and sets the patArr index.
    if( *obsType != 0 ) {
        int num = *obsType - 1;

        // Shifts each element in the obstacle over.
        Obstacle* tempP = (patArr+num)->BP;
        for( int index = 0; index < (patArr+num)->size; index++ ) {
            tempP->posX -= 5;
            tempP = tempP->next;
        }

        // Detects if the Obstacle is off-screen, and resets it.
        if( (patArr+num)->BP->posX < -640 ) {
            tempP = (patArr+num)->BP;
            for( int index = 0; index < (patArr+num)->size; index++ ) {
                tempP->posX += 1280;
                tempP = tempP->next;
            }
            *obsType = 0;
        }    
    }
}

/*---------------------------------------------------------------------------------------/
| PARALLAX BACKGROUND RELATED FUNCTIONS 
/---------------------------------------------------------------------------------------*/

// Spawns in a Foreground Tree. (~17%)
bool getForegroundTree( ) {
    if( (rand() % 6) == 0 ) { return true; }
    else { return false; }
}

// Moves the position of each Background Plane.
void moveParallax(     int* plats, int* trees, int* cacti, int* grass ) {
    
    // Moves the Plateaus.
    if( (get_frame_counter() % 4) == 0 ) {
        *plats -= 1;
        if( *plats < -639 ) { *plats += 640; }
    }

    // Moves the Trees.
    *trees -= 1;
    if( *trees < -639 ) { *trees += 640; }

    // Moves the Cacti.
    *cacti -= 3;
    if( *cacti < -639 ) { *cacti += 640; }

    // Moves the Grass.
    *grass -= 5;
    if( *grass < -639 ) { *grass += 640; }

    // Moves the Foreground.
    Foreground* tempP = foreground->top;
    for( int index = 0; index < 3; index++ ) {
        tempP->posX -= 9;
        tempP = tempP->prev;
    }
    if( foreground->top->posX < -1279 ) {
        tempP = pop( foreground );
        tempP->posX += 1920;
        tempP->isTree = getForegroundTree();
        push( tempP, foreground );
    }
}

/*---------------------------------------------------------------------------------------/
| PLAYER PHYSICS FUNCTION
/---------------------------------------------------------------------------------------*/

void calculatePlayerMotion( int A, int B, bool* check, int timer ) {

    // Triggers the Player's Jump.
    if( ((A == 1) && (P1->isJumping == false)) && (P1->isSliding == false) ) {
        P1->isJumping = true;
        P1->speed = -20;
    }

    // Adjusted Acceleration if A is Held.
    if( ((A >= 1) && (P1->isJumping == true)) && (P1->speed < 0) ) {P1->accel = 1;}
    else if( (!(A >= 1) && (P1->isJumping == true)) && (P1->speed < 0) ) {P1->accel = 3;}
        
    // Sets Downwards Acceleration to be constant.
    if( P1->speed >= 0 ) { P1->accel = 1; }

    // Moves the Player.
    P1->speed += P1->accel;
    P1->posY += P1->speed;

    // Detects Player Collision with the Ground.
    if( P1->posY > 302 ) {
        P1->posY = 302;
        P1->speed = 0;
        P1->accel = 0;
        P1->isJumping = false;
        *check = true;
        if( timer == 0 ) { play_sound( sGrass ); }
        playPlayerWalkingOnGrass();
    }

    // Triggers the Player's Slide.
    if( (B > 0) && (P1->isJumping == false) ) { P1->isSliding = true; }
    else { P1->isSliding = false; }

    // Updates the Player's Running Animation.
    if( (get_frame_counter() % 7) == 0 ) {
        P1->animFrame += 1;
        P1->animFrame = P1->animFrame % 4;
    }    
}

/*---------------------------------------------------------------------------------------/
| PLAYER - OBSTACLE COLLISION FUNCTIONS
/---------------------------------------------------------------------------------------*/

// Checks for Player-Block Running Collision.
bool isPlayerRunningOnBlock( Obstacle* obs ) {
    if( ((P1->posX >= obs->posX) && (P1->posX <= obs->posX+63)) || 
    ((P1->posX+49 >= obs->posX) && (P1->posX+49 <= obs->posX+63)) ) {
        if( (P1->posY >= obs->posY-63) && (P1->posY <= obs->posY-43) ) {
            return true;
        }
    }
    return false;
}

// Checks for Player-Block Hit Collision.
bool isPlayerInsideBlock( Obstacle* obs ) {
    if( (P1->posX+47 >= obs->posX) && (P1->posX+47 <= obs->posX+63) ) {
        if( P1->isSliding == true ) {
            if( ((P1->posY-24 >= obs->posY-63) && (P1->posY-24 <= obs->posY)) ||
            ((P1->posY-5 >= obs->posY-63) && (P1->posY-5 <= obs->posY)) ) {
                return true;
            }    
        } else {
            if( ((P1->posY-50 >= obs->posY-63) && (P1->posY-50 <= obs->posY)) ||
            ((P1->posY-5 >= obs->posY-63) && (P1->posY-5 <= obs->posY)) ) {
                return true;
            }    
        }
    }
    return false;
}

// Checks for Player-Spike Bottom Hit Collision.
bool isPlayerInsideSpikeBottom( Obstacle* obs ) {
    if( ((P1->posX+5 >= obs->posX+24) && (P1->posX+5 <= obs->posX+39)) ||
    ((P1->posX+49 >= obs->posX+24) && (P1->posX+49 <= obs->posX+39)) ) {
        if( P1->isSliding == true ) {
            if( ((P1->posY-24 >= obs->posY-49) && (P1->posY-24 <= obs->posY-22)) ||
            ((P1->posY-5 >= obs->posY-49) && (P1->posY-5 <= obs->posY-22)) ) {
                return true;
            }    
        } else {
            if( ((P1->posY-54 >= obs->posY-49) && (P1->posY-54 <= obs->posY-22)) ||
            ((P1->posY-5 >= obs->posY-49) && (P1->posY-5 <= obs->posY-22)) ) {
                return true;
            }    
        }
    }
    return false;
}

// Checks for Player-Spike Top Hit Collision.
bool isPlayerInsideSpikeTop( Obstacle* obs ) {
    if( ((P1->posX+5 >= obs->posX+10) && (P1->posX+5 <= obs->posX+53)) ||
    ((P1->posX+49 >= obs->posX+10) && (P1->posX+49 <= obs->posX+53)) ) {
        if( P1->isSliding == true ) {
            if( ((P1->posY-24 >= obs->posY-21) && (P1->posY-24 <= obs->posY)) ||
            ((P1->posY-5 >= obs->posY-21) && (P1->posY-5 <= obs->posY)) ) {
                return true;
            }    
        } else {
            if( ((P1->posY-54 >= obs->posY-21) && (P1->posY-54 <= obs->posY)) ||
            ((P1->posY-5 >= obs->posY-21) && (P1->posY-5 <= obs->posY)) ) {
                return true;
            }    
        }
    }
    return false;
}

// Function for checking all Player-Obstacle Collisions.
void calculatePlayerObstacleCollision( int obsState, bool* check, int timer ) {

    // Determines if an obstacle exists to run collision on.
    if( obsState != 0 ) {
        
        // Sets num to the correct patArr index.
        int num = obsState - 1;

        // Calculates collision.
        Obstacle* tempP = (patArr+num)->BP;
        for( int index = 0; index < (patArr+num)->size; index++ ) {

            // Determines if the Object is a Block.
            if( tempP->isSpike == false ) {
                            
                // Player-Block Running Collision.
                if( isPlayerRunningOnBlock( tempP ) == true ) {
                    P1->posY = tempP->posY - 64;
                    P1->speed = 0;
                    P1->accel = 0;
                    P1->isJumping = false;
                    *check = true;
                    if( timer == 0 ) { play_sound( sMetal ); }
                    playPlayerWalkingOnBlock();
                }
        
                // Player-Block Hit Collision.
                if( isPlayerInsideBlock( tempP ) == true ) {
                    P1->isDead = true;
                    play_sound( sDead );
                }

            // Determines if the Object is a Spike.
            } else {

                // Player-Spike Bottom Hit Collision.
                if( isPlayerInsideSpikeBottom( tempP ) == true ) {
                    P1->isDead = true;
                    *check = true;
                    play_sound( sDead );
                }
                
                // Player-Spike Top Hit Collision.
                if( isPlayerInsideSpikeTop( tempP ) == true ) {
                    P1->isDead = true;
                    *check = true;
                    play_sound( sDead );
                }
            }

            // Moves tempP.
            tempP = tempP->next;
        }
    }
}

// Updates the Collision Timer.
void updateCollisionTimer( bool* check, int* timer ) {
    if( *check == true ) { *timer += 1; }
    else { *timer = 0; }
    *check = false;
}

/*---------------------------------------------------------------------------------------/
| GAMEPLAY RENDERING FUNCTIONS 
/---------------------------------------------------------------------------------------*/

// Renders the Background Parallax.
void renderBackground( int platsX, int treesX, int cactiX ) {
    select_texture( 0 );
    select_region( rSky );
    draw_region_at( 0,0 );
    select_region( rPlateaus );
    draw_region_at( platsX,330 );
    draw_region_at( platsX+640,330 );
    select_region( rTrees );
    draw_region_at( treesX,359 );
    draw_region_at( treesX+640,359 );
    select_region( rCacti );
    draw_region_at( cactiX,359 );
    draw_region_at( cactiX+640,359 );
}

// Renders the Player.
void renderPlayer( ) {

    select_texture( 0 );

    // Renders the Slide.
    if( P1->isSliding == true ) {
        select_region( rPSlide );
        draw_region_at( P1->posX,P1->posY );

    // Renders the Jump.
    } else if( P1->isJumping == true ) {
        if( P1->speed >= 0 ) { select_region( rPJump ); }
        else { select_region( rPFall ); }
        draw_region_at( P1->posX,P1->posY );

    // Renders the Run.
    } else {
        select_region( P1->animFrame + 10 );
        draw_region_at( P1->posX,P1->posY );
    }
}

// Renders the Current Obstacle.
void renderObstacle( int obsType ) {
    if( obsType != 0 ) {
        select_texture( 0 );
        int currPat = obsType - 1;
        Obstacle* tempP = (patArr+currPat)->BP;
        for( int index = 0; index < (patArr+currPat)->size; index++ ) {
            if( (tempP->posX > -65) && (tempP->posX < 640) ) {
                if( tempP->isSpike == true ) { select_region( rSpike ); }
                else { select_region( rBlock ); }
                draw_region_at( tempP->posX,tempP->posY );
            }
            tempP = tempP->next;
        }
    }
}

// Renders the Foreground Parallax.
void renderForeground( int grassX ) {

    // Renders the Grass.
    select_texture( 0 );
    select_region( rGrass );
    draw_region_at( grassX,359 );
    draw_region_at( grassX+640,359 );

    // Renders the Foreground.
    select_texture( 1 );
    Foreground* tempP = foreground->top;
    for( int index = 0; index < 3; index++ ) {
        if( (tempP->posX > -642) && (tempP->posX < 642) ) {
            if( tempP->isTree == false ) { select_region( rFGGrass ); }
            else { select_region( rFGTree ); }
            draw_region_at( tempP->posX,359 );
        }
        tempP = tempP->prev;
    }
}

/*---------------------------------------------------------------------------------------/
| MAIN FUNCTION
/---------------------------------------------------------------------------------------*/

void main( void ) {

    // Defines the texture regions.
    defineTextureRegions();

    // Initializes the Game State to the Title Screen.
    int gameState = 2;

    // Initializes RNG.
    srand( get_time() );

    // Initializes all game objects.
    initializePlayer();
    initializeForeground();    
    createObstaclePatterns();
    int obstacleState = 0;
    int[33] obstacleProbs = {    1, 1, 1, 1, 1, 1,
                                2, 2, 2, 2, 2,
                                3, 3, 3, 3,
                                4, 4, 4, 4, 4,
                                5, 5, 5, 5, 5,
                                6, 6, 6, 6, 6, 6,
                                7, 7               };

    // Initializes variables for the parallax background.
    int plateausX = 0;
    int treesX = 0;
    int cactiX = 0;
    int grassX = 0;

    // Initializes Starting/Death Screen Text.
    bool isTextVisible = true;
    
    // Initializes the Background Ambiance.
    initializeBackgroundSound();

    // Initializes variables for Collision SFX.
    bool collisionCheck = false;
    int collisionTimer = 1;

    // Initializes the gamepad for player input.
    select_gamepad( 0 );
    int aPress;
    int bPress;

    /*-----------------------------------------------------------------------------------/
    | PRIMARY WHILE GAMELOOP
    /-----------------------------------------------------------------------------------*/

    while( true ) {

        /*-------------------------------------------------------------------------------/
        | PLAYER INPUT DETECTION
        /-------------------------------------------------------------------------------*/

        // Grabs the Player Input.
        aPress = gamepad_button_a();
        bPress = gamepad_button_b();

        /*-------------------------------------------------------------------------------/
        | GAME SCENE - GAMEPLAY
        /-------------------------------------------------------------------------------*/

        // Checks the Game State to if Gameplay is running.
        if( gameState == 0 ) {

        // Updates Background Elements.
        moveParallax( &plateausX, &treesX, &cactiX, &grassX );

        // Calculates Player Functions.
        calculatePlayerMotion( aPress, bPress, &collisionCheck, collisionTimer );

        // Manages Obstacle Spawning and Movement.
        spawnObstacle( &obstacleState, obstacleProbs );
        moveObstacle( &obstacleState );

        // Calculates Obstacle-Player Collision.
        calculatePlayerObstacleCollision( obstacleState, &collisionCheck, collisionTimer);
        updateCollisionTimer( &collisionCheck, &collisionTimer );

        // Renders the Gameplay.
        renderBackground( plateausX, treesX, cactiX );
        renderPlayer();
        renderObstacle( obstacleState );
        renderForeground( grassX );

        // Triggers a Game Reset if the Player is Dead.
        if( P1->isDead == true ) {

            // Sets the Game State to the Death Screen.
            gameState = 1;

            // Resets the Gameplay Scene.
            resetPlayer();
            resetAllObstacles( &obstacleState );
        }

        /*-------------------------------------------------------------------------------/
        | GAME SCENE - DEATH
        /-------------------------------------------------------------------------------*/

        // Checks the Game State to if the player has died.
        } else if( gameState == 1 ) {        

        // Pauses the Background Ambience.
        pause_channel( 0 );

        // Changes the Game State if the A Button is pressed.
        if( aPress == 1 ) { 
            gameState = 0;
            play_channel( 0 );
         }

        // Swaps the "Press A" text after a certain number of frames.
        if( (get_frame_counter() % 30) == 0 ) {
            if( isTextVisible == true ) {
                isTextVisible = false; 
                play_sound( sText ); 
            } else { isTextVisible = true; }
        }

        // Renders the Title Screen + Text.
        select_texture( 2 );
        select_region( rDScreen );
        draw_region_at( 0,0 );
        if( isTextVisible == true ) {
            select_region( rDText );
            draw_region_at( 320,250 );    
        }

        /*-------------------------------------------------------------------------------/
        | GAME SCENE - TITLE
        /-------------------------------------------------------------------------------*/

        // Checks the Game State to if the Title Screen is loaded.
        } else if( gameState == 2 ) {

        // Changes the Game State if the A Button is pressed.
        if( aPress == 1 ) { gameState = 0; }

        // Swaps the "Press A" text after a certain number of frames.
        if( (get_frame_counter() % 30) == 0 ) {
            if( isTextVisible == true ) { 
                isTextVisible = false; 
                play_sound( sText );
            } else { isTextVisible = true; }
        }

        // Renders the Title Screen + Text.
        select_texture( 3 );
        select_region( rSScreen );
        draw_region_at( 0,0 );
        if( isTextVisible == true ) {
            select_region( rSText );
            draw_region_at( 619,339 );    
        }

        // Closes the Game Scene If-statement.
        }

        // Ends the frame.
        end_frame();
    }
}
