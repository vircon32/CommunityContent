#include "string.h"
#include "video.h"
#include "time.h"
#include "misc.h"
#include "string.h"
#include "commonvars.h"
#include "sound.h"
#include "input.h"
#include "cmainmenu.h"
#include "cboardparts.h"
#include "texture.h"
#include "cselector.h"

CMainMenu* Menu;
CBoardParts* BoardParts; // boardparts instance that will hold all the boardparts
CSelector *GameSelector;

void LoadGraphics()
{
	IMGCredits = newTexture(1,1, 640, 360);
	IMGPeg = newTexture(7, 7, 252, 36);
	IMGBackground = newTexture(0,1, 640, 360);
	IMGVeryEasyInfo = newTexture(2,1, 640, 360);
	IMGEasyInfo = newTexture(3, 1, 640, 360);
	IMGHardInfo = newTexture(4, 1, 640, 360);
	IMGVeryHardInfo = newTexture(5, 1,640, 360);	
}

// Load the settings
void LoadSettings()
{
	BestPegsLeft[VeryEasy] = 0;
	BestPegsLeft[Easy] = 0;
	BestPegsLeft[Hard] = 0;
	BestPegsLeft[VeryHard] = 0;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&BestPegsLeft, sizeof(game_signature), sizeof(BestPegsLeft));
		}
}

// Save the settings
void SaveSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature( &GameSignature );
    		card_write_data(&BestPegsLeft, sizeof(game_signature), sizeof(BestPegsLeft));
		}
}


void resetGlobals()
{
	PrintFormShown = false;
	Difficulty = VeryEasy;
	Moves = 0;
	GameState = GSTitleScreenInit;
}

void setupGame()
{
	resetGlobals();
	initSound();
	initMusic();
	setMusicOn(true);
	setSoundOn(true);
	LoadGraphics();
	LoadSettings();
	BoardParts = CBoardParts_Create();
	Menu = CMainMenu_Create();
	GameSelector = CSelector_Create(4,4);
}

// procedure that calculates how many moves are possible in the current board state
// we can simply do this by checking all parts and see if they can move to all directions
// the canmoveto method in CPegs is does all the checking
// as well as at the same time check how many pegs are left 
// initialy these were 2 seperate functions but then it had to loop 2 times of the boardparts
// so i merged them
void UpdateGameStats()
{
    CPeg *BoardPart;
    int TmpMoves=0, TmpPegs = 0, Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = CBoardParts_GetPart(BoardParts, X,Y);
            // if there is a boardpart on that X,Y Coordinate
            // check all direction if we can move to that if so increases the movesleft
            if (BoardPart)
            {
				if ((BoardPart->Type == IDPeg) && (BoardPart->AnimPhase < 2))
                    TmpPegs++;

                if (CPeg_CanMoveTo(BoardPart,X+2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y-2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X+2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y+2,false))
                    TmpMoves++;
                if (CPeg_CanMoveTo(BoardPart,X-2,Y-2,false))
                    TmpMoves++;
            }
        }
    iMovesLeft = TmpMoves;
	iPegsLeft = TmpPegs;
}

void PrintForm(int *msg)
{
	PrintFormShown = true;
	int color1 = make_color_rgb(111,130,255);
	int color2 = make_color_rgb(45,64,207);
	int msgX = 102;
	int msgY = (screen_height - 105) >> 1;
	set_multiply_color(color1);
	draw_filled_rectangle(msgX,msgY,msgX+310,msgY + 105);
	set_multiply_color(color2);
	draw_rectangle(msgX,msgY,msgX+310,msgY + 105);
	draw_rectangle(msgX+2,msgY+2,msgX+2+310-4,msgY + 2 + 105-4);
	set_multiply_color(color_white);
	print_at(msgX + 5,msgY + 5, msg);
}

// Checks if we won the game
int IsWinningGame()
{
    if (iPegsLeft == 1) //must be 1 peg left
    {
        if ((Difficulty == VeryHard) || (Difficulty == Easy))
        {
            if(CBoardParts_GetPart(BoardParts,4,4)->AnimPhase < 2) // must be in the middle with veryhard or easy
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

void GameInit()
{
	CSelector_SetPosition(GameSelector, 4, 4);
	CBoardParts_InitBoard(BoardParts);
    Moves = 0;
	UpdateGameStats();
	playStartSound();
	PrintFormShown = false;
}

// The main Game Loop
void Game()
{
	if (GameState == GSGameInit)
	{
		GameInit();
		GameState -= GSInitDiff;
	}
	drawTexture(IMGBackground, 0, 0, 0);
 	int[50] Msg;
    int[20] NumberString;
	int MsgX = 444;
	int MsgY = 84;
	int MsgYSpacing = 40;
	// Write some info to the screen
	strcpy(Msg, "Moves Left:");
	itoa(iMovesLeft, NumberString, 10 );
    strcat(Msg, NumberString);
	print_at(MsgX,MsgY, Msg);

	strcpy(Msg, "Moves:");
	itoa(Moves, NumberString, 10 );
    strcat(Msg, NumberString);
	print_at(MsgX,MsgY + MsgYSpacing, Msg);

	strcpy(Msg, "Pegs Left:");
	itoa(iPegsLeft, NumberString, 10 );
    strcat(Msg, NumberString);
	print_at(MsgX,MsgY + 2*MsgYSpacing, Msg);

	// Only show best pegs if it isn't 0
	if (BestPegsLeft[Difficulty] != 0)
	{
		strcpy(Msg, "Best Pegs Left:");
		itoa(BestPegsLeft[Difficulty], NumberString, 10 );
		strcat(Msg, NumberString);
		print_at(MsgX,MsgY + 3*MsgYSpacing, Msg);
		
	}

	CBoardParts_Draw(BoardParts);
	CSelector_Draw(GameSelector);

	//need to repeat showing it until it's no longer shown
	if ( PrintFormShown)
	{
		// if it's the winning game play the winning sound and show the form with the winning message
		if (IsWinningGame())
		{
			PrintForm("Congrats you have solved the\npuzzle! Try a new difficulty!\n\nPress (A) to continue");
		}
		else // show the loser messager, play loser sound
		{
			PrintForm("You couldn't solve the puzzle!\nDon't give up, try it again!\n\nPress (A) to continue");
		}
	}

	if (gamepad_left() == 1)
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, GameSelector->CurrentPoint.X - 1, GameSelector->CurrentPoint.Y);

	if (gamepad_right() == 1)
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, GameSelector->CurrentPoint.X + 1, GameSelector->CurrentPoint.Y);

	if (gamepad_up() == 1)
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y - 1);

	if (gamepad_down() == 1)
		if (!PrintFormShown)
			CSelector_SetPosition(GameSelector, GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y + 1);

	if (gamepad_button_b() == 1)
		if(!PrintFormShown)
		{
			playSelectSound();
			GameState = GSTitleScreenInit;
			PrintFormShown = false;
		}

	if (gamepad_button_x() == 1)
		if (!PrintFormShown && GameSelector->HasSelection)
		{
			CBoardParts_GetPart(BoardParts, GameSelector->SelectedPoint.X, GameSelector->SelectedPoint.Y)->AnimPhase = 0;
			CSelector_DeSelect(GameSelector);
		}

	if (gamepad_button_a() == 1)
	{
		if (PrintFormShown)
	 	{
			playSelectSound();
	 		GameState = GSTitleScreenInit;
	 		PrintFormShown = false;
		}
		else
	 	{
	 		if (GameSelector->HasSelection) // if we have a selection
	 		{
	 			// see if the selected boardpart can move to the current position
	 			if (CPeg_CanMoveTo(CBoardParts_GetPart(BoardParts, GameSelector->SelectedPoint.X, GameSelector->SelectedPoint.Y), GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y, true))
				{
					playGoodSound();
	 				//if so play a sound, increase the moves, set the selected part to empty and the current part to red
	 				Moves++;
					CBoardParts_GetPart(BoardParts, GameSelector->SelectedPoint.X, GameSelector->SelectedPoint.Y)->AnimPhase =  6;
					CBoardParts_GetPart(BoardParts, GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y)->AnimPhase = 0;
					// if no moves are left see if the best pegs left value for the current difficulty is
					// greater if so set te new value
					UpdateGameStats();
					if (iMovesLeft == 0)
					{
						if (BestPegsLeft[Difficulty] != 0)
						{
							if (iPegsLeft < BestPegsLeft[Difficulty])
								BestPegsLeft[Difficulty] = iPegsLeft;
						}
						else
							BestPegsLeft[Difficulty] = iPegsLeft;
						SaveSettings();
						// if it's the winning game play the winning sound and show the form with the winning message
						if (IsWinningGame())
						{
							playWinnerSound();
							PrintFormShown = true;
						}
						else // show the loser messager, play loser sound
						{
	 						playLoserSound();
							PrintFormShown = true;
						}
					}

	 			}
	 			else // if we can't move to the spot, play the wrong move sound, and reset the selection to a red peg (instead of blue / selected)
	 			{
	 				CBoardParts_GetPart(BoardParts, GameSelector->SelectedPoint.X, GameSelector->SelectedPoint.Y)->AnimPhase = 0;
	 				playWrongSound();
	 			}
	 			CSelector_DeSelect(GameSelector); // deselect the selection
	 		}
	 		else // we didn't have a selection, set the new selection
	 		{
	 			if (CBoardParts_GetPart(BoardParts, GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y)->AnimPhase == 0)
	 			{
	 				playSelectSound();
	 				CBoardParts_GetPart(BoardParts, GameSelector->CurrentPoint.X, GameSelector->CurrentPoint.Y)->AnimPhase = 1;
	 				CSelector_Select(GameSelector);
	 			}
	 		}
	 	}
	}
}

void TitleScreenInit()
{
	SelectMusic(musTitle);
}

// main title screen loop
void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
	 	TitleScreenInit();
	 	GameState -= GSInitDiff;
	}
	if (gamepad_down() == 1)
		CMainMenu_NextItem(Menu);
	if (gamepad_up() == 1)
	 	CMainMenu_PreviousItem(Menu);
	if (gamepad_button_a() == 1)
	{
	 	playSelectSound();
	 	switch (CMainMenu_GetSelection(Menu))
	 	{
	 		case 1:
	 			GameState = GSDifficultySelectInit;
	 			break;
	 		case 2:
	 			GameState = GSCreditsInit;
	 			break;
	 	}
	 }
	CMainMenu_Draw(Menu);
}

void DifficultySelectInit()
{

}

// Main difficulty select loop
void DifficultySelect()
{
	if(GameState == GSDifficultySelectInit)
	{
		DifficultySelectInit();
		GameState -= GSInitDiff;
	}

	if ((gamepad_button_a() == 1) ||
		(gamepad_button_start() == 1))
	{
		playSelectSound();
	 	GameState = GSGameInit;
	}
	
	if (gamepad_button_b() == 1)
	{
		playSelectSound();
	 	GameState = GSTitleScreenInit;
	}
	
	if (gamepad_left() == 1)
	{
		playSelectSound();
		if (Difficulty == VeryHard)
	 	{
	 		Difficulty = Hard;
	 	}
	 	else
	 		if (Difficulty == Hard)
	 		{
				Difficulty = Easy;
			}
			else
				if (Difficulty == Easy)
				{
					Difficulty = VeryEasy;
				}
				else
					if (Difficulty == VeryEasy)
						Difficulty = VeryHard;
	}
	
	if (gamepad_right() == 1)
	{
		playSelectSound();
		if (Difficulty == VeryEasy)
		{
			Difficulty = Easy;
		}
		else
			if (Difficulty == Easy)
			{
				Difficulty = Hard;
			}
			else
				if (Difficulty == Hard)
				{
					Difficulty = VeryHard;
				}
				else
					if (Difficulty == VeryHard)
						Difficulty = VeryEasy;
	}
	
	switch(Difficulty)
	{
		case VeryEasy:
	 		drawTexture(IMGVeryEasyInfo, 0, 0, 0);
	 		break;
		case Easy:
			drawTexture(IMGEasyInfo, 0, 0, 0);
	 		break;
		case Hard:
			drawTexture(IMGHardInfo, 0, 0, 0);
	 		break;
		case VeryHard:
			drawTexture(IMGVeryHardInfo, 0, 0, 0);
			break;
	}
}

void CreditsInit()
{

}

//Main Credits loop, will just show an image and wait for a button to be pressed
void Credits()
{
	if (GameState == GSCreditsInit)
	{
		CreditsInit();
		GameState -= GSInitDiff;
	}
	if ((gamepad_button_a() == 1) || 
	 	(gamepad_button_b() == 1) ||
		(gamepad_button_start() == 1))
		{
			playSelectSound();
	 		GameState = GSTitleScreenInit;
		}
	drawTexture(IMGCredits, 0, 0, 0);
}

void main()
{  
	memset( &GameSignature, 0, sizeof(game_signature));
    strcpy( GameSignature, "RUBIDO");
	setupGame();
	while (true)
	{
		switch(GameState)
		{
			case GSGameInit:
			case GSGame :
				Game();
				break;
			case GSTitleScreenInit:
			case GSTitleScreen:
				TitleScreen();
				break;
			case GSDifficultySelectInit:
			case GSDifficultySelect:
				DifficultySelect();
				break;
			case GSCreditsInit:
			case GSCredits:
				Credits();
				break;
			default:
				break;
		}
		end_frame();
	}
}
