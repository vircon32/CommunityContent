#include "time.h"
#include "string.h"
#include "gamestates/game.h"
#include "gamestates/stageclear.h"
#include "gamestates/nextstage.h"
#include "gamestates/options.h"
#include "gamestates/stageselect.h"
#include "gamestates/oldmanspeaking.h"
#include "gamestates/passwordentry.h"
#include "gamestates/titlescreen.h"
#include "gamestates/intro.h"
#include "gamestates/credits.h"
#include "gamestates/gamecommon.h"
#include "gameobjects/chand.h"
#include "commonvars.h"
#include "sound.h"
#include "fonts/Asheville_Sans_14_Bold_14.h"
#include "fonts/Mini_Sans_2X_14.h"
#include "debugspeed.h"

void LoadFonts(void)
{
	setupFontAsheville_Sans_14_Bold_14();
	setupFontMini_Sans_2X_14();

	Mini2X = &FontMini_Sans_2X_14;
	Ash = &FontAsheville_Sans_14_Bold_14;
}

void terminateGame()
{
	switch(GameState)
	{
		case GSIntro :
			IntroDeInit();
			break;
		case GSTitleScreen :
			TitleScreenDeInit();
			break;
		case GSOldManSpeaking :
			OldManSpeakingDeInit();
			break;
		case GSPasswordEntry :
			PassWordEntryDeInit();
			break;
		case GSCredits :
			CreditsDeInit();
			break;
		case GSOptions :
			OptionsDeInit();
			break;
		case GSGame :
			GameDeInit();
			break;
		case GSStageClear:
			StageClearDeInit();
			break;
		case GSNextStage:
			if (Level == 0)
				NextStageLevel0DeInit();
			else
				NextStageLevel1to35DeInit();
			break;
		case GSStageSelect:
			StageSelectDeInit();
			break;
		default:
			break;
	}
	deInitSound();
	deInitMusic();
	UnloadImages();
	SaveSettings();
	CHand_Destroy(Hand);
}

void resetGlobals()
{
	GameState = GSIntroInit;
	NeedGameReset = false;
}

void setupGame()
{
	memset( &GameSignature, 0, sizeof( game_signature ) );
    strcpy( GameSignature, "Puzzleland_V1" );
	resetGlobals();
	initSound();
	initMusic();
	LoadFonts();
	LoadImages();
	LoadSettings();
	Hand = CHand_Create();
}

void main()
{
	setupGame();
	int multiplyColor;
	while(true)
	{
		switch(GameState)
		{
			case GSIntroInit :
			case GSIntro :
				Intro();
				multiplyColor = make_color_rgb(147,70,13);
				break;
			case GSTitleScreenInit :
			case GSTitleScreen :
				TitleScreen();
				multiplyColor = make_color_rgb(147,70,13);
				break;
			case GSOldManSpeakingInit :
			case GSOldManSpeaking :
				OldManSpeaking();
				multiplyColor = make_color_rgb(168,169,218);
				break;
			case GSPasswordEntryInit :
			case GSPasswordEntry :
				PasswordEntry();
				multiplyColor = make_color_rgb(178,106,23);
				break;
			case GSCreditsInit :
			case GSCredits :
				Credits();
				multiplyColor = make_color_rgb(178,106,23);
				break;
			case GSOptionsInit :
			case GSOptions :
				Options();
				multiplyColor = make_color_rgb(178,106,23);
				break;
			case GSGameInit :
			case GSGame :
				Game();
				multiplyColor = make_color_rgb(179,27,7);
				break;
			case GSStageClearInit:
			case GSStageClear:
				StageClear();
				multiplyColor = make_color_rgb(179,27,7);
				break;
			case GSNextStageInit:
			case GSNextStage:
				if (Level == 0)
					NextStageLevel0();
				else
					NextStageLevel1to35();
				multiplyColor = make_color_rgb(168,169,218);				
				break;
			case GSStageSelectInit:
			case GSStageSelect:
				StageSelect();
				multiplyColor = make_color_rgb(178,106,23);
				break;
			default:
				break;
		}		
		set_multiply_color(multiplyColor);
		drawTexture(Border, 0, 0, 0);
		set_multiply_color(color_white);
		if(DEBUG)
		{
			int[100] DebugText;
			int[10] DebugTmpNr;
			strcpy(DebugText, "MEM USE: ");		
			itoa(MemoryUsed(), DebugTmpNr, 10);
			strcat(DebugText, DebugTmpNr);
			set_multiply_color(make_color_rgb(255,0,255));
			print_at(0,bios_character_height, DebugText);
			set_multiply_color(color_white);
		}
		end_frame();
	}	
	terminateGame();
}
