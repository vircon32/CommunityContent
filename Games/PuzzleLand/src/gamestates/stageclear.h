#ifndef STAGECLEAR_H
#define STAGECLEAR_H

#include "input.h"
#include "../sound.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "stageclear.h"


bool KaderVisible;

void StageClearInit()
{
	KaderVisible = true;
}

void StageClearDeInit()
{

}

void StageClear()
{
	if(GameState == GSStageClearInit)
	{
		StageClearInit();
		GameState -= GSInitDiff;
	}
	
	if (gamepad_button_a() == 1)
		GameState = GSOldManSpeakingInit;
	if (gamepad_button_b() == 1)
		KaderVisible = !KaderVisible;
	if(gamepad_button_start() == 1)
		GameState = GSTitleScreenInit;

	drawTextureZoomed(RoomBackground, 0, ScreenXOffset + 0, 0);
	DrawPanel();
	DrawPlayField();
	if (KaderVisible)
	{
		drawTextureZoomed(StageClearKader, 0, ScreenXOffset + ((WINDOW_WIDTH - StageClearKader->width)>>1) *xscale, YOffsetGame + (75*yscale));
	}

	if(GameState != GSStageClear)
		StageClearDeInit();
}


#endif