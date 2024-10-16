#ifndef GAME_H
#define GAME_H

#include "time.h"
#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"
#include "CWorldParts.h"

bool StageDone()
{
	for (int Teller=0;Teller<WorldParts->ItemCount;Teller++)
		if (WorldParts->Items[Teller]->Type == IDDiamond)
		{
			return false;
		}
    return true;
}

void Game()
{
	bool ExplosionsFound =false;
	int[500] Text;
	int teller;
	int Time=0;
	CWorldPart *Player=NULL;
	bool ResetViewPort=false;
	for (teller=0;teller<WorldParts->ItemCount;teller++)
	{
		if (WorldParts->Items[teller]->Type == IDPlayer)
		{
			Player = WorldParts->Items[teller];
			break;
		}
	}
	//should never happen
	if(!Player)
	{
		Player = CWorldPart_Create(0,0,IDPlayer);
		CWorldParts_Add(WorldParts, Player);
	}
	CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		sleep(1);
	Time = get_frame_counter();
    CWorldParts_LimitVPLevel(WorldParts);
    while (GameState == GSGame)
    {
        CInput_Update(Input);
        
        if(Input->JoystickHeld[BUT_B])
        {
			if (AskQuestion("Are you sure you want to return to the stage selector?\n\nPress (A) to confirm (X) to Cancel"))
			{
	        	GameState = GSStageSelect;
				CAudio_PlaySound(Sounds[SND_BACK],0);
			}
			CInput_Delay(Input);
			CInput_Reset(Input);
        }

        //BUT_START
        if(CInput_Ready(Input) && (Input->JoystickHeld[BUT_X]))
        {
			if (AskQuestion("Are you sure you want to reload the level?\n\nPress (A) to confirm (X) to Cancel"))
			{
				CWorldParts_Load(WorldParts, SelectedLevel-1);
				//need to find player again
				for (teller=0;teller<WorldParts->ItemCount;teller++)
				{
					if (WorldParts->Items[teller]->Type == IDPlayer)
					{
						Player = WorldParts->Items[teller];
						break;
					}
				}
			}
			CInput_Reset(Input);
			CInput_Delay(Input);
        }
 
        //BUT_LEFT
        if (CInput_Ready(Input) && (Input->JoystickHeld[BUT_LEFT]))
        {
            CInput_Delay(Input);
        }
        //BUT_RIGHT
        if (CInput_Ready(Input) && (Input->JoystickHeld[BUT_RIGHT]))
        {

            CInput_Delay(Input);
        }
		//BUT_DOWN
        if (CInput_Ready(Input) && Input->JoystickHeld[BUT_DOWN])
        {
            CInput_Delay(Input);
        }

        //BUT_UP
        if (CInput_Ready(Input) && Input->JoystickHeld[BUT_UP])
        {
            CInput_Delay(Input);
        }

        if(Time+1<get_frame_counter())
        {
			//BUT_Y
            if (Input->JoystickHeld[BUT_Y])
            {
				//BUT_LEFT
                if(Input->JoystickHeld[BUT_LEFT])
                    CViewPort_Move(WorldParts->ViewPort, -4,0);
				//BUT_RIGHT
                if(Input->JoystickHeld[BUT_RIGHT])
                    CViewPort_Move(WorldParts->ViewPort, 4,0);
				//BUT_UP
                if(Input->JoystickHeld[BUT_UP])
                    CViewPort_Move(WorldParts->ViewPort, 0,-4);
				//BUT_DOWN
                if( (Input->JoystickHeld[BUT_DOWN]))
                    CViewPort_Move(WorldParts->ViewPort, 0,4);
                ResetViewPort = true;
            }
            else
            {
                if (ResetViewPort)
                {
					CWorldParts_LimitVPLevel(WorldParts);
                    CWorldParts_CenterVPOnPlayer(WorldParts);
                    ResetViewPort = false;
                }
            }
            //BUT_Y
            if (!Player->IsMoving && !Player->IsDeath && !(Input->JoystickHeld[BUT_Y]))
            {
				//BUT_DOWN
                //move down
                if (Input->JoystickHeld[BUT_DOWN])
                {
                    CWorldPart_MoveTo(Player, Player->PlayFieldX,Player->PlayFieldY+1,false);
                }
				//BUT_UP
                //move up
                if (Input->JoystickHeld[BUT_UP])
                {
                        CWorldPart_MoveTo(Player, Player->PlayFieldX,Player->PlayFieldY-1,false);
                }
				//BUT_LEFT
                //move left
                if (Input->JoystickHeld[BUT_LEFT])
                {
                        CWorldPart_MoveTo(Player, Player->PlayFieldX-1,Player->PlayFieldY,false);
                }
				//BUT_RIGHT
                //move right
                if (Input->JoystickHeld[BUT_RIGHT])
                {
                        CWorldPart_MoveTo(Player, Player->PlayFieldX+1,Player->PlayFieldY,false);
                }

            }
            Time = get_frame_counter();

        }

        drawTexture(IMGBackground,0,0,0);
        CWorldParts_Draw(WorldParts);
        CWorldParts_Move(WorldParts);

		end_frame();
        if (Player->IsDeath)
        {
            ExplosionsFound =false;
            for(teller=0;teller<WorldParts->ItemCount;teller++)
            {
                if(WorldParts->Items[teller]->Type == IDExplosion)
                {
                    ExplosionsFound = true;
					break;
                }
            }

            if(!ExplosionsFound)
			{
				if (AskQuestion("Too bad you died !\nDo you want to try again?\n\n(A) Try Again (X) Level Selector"))
				{
					CWorldParts_Load(WorldParts, SelectedLevel-1);
					for (teller=0;teller<WorldParts->ItemCount;teller++)
					{
						if (WorldParts->Items[teller]->Type == IDPlayer)
						{
							Player = WorldParts->Items[teller];
							break;
						}
					}
					
					//should never happen
					if(!Player)
					{
						Player = CWorldPart_Create(0,0,IDPlayer);
						CWorldParts_Add(WorldParts, Player);
					}
					CInput_Reset(Input);
				}
				else
					GameState = GSStageSelect;

			}
        }

        if (StageDone())
		{
			sleep(15);
			CAudio_PlaySound(Sounds[SND_STAGEEND],0);
			if (SelectedLevel == UnlockedLevels)
			{
				if ( UnlockedLevels < InstalledLevels)
				{
					strcpy(Text,"Congratulations !\nYou Succesfully Solved Level ");
					int[10] tmpText;
					itoa(SelectedLevel, tmpText, 10);
					strcat(Text, tmpText);
					strcat(Text,"/");
					itoa(InstalledLevels, tmpText, 10);
					strcat(Text, tmpText);
					strcat(Text, "\nThe next level has now been unlocked!\n\nPress (A) to continue");
					PrintForm(Text);
					UnlockedLevels++;
					SelectedLevel++;
					SaveUnlockData();
					GameState = GSStageSelect;
				}
				else
				{
					strcpy(Text,"Congratulations !\nYou Succesfully Solved Level ");
					int[10] tmpText;
					itoa(SelectedLevel, tmpText, 10);
					strcat(Text, tmpText);
					strcat(Text,"/");
					itoa(InstalledLevels, tmpText, 10);
					strcat(Text, tmpText);
					strcat(Text, "\nlevelpack ");
					strcat(Text, LevelPackName);
					strcat(Text,"\nis now finished, try out another one!\n\nPress (A) to continue");
					PrintForm(Text);
					GameState = GSTitleScreen;
				}
			}
			else
			{
				strcpy(Text,"Congratulations !\nYou Succesfully Solved Level ");
				int[10] tmpText;
				itoa(SelectedLevel, tmpText, 10);
				strcat(Text, tmpText);
				strcat(Text,"/");
				itoa(InstalledLevels, tmpText, 10);
				strcat(Text, tmpText);
				strcat(Text, "\n\nPress (A) to continue");
				PrintForm(Text);

				GameState = GSStageSelect;
			}
		}
    }
    CInput_Destroy(Input);
}


#endif