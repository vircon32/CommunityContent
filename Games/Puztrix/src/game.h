#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "string.h"
#include "main.h"
#include "game.h"
#include "gamefuncs.h"


void GameInit()
{
	Movement = MNone;
    MaxMoves = WorldParts->LevelMoves;
}

void Game_Logic()
{
	if (GameState == GSGameInit)
	{
		GameInit();
		GameState = GSGame;
	}

    if (GameState == GSGame)
    {

        //Moet in deze volgorde !!!!

        //1) als we niet moven en er zijn geen deathblocks blijf moven in de richting die we gingen
        if(!CWorldParts_IsMoving(WorldParts))
        {
            for (int X=0;X<NrOfCols;X++)
                for (int Y=0;Y<NrOfRows;Y++)
                    if(EraseBlocks(WorldParts,X,Y) > 1)
                        CAudio_PlaySound(Sounds[SND_Destroy],0);

            if(!DeathBlocks(WorldParts))
            switch (Movement)
            {
                case MLeft:
                    CWorldParts_MoveLeft(WorldParts);
                    break;
                case MRight:
                    CWorldParts_MoveRight(WorldParts);
                    break;
                case MUp:
                    CWorldParts_MoveUp(WorldParts);
                    break;
                case MDown:
                    CWorldParts_MoveDown(WorldParts);
                    break;
                default:
                    break;
            }
        }

        //2) Zet de richting die we willen moven en start moving zo dat ismoving true teruggeeft
        KeyPressed = false;
		if(gamepad_button_b() > 0)
		{
			GameState = GSTitleScreenInit;			
		}

		if(gamepad_button_a() > 0 )
		{
			if((Movement != MNone))
			{
				CAudio_PlaySound(Sounds[SND_NoMoves],0);
				Movement = MNone;
				Retries--;
				if(Retries == -1)
				{
					GameState = GSGameOverInit;
					Retries = 0;					
				}
				else
				{
					CWorldParts_SetLevel(WorldParts, WorldParts->LevelNumber);
					MaxMoves = WorldParts->LevelMoves;
				}
			}
		}

		if(!KeyPressed && (gamepad_left() > 0))
		{
			if(MaxMoves > 0)
				if(!DeathBlocks(WorldParts))
					if(!CWorldParts_IsMoving(WorldParts))
						if(CWorldParts_CanMoveToLeft(WorldParts))
						{
							CWorldParts_MoveLeft(WorldParts);
							Movement = MLeft;
							MaxMoves--;
							KeyPressed = true;
							CAudio_PlaySound(Sounds[SND_DirectionMove],0);
						}
		}

		if(!KeyPressed && (gamepad_right() > 0))
		{
			if(MaxMoves > 0)
				if(!DeathBlocks(WorldParts))
					if(!CWorldParts_IsMoving(WorldParts))
						if(CWorldParts_CanMoveToRight(WorldParts))
						{
							CWorldParts_MoveRight(WorldParts);
							Movement = MRight;
							MaxMoves--;
							KeyPressed = true;
							CAudio_PlaySound(Sounds[SND_DirectionMove],0);
						}
		}

        if(!KeyPressed && (gamepad_up() > 0))
		{
            if(MaxMoves > 0)
                if(!DeathBlocks(WorldParts))
                    if(!CWorldParts_IsMoving(WorldParts))
                        if(CWorldParts_CanMoveToUp(WorldParts))
                        {
                            CWorldParts_MoveUp(WorldParts);
                            Movement = MUp;
                            MaxMoves--;
                            KeyPressed = true;
                            CAudio_PlaySound(Sounds[SND_DirectionMove],0);
                        }
		}

		if(!KeyPressed && (gamepad_down() > 0))
		{
            if(MaxMoves > 0)
                if(!DeathBlocks(WorldParts))
                    if(!CWorldParts_IsMoving(WorldParts))
                        if(CWorldParts_CanMoveToDown(WorldParts))
                        {
                            CWorldParts_MoveDown(WorldParts);
                            Movement = MDown;
                            MaxMoves--;
                            KeyPressed = true;
                            CAudio_PlaySound(Sounds[SND_DirectionMove],0);
                        }
        }
        
        if(LevelWon(WorldParts))
        {
            GameState = GSStageClearInit;
        }

        //3) anders wordt dit true als we bij 2 ni starten met moven en stopt het direct wanneer er geen moves meer over zijn
        if((MaxMoves == 0) && !CWorldParts_IsMoving(WorldParts) && !DeathBlocks(WorldParts) && (GameState != GSStageClearInit))
        {
            CAudio_PlaySound(Sounds[SND_NoMoves],0);
            Movement = MNone;
            Retries--;
            if(Retries == -1)
            {
                GameState = GSGameOverInit;
                Retries = 0;
            }
            else
            {
                CWorldParts_SetLevel(WorldParts, WorldParts->LevelNumber);
                MaxMoves = WorldParts->LevelMoves;
            }
        }

        if(NoMovesLeft(WorldParts))
        {
            CAudio_PlaySound(Sounds[SND_NoMoves],0);
            Movement = MNone;
            Retries--;
            if(Retries == -1)
            {
                GameState = GSGameOverInit;
                Retries = 0;                
            }
            else
            {
                CWorldParts_SetLevel(WorldParts, WorldParts->LevelNumber);
                MaxMoves = WorldParts->LevelMoves;
            }
        }

        CWorldParts_Move(WorldParts);
    }
}

void Game_Draw()
{
	drawTextureZoomed(IMGBackground, 0, 0, 0);
	int[100] Text;
	int[10] Nr;
	strcpy(Text,"Score: ");
	itoa(Score, Nr, 10);
	strcat(Text, Nr);
	strcat(Text,"\nLevel Number: ");
	itoa(WorldParts->LevelNumber, Nr, 10);
	strcat(Text, Nr);
	strcat(Text,"\nMoves Left: ");
	itoa(MaxMoves, Nr , 10);
	strcat(Text, Nr);
	strcat(Text,"\nRetry: ");
	itoa(Retries, Nr, 10);
	strcat(Text, Nr);
	drawTextColor(font, Text, 21*xscale, 50*yscale, ColorSelection);
	DrawFloor(WorldParts, NULL);
	CWorldParts_Draw(WorldParts);
	DrawArrows();
	RemoveBlocks(WorldParts);
}


#endif