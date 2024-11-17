#include "memcard.h"
#include "string.h"
#include "time.h"
#include "GameFuncs.h"
#include "CWorldParts.h"
#include "Common.h"
#include "Defines.h"
#include "Game.h"
#include "StageSelect.h"
#include "Credits.h"
#include "Titlescreen.h"
#include "CInput.h"
#include "Levels.h"
#include "CLevelPackFile.h"

void main()
{
	memset( &GameSignature, 0, sizeof( game_signature ) );
    strcpy( GameSignature, "Vircoban_V1" );
	srand(get_time() + get_date());
#ifdef DEBUG
	initDebugSpeed();
#endif
	setupFonts();
	setupLevels();
	CAudio_Init();
	CAudio_SetSoundEnabled(true);
	CAudio_SetMusicEnabled(true);
	WorldParts = CWorldParts_Create();	
	SearchForLevelPacks();
	SearchForMusic();
	LoadSettings();
	LoadSounds();
	LoadGraphics();					
	LevelPackFile = CLevelPackFile_Create();
	while (GameState != GSQuit)
	{
		switch(GameState)
		{
			case GSTitleScreen :
				TitleScreen();
				break;
			case GSCredits :
				Credits();
				break;
			case GSGame :
				Game();
				break;
			case GSStageClear:
				break;
			case GSStageSelect:
				StageSelect();
				break;
		}
	}
	CLevelPackFile_Destroy(LevelPackFile);
	SaveSettings();
	UnLoadGraphics();
	UnloadSounds();
	UnloadMusic();
	CWorldParts_RemoveAll(WorldParts);
	CWorldParts_Destroy(WorldParts);
}
