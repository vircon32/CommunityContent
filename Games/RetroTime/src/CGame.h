#ifndef CGAME_H
#define CGAME_H

#include "texture.h"
#include "string.h"
#include "time.h"
#include "video.h"
#include "Common.h"
#include "CImage.h"
#include "CSprites.h"
#include "debugspeed.h"

#include "CFont.h"
#include "TitleScreen.h"
#include "SubScoreScreen.h"
#include "GamesShare.h"
#include "Intro.h"

#undef LoadImage
#undef PlaySound

void CGame_LoadMusic()
{
	MusMenu = CAudio_LoadMusic("main/music");
}

void CGame_UnLoadMusic()
{
	CAudio_UnloadMusics();
}

void CGame_UnLoadGraphics()
{
	CImage_UnloadImages();
}

void CGame_LoadSound()
{
	SfxTimeOver = CAudio_LoadSound("common/timeover");
	SfxReadyGo = CAudio_LoadSound("common/readygo");
	SfxOne = CAudio_LoadSound("common/one");
	SfxTwo = CAudio_LoadSound("common/two");
	SfxThree = CAudio_LoadSound("common/three");
	SfxOneMinute = CAudio_LoadSound("common/oneminute");
	SfxConfirm = CAudio_LoadSound("main/confirm");
	SfxBack = CAudio_LoadSound("main/back");
	SfxSelect = CAudio_LoadSound("main/select");
	SfxScore = CAudio_LoadSound("main/score");
}

void CGame_UnLoadSound()
{
	CAudio_UnloadSounds();
}

void CGame_LoadGraphics()
{
	GFXFrameID = CImage_LoadImage("main/frame.png");
	GFXOuterFrameID = CImage_LoadImage("main/outerframe.png");
	GFXMedal = CImage_LoadImage("main/medal.png");
	GFXPrevewID = CImage_LoadImage("gamepreview/gamepreview.png");
	GFXPreviewID2 = CImage_LoadImage("gamepreview/gamepreview2.png");
}




void CGame_ResetTimer()
{
	Timer = 120;
	if (GameMode == GMRetroCarousel)
	{
		Timer = 2 * 60;
	}
	if (GameMode == GMTimeAttack)
	{
		Timer = 5 * 60;
	}
	TimerTicks = getCurrentTimeMilliseconds();
}

void CGame_UpdateTimer()
{
	if (TimerTicks + 250 < getCurrentTimeMilliseconds())
	{
		TimerTicks = getCurrentTimeMilliseconds();
		if (SubGameState == SGGame)
		{
			if (GameMode == GMGame)
				Timer += 0.25;
			else
			{
				Timer -= 0.25;

				if (Timer == 60)
				 	CAudio_PlaySound(SfxOneMinute, 0);

				if (Timer == 3)
				 	CAudio_PlaySound(SfxThree, 0);

				if (Timer == 2)
				 	CAudio_PlaySound(SfxTwo, 0);

				if (Timer == 1)
				 	CAudio_PlaySound(SfxOne, 0);


				if (Timer <= 0)
				{
					CAudio_PlaySound(SfxTimeOver, 0);
					SubGameState = SGTimeUp;
					SubStateTime = getCurrentTimeMilliseconds() + 750;
					SubStateCounter = 0;
				}
			}
		}
	}
}

void CGame_DestroyActiveGame()
{
	switch(ActiveGameGameStateId)
	{
	 	case GSSnake:
	 		CGameSnake_deinit(GameSnake);
	 		Destroy_CGameSnake(GameSnake);
	 		ActiveGameGameStateId = -1;
			break;
	 	case GSRamIt:
	 		CGameRamIt_deinit(GameRamIt);
	 		Destroy_CGameRamIt(GameRamIt);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSPang:
	 		CGamePang_deinit(GamePang);
	 		Destroy_CGamePang(GamePang);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSSpaceInvaders:
	 		CGameInvaders_deinit(GameInvaders);
	 		Destroy_CGameInvaders(GameInvaders);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	case GSFrog:
	 		CGameFrog_deinit(GameFrog);
	 		Destroy_CGameFrog(GameFrog);
	 		ActiveGameGameStateId = -1;
	 		break;
		case GSEddy:
	 		CGameFastEddy_deinit(GameFastEddy);
	 		Destroy_CGameFastEddy(GameFastEddy);
	 		ActiveGameGameStateId = -1;
	 		break;
		case GSBreakout:
			CGameBreakOut_deinit(GameBreakOut);
			Destroy_CGameBreakOut(GameBreakOut);
			ActiveGameGameStateId = -1;
			break;
	 	case GSTetris:
	 		CGameBlockStacker_deinit(GameBlockStacker);
	 		Destroy_CGameBlockStacker(GameBlockStacker);
	 		ActiveGameGameStateId = -1;
	 		break;
	 	default:
	 		ActiveGameGameStateId = -1;
			break;
	}
}

void CGame_CreateActiveGame()
{
	switch (GameState)
	{
	 	case GSSnakeInit:
	 		GameSnake = Create_CGameSnake();
	 		ActiveGameGameStateId = GSSnake;
	 		break;
	 	case GSTetrisInit:
	 		GameBlockStacker = Create_CGameBlockStacker();
	 		ActiveGameGameStateId = GSTetris;
	 		break;
	 	case GSRamItInit:
	 		GameRamIt = Create_CGameRamIt();
	 		ActiveGameGameStateId = GSRamIt;
	 		break;
	 	case GSEddyInit:
	 		GameFastEddy = Create_CGameFastEddy();
	 		ActiveGameGameStateId = GSEddy;
	 		break;
	 	case GSFrogInit:
	 		GameFrog = Create_CGameFrog();
	 		ActiveGameGameStateId = GSFrog;
	 		break;
	 	case GSBreakoutInit:
			GameBreakOut = Create_CGameBreakOut();
			ActiveGameGameStateId = GSBreakout;
			break;
		case GSPangInit:
	 		GamePang = Create_CGamePang();
	 		ActiveGameGameStateId = GSPang;
	 		break;
	 	case GSSpaceInvadersInit:
	 		GameInvaders = Create_CGameInvaders();
	 		ActiveGameGameStateId = GSSpaceInvaders;
	 		break;
	 	default:
	 		ActiveGameGameStateId = -1;
	 		break;
	}
}
void CGame_DeInit()
{
	switch(ActiveGameGameStateId)
	{
	 	case GSSnake:
	 		CGameSnake_deinit(GameSnake);
	 		Destroy_CGameSnake(GameSnake);
	 		break;
	 	case GSRamIt:
	 		CGameRamIt_deinit(GameRamIt);
	 		Destroy_CGameRamIt(GameRamIt);
	 		break;
	 	case GSPang:
	 		CGamePang_deinit(GamePang);
	 		Destroy_CGamePang(GamePang);
	 		break;
	 	case GSSpaceInvaders:
	 		CGameInvaders_deinit(GameInvaders);
	 		Destroy_CGameInvaders(GameInvaders);
	 		break;
	 	case GSFrog:
	 		CGameFrog_deinit(GameFrog);
	 		Destroy_CGameFrog(GameFrog);
	 		break;
	 	case GSEddy:
	 		CGameFastEddy_deinit(GameFastEddy);
	 		Destroy_CGameFastEddy(GameFastEddy);
	 		break;
	 	case GSBreakout:
	 		CGameBreakOut_deinit(GameBreakOut);
	 		Destroy_CGameBreakOut(GameBreakOut);
	 		break;
	 	case GSTetris:
	 		CGameBlockStacker_deinit(GameBlockStacker);
	 		Destroy_CGameBlockStacker(GameBlockStacker);
	 		break;
	 	default:
	 		break;
	}

	DeInitSubScoreScreen();


	CGame_UnLoadMusic();
	CGame_UnLoadGraphics();
	CGame_UnLoadSound();
	CGame_SaveHighScoresSettings();

	CAudio_DeInit();
	CFont_DeInit();
	CImage_DeInit();
	CSprites_DeInit();
}

void CGame_Init()
{
	srand(get_time() + get_date());
	initDebugSpeed();
	memset( &GameSignature, 0, sizeof( game_signature ) );
    strcpy( GameSignature, "RETROTIME_V1" );
	CAudio_Init();
	CFont_Init();
	CImage_Init();
	CSprites_Init();
	CGame_ResetHighScores();
	CSprites_SetForceShowCollisionShape(debugShowCollisionShapes);

	CGame_LoadHighScoresSettings();
	CGame_LoadGraphics();
	CGame_LoadMusic();
	CGame_LoadSound();

	ResetGlobalsTitleScreen();

	//Main State Variables and such
	CurrentGameMusicID = -1;
	GameState = GSIntroInit;
	Game = 0;
	GameMode = GMGame;
	SubStateTime = 0;
	Timer = 0.0;
	SubStateCounter = 0;
	TimerTicks = 0;
	SubGameState = SGNone;
	NextSubState = 0;
	NextSubStateCounter = 0;
	NextSubStateTimeAdd = 0;
	ActiveGameGameStateId = -1;

	//Clear score values
	CGame_ResetScores();

}

int[1000] DebugTmpText;
int[10] DebugTmpNr;
int frames = 0;	

void CGame_MainLoop()
{
	//if((frames != 0) && (get_frame_counter() - frames > 16000))
	//	exit();
	CSprites_SpritesDrawnReset();
	CGame_UpdateTimer();

	//in vircon32 c compiler switch statements are not the same as in gcc, it does not use a look up table
	//and the order of your case statement affects number of instructions used. Generally it does a quick check
	//of each case statement in order and each check takes 3 asm instructions so it's wiser to put games
	//that need more cpu usuage first or gamesstates that are les important last 
	switch (GameState)
	{
	 	case GSFrog:
		case GSBreakout:
		case GSEddy:
	 	case GSSpaceInvaders:
		case GSPang:
	 	case GSTetris:
	 	case GSSnake:
	 	case GSRamIt:
	 		switch (ActiveGameGameStateId)
	 		{
	 			case GSFrog:
					StartDebugSpeed(5);
					CGameFrog_UpdateLogic(GameFrog);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameFrog_Draw(GameFrog);
	 				StopDebugSpeed(6);
					break;
	 			case GSBreakout:
					StartDebugSpeed(5);
					CGameBreakOut_UpdateLogic(GameBreakOut);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameBreakOut_Draw(GameBreakOut);
					StopDebugSpeed(6);
	 				break;
				case GSEddy:
					StartDebugSpeed(5);	
	 				CGameFastEddy_UpdateLogic(GameFastEddy);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameFastEddy_Draw(GameFastEddy);
					StopDebugSpeed(6);
	 				break;
	 			case GSSpaceInvaders:
	 				StartDebugSpeed(5);
					CGameInvaders_UpdateLogic(GameInvaders);
	 				StopDebugSpeed(5);
					StartDebugSpeed(6);
					CGameInvaders_Draw(GameInvaders);
					StopDebugSpeed(6);
	 				break;
				case GSPang:
					StartDebugSpeed(5);
	 				CGamePang_UpdateLogic(GamePang);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGamePang_Draw(GamePang);
					StopDebugSpeed(6);
	 				break;
				case GSTetris:
					StartDebugSpeed(5);
	 				CGameBlockStacker_UpdateLogic(GameBlockStacker);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameBlockStacker_Draw(GameBlockStacker);
					StopDebugSpeed(6);
	 				break;
				case GSSnake:
					StartDebugSpeed(5);
	 				CGameSnake_UpdateLogic(GameSnake);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameSnake_Draw(GameSnake);
					StopDebugSpeed(6);
	 				break;
	 			case GSRamIt:
					StartDebugSpeed(5);
	 				CGameRamIt_UpdateLogic(GameRamIt);
					StopDebugSpeed(5);
					StartDebugSpeed(6);
	 				CGameRamIt_Draw(GameRamIt);
					StopDebugSpeed(6);
	 				break;
	 			default:
	 				break;
	 		}
	 		break;
		
		case GSFrogInit:
	 	case GSBreakoutInit:
	 	case GSEddyInit:
	 	case GSSpaceInvadersInit:
	 	case GSPangInit:
		case GSTetrisInit:
		case GSSnakeInit:
	 	case GSRamItInit:
			StartDebugSpeed(4);
			//no game created yet or it was destroyed
	 		if(ActiveGameGameStateId == -1)
			{
				CGame_CreateActiveGame();
				frames = get_frame_counter()-1;
				ResetAllDebugSpeedMaxValues();
				//return so game creation & game init is in seperate frame
				StopDebugSpeed(4);
				return;
			}
			//game had been created init it
	 		switch (ActiveGameGameStateId)
	 		{
	 			case GSFrog:
	 				CGameFrog_init(GameFrog);
	 				break;
	 			case GSBreakout:
	 				CGameBreakOut_init(GameBreakOut);
	 				break;
				case GSEddy:
	 				CGameFastEddy_init(GameFastEddy);
	 				break;
	 			case GSSpaceInvaders:
	 				CGameInvaders_init(GameInvaders);
	 				break;
	 			case GSPang:
	 				CGamePang_init(GamePang);
	 				break;
	 			case GSTetris:
	 				CGameBlockStacker_init(GameBlockStacker);
	 				break;
				case GSSnake:
	 				CGameSnake_init(GameSnake);
	 				break;
				case GSRamIt:
	 				CGameRamIt_init(GameRamIt);
	 				break;
	 		}
			//game was inited switch to non init gamestate
			if (ActiveGameGameStateId != -1)
			{
				CGame_ResetTimer();
	 			CGame_StartCrossFade(ActiveGameGameStateId, SGReadyGo, 3);
			}
			StopDebugSpeed(4);
	 		break;	

		case GSSubScoreInit:
		case GSSubScore:
			//subscorescreen returns false if we exit the state
			if (SubScoreScreen())
				CGame_DestroyActiveGame();
		 	break;

		case GSTitleScreenInit:
		case GSTitleScreen:
		 	//to clear the game data & set ActiveGameGameStateId to -1
			//if we quited from pause menu
		 	CGame_DestroyActiveGame();
		 	TitleScreen();
		 	break;

		case GSIntroInit:
		case GSIntro:
			Intro();
			break;
	
	 	default:
	 		break;
	}

	if(debugInfoStats)
	{
		int* PDebugText = DebugTmpText;
		*PDebugText = 0;
		PDebugText = faststrcat(PDebugText, "GFX Slots: ");
		itoa(GFX_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CImage_ImageSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "SND Slots: ");
		itoa(SND_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CAudio_SoundSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "MUS Slots: ");
		itoa(MUS_Max, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CAudio_MusicSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "SPR Slots: ");		
		itoa(CSprites_spriteMax, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CSprites_MaxSpriteSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);		
		PDebugText = faststrcat(PDebugText,"/");
		itoa(CSprites_SpriteSlotsUsed, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");
				

		PDebugText = faststrcat(PDebugText, "SPR Draws: ");
		itoa(CSprites_SpritesDrawn, DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		PDebugText = faststrcat(PDebugText,"\n");

		PDebugText = faststrcat(PDebugText, "LOW SPR: ");
		if(CSprites_notEnoughSpots)
			PDebugText = faststrcat(PDebugText, "T");
		else
			PDebugText = faststrcat(PDebugText, "F");
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "MEM USE: ");		
		itoa(MemoryUsed(), DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);
		
		PDebugText = faststrcat(PDebugText,"\n");
		
		PDebugText = faststrcat(PDebugText, "CPU USE: ");		
		itoa(CpuUsed(), DebugTmpNr, 10);
		PDebugText = faststrcat(PDebugText, DebugTmpNr);

		PDebugText = faststrcat(PDebugText,"\n");
		
		set_multiply_color(make_color_rgba(255,0,255,255));
		int[10] Nr;
		itoa(get_frame_counter()-frames, Nr, 10);
		print_at(screen_width - strlen(Nr) * bios_character_width,bios_character_height, Nr);
		print_at(0,bios_character_height,DebugTmpText);
		set_multiply_color(color_white);
	}
}



#endif