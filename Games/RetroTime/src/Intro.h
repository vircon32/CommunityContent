#ifndef INTRO_H
#define INTRO_H


#include "string.h"
#include "CFont.h"
#include "CGame.h"
#include "Common.h"
#include "Intro.h"
#include "CTween.h"
#include "Vec2F.h"
#include "SDL_HelperTypes.h"


int maxticks = 75*2;
int scene = 0;
int sceneticks = 0;
int tsize = (int)(60.0*yscale);

void InroInit()
{
	scene = 0;
	sceneticks = 0;
	maxticks = 75*2;
	tsize = (int)(60.0*yscale);
}

void Intro()
{
	if(GameState == GSIntroInit)
	{
		InroInit();
		GameState -= initDiff;
	}

	int[500] s;
	int[10] Nr;
	int* Ps;
	int w,h;

	clear_screen(color_black);
	if (scene == 0)
	{
		Ps = s; *Ps = 0; Ps = faststrcat(Ps,"Willems Davy aka Joyrider3774");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		h = tsize*2;
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (ScreenHeight - h) /2, color_white);
		
		Ps = s; *Ps = 0; Ps = faststrcat(Ps,"presents");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		h = tsize;
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (ScreenHeight) /2, color_white);
	}

	if (scene == 1)
	{
		Ps = s; *Ps = 0; Ps = faststrcat(Ps,"Retro Time");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (int)(40.0*yscale), color_white);
		
		Ps = s; *Ps = 0; Ps = faststrcat(Ps,"A game containing");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s,(ScreenWidth - w) / 2, (int)((ScreenHeight - 3.0 * (tsize + 10.0*yscale)) /2.0), color_white);
		
		itoa(Games, Nr, 10);
		Ps = s; *Ps = 0; Ps = faststrcat(Ps, Nr);
		Ps = faststrcat(Ps," retro based games");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2,(int) ((ScreenHeight - 1 * (tsize + 10*yscale)) / 2.0), color_white);
		
		Ps = s; *Ps = 0; Ps = faststrcat(Ps, "playable in ");
		itoa(Modes, Nr, 10);
		Ps = faststrcat(Ps, Nr);
		Ps = faststrcat(Ps," game modes");
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (int)((ScreenHeight + 1 * (tsize + 10*yscale)) /2.0), color_white);
	}

	if (scene >= 2)
	{
		Ps = s; *Ps = 0; Ps = faststrcat(Ps, GSGames[scene-2].name);
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (int)(40.0*yscale), color_white);

		SDL_Point *TmpTz = CImage_ImageSize(GFXPreviewID2);
		CImage_DrawImageFuze(GFXPreviewID2, scene-2, false, (ScreenWidth - TmpTz->x / 3) / 2, (int)(40.0*yscale) + tsize*2 + 10, 0, 1.0,1.0,1.0,1.0,1.0,1.0);
		
		Ps = s; *Ps = 0; Ps = faststrcat(Ps, GSGames[scene-2].shortdescription);
		w = CFont_TextWidth("Roboto-Regular", tsize, s);
		CFont_WriteText("Roboto-Regular", tsize, s, (ScreenWidth - w) / 2, (int)(40.0*yscale) + tsize*2 + 10 + TmpTz->y/3 + 30, color_white);

		free(TmpTz);		
	}

	sceneticks += 1;

	if (sceneticks >= maxticks)
	{
		scene += 1;
		sceneticks = 0;
	}

	if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) || (gamepad_button_start() == 1) || (scene -2 >= Games))
		GameState = GSTitleScreenInit;
}

#endif