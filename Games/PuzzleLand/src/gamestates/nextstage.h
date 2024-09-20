#ifndef NEXTSTAGE_H
#define NEXTSTAGE_H

#include "input.h"
#include "string.h"
#include "../texture.h"
#include "../sound.h"
#include "../gameobjects/cspaceship.h"
#include "../gameobjects/ccloud.h"
#include "../gameobjects/cstageblock.h"
#include "../gameobjects/cplayer.h"
#include "../gameobjects/cfairy.h"
#include "../commonvars.h"
#include "../libs/TextFonts/textfont.h"
#include "gamecommon.h"
	
CStageBlock *StageBlock;
CPlayer* Player;
CCloud* Cloud1;
CCloud* Cloud2;
CCloud* Cloud3;
CCloud* Cloud4;
CSpaceShip* SpaceShip;
CFairy* Fairy;

bool BridgeShown;
bool BridgeDrawing;
int BridgeDrawnWidth;


void NextStageLevel1to35Init()
{
	BridgeShown = false;
	BridgeDrawing = false;
	BridgeDrawnWidth = 0;

	StageBlock = CStageBlock_Create();
	Player = CPlayer_Create(30*xscale,167*yscale,30*xscale,268*xscale);
	Cloud1 = CCloud_Create(259*xscale,15*yscale,-0.40*xscale,Big);
	Cloud2 = CCloud_Create(185*xscale,45*yscale,-0.25*xscale,Small);
	Cloud3 = CCloud_Create(134*xscale,7*yscale,-0.40*xscale,Big);
	Cloud4 = CCloud_Create(50*xscale,50*yscale,-0.25*xscale,Small);
	SpaceShip = CSpaceShip_Create();
	Fairy = CFairy_Create(172*xscale,150*yscale,6*fpsscale);
	Background = loadImageAtPath("graphics/betweenstage");
	SelectMusic(musStage);
	switch (Level)
	{
		case 1:
			CStageBlock_Load(StageBlock, 1);
			break;
  		case 2:
			CStageBlock_Load(StageBlock,2);
  			break;
  		case 3:
			CStageBlock_Load(StageBlock,3);
  			break;
  		case 4:
			CStageBlock_Load(StageBlock,4);
  			break;
  		case 5:
			CStageBlock_Load(StageBlock,5);
  			break;
  		case 6:
			CStageBlock_Load(StageBlock,6);
  			break;
  		case 8:
  			CStageBlock_Load(StageBlock,7);
  			break;
  		case 9:
  			CStageBlock_Load(StageBlock,8);
  			break;
  		case 11:

  			CStageBlock_Load(StageBlock,9);
  			break;
  		case 35:
  			CStageBlock_Load(StageBlock,10);
  			break;
  		default: Fairy->Hidden = true;
	}
}

void NextStageLevel1to35DeInit()
{
	freeTexture(Background);
	CStageBlock_destroy(StageBlock);
	CSpaceShip_destroy(SpaceShip);
	CFairy_Destroy(Fairy);
	CCloud_Destroy(Cloud1);
	CCloud_Destroy(Cloud2);
	CCloud_Destroy(Cloud3);
	CCloud_Destroy(Cloud4);
	CPlayer_Destroy(Player);
}

void NextStageLevel1to35()
{
	if(GameState == GSNextStageInit)
	{
		NextStageLevel1to35Init();
		GameState -= GSInitDiff;
	}
	
	if (GameState == GSNextStage)
	{
		if ((gamepad_button_a() == 1) ||
			(gamepad_button_b() == 1) ||
			(gamepad_up() == 1))
		{
			if(CPlayer_GetX(Player) > 265*xscale)
				Player->State = EnterBuilding;
			if(CPlayer_GetX(Player) < 32*xscale)
				Player->State = EnterBuilding;
		}

		if(gamepad_button_start() == 1)
			GameState = GSTitleScreenInit;

		drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
		CCloud_Move(Cloud1);
		CCloud_Draw(Cloud1);
		CCloud_Move(Cloud2);
		CCloud_Draw(Cloud2);
		CCloud_Move(Cloud3);
		CCloud_Draw(Cloud3);
		CCloud_Move(Cloud4);
		CCloud_Draw(Cloud4);
		int	dstx = 111*xscale;
		int	dsty = 188*yscale;
		if (!BridgeShown)
		{
			if(!BridgeDrawing)
			{
				if(CPlayer_GetX(Player) > 92*xscale)
				{
					BridgeDrawing = true;
					playBridgeSound();
				}
			}
			else
			{
				int srcx = 0;
				int srcy = 0;
				int srcw = BridgeDrawnWidth;
				int srch = Bridge->height;			
				BridgeDrawnWidth = BridgeDrawnWidth + 3;
				if (BridgeDrawnWidth >= Bridge->width)
				{
					BridgeDrawing = false;
					BridgeShown = true;
					srcw = Bridge->width;
				}
				setSingleFrameClipRect(Bridge, srcx, srcy, srcw, srch);
				
				drawTextureZoomed(Bridge, 0, ScreenXOffset + dstx, dsty);
			}
		}
		else
		{
			drawTextureZoomed(Bridge,0, ScreenXOffset + dstx, dsty);
		}
		CPlayer_Move(Player);
		CPlayer_Draw(Player);
		switch(Level)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 8:
			case 9:
			case 11:
			case 35:
				CFairy_Draw(Fairy);

				if((Player->State != LookingUp) && (! Fairy->Hidden) && (CPlayer_GetX(Player) + CPlayer_GetWidth(Player) >= CFairy_GetX(Fairy)))
				{
					playElfSound();
					Fairy->Hidden = true;
					Player->State = LookingUp;
				}
				if (Player->State == LookingUp)
				{
					CStageBlock_Draw(StageBlock);
					CStageBlock_Move(StageBlock);
					if( CStageBlock_GetY(StageBlock) + CStageBlock_GetHeight(StageBlock) >= CPlayer_GetY(Player))
					{
						Player->State = Waiting;
						StageBlock->Hidden = true;
					}
				}
				break;
		}

		CSpaceShip_Move(SpaceShip);
		int textw = textfont_get_line_width(Mini2X, LevelPasswords[Level]);
		if (CSpaceShip_GetX(SpaceShip) > ((WINDOW_WIDTH - textw) >> 1) + ((int)(SpaceShip->Image->width*xscale) >> 1))
		{
			draw_filled_rectangle(ScreenXOffset + ((WINDOW_WIDTH >> 1) - (textw >> 1) - 2)*xscale, 32*yscale,ScreenXOffset + ((WINDOW_WIDTH >> 1) - (textw >> 1) -2 + textw + 4)*xscale, (32 + Mini2X->character_height)*yscale);
			set_multiply_color(color_black);
			textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((WINDOW_WIDTH >> 1) - (textw >> 1))*xscale, 34*yscale, LevelPasswords[Level], xscale, yscale);
			set_multiply_color(color_white);
		}
		CSpaceShip_Draw(SpaceShip);
		
		set_multiply_color(color_black);
		int[100] ChrLevel;
		int[10] Nr;
		memset(ChrLevel, 0, 100);

		itoa(Level+1, Nr, 10);
		if(strlen(Nr) < 2)
			strcat(ChrLevel, "0");
		strcat(ChrLevel, Nr);
		textfont_print_from_left_zoomed(Ash, ScreenXOffset + 270*xscale, 110*yscale, ChrLevel, xscale, yscale);

		memset(ChrLevel, 0, 100);

		itoa(Level, Nr, 10);
		if(strlen(Nr) < 2)
			strcat(ChrLevel, "0");
		strcat(ChrLevel, Nr);
		textfont_print_from_left_zoomed(Ash, ScreenXOffset +  31 *xscale, 110 *yscale, ChrLevel, xscale, yscale);
		set_multiply_color(color_white);
		if (Player->State == EnteredBuilding)
		{
			if(CPlayer_GetX(Player) > 265)
				Level++;
			GameState = GSGameInit;
		}
	}
	
	if(GameState != GSNextStage)
		NextStageLevel1to35DeInit();
}

void NextStageLevel0Init()
{
	BridgeShown = false;
	BridgeDrawing = false;
	BridgeDrawnWidth = 0;
	Player = CPlayer_Create(225*xscale,167*yscale,225*xscale,268*xscale);
	Cloud1 = CCloud_Create(259*xscale,15*yscale,-0.40*xscale,Big);
	Cloud2 = CCloud_Create(185*xscale,45*yscale,-0.25*xscale,Small);
	Cloud3 = CCloud_Create(134*xscale,7*yscale,-0.40*xscale,Big);
	Cloud4 = CCloud_Create(50*xscale,50*yscale,-0.25*xscale,Small);
	Background = loadImageAtPath("graphics/betweenstagelevel1");
	SelectMusic(musStage);
}

void NextStageLevel0DeInit()
{
	freeTexture(Background);
	CPlayer_Destroy(Player);
	CCloud_Destroy(Cloud1);
	CCloud_Destroy(Cloud2);
	CCloud_Destroy(Cloud3);
	CCloud_Destroy(Cloud4);
}

void NextStageLevel0()
{
	if(GameState == GSNextStageInit)
	{
		NextStageLevel0Init();
		GameState -= GSInitDiff;
	}	
	
	if ((gamepad_button_a() == 1) ||
		(gamepad_button_b() == 1) ||
		(gamepad_up() == 1))
	{
		if (CPlayer_GetX(Player) > 265*xscale)
			Player->State = EnterBuilding;
	}

	if(gamepad_button_start() == 1)
		GameState = GSTitleScreenInit;

	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);

	int[100] ChrLevel;
	int[10] Nr;
	memset(ChrLevel, 0, 100);

	itoa(Level+1, Nr, 10);
	if(strlen(Nr) < 2)
		strcat(ChrLevel, "0");
	strcat(ChrLevel, Nr);
	set_multiply_color(color_black);
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + 270 *xscale, 110*yscale, ChrLevel, xscale, yscale);
	set_multiply_color(color_white);



	CCloud_Move(Cloud1);
	CCloud_Draw(Cloud1);
	CCloud_Move(Cloud2);
	CCloud_Draw(Cloud2);
	CCloud_Move(Cloud3);
	CCloud_Draw(Cloud3);
	CCloud_Move(Cloud4);
	CCloud_Draw(Cloud4);
	CPlayer_Move(Player);
	CPlayer_Draw(Player);
	if (Player->State == EnteredBuilding)
	{
		if(CPlayer_GetX(Player) > 265*xscale)
			Level++;
		GameState = GSGameInit;
	}

	if(GameState != GSNextStage)
		NextStageLevel0DeInit();
}

#endif