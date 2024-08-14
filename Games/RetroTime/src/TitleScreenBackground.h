#ifndef TITLESCREENBACKGROUND_H
#define TITLESCREENBACKGROUND_H

#include "video.h"
#include "misc.h"
#include "common.h"
#include "CImage.h"

#define NumColsRandomBackground (int)((ScreenWidth/(320 * xscale))*2) //320 = width quarter size game screen preview
#define NumRowsRandomBackground (int)((ScreenHeight/(180 * yscale))*2) //180 = height quarter size game screen preview

int[NumColsRandomBackground][NumRowsRandomBackground] RandomBackground;
int menubackgroundx;
int menubackgroundy;
int menubackgrounddx;
int menubackgrounddy;
int pinc = ScreenWidth;
int funlen;
																																																																																																																									int[170] funmsg = "Hello to all Vircon32 Players and thanks to the FUZE Team and Wireframe magazine for doing a competition that made me initially create this game!!!!";


void CGame_CreateRandomBackground()
{
	funlen = strlen(funmsg);
	int x = 0;
	int y = 0;
	int r = rand() % Games;
	int prevr = r;

	
	while (y < NumRowsRandomBackground)
	{
		x = 0;
		while(r == prevr)
			r = rand() % Games;
		prevr = r;

		while (x < NumColsRandomBackground)
		{
			r += 1;
			if (r == Games)
				r = 0;
			RandomBackground[x][y] = r;
			x +=1;
		}
		y += 1;
	}

	menubackgroundx = rand() % ScreenWidth;
	menubackgroundy = rand() % ScreenHeight;
	if(rand() % 2 == 0)
		menubackgrounddx =  1;
	else
		menubackgrounddx = -1;
	if(rand() % 2 == 0)
		menubackgrounddy =  1;
	else
		menubackgrounddy =  -1;
}

void CGame_DrawTitleBackground(bool k)
{
	menubackgroundx += menubackgrounddx;
	menubackgroundy += menubackgrounddy;
	if ((menubackgroundx == 0) || (menubackgroundx == ScreenWidth))
		menubackgrounddx *= -1;

	if ((menubackgroundy == 0) || (menubackgroundy == ScreenHeight))
		menubackgrounddy *= -1;

	for (int y = 0; y < NumRowsRandomBackground; y++)
		for(int x = 0; x < NumColsRandomBackground; x++)
		{
			CImage_DrawImageFuze(GFXPrevewID, RandomBackground[x][y], false, -ScreenWidth+menubackgroundx + (int)(x*320*xscale), -ScreenHeight+menubackgroundy + (int)(y*180*yscale), 0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		}
	if (k)
	{
		int[2] T;
		for(int i = 0; i < funlen; i++)
		{
			int color = make_color_rgba(255, 128 + (sin(i*25 % 360 * pi/180))*127, 0, 64*3);
			T[0] = funmsg[i];
			T[1] = 0;
			CFont_WriteText("Roboto-Regular", 40, T, pinc + i * 65, ((ScreenHeight / 2)) - 25 + (sin((((pinc + (i*15)) % 360)*pi/180)) * 150), color);
		}
		pinc = pinc- 2;
		if (pinc < (int)(funlen * -65))
		{
			pinc = ScreenWidth;
		}
	}
}

#endif