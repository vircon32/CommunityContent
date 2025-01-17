#include "time.h"
#include "texture.h"
#include "defines.h"
#include "cworldparts.h"
#include "common.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include "cselector.h"
#include "state_gametypemenu.h"
#include "state_credits.h"
#include "state_titlescreen.h"
#include "state_timeover.h"
#include "state_readygo.h"
#include "state_intro.h"
#include "state_game.h"
#include "state_showhighscores.h"
#include "gamefuncs.h"

void main()
{
	memset( &GameSignature, 0, sizeof( game_signature ) );
	strcpy( GameSignature, "Znax_V1" );
    srand(get_date() + get_time());
    CAudio_Init();
	CAudio_SetSoundEnabled(true);
	CAudio_SetMusicEnabled(true);
    setupFonts();
    LoadGraphics();
    LoadSounds();
    LoadHighScores();
    World = CWorldParts_Create();
    while (GameState != GSQuit)
    {
        switch(GameState)
        {
            case GSGame :
                Game();
                break;
            case GSTitleScreen:
                TitleScreen();
                break;
            case GSIntro :
                Intro();
                break;
            case GSReadyGo:
                ReadyGo();
                break;
            case GSTimeOver:
                TimeOver();
                break;
            case GSCredits:
                Credits();
                break;
            case GSGameTypeMenu:
                GameTypeMenu();
                break;
            case GSShowHighScores:
                ShowHighScores();
                break;
            default :
                break;
        }
    }
    CWorldParts_Destroy(World);    
    UnloadSounds();
    UnloadMusic();
    UnLoadGraphics();
    CAudio_DeInit();
}
