#ifndef CREDITS_H
#define CREDITS_H

#include "string.h"
#include "../texture.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"
#include "credits.h"

int CreditsNrOfChars;

void CreditsInit()
{
	CreditsNrOfChars = 0;
	Background = loadImageAtPath("graphics/paper");
	playTextSound();
}

void CreditsDeInit()
{
	freeTexture(Background);
	stopTextSound();
}

void Credits()
{
	int *Tekst = "Puzzle Land is made by Willems Davy\nGraphics made using gimp\nSprites by Yann R. Fernandez\nMusic by MusMus:\nhttps://musmus.main.jp\n\nPuzzle Land is a remake of\nDaedalian opus for gameboy by\nVic Tokai Inc. 1990";

	if(GameState == GSCreditsInit)
	{
		CreditsInit();
		GameState -= GSInitDiff;
	}
	
	if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) || (gamepad_button_start() == 1))
		GameState = GSTitleScreenInit;

	if (CreditsNrOfChars < strlen(Tekst))
	{
		CreditsNrOfChars++;
	}
	else
		stopTextSound();

	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
	set_multiply_color(color_black);
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + (WINDOW_WIDTH / 2 - 32) * xscale, 20 *yscale, "CREDITS", xscale, yscale);
	int[255] Text;
	memset(Text, 0, 255);
	strncpy(Text, Tekst, CreditsNrOfChars);
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + 30 * xscale, 40 *yscale,Text, xscale, yscale);
	set_multiply_color(color_white);

	if (GameState != GSCredits)
		CreditsDeInit();
}


#endif