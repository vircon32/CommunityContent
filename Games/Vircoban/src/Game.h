#ifndef GAME_H
#define GAME_H

#include "misc.h"
#include "Texture.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"
#include "Debugspeed.h"

bool StageDone()
{
	int Teller,FilledSpots=0,Spots=0;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		if (WorldParts->Items[Teller]->Type == IDBox)
		{
			if (WorldParts->Items[Teller]->AnimPhase == 1)
                FilledSpots++;
		}
		else
            if (WorldParts->Items[Teller]->Type == IDSpot)
                Spots++;
    if (FilledSpots >= Spots)
        return true;
    else
        return false;
}

void Game()
{
    CInput *Input = CInput_Create(InputDelay);
	CInput_WaitNoInput(Input);
	int Teller;
	int[1500] Msg;
	int[10] Nr;
	if (MusicCount > 1)
 	{
 	 	SelectedMusic =	1+rand()%(MusicCount-1);
 		CAudio_PlayMusic(Music[SelectedMusic],-1);
	}
	CWorldPart *Player=NULL;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		if (WorldParts->Items[Teller]->Type == IDPlayer)
		{
			Player = WorldParts->Items[Teller];
			break;
		}
	}
	//should never happen
	if(!Player)
	{
		Player = CWorldPart_Create(0,0, true, IDPlayer);
		CWorldParts_Add(WorldParts,Player);
	}

	while (GameState == GSGame)
	{
#ifdef DEBUG
		StartDebugSpeed(3);
#endif
        CInput_Update(Input);

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_B)]) )
		{
			GameState = GSStageSelect;
			CAudio_PlaySound(Sounds[SND_BACK],0);
			CAudio_StopMusic();
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_R)]))
		{
			SelectedMusic++;
			if (SelectedMusic >= MusicCount)
				SelectedMusic = 1;
			
			CAudio_PlayMusic(Music[SelectedMusic],-1);
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_L)]))
		{
			SelectedMusic--;
			if (SelectedMusic <= 0)
				SelectedMusic = MusicCount-1;

			CAudio_PlayMusic(Music[SelectedMusic],-1);
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_Y)]))
		{
			drawTexture(IMGBackground,0,0,0);
			CWorldParts_Draw(WorldParts);
			if(AskQuestion("You are about to restart this level\nAre you sure you want to restart?\n\nPress (A) to Restart (X) to Cancel"))
			{
				CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
				for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
				{
					if (WorldParts->Items[Teller]->Type == IDPlayer)
					{
						Player = WorldParts->Items[Teller];
						break;
					}
				}
			}
			CInput_Reset(Input);
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_START)]))
		{
			drawTexture(IMGBackground, 0, 0, 0);
			CWorldParts_Draw(WorldParts);
		
			strcpy(Msg,"Level Pack: ");
			strcat(Msg, LevelPackName);
			strcat(Msg,"\nLevel: ");

			itoa(SelectedLevel, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, "/");
			itoa(InstalledLevels, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg," - Moves: ");
			itoa(WorldParts->Moves, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg," - Pushes: ");
			itoa(WorldParts->Pushes, Nr, 10);
			strcat(Msg, Nr);
			if(LevelPackFile->Loaded)
			{
				strcat(Msg,"\nAuthor: ");
				
				if(strlen(LevelPackFile->LevelsMeta[SelectedLevel-1].author) > 0)
				{
					strcat(Msg, LevelPackFile->LevelsMeta[SelectedLevel-1].author);	
				}
				else
				{
					strcat(Msg, LevelPackFile->author);
				}
				strcat(Msg,"\nComments: ");
				strcat(Msg, LevelPackFile->LevelsMeta[SelectedLevel-1].comments);
			}
			PrintForm(Msg);
			sleep(15);
			CInput_Delay(Input);
			CInput_Reset(Input);
		}


		if (!Player->IsMoving)
		{
			if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_A)]))
			{
				CWorldParts_HistoryGoBack(WorldParts);
			}

			if ( CInput_Ready(Input) && !(Input->JoystickHeld[0][(BUT_A)]) &&
				(Input->JoystickHeld[0][(BUT_RIGHT)]))
			{
				if (CWorldPart_CanMoveTo(Player, Player->PlayFieldX + 1, Player->PlayFieldY))
				{
					CWorldParts_HistoryAdd(WorldParts);
				}
				CWorldPart_MoveTo(Player, Player->PlayFieldX + 1, Player->PlayFieldY,false);
			}
			else
			{
				if ( CInput_Ready(Input) &&  !(Input->JoystickHeld[0][(BUT_A)]) && 
					(Input->JoystickHeld[0][(BUT_LEFT)]))
				{
					if (CWorldPart_CanMoveTo(Player, Player->PlayFieldX - 1, Player->PlayFieldY))
					{
						CWorldParts_HistoryAdd(WorldParts);
					}
					CWorldPart_MoveTo(Player, Player->PlayFieldX - 1, Player->PlayFieldY,false);
				}
				else
				{
					if ( CInput_Ready(Input) && !(Input->JoystickHeld[0][(BUT_A)]) &&
						(Input->JoystickHeld[0][(BUT_UP)]))
					{
						if (CWorldPart_CanMoveTo(Player, Player->PlayFieldX , Player->PlayFieldY-1))
						{
							CWorldParts_HistoryAdd(WorldParts);
						}
						CWorldPart_MoveTo(Player, Player->PlayFieldX, Player->PlayFieldY - 1,false);
					}
					else
					{
						if ( CInput_Ready(Input) && !(Input->JoystickHeld[0][(BUT_A)]) &&
							(Input->JoystickHeld[0][(BUT_DOWN)]))
						{
							if (CWorldPart_CanMoveTo(Player, Player->PlayFieldX , Player->PlayFieldY+1))
							{
								CWorldParts_HistoryAdd(WorldParts);
							}
							CWorldPart_MoveTo(Player, Player->PlayFieldX, Player->PlayFieldY +1,false);
						}
					}
				}
			}
		}
		drawTexture(IMGBackground,0,0,0);
		CWorldParts_Move(WorldParts);
		CWorldParts_Draw(WorldParts);
		
		if (!Player->IsMoving && (WorldParts->Moves >0) && StageDone())
		{
			sleep(15);
			CAudio_PlaySound(Sounds[SND_STAGEEND],0);
			strcpy(Msg,"Congratulations !\nYou Succesfully Solved Level ");
			itoa(SelectedLevel, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, "/");
			itoa(InstalledLevels, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg," in\n");
			itoa(WorldParts->Moves, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg," moves and ");
			itoa(WorldParts->Pushes, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg," pushes\n");
			if (SelectedLevel == UnlockedLevels)
			{
				if ( UnlockedLevels < InstalledLevels)
				{
					strcat(Msg,"The next level has now been unlocked!\n\nPress (A) to continue");
					PrintForm(Msg);
					UnlockedLevels++;
					SelectedLevel++;
					SaveUnlockData();
					GameState = GSStageSelect;
					CAudio_StopMusic();
					CInput_Reset(Input);
				}
				else
				{
					strcat(Msg, "levelpack ");
					strcat(Msg, LevelPackName);
					strcat(Msg,"\nis now finished, try out another one!\nPress (A) to continue");
					PrintForm(Msg);
					GameState = GSTitleScreen;
					CAudio_StopMusic();
					CInput_Reset(Input);
				}
			}
			else
			{
				strcat(Msg,"\n\nPress (A) to continue");
				PrintForm(Msg);
				GameState = GSStageSelect;
				CAudio_StopMusic();
				CInput_Reset(Input);

			}
		}
#ifdef DEBUG
		StopDebugSpeed(3);
		int[500] Debug;
		int[100] Nr;
		itoa(MemoryUsed(), Nr, 10);
		strcpy(Debug, "RAM: ");
		strcat(Debug, Nr);
		itoa(WorldParts->ItemCount, Nr, 10);
		strcat(Debug, "\nITEMS: ");
		strcat(Debug, Nr);
		set_multiply_color(make_color_rgb(255,0,255));
		print_at(0,10,Debug);
		printDebugSpeed(1, 0,60,"LVL LOAD", 1.0);
		printDebugSpeed(3, 0,80,"FRAME G", 1.0);
        set_multiply_color(color_white);
#endif
		end_frame();
	}
	CInput_Destroy(Input);
	// if (GlobalSoundEnabled)
	// 	Mix_HaltMusic();
	SelectedMusic++;
	if (SelectedMusic >= MusicCount)
		SelectedMusic = 1;
}


#endif