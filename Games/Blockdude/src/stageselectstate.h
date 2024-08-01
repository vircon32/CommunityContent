#ifndef STAGESELECT_H
#define STAGESELECT_H

#include "input.h"
#include "string.h"
#include "savestate.h"
#include "libs/TextFonts/textfont.h"
#include "fonts/Roboto_Bold_12.h"
#include "libs/DrawPrimitives/draw_primitives.h"

void StageSelectInit(CWorldParts* WorldParts)
{
	LoadSelectedLevel(WorldParts);
	NeedRedraw = true;
}

void StageSelect(CWorldParts* WorldParts)
{
	if (GameState == GSStageSelectInit)
	{
		StageSelectInit(WorldParts);
		GameState -= GSDiff;
	}

	if(!AskingQuestion && (gamepad_button_r() == 1))
	{
		playMenuSelectSound();
		int i = skinSaveState();
		i++;
		if (i == MAXSKINS)
			i = 0;
		setSkinSaveState(i);
		LoadGraphics();
		CWorldParts_UpdateGraphics(WorldParts);
		NeedRedraw = true;
	}


	if (!AskingQuestion && (gamepad_button_b() == 1))
	{
		GameState = GSTitleScreenInit;
		CWorldParts_RemoveAll(WorldParts);
		playMenuBackSound();
	}
	else
	if (!AskingQuestion && ((gamepad_button_a() == 1) || (gamepad_button_start() == 1)))
	{
		playMenuSelectSound();
		if (SelectedLevel <= lastUnlockedLevel())
			GameState = GSGameInit;
		else
		{
			//int* Text;
			int[200] Msg;
			int[10] Nr;
			strcpy(Msg, "This Level Hasn't been unlocked yet!\nDo you want to play the last unlocked\nlevel ");
			itoa(lastUnlockedLevel(), Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, "/");
			itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, "?\n\nPress (A) to Play (B) to cancel");
			AskQuestion(qsNotUnlocked, Msg);
		}
		
	}

	if (!AskingQuestion && (gamepad_left() == 1))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel--;
		bool doLoad = true;
		if (SelectedLevel < 1)
		{
			SelectedLevel = 1;
			doLoad = false;
		}
		if(doLoad)
			LoadSelectedLevel(WorldParts);
	}

	if (!AskingQuestion && (gamepad_right() == 1))
	{
		playMenuSound();
		NeedRedraw = true;
		SelectedLevel++;
		bool doLoad = true;
		if (SelectedLevel > MaxLevels[CurrentLevelPackIndex])
		{
			SelectedLevel = MaxLevels[CurrentLevelPackIndex];
			doLoad = false;
		}
		if(doLoad)
			LoadSelectedLevel(WorldParts);
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
	
		drawTexture(IMGBackground, 0, 0, 0);
		CWorldParts_Draw(WorldParts);
		set_multiply_color(Color1);
		draw_filled_rectangle(0, 0, WINDOW_WIDTH, 15);
		set_multiply_color(Color2);
		draw_line(0, 16, WINDOW_WIDTH, 16);
		
		int[250] Msg;
		int[10] Nr;
		
		if (SelectedLevel <= lastUnlockedLevel())
		{
			strcpy(Msg, "Stage Select - Level: ");
			itoa(SelectedLevel, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg,"/");
			itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, " dpad:Select A:Play Level B:Titlescreen R: Next Skin");			
		}
		else
		{
			strcpy(Msg, "Stage Select - Level: ");
			itoa(SelectedLevel, Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg,"/");
			itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
			strcat(Msg, Nr);
			strcat(Msg, " is locked! dpad:Select B:Titlescreen R: Next Skin");
		}

		textfont_print_from_left(&FontRoboto_Bold_12,0,0, Msg);
		set_multiply_color(color_white);
	}

	int id = -1;
	bool answer = false;
	if (AskQuestionUpdate(&id, &answer, false))
	{
		if (id == qsNotUnlocked)
		{
			if (answer)
			{
				SelectedLevel = lastUnlockedLevel();
				LoadSelectedLevel(WorldParts);
				GameState = GSGameInit;
			}
		}
	}
}


#endif 