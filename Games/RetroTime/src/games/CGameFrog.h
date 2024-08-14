#ifndef CGAMEFROG_H
#define CGAMEFROG_H

//this game updates one frame the logic and one frame it draws the sprites
//but it always reads inputs every frame but only handles them in the logic frame
//speeds have been accounted for this using the NumLogicFrames variable
//
//Compared to the original game the also has less tiles, defined using CGameFrog_ExtraScale
//variable it scales the tilesizes up with that value (among other things) so that less sprites
//are needed and the game runs faster on slower hardware.

#include "CGameBase.h"
#include "CSpriteObject.h"
#include "../Common.h"
#include "../CGame.h"
#include "../Vec2F.h"
#include "../SDL_HelperTypes.h"

//#define CEILING(x,y) (((x) + (y) + 1) / (y))
//#define FLOORING(x,y) (((x) + (y) - 1) / (y))

struct SRowType {
	int type;
	int backgroundtile;
	int backgroundtileend;
	bool deadlyground;
	int id;
	float speed;
	int minspace;
	int maxrepeats;
};

struct SObjectInfo {
	int mostleft;
	int mostright;
	int mostbottom;
	int mosttop;
};

#define EnablePlayerDeath true
#define CGameFrog_ExtraScale 1.5
#define CGameFrog_NumLogicFrames 2
#define CGameFrog_playerspeed 16.0*3.0*CGameFrog_ExtraScale*yscale
#define CGameFrog_globalworldspeed 0.5*CGameFrog_ExtraScale*yscale*CGameFrog_NumLogicFrames

#define CGameFrog_rowtypewater 0
#define CGameFrog_rowtyperoad 1
#define CGameFrog_rowtypesafety 2

#define CGameFrog_idenemycar1 0
#define CGameFrog_idenemycar2 1
#define CGameFrog_idenemycar3 2
#define CGameFrog_idenemycar4 3
#define CGameFrog_idenemycar5 4
#define CGameFrog_idenemyplant 5
#define CGameFrog_idenemylog 6
#define CGameFrog_idnone 7
#define CGameFrog_idwater 8
#define CGameFrog_idroad 9
#define CGameFrog_idgrass 10
#define CGameFrog_idcherry 11
#define CGameFrog_idapple 12
#define CGameFrog_idlemon 13
#define CGameFrog_idcount 14


#define CGameFrog_cherryspawntrigger 103
#define CGameFrog_applespawntrigger 57
#define CGameFrog_lemonspawntrigger 23

#define CGameFrog_lemonscore 10
#define CGameFrog_applescore 25
#define CGameFrog_cherryscore 50

#define CGameFrog_lenlevelincspeeds 5

#define CGameFrog_numcols (int)(14 / CGameFrog_ExtraScale)
#define CGameFrog_generatorrows 1
#define CGameFrog_maxrowsbeforesafetyrow 4
// or screensheight / playerspeed ceiled
#define CGameFrog_visiblerows (int)(16 / CGameFrog_ExtraScale)
//CGameFrog_visiblerows + CGameFrog_generatorrows
#define CGameFrog_numrows (int)(CGameFrog_visiblerows + CGameFrog_generatorrows)
//(int)FLOORING(CGameFrog_visiblerows, 2) or visible rows / 2 floored
#define CGameFrog_playerstartrow 4

#define CGameFrog_speeddeviation 0.25*yscale

#define CGameFrog_rowtypewaterstart 0
#define CGameFrog_rowtypewaterend 2
#define CGameFrog_rowtyperoadstart 3
#define CGameFrog_rowtyperoadend 7
#define CGameFrog_maxobjects 175

#define CGameFrog_lenrowtypes 9

struct CGameFrog {

	CGameBase *GameBase;

	SRowType[CGameFrog_lenrowtypes] rowtypes;
	float[CGameFrog_lenlevelincspeeds] levelincspeeds;
	int[CGameFrog_lenlevelincspeeds] levelincspawns;

	float worldspeed;
	int nextrowtype;
	int nextrowtypecountmax;
	int nextrowtypecount;
	int numobjects;
	int previd;
	int prevrowtype;
	int playerdeath;
	int playerdeathtime;
	int playermaxrow;
	int playerrow;
	int plantsspawned;
	int rowsspawned;
	int dolevelinc;
	bool uppressed;
	bool downpressed;
	bool leftpressed;
	bool rightpressed;

	CSpriteObject[CGameFrog_maxobjects] objects;
	CSpriteObject player;
	SObjectInfo objectinfo;

	SDL_Point*[CGameFrog_idcount] TzCache;

	int MusMusic, SfxSucces, SfxCollect, SfxDie, SfxPlayerMove;

	int background;
	int spritesheetfrog;
	int spritesheetbackground;
	int spritesheetcar1;
	int spritesheetcar2;
	int spritesheetcar3;
	int spritesheetcar4;
	int spritesheetcar5;

	int spritesheetplant;
	int spritesheetfruit1;
	int spritesheetfruit2;
	int spritesheetfruit3;
};


CGameFrog* Create_CGameFrog()
{
	CSprites_SetSpriteMax(CGameFrog_maxobjects);
	CGameFrog* GameFrog = (CGameFrog*) malloc(sizeof(CGameFrog));
	GameFrog->GameBase = Create_CGameBase(GSFrog, true);
	GameFrog->MusMusic = -1;
	GameFrog->SfxDie = -1;
	GameFrog->SfxCollect = -1;
	GameFrog->SfxPlayerMove = -1;
	GameFrog->prevrowtype = -1;
	GameFrog->GameBase->playfieldwidth = (int)(CGameFrog_numcols * CGameFrog_playerspeed);
	GameFrog->GameBase->playfieldheight = (int)(CGameFrog_numrows * CGameFrog_playerspeed);
	GameFrog->GameBase->screenleft = (ScreenWidth - GameFrog->GameBase->playfieldwidth) / 2;
	GameFrog->GameBase->screenright = GameFrog->GameBase->screenleft + GameFrog->GameBase->playfieldwidth;
	GameFrog->GameBase->screentop = ScreenHeight - GameFrog->GameBase->playfieldheight;
	GameFrog->GameBase->screenbottom = ScreenHeight;
	GameFrog->uppressed = false;
	GameFrog->downpressed = false;
	GameFrog->leftpressed = false;
	GameFrog->rightpressed = false;

	GameFrog->rowtypes[0].type = CGameFrog_rowtypewater;
	GameFrog->rowtypes[0].backgroundtile = 6;
	GameFrog->rowtypes[0].backgroundtileend = 10;
	GameFrog->rowtypes[0].deadlyground = true;
	GameFrog->rowtypes[0].id = CGameFrog_idenemyplant;
	GameFrog->rowtypes[0].speed = 2.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[0].minspace = 2;
	GameFrog->rowtypes[0].maxrepeats = 3;

	GameFrog->rowtypes[1].type = CGameFrog_rowtypewater;
	GameFrog->rowtypes[1].backgroundtile = 6;
	GameFrog->rowtypes[1].backgroundtileend = 10;
	GameFrog->rowtypes[1].deadlyground = true;
	GameFrog->rowtypes[1].id = CGameFrog_idenemyplant;
	GameFrog->rowtypes[1].speed = 3.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[1].minspace = 3;
	GameFrog->rowtypes[1].maxrepeats = 2;

	GameFrog->rowtypes[2].type = CGameFrog_rowtypewater;
	GameFrog->rowtypes[2].backgroundtile = 6;
	GameFrog->rowtypes[2].backgroundtileend = 10;
	GameFrog->rowtypes[2].deadlyground = true;
	GameFrog->rowtypes[2].id = CGameFrog_idenemyplant;
	GameFrog->rowtypes[2].speed = 4.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[2].minspace = 4;
	GameFrog->rowtypes[2].maxrepeats = 3;

	GameFrog->rowtypes[3].type = CGameFrog_rowtyperoad;
	GameFrog->rowtypes[3].backgroundtile = 0;
	GameFrog->rowtypes[3].backgroundtileend = 0;
	GameFrog->rowtypes[3].deadlyground = false;
	GameFrog->rowtypes[3].id = CGameFrog_idenemycar1;
	GameFrog->rowtypes[3].speed = 2.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[3].minspace = 4;
	GameFrog->rowtypes[3].maxrepeats = 2;

	GameFrog->rowtypes[4].type = CGameFrog_rowtyperoad;
	GameFrog->rowtypes[4].backgroundtile = 0;
	GameFrog->rowtypes[4].backgroundtileend = 0;
	GameFrog->rowtypes[4].deadlyground = false;
	GameFrog->rowtypes[4].id = CGameFrog_idenemycar2;
	GameFrog->rowtypes[4].speed = 2.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[4].minspace = 3;
	GameFrog->rowtypes[4].maxrepeats = 2;

	GameFrog->rowtypes[5].type = CGameFrog_rowtyperoad;
	GameFrog->rowtypes[5].backgroundtile = 0;
	GameFrog->rowtypes[5].backgroundtileend = 0;
	GameFrog->rowtypes[5].deadlyground = false;
	GameFrog->rowtypes[5].id = CGameFrog_idenemycar3;
	GameFrog->rowtypes[5].speed = 8.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[5].minspace = CGameFrog_numrows;
	GameFrog->rowtypes[5].maxrepeats = 1;

	GameFrog->rowtypes[6].type = CGameFrog_rowtyperoad;
	GameFrog->rowtypes[6].backgroundtile = 0;
	GameFrog->rowtypes[6].backgroundtileend = 0;
	GameFrog->rowtypes[6].deadlyground = false;
	GameFrog->rowtypes[6].id = CGameFrog_idenemycar4;
	GameFrog->rowtypes[6].speed = 2.5*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[6].minspace = 4;
	GameFrog->rowtypes[6].maxrepeats = 2;
	
	GameFrog->rowtypes[7].type = CGameFrog_rowtyperoad;
	GameFrog->rowtypes[7].backgroundtile = 0;
	GameFrog->rowtypes[7].backgroundtileend = 0;
	GameFrog->rowtypes[7].deadlyground = false;
	GameFrog->rowtypes[7].id = CGameFrog_idenemycar5;
	GameFrog->rowtypes[7].speed = 3.5*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[7].minspace = 3;
	GameFrog->rowtypes[7].maxrepeats = 2;
	
	GameFrog->rowtypes[8].type = CGameFrog_rowtypesafety;
	GameFrog->rowtypes[8].backgroundtile = 12;
	GameFrog->rowtypes[8].backgroundtileend = 12;
	GameFrog->rowtypes[8].deadlyground = false;
	GameFrog->rowtypes[8].id = CGameFrog_idnone;
	GameFrog->rowtypes[8].speed = 3.0*yscale*CGameFrog_NumLogicFrames;
	GameFrog->rowtypes[8].minspace = 2;
	GameFrog->rowtypes[8].maxrepeats = 2;

	GameFrog->levelincspeeds[0] = 0.0;
	GameFrog->levelincspeeds[1] = 0.25*CGameFrog_ExtraScale*yscale * CGameFrog_NumLogicFrames;
	GameFrog->levelincspeeds[2] = 0.5*CGameFrog_ExtraScale*yscale * CGameFrog_NumLogicFrames;
	GameFrog->levelincspeeds[3] = 1.0*CGameFrog_ExtraScale*yscale * CGameFrog_NumLogicFrames;
	GameFrog->levelincspeeds[4] = 1.5*CGameFrog_ExtraScale*yscale * CGameFrog_NumLogicFrames;

	GameFrog->levelincspawns[0] = 30;
	GameFrog->levelincspawns[1] = 90;
	GameFrog->levelincspawns[2] = 240;
	GameFrog->levelincspawns[3] = 570;
	GameFrog->levelincspawns[4] = 0;

	for (int i= 0; i < CGameFrog_idcount; i++)
		GameFrog->TzCache[i] = NULL;

	for (int i= 0; i < CGameFrog_maxobjects; i++)
		Initialize_CSpriteObject(&GameFrog->objects[i]);
	Initialize_CSpriteObject(&GameFrog->player);

	return GameFrog;
}

void Destroy_CGameFrog(CGameFrog* GameFrog)
{
	for (int i= 0; i < CGameFrog_idcount; i++)
		if(GameFrog->TzCache[i])
			free(GameFrog->TzCache[i]);

	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameFrog->GameBase);
	free(GameFrog);
	GameFrog = NULL;
}


//objects ----------------------------------------------------------------------------------------------------------------

void CGameFrog_destroyobject(CGameFrog* GameFrog, int index)
{
	if (GameFrog->objects[index].alive)
	{
		CSprites_RemoveSprite(GameFrog->objects[index].spr);
		GameFrog->objects[index].alive = false;
		GameFrog->numobjects -=1;
	}
}


void CGameFrog_destroyallobjects(CGameFrog* GameFrog)
{
	for (int i = 0; i < CGameFrog_maxobjects; i++)
		CGameFrog_destroyobject(GameFrog,i);
}


int CGameFrog_createobject(CGameFrog* GameFrog, int rownr, int col, int id, int arowtype, float speed, int dir, int startobjectindex)
{
	SDL_Point *tz;
	Vec2F scale;
	Vec2F visualscale;
	int tilenr;
	int endtilenr;
	CSpriteObject *object;
	int result = 0;

	for (int i = startobjectindex; i < CGameFrog_maxobjects; i++)
	{
		if (!GameFrog->objects[i].alive)
		{
			object = &(GameFrog->objects)[i];
			Initialize_CSpriteObject(object);

			object->spr = CSprites_CreateSprite();
			switch(id)
			{

				case CGameFrog_idwater:
				case CGameFrog_idroad:
				case CGameFrog_idgrass:
					// tilenr = GameFrog->rowtypes[arowtype].backgroundtile;
					// endtilenr = GameFrog->rowtypes[arowtype].backgroundtileend;
					// CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetbackground,5,3);
					// tz = CSprites_TileSize(object->spr);
					// CSprites_SetSpriteAnimation(object->spr, tilenr, endtilenr, 6);
					// CSprites_SetSpriteDepth(object->spr, 0);
					// //col == 0 is hack to have less drawing calls for the sprites
					// //i made the road water and grass tile equal in size as the width needed for a row
					// //so we only need the 1st tile to be visible
					// //however i was not able to not create the other sprite parts somehow
					// //it introduced a bug with row generating and i have not figured out yet
					// //whats causing that so this is a nasty workaround but still have an optimazation
					// //of only doing 1 big draw call for the road / water per row instead of multiple small ones
					// CSprites_SetSpriteVisibility(object->spr, col == 0);
					// object->vel.x = 0.0;
					// object->vel.y = 0.0;
					// //scale.x = {CGameFrog_playerspeed / tz.x, CGameFrog_playerspeed / tz.y}
					// scale.x = 6.0;
					// scale.y = CGameFrog_playerspeed / tz->y;
					// visualscale = scale;
					// object->tz.x = (int)(tz->x * scale.x);
					// object->tz.y = (int)(tz->y * scale.y);

					tilenr = GameFrog->rowtypes[arowtype].backgroundtile;
					endtilenr = GameFrog->rowtypes[arowtype].backgroundtileend;
					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetbackground,6,3);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, endtilenr, 6);
					CSprites_SetSpriteDepth(object->spr, 0);
					object->vel.x = 0.0;
					object->vel.y = 0.0;
					scale.x = CGameFrog_playerspeed / tz->x;
					scale.y = CGameFrog_playerspeed / tz->y;
					visualscale = scale;
					object->tz.x = tz->x * scale.x;
					object->tz.y = tz->y * scale.y;
					break;
				case CGameFrog_idenemycar1:
					tilenr = 0;
					if (dir == -1)
						tilenr = 1;

					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetcar1, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 3);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->x;
					scale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->y;
					visualscale = scale;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;
				case CGameFrog_idenemycar2:
					tilenr = 0;
					if (dir == -1)
						tilenr = 1;

					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetcar2, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 3);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->x;
					scale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->y;
					visualscale = scale;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;
				case CGameFrog_idenemycar3:
					tilenr = 0;
					if (dir == -1)
						tilenr = 1;

					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetcar3, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 3);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->x;
					scale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->y;
					visualscale = scale;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;

				case CGameFrog_idenemycar4:
					tilenr = 0;
					if (dir == -1)
						tilenr = 1;

					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetcar4, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 3);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->x;
					scale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->y;
					visualscale = scale;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;
				
				case CGameFrog_idenemycar5:
					tilenr = 0;
					if (dir == -1)
						tilenr = 1;

					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetcar5, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 3);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->x;
					scale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 6)) / tz->y;
					visualscale = scale;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;
				case CGameFrog_idenemyplant:
					tilenr = 1;
					CSprites_SetSpriteImageTiles(object->spr, &GameFrog->spritesheetplant, 2, 1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];

					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					CSprites_SetSpriteDepth(object->spr, 1);
					//scale = {(CGameFrog_playerspeed - int(CGameFrog_playerspeed / 48)) / tz.x, (CGameFrog_playerspeed - int(CGameFrog_playerspeed / 48)) / tz.y}
					scale.x = CGameFrog_playerspeed / tz->x;
					scale.y = CGameFrog_playerspeed / tz->y;
					visualscale = scale;
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					object->tz.x = (int)(tz->x * scale.x);
					object->tz.y = (int)(tz->y * scale.y);
					break;
				case CGameFrog_idcherry:
					tilenr = 0;

					CSprites_SetSpriteImage(object->spr, &GameFrog->spritesheetfruit1);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = CGameFrog_playerspeed / tz->x;
					scale.y = CGameFrog_playerspeed / tz->y;
					visualscale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->x;
					visualscale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->y;
					CSprites_SetSpriteDepth(object->spr, 3);
					break;
				case CGameFrog_idlemon:
					tilenr = 0;

					CSprites_SetSpriteImage(object->spr, &GameFrog->spritesheetfruit2);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = CGameFrog_playerspeed / tz->x;
					scale.y = CGameFrog_playerspeed / tz->y;
					visualscale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->x;
					visualscale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->y;
					CSprites_SetSpriteDepth(object->spr, 3);
					break;
				case CGameFrog_idapple:
					tilenr = 0;

					CSprites_SetSpriteImage(object->spr, &GameFrog->spritesheetfruit3);
					if(GameFrog->TzCache[id] == NULL)
						GameFrog->TzCache[id] = CSprites_TileSize(object->spr);
					tz = GameFrog->TzCache[id];
					CSprites_SetSpriteAnimation(object->spr, tilenr, tilenr, 0);
					object->vel.x = dir*speed;
					object->vel.y = 0.0;
					scale.x = CGameFrog_playerspeed / tz->x;
					scale.y = CGameFrog_playerspeed / tz->y;
					visualscale.x = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->x;
					visualscale.y = (CGameFrog_playerspeed - (CGameFrog_playerspeed / 2)) / tz->y;
					CSprites_SetSpriteDepth(object->spr, 3);
					break;
				default:
					break;
			}
			//setSpriteRotation(GameFrog->object->s[i].spr, 0)
			object->spr->sxscale = visualscale.x;
			object->spr->syscale = visualscale.y;
			object->tz.x =(int)(tz->x * scale.x);
			object->tz.y =(int)(tz->y * scale.y);
			object->pos.x = GameFrog->GameBase->screenleft + (col * CGameFrog_playerspeed) + (CGameFrog_playerspeed / 2);
			object->pos.y = GameFrog->GameBase->screenbottom - ((rownr+1) * CGameFrog_playerspeed) + (CGameFrog_playerspeed / 2);
			object->spr->x = (float)((int)object->pos.x);
			object->spr->y = (float)((int)object->pos.y);
			object->rowtype = arowtype;
			object->id = id;
			object->alive = true;
			GameFrog->numobjects +=1;
			result = i;
			break;
		}
	}
	return result;
}

void CGameFrog_createobjectrow(CGameFrog* GameFrog, int rownr, int arowtype)
{
	int type = GameFrog->rowtypes[arowtype].type;
	int minspace = GameFrog->rowtypes[arowtype].minspace;
	int maxrepeats = 1 + (rand() % (GameFrog->rowtypes[arowtype].maxrepeats));
	int id = GameFrog->rowtypes[arowtype].id;
	int rowtypemaxrepeats = GameFrog->rowtypes[arowtype].maxrepeats;
	int repeats = 0;
	int lastplaced = 0;
	int dir = rand() % 2;
	if (dir == 0)
		dir = -1;

	float speed = (GameFrog->rowtypes[arowtype].speed - CGameFrog_speeddeviation) + ((rand() % (int)(CGameFrog_speeddeviation*100)/100));
	int index = 0;
	for (int x = 0; x < CGameFrog_numcols; x++)
	{
		if (type == CGameFrog_rowtyperoad)
		{
			index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idroad, arowtype, 0, 0, index);

			if ((x - lastplaced > minspace) || (repeats < maxrepeats))
			{
				if (x - lastplaced > minspace)
				{
					maxrepeats = 1 + (rand() % rowtypemaxrepeats);
					repeats = 0;
				}
				lastplaced = x;
				repeats += 1;
				index = CGameFrog_createobject(GameFrog,rownr, x, id, arowtype, speed, dir, index);
			}
		}
		else
		{
			if (type == CGameFrog_rowtypewater)
			{
				index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idwater, arowtype, 0, 0, index);
				if ((x - lastplaced > minspace) || (repeats < maxrepeats))
				{
					if (x - lastplaced > minspace)
					{
						maxrepeats = 1 + (rand()% rowtypemaxrepeats);
						repeats = 0;
					}
					lastplaced = x;
					repeats += 1;
					index = CGameFrog_createobject(GameFrog,rownr, x, id, arowtype, speed, dir, index);
					GameFrog->plantsspawned += 1;

					if (GameFrog->plantsspawned % CGameFrog_cherryspawntrigger == 0)
						index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idcherry, arowtype, speed, dir, index);

					if (GameFrog->plantsspawned % CGameFrog_lemonspawntrigger == 0)
						index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idlemon, arowtype, speed, dir, index);

					if (GameFrog->plantsspawned % CGameFrog_applespawntrigger == 0)
						index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idapple, arowtype, speed, dir, index);
				}
			}
			else
			{
				if (type == CGameFrog_rowtypesafety)
					index = CGameFrog_createobject(GameFrog,rownr, x, CGameFrog_idgrass, arowtype, 0, 0, index);
			}
		}
	}
}

void CGameFrog_createobjects(CGameFrog* GameFrog, bool initialize)
{
	int rowtype = GameFrog->prevrowtype;
	int i = 0;
	int r = 0;

	if (initialize)
	{
		GameFrog->nextrowtype = CGameFrog_rowtyperoad;
		GameFrog->plantsspawned = 0;
		GameFrog->nextrowtypecountmax = rand() % (CGameFrog_maxrowsbeforesafetyrow+1);
		GameFrog->nextrowtypecount = 0;
		while (i < CGameFrog_numrows)
		{
			if (i < CGameFrog_playerstartrow)
				CGameFrog_createobjectrow(GameFrog,i, CGameFrog_lenrowtypes - 1);
			else
			{
				if (GameFrog->nextrowtype == CGameFrog_rowtyperoad)
				{
					rowtype = CGameFrog_rowtyperoadstart + rand() % (CGameFrog_rowtyperoadend - CGameFrog_rowtyperoadstart + 1);
					if (rowtype == GameFrog->prevrowtype)
					{
						rowtype += 1;
						if (rowtype > CGameFrog_rowtyperoadend)
							rowtype = CGameFrog_rowtyperoadstart;
					}
					GameFrog->prevrowtype = rowtype;
				}
				else
				{
					if (GameFrog->nextrowtype == CGameFrog_rowtypewater)
					{
						rowtype = CGameFrog_rowtypewaterstart + rand() % (CGameFrog_rowtypewaterend - CGameFrog_rowtypewaterstart + 1);
						if (rowtype == GameFrog->prevrowtype)
						{
							rowtype += 1;
							if (rowtype > CGameFrog_rowtypewaterend)
								rowtype = CGameFrog_rowtypewaterstart;
						}
					}

					GameFrog->prevrowtype = rowtype;
				}

				if(GameFrog->nextrowtypecount == GameFrog->nextrowtypecountmax)
				{
					rowtype = CGameFrog_lenrowtypes -1;
					GameFrog->nextrowtypecountmax = 2+(rand() %(CGameFrog_maxrowsbeforesafetyrow-1));
					GameFrog->nextrowtypecount = 0;

					r = rand() % 2;

					if (r == 0)
						GameFrog->nextrowtype = CGameFrog_rowtyperoad;
					else
					{
						if (r == 1)
							GameFrog->nextrowtype = CGameFrog_rowtypewater;

					}
				}
				else
					GameFrog->nextrowtypecount += 1;

				CGameFrog_createobjectrow(GameFrog,i, rowtype);

			}
			i+=1;

		}
	}
	else
	{
		i = CGameFrog_visiblerows;

		while (i < CGameFrog_numrows)
		{
			if (GameFrog->nextrowtype == CGameFrog_rowtyperoad)
			{
				rowtype = CGameFrog_rowtyperoadstart + (rand() % (CGameFrog_rowtyperoadend - CGameFrog_rowtyperoadstart + 1));
				if (rowtype == GameFrog->prevrowtype)
				{
					rowtype += 1;
					if (rowtype > CGameFrog_rowtyperoadend)
						rowtype = CGameFrog_rowtyperoadstart;
				}
				GameFrog->prevrowtype = rowtype;
			}
			else
			{
				if(GameFrog->nextrowtype == CGameFrog_rowtypewater)
				{
					rowtype = CGameFrog_rowtypewaterstart + (rand() % (CGameFrog_rowtypewaterend - CGameFrog_rowtypewaterstart + 1));
					if(rowtype == GameFrog->prevrowtype)
					{
						rowtype += 1;
						if (rowtype > CGameFrog_rowtypewaterend)
							rowtype = CGameFrog_rowtypewaterstart;
					}

					GameFrog->prevrowtype = rowtype;
				}
			}

			if(GameFrog->nextrowtypecount == GameFrog->nextrowtypecountmax)
			{
				rowtype = CGameFrog_lenrowtypes -1;
				GameFrog->nextrowtypecountmax = 2+(rand() % (CGameFrog_maxrowsbeforesafetyrow-1));
				//for debugging finding max objects count
				//GameFrog->nextrowtypecountmax = 4
				GameFrog->nextrowtypecount = 0;
				r = rand() % 2;
				if (r == 0)
					GameFrog->nextrowtype = CGameFrog_rowtyperoad;
				else
				{
					if (r == 1)
						GameFrog->nextrowtype = CGameFrog_rowtypewater;
				}
			}
			else
				GameFrog->nextrowtypecount += 1;
			CGameFrog_createobjectrow(GameFrog,i, rowtype);
			i += 1;
		}
	}
}


void CGameFrog_updateobjects(CGameFrog* GameFrog)
{
	GameFrog->objectinfo.mostleft = -1;
	GameFrog->objectinfo.mostright = -1;
	GameFrog->objectinfo.mostbottom = -1;
	GameFrog->objectinfo.mosttop = -1;

	float x1 = (float)(GameFrog->GameBase->screenright + 1);
	float x2 = (float)(GameFrog->GameBase->screenleft - 1);
	float y1 = (float)(GameFrog->GameBase->screentop - 1);
	float y2 = (float)(GameFrog->GameBase->screenbottom + 1);
	bool playermoved = false;
	int id = -1;
	bool plantcol = false;
	bool stopcheckplantcol = false;

	for (int i = 0; i < CGameFrog_maxobjects; i++)
	{
		if(GameFrog->objects[i].alive)
		{
			//if (floatequal(GameFrog->objects[i].pos.y,GameFrog->player.pos.y))
			if(true)
			{
				if (CSprites_DetectSpriteCollision(GameFrog->objects[i].spr, GameFrog->player.spr))
				{
					id = GameFrog->objects[i].id;

					if (!playermoved && (id == CGameFrog_idenemyplant) && !GameFrog->playerdeath &&
						(GameFrog->player.pos.x - GameFrog->player.tz.x / 4 <= GameFrog->objects[i].pos.x + GameFrog->objects[i].tz.x / 2) &&
						(GameFrog->player.pos.x + GameFrog->player.tz.x / 4 >= GameFrog->objects[i].pos.x - GameFrog->objects[i].tz.x / 2))
						{
							GameFrog->player.pos = GameFrog->objects[i].pos;
							GameFrog->player.spr->x = (float)((int)GameFrog->player.pos.x);
							GameFrog->player.spr->y = (float)((int)GameFrog->player.pos.y);
							if ((GameFrog->player.pos.x < GameFrog->GameBase->screenleft) || (GameFrog->player.pos.x > GameFrog->GameBase->screenright))
							{
								if(!GameFrog->playerdeath && EnablePlayerDeath)
								{
									GameFrog->playerdeath = true ;
									GameFrog->playerdeathtime = getCurrentTimeMilliseconds() + 500;
									CAudio_PlaySound(GameFrog->SfxDie, 0);
									if (!(GameMode == GMGame))
										CGame_AddToScore(-150);
								}
							}

							playermoved = true;
							plantcol = true;
						}

					if ((id == CGameFrog_idenemycar1) || (id == CGameFrog_idenemycar2) || (id == CGameFrog_idenemycar3) ||
						(id == CGameFrog_idenemycar4) || (id == CGameFrog_idenemycar5))
					{
						if(!GameFrog->playerdeath && EnablePlayerDeath)
						{
							GameFrog->playerdeath = true;
							GameFrog->playerdeathtime = getCurrentTimeMilliseconds() + 500;
							CAudio_PlaySound(GameFrog->SfxDie, 0);
							if (!(GameMode == GMGame))
								CGame_AddToScore(-150);
						}
					}
					else
					{
						if ((id == CGameFrog_idroad) || (id == CGameFrog_idgrass))
							playermoved = true;
						else
						{
							if (id == CGameFrog_idlemon)
							{
								CGame_AddToScore(CGameFrog_lemonscore);
								CGameFrog_destroyobject(GameFrog,i);
								CAudio_PlaySound(GameFrog->SfxCollect, 0);
							}
							else
							{
								if (id == CGameFrog_idapple)
								{
									CGame_AddToScore(CGameFrog_applescore);
									CGameFrog_destroyobject(GameFrog,i);
									CAudio_PlaySound(GameFrog->SfxCollect, 0);
								}
								else
								{
									if (id == CGameFrog_idcherry)
									{
										CGame_AddToScore(CGameFrog_cherryscore);
										CGameFrog_destroyobject(GameFrog,i);
										CAudio_PlaySound(GameFrog->SfxCollect, 0);
									}
								}
							}
						}
					}

					if ((!stopcheckplantcol) && (!plantcol) && (id == CGameFrog_idwater) && (!GameFrog->playerdeath))
					{
						stopcheckplantcol = true;
						for (int j = i + 1; j < CGameFrog_maxobjects;j++)
						{
							if ((GameFrog->objects[j].alive) /*&& floatequal(GameFrog->objects[j].pos.y,GameFrog->player.pos.y)*/)
							{
								if(CSprites_DetectSpriteCollision(GameFrog->objects[j].spr, GameFrog->player.spr))
								{
									if (id == CGameFrog_idenemyplant)
									{
										if ((GameFrog->player.pos.x - GameFrog->player.tz.x / 4 <= GameFrog->objects[i].pos.x + GameFrog->objects[i].tz.x / 2) &&
											(GameFrog->player.pos.x + GameFrog->player.tz.x / 4 >= GameFrog->objects[i].pos.x - GameFrog->objects[i].tz.x / 2))
										{
											//GameFrog->player.pos = GameFrog->objects[i].pos //GameFrog->player.pos + GameFrog->objects[i].vel
											plantcol = true;
											break;
										}
									}
								}
							}
						}
					}
				}
			}

			if (GameFrog->objects[i].alive)
			{
				GameFrog->objects[i].pos.y = GameFrog->objects[i].pos.y + GameFrog->worldspeed + GameFrog->levelincspeeds[GameFrog->GameBase->level-1];
				if (GameFrog->objects[i].pos.y - GameFrog->objects[i].tz.y / 2 > GameFrog->GameBase->screenbottom)
					CGameFrog_destroyobject(GameFrog,i);
				else
				{
					GameFrog->objects[i].pos.x = GameFrog->objects[i].pos.x + GameFrog->objects[i].vel.x;
					GameFrog->objects[i].pos.y = GameFrog->objects[i].pos.y + GameFrog->objects[i].vel.y;
					if (GameFrog->objects[i].vel.x < 0)
					{
						if (GameFrog->objects[i].pos.x + GameFrog->objects[i].tz.x / 2 < GameFrog->GameBase->screenleft)
							GameFrog->objects[i].pos.x = GameFrog->GameBase->screenright - (GameFrog->GameBase->screenleft - GameFrog->objects[i].pos.x) + GameFrog->objects[i].tz.x / 2 + GameFrog->objects[i].tz.x / 2;
					}
					else
					{
						if (GameFrog->objects[i].pos.x - GameFrog->objects[i].tz.x / 2 > GameFrog->GameBase->screenright)
							GameFrog->objects[i].pos.x = GameFrog->GameBase->screenleft + (GameFrog->objects[i].pos.x - GameFrog->GameBase->screenright) - GameFrog->objects[i].tz.x / 2 - GameFrog->objects[i].tz.x / 2;
					}
					GameFrog->objects[i].spr->x = (float)((int)GameFrog->objects[i].pos.x);
					GameFrog->objects[i].spr->y = (float)((int)GameFrog->objects[i].pos.y);

					if ((GameFrog->objects[i].id == CGameFrog_idwater) || (GameFrog->objects[i].id == CGameFrog_idroad) || (GameFrog->objects[i].id == CGameFrog_idgrass))
					{
						if (GameFrog->objects[i].pos.x < x1)
						{
							x1 = GameFrog->objects[i].pos.x;
							GameFrog->objectinfo.mostleft = i;
						}
						else
						{
							if (GameFrog->objects[i].pos.x > x2)
							{
								x2 = GameFrog->objects[i].pos.x;
								GameFrog->objectinfo.mostright = i;
							}
						}

						if (GameFrog->objects[i].pos.y > y1)
						{
							y1 = GameFrog->objects[i].pos.y;
							GameFrog->objectinfo.mostbottom = i;
						}
						else
						{
							if (GameFrog->objects[i].pos.y < y2)
							{
								y2 = GameFrog->objects[i].pos.y;
								GameFrog->objectinfo.mosttop = i;
							}
						}
					}
				}
			}
		}
	}

	if (GameFrog->objectinfo.mosttop > -1)
	{
		if ((GameFrog->objects[GameFrog->objectinfo.mosttop].pos.y - GameFrog->objects[GameFrog->objectinfo.mosttop].tz.y / 2 <= (GameFrog->GameBase->screenbottom - (CGameFrog_visiblerows * CGameFrog_playerspeed) + epsilion)) &&
			(GameFrog->objects[GameFrog->objectinfo.mosttop].pos.y - GameFrog->objects[GameFrog->objectinfo.mosttop].tz.y / 2 >= (GameFrog->GameBase->screenbottom - (CGameFrog_visiblerows * CGameFrog_playerspeed) - epsilion)))
		{
			CGameFrog_createobjects(GameFrog,false);
			GameFrog->rowsspawned += 1;
			if (GameFrog->rowsspawned == GameFrog->levelincspawns[GameFrog->GameBase->level-1])
				GameFrog->dolevelinc = true;
		}
	}

	if (!playermoved && !GameFrog->playerdeath && EnablePlayerDeath)
	{
		GameFrog->playerdeath = true;
		GameFrog->playerdeathtime = getCurrentTimeMilliseconds() + 500;
		CAudio_PlaySound(GameFrog->SfxDie, 0);
		if (!(GameMode == GMGame))
			CGame_AddToScore(-150);
	}
}



//player ----------------------------------------------------------------------------------------------------------------

void CGameFrog_destroyplayer(CGameFrog* GameFrog)
{
	CSprites_RemoveSprite(GameFrog->player.spr);
	GameFrog->player.alive = false;
}

void CGameFrog_createplayer(CGameFrog* GameFrog)
{
	GameFrog->player.spr = CSprites_CreateSprite();
	CSprites_SetSpriteDepth(GameFrog->player.spr, 2);
	CSprites_SetSpriteImageTiles(GameFrog->player.spr, &GameFrog->spritesheetfrog, 3, 4);
	CSprites_SetSpriteAnimation(GameFrog->player.spr, 11, 11, 10);
	SDL_Point* tz = CSprites_TileSize(GameFrog->player.spr);

	Vec2F scale = {((CGameFrog_playerspeed -8*xscale)) / tz->x, ((CGameFrog_playerspeed -8*yscale)) / tz->y};
	GameFrog->player.spr->sxscale =  scale.x;
	GameFrog->player.spr->syscale =  scale.y;
	CSprites_SetSpriteCollisionShape(GameFrog->player.spr, SHAPE_BOX, 20.0, 20.0, 0, 1.0, 1.0);
	GameFrog->player.tz.x = (int)(tz->x * scale.x);
	GameFrog->player.tz.y = (int)(tz->y * scale.y);
	GameFrog->player.pos.x = GameFrog->GameBase->screenleft + (CGameFrog_numcols / 2) * CGameFrog_playerspeed + CGameFrog_playerspeed / 2;
	GameFrog->player.pos.y = GameFrog->GameBase->screenbottom - CGameFrog_playerstartrow * CGameFrog_playerspeed + CGameFrog_playerspeed / 2;
	GameFrog->GameBase->HealthPoints = 3;
	GameFrog->player.spr->x = GameFrog->player.pos.x;
	GameFrog->player.spr->y = GameFrog->player.pos.y;
	GameFrog->playermaxrow = 0;
	GameFrog->playerrow = 0;
	GameFrog->player.alive = true;
	free(tz);
}

void CGameFrog_updateplayer(CGameFrog* GameFrog)
{
	GameFrog->player.spr->show = GameFrog->player.alive;
	if (GameFrog->player.alive)
	{
		if (GameFrog->leftpressed)
		{
			CSprites_SetSpriteAnimation(GameFrog->player.spr, 4, 4, 10);

			if ((GameFrog->player.pos.x - GameFrog->player.tz.x / 2) - CGameFrog_playerspeed >= GameFrog->GameBase->screenleft)
			{
				if ((GameFrog->player.pos.x - GameFrog->player.tz.x / 2) - CGameFrog_playerspeed >= 0)
				{
					GameFrog->player.pos.x -= CGameFrog_playerspeed;
					CAudio_PlaySound(GameFrog->SfxPlayerMove, 0);
				}
			}
		}

		if (GameFrog->rightpressed)
		{
			CSprites_SetSpriteAnimation(GameFrog->player.spr, 7, 7, 10);

			if ((GameFrog->player.pos.x + GameFrog->player.tz.x / 2) + CGameFrog_playerspeed <= GameFrog->GameBase->screenright)
			{
				if ((GameFrog->player.pos.x + GameFrog->player.tz.x / 2) + CGameFrog_playerspeed <= ScreenWidth)
				{
					GameFrog->player.pos.x += CGameFrog_playerspeed;
					CAudio_PlaySound(GameFrog->SfxPlayerMove, 0);
				}
			}
		}

		if (GameFrog->uppressed)
		{
			CSprites_SetSpriteAnimation(GameFrog->player.spr, 11, 11, 10);

			if ((GameFrog->player.pos.y - GameFrog->player.tz.y / 2) - CGameFrog_playerspeed >= GameFrog->GameBase->screentop)
			{
				if ((GameFrog->player.pos.y - GameFrog->player.tz.y / 2) - CGameFrog_playerspeed >= 0)
				{
					GameFrog->player.pos.y -= CGameFrog_playerspeed;
					GameFrog->playerrow += 1;
					if (GameFrog->playerrow > GameFrog->playermaxrow)
					{
						CGame_AddToScore(20);
						GameFrog->playermaxrow = GameFrog->playerrow;
					}
					CAudio_PlaySound(GameFrog->SfxPlayerMove, 0);
				}
			}
		}

		if (GameFrog->downpressed)
		{
			CSprites_SetSpriteAnimation(GameFrog->player.spr, 2, 2, 10);

			if ((GameFrog->player.pos.y + GameFrog->player.tz.y / 2) + CGameFrog_playerspeed <= GameFrog->GameBase->screenbottom)
			{
				if ((GameFrog->player.pos.y + GameFrog->player.tz.y / 2) + CGameFrog_playerspeed <= ScreenHeight)
				{
					GameFrog->player.pos.y += CGameFrog_playerspeed;
					GameFrog->playerrow -= 1;
				}
				CAudio_PlaySound(GameFrog->SfxPlayerMove, 0);
			}
		}

		GameFrog->player.pos.y = GameFrog->player.pos.y + GameFrog->worldspeed + GameFrog->levelincspeeds[GameFrog->GameBase->level-1];
		GameFrog->player.spr->x = (float)((int)(floor(GameFrog->player.pos.x)));
		GameFrog->player.spr->y = (float)((int)(floor(GameFrog->player.pos.y)));

		if (GameFrog->player.pos.y >= GameFrog->GameBase->screenbottom)
		{
			if(!GameFrog->playerdeath && EnablePlayerDeath)
			{
				GameFrog->playerdeath = true;
				GameFrog->playerdeathtime = getCurrentTimeMilliseconds() + 500;
				CAudio_PlaySound(GameFrog->SfxDie, 0);
				if (!(GameMode == GMGame))
					CGame_AddToScore(-150);
			}
		}
	}
	else
	{
		if (GameFrog->player.freeze > 0)
			GameFrog->player.freeze -= 1;
		else
			GameFrog->player.alive = true;
	}
}

//background ----------------------------------------------------------------------------------------------------------------

void CGameFrog_DrawBackground(CGameFrog* GameFrog)
{
	//if(EnablePlayerDeath)
		CImage_DrawImage( GameFrog->background, 0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------


void CGameFrog_LoadSound(CGameFrog* GameFrog)
{
	GameFrog->SfxDie = CAudio_LoadSound("common/die");
	GameFrog->SfxCollect = CAudio_LoadSound("common/coin");
	GameFrog->SfxPlayerMove = CAudio_LoadSound("frog/move");
	GameFrog->MusMusic = CAudio_LoadMusic("frog/music");
}

void CGameFrog_UnLoadSound(CGameFrog* GameFrog)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameFrog->MusMusic);
	CAudio_UnLoadSound(GameFrog->SfxDie);
	CAudio_UnLoadSound(GameFrog->SfxCollect);
	CAudio_UnLoadSound(GameFrog->SfxPlayerMove);
}

void CGameFrog_UnloadGraphics(CGameFrog* GameFrog)
{
	CImage_UnLoadImage(GameFrog->background);
	CImage_UnLoadImage(GameFrog->spritesheetfrog);
	CImage_UnLoadImage(GameFrog->spritesheetbackground);
	CImage_UnLoadImage(GameFrog->spritesheetcar1);
	CImage_UnLoadImage(GameFrog->spritesheetcar2);
	CImage_UnLoadImage(GameFrog->spritesheetcar3);
	CImage_UnLoadImage(GameFrog->spritesheetcar4);
	CImage_UnLoadImage(GameFrog->spritesheetcar5);
	CImage_UnLoadImage(GameFrog->spritesheetplant);
	CImage_UnLoadImage(GameFrog->spritesheetfruit1);
	CImage_UnLoadImage(GameFrog->spritesheetfruit2);
	CImage_UnLoadImage(GameFrog->spritesheetfruit3);
}


void CGameFrog_LoadGraphics(CGameFrog* GameFrog)
{
	GameFrog->background = CImage_LoadImage( "frog/background.png");
	GameFrog->spritesheetfrog = CImage_LoadImage( "frog/player.png");
	GameFrog->spritesheetbackground = CImage_LoadImage( "frog/watergrass.png");
	GameFrog->spritesheetcar1 = CImage_LoadImage( "frog/carblue.png");
	GameFrog->spritesheetcar2 = CImage_LoadImage( "frog/garbagetruck.png");
	GameFrog->spritesheetcar3 = CImage_LoadImage( "frog/ambulance.png");
	GameFrog->spritesheetcar4 = CImage_LoadImage( "frog/taxi.png");
	GameFrog->spritesheetcar5 = CImage_LoadImage( "frog/police.png");
	GameFrog->spritesheetplant = CImage_LoadImage( "frog/waterplant.png");
	GameFrog->spritesheetfruit1 = CImage_LoadImage( "frog/apple.png");
	GameFrog->spritesheetfruit2 = CImage_LoadImage( "frog/lemon.png");
	GameFrog->spritesheetfruit3 = CImage_LoadImage( "frog/cherry.png");
}

void CGameFrog_init(CGameFrog* GameFrog)
{
	CGameFrog_LoadGraphics(GameFrog);
	GameFrog->GameBase->level = 1;
	GameFrog->dolevelinc = false;
	GameFrog->rowsspawned = 0;
	GameFrog->plantsspawned = 0;
	GameFrog->numobjects = 0;
	GameFrog->worldspeed = CGameFrog_globalworldspeed;
	CGameFrog_createplayer(GameFrog);
	CGameFrog_createobjects(GameFrog,true);
	CGameFrog_LoadSound(GameFrog);
	CurrentGameMusicID = GameFrog->MusMusic;
	CAudio_PlayMusic(GameFrog->MusMusic, -1);
}

void CGameFrog_deinit(CGameFrog* GameFrog)
{
	CGameFrog_destroyplayer(GameFrog);
	CGameFrog_destroyallobjects(GameFrog);
	CGameFrog_UnLoadSound(GameFrog);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGameFrog_UnloadGraphics(GameFrog);
}


//Update ----------------------------------------------------------------------------------------------------------------

void CGameFrog_OnGameStart(CGameFrog* GameFrog)
{
	GameFrog->playerdeath = false;
	GameFrog->playerdeathtime = 0;
}

void CGameFrog_UpdateLogic(CGameFrog* GameFrog)
{
	if (CGameBase_UpdateLogic(GameFrog->GameBase))
		CGameFrog_OnGameStart(GameFrog);

	GameFrog->uppressed |= gamepad_up() == 1;
	GameFrog->downpressed |= gamepad_down() == 1;
	GameFrog->rightpressed |= gamepad_right() == 1;
	GameFrog->leftpressed |= gamepad_left() == 1;
	
	if(CGameFrog_NumLogicFrames > 1)
		if (get_frame_counter() % 2 == 1)
			return;

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
	{
		GameFrog->uppressed = false;
		GameFrog->downpressed = false;
		GameFrog->rightpressed = false;
		GameFrog->leftpressed = false;
		return;
	}

	if (SubGameState == SGGame)
	{
		if (!GameFrog->playerdeath)
		{
			CGameFrog_updateplayer(GameFrog);
			//needs to be done after player update and before object update
			//object update checks collisions etc and thus also player death
			//it does this before adjusting GameFrog->worldspeed to y value
			//so if not done here weird collisions and false deaths happen
			if (GameFrog->dolevelinc)
			{
				if (GameFrog->GameBase->level - 1 < CGameFrog_lenlevelincspeeds - 1)
				{
					GameFrog->GameBase->level += 1;
					GameFrog->dolevelinc = false;
				}
			}

			CGameFrog_updateobjects(GameFrog);
			CSprites_UpdateSprites();

		}
		else
		{
			if(GameFrog->GameBase->HealthPoints > 1)
			{
				if (GameFrog->playerdeathtime < getCurrentTimeMilliseconds())
				{
					CGameFrog_destroyallobjects(GameFrog);
					CGameFrog_destroyplayer(GameFrog);
					CGameFrog_createobjects(GameFrog, true);
					if (GameMode == GMGame)
					{
						//createplayer sets healthpoints!
						int tmpHealthPoints = GameFrog->GameBase->HealthPoints - 1;
						CGameFrog_createplayer(GameFrog);
						GameFrog->GameBase->HealthPoints = tmpHealthPoints;
					}
					else
						CGameFrog_createplayer(GameFrog);
					SubGameState = SGReadyGo;
					SubStateTime = getCurrentTimeMilliseconds() + 500;
				}
			}
			else
				if(GameMode == GMGame)
					if (GameFrog->GameBase->HealthPoints > 0)
						GameFrog->GameBase->HealthPoints = GameFrog->GameBase->HealthPoints - 1;
		}
	}
	GameFrog->uppressed = false;
	GameFrog->downpressed = false;
	GameFrog->rightpressed = false;
	GameFrog->leftpressed = false;
}

void CGameFrog_Draw(CGameFrog* GameFrog)
{
	if (CGameFrog_NumLogicFrames > 1)
		if (get_frame_counter() % 2 == 0)
			return;

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CSprites_DrawSprites();
	CGameFrog_DrawBackground(GameFrog);
	CGameBase_DrawScoreBar(GameFrog->GameBase);
	CGameBase_DrawSubstateText(GameFrog->GameBase);
}


#endif