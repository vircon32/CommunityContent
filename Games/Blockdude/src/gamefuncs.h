#ifndef game_h
#define game_h

#include "input.h"
#include "texture.h"
#include "cworldparts.h"
#include "levels.h"
#include "string.h"
#include "savestate.h"
#include "fonts/Roboto_Bold_12.h"
#include "fonts/Roboto_Bold_18.h"
#include "fonts/Roboto_Bold_32.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "libs/TextFonts/textfont.h"

void UnLoadGraphics()
{
	if (IMGBackground)
	{
		freeTexture(IMGBackground);
		IMGBackground = NULL;
	}

	if (IMGExit)
	{
		freeTexture(IMGExit);
		IMGExit = NULL;
	}

	if (IMGFloor)
	{
		freeTexture(IMGFloor);
		IMGFloor = NULL;
	}

	if (IMGPlayer)
	{
		freeTexture(IMGPlayer);
		IMGPlayer = NULL;
	}

	if (IMGBox)
	{
		freeTexture(IMGBox);
		IMGBox = NULL;
	}

	if (IMGEmpty)
	{
		freeTexture(IMGEmpty);
		IMGEmpty = NULL;
	}

	if (IMGFloorLeft)
	{
		freeTexture(IMGFloorLeft);
		IMGFloorLeft = NULL;
	}

	if (IMGFloorRight)
	{
		freeTexture(IMGFloorRight);
		IMGFloorRight = NULL;
	}

	if (IMGEarthGrassRight)
	{
		freeTexture(IMGEarthGrassRight);
		IMGEarthGrassRight = NULL;
	}

	if (IMGEarthGrassLeft)
	{
		freeTexture(IMGEarthGrassLeft);
		IMGEarthGrassLeft = NULL;
	}

	if (IMGEarthLeft)
	{
		freeTexture(IMGEarthLeft);
		IMGEarthLeft = NULL;
	}

	if (IMGEarthRight)
	{
		freeTexture(IMGEarthRight);
		IMGEarthRight = NULL;
	}

	if (IMGEarthMiddle)
	{
		freeTexture(IMGEarthMiddle);
		IMGEarthMiddle = NULL;
	}

	if (IMGFloatingFloor)
	{
		freeTexture(IMGFloatingFloor);
		IMGFloatingFloor = NULL;
	}

	if (IMGFloatingFloorLeft)
	{
		freeTexture(IMGFloatingFloorLeft);
		IMGFloatingFloorLeft = NULL;
	}

	if (IMGFloatingFloorRight)
	{
		freeTexture(IMGFloatingFloorRight);
		IMGFloatingFloorRight = NULL;
	}

	if (IMGFloatingFloorMiddle)
	{
		freeTexture(IMGFloatingFloorMiddle);
		IMGFloatingFloorMiddle = NULL;
	}

	if (IMGTower)
	{
		freeTexture(IMGTower);
		IMGTower = NULL;
	}

	if (IMGStartTower)
	{
		freeTexture(IMGStartTower);
		IMGStartTower = NULL;
	}

	if (IMGTowerShaft)
	{
		freeTexture(IMGTowerShaft);
		IMGTowerShaft = NULL;
	}

	if (IMGRoof1)
	{
		freeTexture(IMGRoof1);
		IMGRoof1 = NULL;
	}

	if (IMGRoof2)
	{
		freeTexture(IMGRoof2);
		IMGRoof2 = NULL;
	}

	if (IMGRoofCornerLeft)
	{
		freeTexture(IMGRoofCornerLeft);
		IMGRoofCornerLeft = NULL;
	}

	if (IMGRoofCornerRight)
	{
		freeTexture(IMGRoofCornerRight);
		IMGRoofCornerRight = NULL;
	}

	if (IMGRoofDownRight)
	{
		freeTexture(IMGRoofDownRight);
		IMGRoofDownRight = NULL;
	}

	if (IMGRoofDownLeft)
	{
		freeTexture(IMGRoofDownLeft);
		IMGRoofDownLeft = NULL;
	}

	if (IMGRoofCornerBoth)
	{
		freeTexture(IMGRoofCornerBoth);
		IMGRoofCornerBoth = NULL;
	}

	if (IMGTitleScreen)
	{
		freeTexture(IMGTitleScreen);
		IMGTitleScreen = NULL;
	}

	if (IMGIntroBackground)
	{
		freeTexture(IMGTitleScreen);
		IMGTitleScreen = NULL;
	}

	if (IMGIntroSoleau)
	{
		freeTexture(IMGTitleScreen);
		IMGTitleScreen = NULL;
	}
}

void LoadGraphics(void)
{
	UnLoadGraphics();
		
	//there are 5 skins and the are placed right after each other in correct order
	//so we can just offset the values to load another skin in this order
	//we also change colors used in text and boxes
	//"Default", "Tech", "Flat", "Ti-83", "Kenney"
	switch(skinSaveState())
	{
		case 0: // Default
			//Color1 = make_color_rgba(86,27,0,255);
			Color1 = make_color_rgba(107,128,128,255);
			Color2 = make_color_rgba(255,255,255,255);
			TitleTextColor = make_color_rgba(107,128,128,255);
			break;
		case 1: // Tech
			Color1 = make_color_rgba(6,6,72,255);
			Color2 = make_color_rgba(255,255,255,255);
			TitleTextColor = make_color_rgba(255,255,255,255);
			break;
		case 2: // Flat
			//Color1 = make_color_rgba(128,64,0,255);
			Color1 = make_color_rgba(107,128,128,255);
			Color2 = make_color_rgba(255,255,255,255);
			TitleTextColor = make_color_rgba(107,128,128,255);
			break;
		case 3: // TI-83
			Color1 = make_color_rgba(204,224,207,255);
			Color2 = make_color_rgba(79,80,67,255);
			TitleTextColor = make_color_rgba(79,80,67,255);
			break;
		case 4: // Kenney
			Color1 = make_color_rgba(0,0,0,255);
			Color2 = make_color_rgba(255,255,255,255);
			TitleTextColor =  make_color_rgba(0,0,0,255);
			break;
	}
	
	int skin = skinSaveState();
	
	//Texture 'all.png' is placed in such in order that they match skin Nr
	//The texture region ID is unique and for single images matches with the postion in the image divided by 16
	//hence why region ID * TileWidthOriginal dictates the start x
	IMGBox = newTexture(skin, IDBox, 1, IDBox * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGExit = newTexture(skin, IDExit, 1, IDExit * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGEarthGrassLeft = newTexture(skin, IDEarthGrassLeft, 1, IDEarthGrassLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGEarthGrassRight = newTexture(skin, IDEarthGrassRight, 1, IDEarthGrassRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGEarthLeft = newTexture(skin, IDEarthLeft, 1 , IDEarthLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGEarthMiddle = newTexture(skin, IDEarthMiddle, 1, IDEarthMiddle * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 	
	IMGEarthRight = newTexture(skin, IDEarthRight, 1, IDEarthRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGFloatingFloor = newTexture(skin, IDFloatingFloor, 1, IDFloatingFloor * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGFloatingFloorLeft = newTexture(skin, IDFloatingFloorLeft, 1, IDFloatingFloorLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGFloatingFloorMiddle = newTexture(skin, IDFloatingFloorMiddle, 1, IDFloatingFloorMiddle * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 	
	IMGFloatingFloorRight = newTexture(skin, IDFloatingFloorRight, 1, IDFloatingFloorRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGFloor = newTexture(skin, IDFloor, 1, IDFloor * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
    IMGFloorLeft = newTexture(skin, IDFloorLeft, 1, IDFloorLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGFloorRight = newTexture(skin, IDFloorRight, 1, IDFloorRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGRoof1 = newTexture(skin, IDRoof1, 1, IDRoof1 * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoof2 = newTexture(skin, IDRoof2, 1, IDRoof2 * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoofCornerBoth = newTexture(skin, IDRoofCornerBoth, 1, IDRoofCornerBoth * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoofCornerLeft = newTexture(skin, IDRoofCornerLeft, 1, IDRoofCornerLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoofCornerRight = newTexture(skin, IDRoofCornerRight, 1, IDRoofCornerRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoofDownLeft = newTexture(skin, IDRoofDownLeft, 1, IDRoofDownLeft * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGRoofDownRight = newTexture(skin, IDRoofDownRight, 1, IDRoofDownRight * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel);
	IMGStartTower = newTexture(skin, IDStartTower, 1, IDStartTower * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGTower = newTexture(skin, IDTower, 1, IDTower * TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 
	IMGTowerShaft = newTexture(skin, IDTowerShaft, 1, IDTowerShaft* TileWidthOriginal, 0, TileWidthOriginal, TileHeightOriginal, zoomlevel, zoomlevel); 

	//the player is special as it has multiple frames so we need to put it at the end i did that also in the image
	//IDRoofDownLeft is last image in normal order with tilewidth sizes before the player
	//so for region id i just added both up and for calculating startx i added + 1
	IMGPlayer = newTexture(skin, IDRoofDownLeft + IDPlayer, 16,  (IDRoofDownLeft + 1 ) * TileWidthOriginal, 0, TileWidthOriginal*16, TileHeightOriginal, zoomlevel, zoomlevel); 
	
	//these are on the 2nd "line" of image and the ID's are just high numbers so they do not interfere with the previous images
	IMGBackground = newTexture(skin, IDBackground, 1, 0, 16, 356, 200, 640.0/356.0, 360.0/200.0);
	IMGTitleScreen = newTexture(skin, IDTitlescreen, 1, 356, 16, 356, 200, 640.0/356.0, 360.0/200.0); 

	//these are on a seperate texture
	IMGIntroBackground = newTexture(5, IDIntrobackground, 1, 0, 0, 356, 200, 640.0/356.0, 360.0/200.0);
	IMGIntroSoleau = newTexture(5, IDIntroSoleau, 1, 356, 0, 356, 200, 640.0/356.0, 360.0/200.0); 
	
}

void LoadFonts(void)
{
	setupFontRoboto_Bold_12();
	setupFontRoboto_Bold_18();
	setupFontRoboto_Bold_32();
}

void FindLevelPacks(void)
{
	FoundLevelPacks = MaxLevelPacks;
	LevelPacks[0] = "blockman";
	LevelPacks[1] = "davy";
}

bool AskQuestionUpdate(int* Id, bool* Answer, bool MustBeAButton)
{
	*Answer = false;
	*Id = AskingQuestionID;

	if ((!JustAsked) && (AskingQuestionID > -1))
	{
		if (gamepad_button_a() == 1)
		{
			*Answer = true;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
			playMenuSelectSound();
			return true;
		}

		if (!MustBeAButton && (gamepad_button_b() == 1))
		{
			*Answer = false;
			AskingQuestion = false;
			NeedRedraw = true;
			AskingQuestionID = -1;
			playMenuBackSound();
			return true;
		}
	}
	JustAsked = false;
	return false;
}

int HighestLineWidth(textfont *tf, int *Msg)
{
	int high = 0;
	int* startline = Msg;
	int* chars = Msg;
	int tmplinewidth = 0;
	high = textfont_get_line_width(tf, Msg);
	while(chars)
	{
		if((*chars == '\n') || (*chars == 0))
		{
			tmplinewidth = textfont_get_line_width(tf, startline );	
			if(tmplinewidth > high)
				high = tmplinewidth;		
			if(*chars == 0)
				break;
			startline = chars + 1;
		}
		chars++;
	}
	return high;
}

int countChars(int *Msg, int fchar)
{
	int* chars = Msg;
	int count = 0;
	while(true)
	{
		if(*chars == fchar)
			count++;

		if(*chars == 0)
			break;
		chars++;
	}
	return count;
}

void AskQuestion(int Id, int* Msg)
{
	JustAsked = true;
	int width = HighestLineWidth(&FontRoboto_Bold_18, Msg) + 14;
	int height = ((countChars(Msg, '\n') +1) * (FontRoboto_Bold_18.character_height + FontRoboto_Bold_18.line_separation)) + 14;
	int posx = (screen_width - width) >> 1;
	int posy = (screen_height - height) >> 1;

	set_multiply_color(Color1);
	draw_filled_rectangle(posx + 0, posy+ 0,posx + 0 + width, posy + 0 + height);
	set_multiply_color(Color2);
	draw_rectangle(posx + 0, posy + 0, posx + 0 + width,  posy + 0 + height);
	draw_rectangle(posx + 2, posy + 2, posx + 2 + width - 4, posy + 2 +height - 4);
	textfont_print_from_left(&FontRoboto_Bold_18,posx + 5, posy + 5, Msg);
	set_multiply_color(color_white);

	AskingQuestionID = Id;
	AskingQuestion = true;
}

void LoadSelectedLevel(CWorldParts* WorldParts)
{
	if ((SelectedLevel > 0) && (SelectedLevel <= MaxLevels[CurrentLevelPackIndex]))
	{
		CWorldParts_Load(WorldParts, Levels[CurrentLevelPackIndex][SelectedLevel-1]);
	}
}

bool LevelErrorsFound(CWorldParts* WorldParts, int* ErrorType)
{
	int NumPlayer = 0, NumExit = 0, NumBlocksNotFloor = 0, NumExitsNotFloor = 0, NumPlayerNotFloor = 0, NumBlocksOnPlayerNotOne = 0;
	CWorldPart* Part;

	*ErrorType = errNoError;

	if(WorldParts->Player)
	{
		NumPlayer++;
		Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY + 1);
		if (Part == NULL)
			NumPlayerNotFloor++;

		Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
		if (Part != NULL)
		{
			if (Part->Group == GroupBox)
			{
				Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 2);
				if (Part != NULL)
				{
					if (Part->Group == GroupBox)
						NumBlocksOnPlayerNotOne++;
				}
			}
		}
	}
	
	for (int Teller = 0; Teller < WorldParts->ItemCount; Teller++)
	{

		if (WorldParts->Items[Teller]->Type == IDExit)
			NumExit++;

		if (WorldParts->Items[Teller]->Group == GroupBox)
		{
			Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Items[Teller]->PlayFieldX, WorldParts->Items[Teller]->PlayFieldY + 1);
			if (Part == NULL)
				NumBlocksNotFloor++;
		}
		
		if (WorldParts->Items[Teller]->Group == GroupExit)
		{
			Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Items[Teller]->PlayFieldX, WorldParts->Items[Teller]->PlayFieldY + 1);
			if (Part == NULL)
				NumExitsNotFloor++;
		}
	}

	if (NumPlayer == 0)
	{

		*ErrorType = errNoPlayer;
		return true;
	}

	else if (NumExit == 0)
	{
		*ErrorType = errNoExit;
		return true;
	}

	else if ((NumBlocksNotFloor > 0) || (NumPlayerNotFloor > 0) || (NumExitsNotFloor > 0))
	{
		*ErrorType = errBlocksPlayerNotOnAFloor;
		return true;
	}

	else if (NumBlocksOnPlayerNotOne > 0)
	{
		*ErrorType = errBlocksOnPlayerNotOne;
		return true;
	}

	return false;
}

void PlayLevelIfNoErrorsFound(CWorldParts* WorldParts)
{
	int errType;
	if (!LevelErrorsFound(WorldParts, &errType))
	{
		GameState = GSGameInit;
	}
	else
	{
		if (errType == errNoPlayer)
		{
			AskQuestion(qsErrPlayer, "Can not play this level because there\nis no player in the level! Please add\na Player and try again.\n\nPress (A) to continue");
		}
		else if (errType == errNoExit)
		{
			AskQuestion(qsErrExit, "Can not play this level because there\nis no exit in the level! Please add an\nexit and try again.\n\nPress (A) to continue");
		}
		else if (errType == errBlocksPlayerNotOnAFloor)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because there\nare boxes, players or exits not on a\nfloor!\nPlease correct this and and try again.\n\nPress (A) to continue");
		}
		else if (errType == errBlocksOnPlayerNotOne)
		{
			AskQuestion(qsErrBlocksOrPlayerNotOnAFloor, "Can not play this level because the\nplayer is carrying more than one box!\nPlease correct this and and try again.\n\nPress (A) to continue");
		}
	}
}




#endif