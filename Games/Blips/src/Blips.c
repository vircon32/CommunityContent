
#include "time.h"
#include "Common.h"
#include "Intro.h"
#include "CWorldParts.h"
#include "GameFuncs.h"
#include "StageSelect.h"
#include "Credits.h"
#include "TitleScreen.h"
#include "Levels.h"
#include "Game.h"
#include "CAudio.h"

void main()
{
	memset( &GameSignature, 0, sizeof( game_signature ) );
	strcpy( GameSignature, "Blips_V1" );
	MenuBoxColor = make_color_rgb(75,138,158);
	MenuBoxBorderColor = make_color_rgb(2,66,87);
	MenuTextColor = make_color_rgb(2,66,87);
	setupLevels();
	WorldParts = CWorldParts_Create();
	SearchForLevelPacks();
	LoadSounds();
	FindLevels();
	LoadGraphics();
	loadFonts();
	while (true)
	{
		switch(GameState)
		{
		 	case GSIntro :
		 		Intro();
		 		break;
		 	case GSTitleScreen :
		 		TitleScreen();
		 		break;
			case GSCredits :
		 		Credits();
		 		break;
		 	case GSGame :
		 		Game();
		 		break;
			case GSStageSelect:
		 		StageSelect();
		 		break;																
		 	default:
		 		break;
		}
	}
	UnLoadGraphics();
	UnloadSounds();
	CWorldParts_Destroy(WorldParts);
}
