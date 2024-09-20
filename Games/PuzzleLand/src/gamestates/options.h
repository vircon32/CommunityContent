#ifndef OPTIONS_H
#define OPTIONS_H

#include "string.h"
#include "../gameobjects/coptionsselector.h"
#include "../texture.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"
#include "options.h"

COptionsSelector* Selector;

void OptionsInit()
{
	Selector = COptionsSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void OptionsDeInit()
{
	freeTexture(Background);
	COptionsSelector_Destroy(Selector);
	SaveSettings();
}

void Options()
{
	if(GameState == GSOptionsInit)
	{
		OptionsInit();
		GameState -= GSInitDiff;
	}

	if (gamepad_button_b() == 1)
		GameState = GSTitleScreenInit;

	if(gamepad_button_start() == 1)
		GameState = GSTitleScreenInit;

	if (gamepad_button_a() == 1)
	{
		if (COptionsSelector_GetSelection(Selector) == 1)
		{
			setSoundOn(!isSoundOn());
			SaveSettings();
		}
	
		if (COptionsSelector_GetSelection(Selector) == 2)
		{
			setMusicOn(!isMusicOn());
			SaveSettings();
		}

		playMenuSelectSound();
	}
	
	if (gamepad_up() == 1)
		COptionsSelector_MoveUp(Selector);
	
	if (gamepad_down() == 1)
		COptionsSelector_MoveDown(Selector);

	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
	set_multiply_color(color_black);
	int textw = textfont_get_line_width(Mini2X, "OPTIONS");
	textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - (textw >> 1)) * xscale, 30 *yscale, "OPTIONS", xscale, yscale);
	
	if (isSoundOn())
		textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - 55) * xscale, 70 * yscale, "SOUND: ON", xscale, yscale);
	else
		textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - 55) * xscale, 70 *yscale, "SOUND: OFF", xscale, yscale);
	
	if (isMusicOn())
		textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - 55) * xscale, 100 *yscale, "MUSIC: ON", xscale, yscale);
	else
		textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - 55) * xscale, 100 *yscale, "MUSIC: OFF", xscale, yscale);
	set_multiply_color(color_white);
	COptionsSelector_Draw(Selector);

	if(GameState != GSOptions)
		OptionsDeInit();
}


#endif