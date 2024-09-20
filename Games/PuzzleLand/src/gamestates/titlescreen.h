#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "input.h"
#include "../texture.h"
#include "../sound.h"
#include "../gameobjects/ctitlescreenselector.h"
#include "../commonvars.h"
#include "gamecommon.h"


CTitleScreenSelector* TitleScreenSelector;

void TitleScreenInit()
{
	TitleScreenSelector = CTitleScreenSelector_Create();
	Background = loadImageAtPath("graphics/title");
	SelectMusic(musTitle);
}

void TitleScreenDeInit()
{
	freeTexture(Background);
	CTitleScreenSelector_destroy(TitleScreenSelector);
}

void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSInitDiff;
	}

	if (gamepad_up() == 1)
		CTitleScreenSelector_MoveUp(TitleScreenSelector);
	
	if (gamepad_down() == 1)
		CTitleScreenSelector_MoveDown(TitleScreenSelector);

	if (gamepad_button_a() == 1)
	{
		playMenuSelectSound();
		switch (TitleScreenSelector->Selection)
		{
			case 1:
				Level = 0;
				GameState = GSOldManSpeakingInit;
				break;
			case 2:
				GameState = GSPasswordEntryInit;
				break;
			case 3:
				GameState = GSOptionsInit;
				break;
			case 4:
				GameState = GSCreditsInit;
				break;
		}
	}
	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
	
	CTitleScreenSelector_Draw(TitleScreenSelector);

	if(GameState != GSTitleScreen)
		TitleScreenDeInit();
}


#endif