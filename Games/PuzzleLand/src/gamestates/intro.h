#ifndef INTRO_H
#define INTRO_H

#include "input.h"
#include "gamecommon.h"
#include "../texture.h"
#include "../commonvars.h"


Texture *Pict1;
int screenDelay;

void IntroInit()
{
	screenDelay = 100;
	Pict1 = loadImageAtPath("graphics/intro");

}

void IntroDeInit()
{
    freeTexture(Pict1);
}

void Intro()
{
    if(GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSInitDiff;
	}

	if(GameState == GSIntro)
	{
		screenDelay--;
		if(screenDelay == 0)
			GameState = GSTitleScreenInit;

		if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) || (gamepad_button_start() == 1))
			GameState = GSTitleScreenInit;

		drawTextureZoomed(Pict1, 0, ScreenXOffset + 0, 0);
	}

	if(GameState != GSIntro)
		IntroDeInit();
}

#endif