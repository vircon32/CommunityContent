#ifndef STAGESELECT_H
#define STAGESELECT_H

#include "input.h"
#include "string.h"
#include "../sound.h"
#include "../gameobjects/cstageselectselector.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "stageselect.h"


CStageSelectSelector *StageSelectSelector;

void StageSelectInit()
{
	StageSelectSelector = CStageSelectSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void StageSelectDeInit()
{
	freeTexture(Background);
	CStageSelectSelector_destroy(StageSelectSelector);
}

void StageSelect()
{
	if(GameState == GSStageSelectInit)
	{
		StageSelectInit();
		GameState -= GSInitDiff;
	}

	if (gamepad_button_b() == 1)
	{
		GameState = GSPasswordEntryInit;
	}

	if (gamepad_button_a() == 1)
	{
		playMenuSelectSound();
		Level = CStageSelectSelector_GetSelection(StageSelectSelector);
		GameState = GSOldManSpeakingInit;
	}

	if(gamepad_button_start() == 1)
		GameState = GSTitleScreenInit;
	
	if (gamepad_up() == 1)
		CStageSelectSelector_MoveUp(StageSelectSelector);
	
	if (gamepad_down() == 1)
		CStageSelectSelector_MoveDown(StageSelectSelector);
	
	if (gamepad_left() == 1)
		CStageSelectSelector_MoveLeft(StageSelectSelector);
	
	if (gamepad_right() == 1)
		CStageSelectSelector_MoveRight(StageSelectSelector);


	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
	set_multiply_color(color_black);
	int textw = textfont_get_line_width(Ash, "ROOM SELECT");
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + ((WINDOW_WIDTH - textw)>> 1)*xscale, 20*yscale,"ROOM SELECT", xscale, yscale);
	
	int Teller;
	int[100] ChrRoom;
	int[10] Nr;

	for (Teller=0;Teller< 36;Teller++)
	{
		strcpy(ChrRoom, "Room ");
		itoa(Teller + 1, Nr, 10);
		strcat(ChrRoom, Nr);
		textfont_print_from_left_zoomed(Ash, ScreenXOffset + XOffsetStageSelect + (((Teller % 3) * 82) * xscale), YOffsetStageSelect + (((Teller / 3) * 15) *yscale), ChrRoom, xscale, yscale);
	}
	set_multiply_color(color_white);
	CStageSelectSelector_Draw(StageSelectSelector);

	if(GameState != GSStageSelect)
		StageSelectDeInit();
}


#endif