#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "string.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"
#include "../gameobjects/chand.h"

CHand* Hand;

void MoveBlockRight()
{
	int X,Y;
	bool CanMove;
	CanMove = true;
	for (Y=0;Y<Rows;Y++)
		if(PlayField[1][Cols-1][Y] != 0)
		{
			CanMove = false;
			break;
		}
	if (CanMove)
		for(X=Cols-1;X >= 1;X--)
			for(Y=0;Y<Rows;Y++)
				PlayField[1][X][Y] = PlayField[1][X-1][Y];
	for (Y=0;Y<Rows;Y++)
		PlayField[1][0][Y] = 0;
}

void MoveBlockLeft()
{
	int X,Y;
	bool CanMove;
	CanMove = true;
	for (Y=0;Y<Rows;Y++)
		if(PlayField[1][0][Y] != 0)
		{
			CanMove = false;
			break;
		}
	if (CanMove)
		for(X=0;X <Cols-1;X++)
			for(Y=0;Y<Rows;Y++)
				PlayField[1][X][Y] = PlayField[1][X+1][Y];
	for (Y=0;Y<Rows;Y++)
		PlayField[1][Cols-1][Y] = 0;
}

void MoveBlockUp()
{
	int X,Y;
	bool CanMove;
	CanMove = true;
	for (X=0;X<Cols;X++)
		if(PlayField[1][X][0] != 0)
		{
			CanMove = false;
			break;
		}
	if (CanMove)
		for(X=0;X<Cols;X++)
			for(Y=0;Y<Rows-1;Y++)
				PlayField[1][X][Y] = PlayField[1][X][Y+1];
	for (X=0;X<Cols;X++)
		PlayField[1][X][Rows-1] = 0;
}

void MoveBlockDown()
{
	int X,Y;
	bool CanMove;
	CanMove = true;
	for (X=0;X<Cols;X++)
		if(PlayField[1][X][Rows-1] != 0)
		{
			CanMove = false;
			break;
		}
	if (CanMove)
		for(X=0;X<Cols;X++)
			for(Y=Rows-1;Y>=1;Y--)
				PlayField[1][X][Y] = PlayField[1][X][Y-1];
	for (X=0;X<Cols;X++)
		PlayField[1][X][0] = 0;
}

void MakeBlockActive(int X,int Y,int BlockNr)
{
	int TellerX,TellerY;
	if((X >= 0) && (Y >=0) && (X < Cols) && (Y < Rows))
	{

		for(TellerX=Cols-1;TellerX>=0;TellerX--)
			for(TellerY=Rows-1;TellerY>=0;TellerY--)
			{
				if(PlayField[0][TellerX][TellerY] == BlockNr)
				{
					PlayField[0][TellerX][TellerY] = 0;
					PlayField[1][TellerX][TellerY] = BlockNr;
				}
			}
	}
}

bool MakeBlockUnActive()
{
	int X,Y;
	bool FirstBlockFound,UnActive;
	FirstBlockFound = false;
	UnActive = true;
	for (X=Cols-1;X>=0;X--)
		for(Y=Rows-1;Y>=0;Y--)
			if ((PlayField[1][X][Y] > 0)&& (PlayField[0][X][Y] != 0))
			{
				UnActive = false;
				break;
			}
	if(UnActive)
		for(X=Cols-1;X >=0; X--)
			for(Y=Rows-1 ; Y >=0 ;Y--)
				if(PlayField[1][X][Y] > 0)
				{
					if (!FirstBlockFound)
					{
						CHand_SetPosition(Hand,X, Y );
						FirstBlockFound = true;
					}
					PlayField[0][X][Y] = PlayField[1][X][Y];
					PlayField[1][X][Y] = 0;
				}
	return UnActive;
}

void FlipBlock(bool Horizontal)
{
	int BlockW,BlockH,X,Y,MinX,MinY,MaxX,MaxY;
	int[Cols][Rows] Tmp;
	MinX = 100;
	MinY = 100;
	MaxX = -1;
	MaxY = -1;
	for (X = Cols-1 ; X >=0; X--)
		for(Y = Rows-1; Y>=0;Y--)
		{
			if(PlayField[1][X][Y] > 0)
			{
				if(MinX > X)
					MinX = X;
				if(MaxX < X)
					MaxX = X;
				if(MinY > Y)
					MinY = Y;
				if(MaxY < Y)
					MaxY = Y;
				Tmp[X][Y] = 0;
			}
		}

	BlockW = MaxX - MinX;
	BlockH = MaxY - MinY;
	for(X=BlockW;X>=0;X--)
		for(Y=BlockH;Y>=0;Y--)
		{
			if(Horizontal)
				Tmp[X][BlockH- Y] = PlayField[1][MinX + X][MinY + Y];
			else
				Tmp[BlockW - X][Y] = PlayField[1][MinX+X][MinY + Y];
			PlayField[1][MinX+X][MinY+Y] = 0;
		}
	for(X=BlockW;X>=0;X--)
		for(Y=BlockH;Y>=0;Y--)
			PlayField[1][MinX+X][MinY+Y] = Tmp[X][Y];
	playFlipBlockSound();
}

void RotateBlock()
{
 	int Tmp1,Tmp2,Offset,NewBlockW,NewBlockH,BlockW,BlockH,MinX,MinY,MaxX,MaxY,X,Y;
 	int[Cols][Rows] Tmp;
	MinX = 100;
	MinY = 100;
	MaxX = -1;
	MaxY = -1;
	for (X = Cols-1 ; X >=0; X--)
		for(Y = Rows-1; Y>=0;Y--)
		{
			if(PlayField[1][X][Y] > 0)
			{
				if(MinX > X)
					MinX = X;
				if(MaxX < X)
					MaxX = X;
				if(MinY > Y)
					MinY = Y;
				if(MaxY < Y)
					MaxY = Y;
			}
			Tmp[X][Y] = 0;
		}

	BlockW = MaxX - MinX +1;
	BlockH = MaxY - MinY +1;
	if(BlockW == BlockH)
 	{
 		for(X=BlockW-1;X>=0;X--)
 			for(Y=BlockH-1;Y>=0;Y--)
 			{
 				Tmp[BlockW-1-Y][X] = PlayField[1][X+MinX][Y+MinY];
 				PlayField[1][X+MinX][Y+MinY] = 0;
 			}
 		for(X=BlockW-1;X>=0;X--)
 			for(Y=BlockH-1;Y>=0;Y--)
 				PlayField[1][MinX+X][MinY+Y] = Tmp[X][Y];

 	}

 	if(BlockW > BlockH)
 	{
  		NewBlockH = BlockW;
 
		if((MinY + ( NewBlockH / 2) >= Rows) || (MinY - ((NewBlockH -1)/ 2) <0) || (MinX + BlockW / 2 > Cols))
 		{
			playErrorSound();
 			return;
 		}

 		for(X=BlockW-1;X>=0;X--)
 		{
 			for(Y=BlockH-1;Y>=0;Y--)
 			{
 				Tmp[BlockW-1-Y][X] = PlayField[1][X+MinX][Y+MinY];
 				PlayField[1][X+MinX][Y+MinY] = 0;
 			}
 		}
 
		Tmp1 = (BlockW - 1) / 2;
 		Tmp2 = (NewBlockH-1)/ 2;

 		for(X=BlockW-1;X>=0;X--)
 			for(Y=NewBlockH-1;Y>=0;Y--)
 			{
				if ((MinX + X - Tmp1 >= 0) && (MinX + X - Tmp1 <= Cols - 1) &&
					(MinY + Y - Tmp2 >= 0) && (MinY + Y - Tmp2 <= Rows - 1))
				{
					PlayField[1][MinX + X - Tmp1][MinY + Y - Tmp2] = Tmp[X][Y];
				}
			}
 	}
 	if(BlockW < BlockH)
 	{
 		NewBlockW = BlockH;
 		NewBlockH = BlockW;

		if ((BlockW == 2) && (BlockH == 3))
			Offset = 1;
		else
			Offset = 0;

		if((MinX + Offset +  NewBlockW / 2 >= Cols) || (MinX + Offset - (NewBlockW-1)/2 <0) || (MinY + (BlockH) /2 > Rows))
		{
			playErrorSound();
 			return;
		}

		for(X=BlockW-1;X>=0;X--)
			for(Y=BlockH-1;Y>=0;Y--)
			{
				Tmp[NewBlockW-1-Y][X] = PlayField[1][X+MinX][Y+MinY];
				PlayField[1][X+MinX][Y+MinY] = 0;
			}

		Tmp1 = (NewBlockW-1) / 2;
		Tmp2 = (BlockH -1) / 2;
		for(X=NewBlockW-1;X>=0;X--)
			for(Y=NewBlockH-1;Y>=0;Y--)
			{
				if((MinX+X + Offset - Tmp1  >= 0) && (MinX+X + Offset - Tmp1 <= Cols-1) &&
				   (MinY+Y + Tmp2  >=0) && (MinY+Y + Tmp2 <= Rows-1))
				   	PlayField[1][MinX+X + Offset - Tmp1][MinY + Y +  Tmp2] = Tmp[X][Y];
			}
	}
	playRotateBlockSound();
}

void LoadLevel()
{
	int X,Y;
 	for (X=0;X<Cols;X++)
 	{ 	
		for (Y=0;Y <Rows;Y++)
  		{
			PlayField[0][X][Y] = levels[((Level-1) * (Cols * Rows))  + (X * Rows + Y)  ];
  			PlayField[1][X][Y] = 0;
  		}
 	}
}


bool IsStageClear()
{
	int X,Y,TellerX,TellerY;
	bool StartBorderFound,VertStartBorderFound,VertEndBorderFound,Temp;
	Temp = true;
	if (Level == 17)
	{
		for(Y=6;Y<=8;Y++)
			for(X=0;X<Cols;X++)
				Temp = Temp && (PlayField[0][X][Y] > 0);
	}
	else
	if (Level == 32)
	{
		for (Y=0;Y<=14;Y++)
			for (X=7;X<=9;X++)
				Temp = Temp && (PlayField[0][X][Y] > 0);
		for (Y=6;Y<=8;Y++)
			for (X = 10;X<=14;X++)
				Temp = Temp && (PlayField[0][X][Y] > 0);

	}
	else
	{
		StartBorderFound = false;
		for (Y=0;Y<Rows;Y++)
			for (X=0;X<Cols;X++)
			{
				if (!StartBorderFound)
				{
					if(X < Cols-1)
						if((PlayField[0][X][Y] < 0) && (PlayField[0][X+1][Y] >=0))
							for(TellerX = X+1;TellerX<Cols;TellerX++)
								if(PlayField[0][TellerX][Y] < 0)
									StartBorderFound = true;
				}
				else
				{
					if(PlayField[0][X][Y] < 0)
					{
						StartBorderFound = false;
						if( X < Cols-1)
							if((PlayField[0][X][Y] < 0) && (PlayField[0][X+1][Y] >= 0))
								for(TellerX = X+1;TellerX < Cols;TellerX++)
									if(PlayField[0][TellerX][Y] < 0)
										StartBorderFound=true;
						continue;
					}

					if (StartBorderFound)
					{
						VertEndBorderFound = false;
						VertStartBorderFound = false;
						if (Y < Rows -1)
							for (TellerY=Y+1;TellerY<Rows;TellerY++)
								if(PlayField[0][X][TellerY] < 0)
									VertEndBorderFound = true;
						if (Y > 0)
							for(TellerY = Y -1; TellerY >=0;TellerY--)
								if(PlayField[0][X][TellerY] < 0)
									VertStartBorderFound = true;
						if(VertStartBorderFound && VertEndBorderFound)
							Temp = Temp && (PlayField[0][X][Y] > 0);
					}

				}
			}


	}
	return Temp;
}

void GameInit()
{
	srand(get_time() + get_date());
	GameMoveCoolDown = 0;
	BlockActive = false;
	LoadLevel();
	CHand_SetPosition(Hand,10, 8);
	CHand_Show(Hand);
	srand (getSecondsSinceEpoch());
	StartTime = getSecondsSinceEpoch();
	Background = loadImageAtPath("graphics/roombackground");
	switch(rand()%2)
	{
		case 0: SelectMusic(musGame1);
				break;
		case 1 : SelectMusic(musGame2);
				 break;

	}
}

void GameDeInit()
{
	freeTexture(Background);
}

void Game()
{
	if(GameState == GSGameInit)
	{
		GameInit();
		GameState -= GSInitDiff;
	}

	if (gamepad_button_a() == 1)
	{
		if (!BlockActive)
		{
			int PlayFieldX, PlayFieldY, BlockNr;
			PlayFieldX = CHand_GetPlayFieldX(Hand);
			PlayFieldY = CHand_GetPlayFieldY(Hand);
			BlockNr = PlayField[0][PlayFieldX][PlayFieldY];
			if (BlockNr > 0)
			{
				playPickupBlockSound();
				BlockActive = true;
				CHand_Hide(Hand);
				MakeBlockActive(PlayFieldX, PlayFieldY, BlockNr);
			}
		}
		else
		{
			if (MakeBlockUnActive())
			{
				playDropBlockSound();
				BlockActive = false;
				if (IsStageClear())
				{
					GameState = GSStageClearInit;
					playStageEndSound();
				}
				else
					CHand_Show(Hand);
			}
			else
				playErrorSound();
		}
	}

	if (gamepad_button_x() == 1)
	{
		if (BlockActive)
			FlipBlock(true);
	}
	
	if (gamepad_button_y() == 1)
	{
		if (BlockActive)
			FlipBlock(false);
	}

	if (gamepad_button_b() == 1)
	{
		if (BlockActive)
			RotateBlock();
	}

	if(gamepad_button_r() == 1)
	{
		LoadLevel();
		BlockActive = false;
		CHand_SetPosition(Hand, 10, 8);
		CHand_Show(Hand);
	}

	if(gamepad_button_start() == 1)
		GameState = GSTitleScreenInit;

	if (GameMoveCoolDown > 0)
		GameMoveCoolDown--;
	if (BlockActive && (GameMoveCoolDown == 0))
	{
		if (gamepad_right() > 0)
		{
			MoveBlockRight();
			GameMoveCoolDown = 3*fpsscale;
		}
		if (gamepad_left() > 0)
		{
			MoveBlockLeft();
			GameMoveCoolDown = 3*fpsscale;
		}
		if (gamepad_up() > 0)
		{
			MoveBlockUp();
			GameMoveCoolDown = 3*fpsscale;
		}
		if (gamepad_down() > 0)
		{
			MoveBlockDown();
			GameMoveCoolDown = 3*fpsscale;
		}
	}

	EndTime = getSecondsSinceEpoch();
	
	drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);
	DrawPanel();
	DrawPlayField();
	CHand_Move(Hand);
	CHand_Draw(Hand);

	if(GameState != GSGame)
		GameDeInit();
}


#endif