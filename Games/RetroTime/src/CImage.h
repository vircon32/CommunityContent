#ifndef CIMAGE_H
#define CIMAGE_H

#include "math.h"
#include "string.h"
#include "texture.h"
#include "CImage.h"
#include "Vec2F.h"
#include "SDL_HelperTypes.h"
#include "Common.h"
#include "Vec2F.h"
#include "SDL_HelperTypes.h"


struct CTexture {
	Texture* Img;
	int[100] BaseFilename;
};

#define GFX_Max 40
int CImage_ImageSlotsUsed = 0;
CTexture*[GFX_Max] CImage_Images;
bool CImage_ImgEnabled = false;


Texture* getTextureFromName(int* Name)
{
	
	if (strcmp(Name, "fasterdave/background.png") == 0)
	{
		return newTextureHorz(0, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/ladder.png") == 0)
	{
		return newTextureHorz(0, 1, 1, 960, 944, 64, 80, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/key.png") == 0)
	{
		return newTextureHorz(0, 2, 1, 967, 0, 29, 14, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/floortileset.png") == 0)
	{
		return newTextureHorzVert(0, 10, 9,10, 0, 360, 576, 640, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/Character_character_climb.png") == 0)
	{
		return newTextureVert(0, 100, 15, 693, 0, 27, 525, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/Character_character_run.png") == 0)
	{
		return newTextureVert(0, 150, 7, 640, 0, 27, 259, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/Character_character_idle.png") == 0)
	{
		return newTextureVert(0, 160, 15, 720, 0, 25, 525, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/Character_character_jump_up.png") == 0)
	{
		return newTextureVert(0, 180, 6, 667, 0, 26, 210, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/enemy.png") == 0)
	{
		return newTextureHorzVert(0, 200, 3, 4, 745, 0, 96, 128, 1.0,1.0);	
	}

	if (strcmp(Name, "fasterdave/orbs.png") == 0)
	{
		return newTextureVert(0, 250, 5, 841, 0, 128, 640, 1.0,1.0);	
	}


	if (strcmp(Name, "blockstacker/background.png") == 0)
	{
		return newTextureHorz(1, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	
	if (strcmp(Name, "breakout/background.png") == 0)
	{
		return newTextureHorz(2, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "breakout/paddle.png") == 0)
	{
		return newTextureHorz(2, 1, 1, 992, 1016, 32, 8, 1.0,1.0);	
	}

	if (strcmp(Name, "breakout/ball.png") == 0)
	{
		return newTextureHorz(2, 2, 1, 1012, 0, 16, 16, 1.0,1.0);	
	}

	if (strcmp(Name, "breakout/blocks.png") == 0)
	{
		return newTextureHorz(2, 3, 6, 0, 1008, 384, 16, 1.0,1.0);	
	}


	if (strcmp(Name, "frog/background.png") == 0)
	{
		return newTextureHorz(3, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/player.png") == 0)
	{
		return newTextureHorzVert(3, 1, 3, 4, 701, 24, 96, 128, 1.0,1.0);	
	}
	
	if (strcmp(Name, "frog/watergrass.png") == 0)
	{
		return newTextureHorzVert(3, 20, 6, 3, 866, 34, 96, 48, 1.0,1.0);	
	}

    if (strcmp(Name, "frog/carblue.png") == 0)
	{
		return newTextureHorz(3, 50, 2, 56, 572, 78, 29, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/garbagetruck.png") == 0)
	{
		return newTextureHorz(3, 55, 2, 53, 638, 66, 29, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/ambulance.png") == 0)
	{
		return newTextureHorz(3, 60, 2, 71, 509, 66, 29, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/taxi.png") == 0)
	{
		return newTextureHorz(3, 65, 2, 44, 794, 78, 29, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/police.png") == 0)
	{
		return newTextureHorz(3, 70, 2, 46, 722, 74, 29, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/waterplant.png") == 0)
	{
		return newTextureHorz(3, 75, 2, 727, 275, 32, 16, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/apple.png") == 0)
	{
		return newTextureHorz(3, 80, 1, 723, 206, 16, 16, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/lemon.png") == 0)
	{
		return newTextureHorz(3, 85, 1, 792, 206, 16, 16, 1.0,1.0);	
	}

	if (strcmp(Name, "frog/cherry.png") == 0)
	{
		return newTextureHorz(3, 90, 1, 759, 206, 16, 16, 1.0,1.0);	
	}


	if (strcmp(Name, "invaders/background.png") == 0)
	{
		return newTextureHorz(4, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/bullet.png") == 0)
	{
		return newTextureHorz(4, 5, 2, 751, 80, 32, 10, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/explosion.png") == 0)
	{
		return newTextureHorz(4, 10, 7, 67, 771, 560, 80, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/asteroid-01.png") == 0)
	{
		return newTextureHorz(4, 20, 1, 748, 210, 67, 63, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/enemy1.png") == 0)
	{
		return newTextureHorz(4, 25, 5, 29, 376, 240, 48, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/enemy2.png") == 0)
	{
		return newTextureHorz(4, 35, 4, 41, 445, 192, 48, 1.0,1.0);	
	}


	if (strcmp(Name, "invaders/enemy3.png") == 0)
	{
		return newTextureHorz(4, 40, 4, 41, 517, 192, 48, 1.0,1.0);	
	}

	if (strcmp(Name, "invaders/player.png") == 0)
	{
		return newTextureHorz(4, 45, 5, 203, 646, 240, 48, 1.0,1.0);	
	}



	if (strcmp(Name, "pang/background.png") == 0)
	{
		return newTextureHorz(5, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "pang/backgroundsub.png") == 0)
	{
		return newTextureHorz(5, 3, 1, 0, 345, 640, 15, 1.0,1.0);	
	}

	if (strcmp(Name, "pang/character.png") == 0)
	{
		return newTextureHorzVert(5, 5, 12, 8, 23, 364, 624, 576, 1.0,1.0);	
	}

	if (strcmp(Name, "pang/weapon.png") == 0)
	{
		return newTextureVert(5, 50, 2, 34, 953, 800, 66, 1.0,1.0);	
	}

	if (strcmp(Name, "pang/ball.png") == 0)
	{
		return newTextureHorz(5, 55, 1, 789, 174, 45, 45, 1.0,1.0);	
	}

	if (strcmp(Name, "main/frame.png") == 0)
	{
		return newTextureHorz(6, 0, 1, 0, 0, 512, 102, 1.0,1.0);	
	}

	if (strcmp(Name, "main/outerframe.png") == 0)
	{
		return newTextureHorz(6, 1, 1, 0, 922, 512, 102, 1.0,1.0);	
	}

	if (strcmp(Name, "main/medal.png") == 0)
	{
		return newTextureHorz(6, 2, 1, 513, 0, 77, 122, 1.0,1.0);	
	}
	
	if (strcmp(Name, "gamepreview/gamepreview.png") == 0)
	{
		return newTextureHorzVert(7, 0, 3, 3, 0, 0, 160*3, 90*3, 1.0,1.0);	
	}

	if (strcmp(Name, "gamepreview/gamepreview2.png") == 0)
	{
		return newTextureHorzVert(7, 20, 3, 3, 0, 484, 320*3, 180*3, 1.0,1.0);	
	}

	if (strcmp(Name, "ramit/background.png") == 0)
	{
		return newTextureHorz(8, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}

	if (strcmp(Name, "snakey/background.png") == 0)
	{
		return newTextureHorz(9, 0, 1, 0, 0, 640, 360, 1.0,1.0);	
	}
	return NULL;
}

void CImage_Init()
{
	CImage_ImgEnabled = true;
	CImage_ImageSlotsUsed = 0;
	for (int i=0; i < GFX_Max; i++)
		CImage_Images[i] = NULL;	
}


int CImage_LoadImage(int* FileName)
{
	int result = -1;

	if(CImage_ImgEnabled)
		for (int i=0; i < GFX_Max; i++)
		{
			if(CImage_Images[i] == NULL)
			{
				Texture *Img = getTextureFromName(FileName);
				if(Img)
				{	
					CImage_ImageSlotsUsed++;			
					CImage_Images[i] = (CTexture*) malloc(sizeof(CTexture));
					strcpy(CImage_Images[i]->BaseFilename, FileName);					
					CImage_Images[i]->Img = Img;
					result = i;
					break;
				}
			}
		}

	return result;
}

void CImage_UnLoadImage(int GFXID)
{
	if(!CImage_ImgEnabled)
		return;

	if ((GFXID < 0) || (GFXID >= GFX_Max))
		return;

	if (CImage_Images[GFXID] != NULL)
	{
		freeTexture(CImage_Images[GFXID]->Img);
		
		free(CImage_Images[GFXID]);
		CImage_Images[GFXID] = NULL;
		CImage_ImageSlotsUsed--;
	}
}

void CImage_UnloadImages()
{
	for (int i=0; i < GFX_Max; i++)
		CImage_UnLoadImage(i);
}

SDL_Point* CImage_ImageSizeTex(Texture *Texture)
{
	SDL_Point *Result = (SDL_Point*) malloc(sizeof(SDL_Point));
	Result->x = -1;
	Result->y = -1;
	
	if(!CImage_ImgEnabled)
		return Result;

	if(Texture == NULL)
		return Result;

	Result->x = Texture->width;
	Result->y = Texture->height;
	return Result;
}

SDL_Point* CImage_ImageSize(int GFXID)
{
	SDL_Point *Result = (SDL_Point*) malloc(sizeof(SDL_Point));
	Result->x = -1;
	Result->y = -1;
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return Result;

	free(Result);
	return CImage_ImageSizeTex(CImage_Images[GFXID]->Img);
}


void CImage_DrawImageTex(Texture *aTexture,int AnimTile, SDL_Rect* Src, SDL_Rect* Dst)
{
	if(!CImage_ImgEnabled)
		return;

	if(aTexture == NULL)
		return;
	
	int texw = aTexture->width;
	int texh = aTexture->height;
	if ((Src == NULL) && (Dst == NULL))
	{
		drawTextureZoomed(aTexture, AnimTile, ScreenWidth / 2, ScreenHeight / 2, (float)ScreenWidth / texw, (float)ScreenHeight / texh);
	}	
	else
	{
		if ((Src != NULL) && (Dst == NULL))
		{
			drawTextureZoomed(aTexture,AnimTile,ScreenWidth / 2 , ScreenHeight / 2, (float)ScreenWidth / Src->w, (float)ScreenHeight / Src->h);
		}
		else
		{
			if ((Src == NULL) && (Dst != NULL))
			{
					drawTextureZoomed(aTexture,AnimTile, Dst->x + texw /2, Dst->y + texh / 2, (float)Dst->w / texw, (float)Dst->h / texh);
			}
			else
			{
					drawTextureZoomed(aTexture,AnimTile, Dst->x + Src->w/2, Dst->y + Src->h / 2, (float)Dst->w / Src->w, (float)Dst->h / Src->h);
			}
		}
	}
}


void CImage_DrawImage(int GFXID, int AnimTile, SDL_Rect* Src, SDL_Rect* Dst)
{
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return;

	CImage_DrawImageTex(CImage_Images[GFXID]->Img, AnimTile, Src, Dst);
}


//fuze used center points for positions and a floating point scale vector
void CImage_DrawImageFuzeTex(Texture *aTexture, int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley,int TintR, int TintG, int TintB, int Alpha)
{
	if(!CImage_ImgEnabled)
		return;

	if(aTexture == NULL)
		return;

	SDL_Rect Dst;
	
	if(!CenterImagePos)
	{
		Dst.x = (int)(Posx + ((aTexture->width / aTexture->framesHorz * Scalex) / 2));
		Dst.y = (int)(Posy + ((aTexture->height / aTexture->framesVert * Scaley) / 2));
	}
	else
	{
		Dst.x = Posx;
		Dst.y = Posy;
	}

	//Draw
	bool needRotation = ((fabs(Angle) >= epsilion) || (fabs(Angle) <= -epsilion));
	bool needScale = ((fabs(Scalex) <= 1.0 - epsilion) || (fabs(Scalex) >= 1.0 + epsilion) || (fabs(Scaley) <= 1.0 - epsilion) || (fabs(Scaley)>= 1.0 + epsilion));

	set_multiply_color(make_color_rgba(TintR, TintG, TintB, Alpha));
	if(needRotation && needScale)
		drawTextureRotatedZoomed(aTexture,AnimTile, Dst.x, Dst.y, Scalex, Scaley, Angle);
	else
	{
		if(needScale)
		{
			drawTextureZoomed(aTexture,AnimTile, Dst.x, Dst.y, Scalex, Scaley);
		}
		else
		{
			if(needRotation)
			{
				drawTextureRotated(aTexture,AnimTile, Dst.x, Dst.y, Angle);
			}
			else
			{
				drawTexture(aTexture, AnimTile, Dst.x, Dst.y);
			}
		}
	}
	set_multiply_color(make_color_rgba(255, 255, 255, 255));
}


//fuze used center points for positions and a floating point scale vector
void CImage_DrawImageFuzeSrcRectTintFloat(int GFXID, int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley, float TintR, float TintG, float TintB, float Alpha)
{
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return;

	CImage_DrawImageFuzeTex(CImage_Images[GFXID]->Img,AnimTile, CenterImagePos, Posx, Posy, Angle, Scalex,  Scaley, (int)floor(255.0 * TintR) , (int)floor(255.0 * TintG), (int)floor(255.0 * TintB) , (int)floor(255.0 * Alpha));
}

void CImage_DrawImageFuzeSrcRectTintFloatTex(Texture* Texture, int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley,float TintR, float TintG, float TintB, float Alpha)
{
	if(Texture == NULL)
		return;

	CImage_DrawImageFuzeTex(Texture, AnimTile, CenterImagePos, Posx, Posy, Angle, Scalex,  Scaley, (int)floor(255.0 * TintR) , (int)floor(255.0 * TintG), (int)floor(255.0 * TintB) , (int)floor(255.0 * Alpha));
}

//fuze used center points for positions and a floating point scale vector
void CImage_DrawImageFuzeTintFloat(int GFXID, int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley,float TintR, float TintG, float TintB, float Alpha)
{
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return;

	CImage_DrawImageFuzeTex(CImage_Images[GFXID]->Img, AnimTile, CenterImagePos, Posx, Posy, Angle, Scalex,  Scaley, (int)floor(255.0 * TintR) , (int)floor(255.0 * TintG), (int)floor(255.0 * TintB) , (int)floor(255.0 * Alpha));
}

void CImage_DrawImageFuzeTintFloatTex(Texture *Texture, int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley,float TintR, float TintG, float TintB, float Alpha)
{
	if(Texture == NULL)
		return;

	CImage_DrawImageFuzeTex(Texture, AnimTile, CenterImagePos, Posx, Posy, Angle, Scalex,  Scaley, (int)floor(255.0 * TintR) , (int)floor(255.0 * TintG), (int)floor(255.0 * TintB) , (int)floor(255.0 * Alpha));
}

void CImage_DrawImageFuze(int GFXID,int AnimTile, bool CenterImagePos, int Posx, int Posy, float Angle, float Scalex, float Scaley,float TintR, float TintG, float TintB, float Alpha)
{
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return;

	CImage_DrawImageFuzeTex(CImage_Images[GFXID]->Img,AnimTile, CenterImagePos, Posx, Posy, Angle, Scalex,  Scaley, (int)floor(255.0 * TintR) , (int)floor(255.0 * TintG), (int)floor(255.0 * TintB) , (int)floor(255.0 * Alpha));
}


Texture* CImage_GetImage(int GFXID)
{
	if((GFXID < 0) || (GFXID >= GFX_Max))
		return NULL;
	
	if (CImage_Images[GFXID] == NULL)
		return NULL;

	return CImage_Images[GFXID]->Img;
}

void CImage_DeInit()
{
	CImage_UnloadImages();	
}

#endif