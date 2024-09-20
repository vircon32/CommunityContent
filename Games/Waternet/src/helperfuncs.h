#ifndef helperfuncs_h
#define helperfuncs_h

#include "texture.h"
#include "commonvars.h"
#include "savestate.h"


Texture** currentTiles;

void set_bkg_tile_xy(int ax, int ay, int tile)
{
	drawTextureZoomed(*currentTiles, tile, xoffset + ax * tileSize, yoffset + ay * tileSize);
}

void set_bkg_data(Texture* tiles)
{
    *currentTiles = tiles;
}

void set_bkg_tiles(int ax, int ay, Texture* bitmap)
{
	drawTextureZoomed(bitmap, 0, xoffset + ax, yoffset + ay);
}

void setBlockTilesAsBackground()
{
    switch (skinSaveState())
    {
        case 1:
            set_bkg_data(blockTiles2);
            break;
        default:
            set_bkg_data(blockTiles);
            break;
    }
}

void preloadImages()
{
   	titlescreenMap = newTextureHorz(mainSkinSaveState(), 0, 1, 0, 0,384,120,xscale,yscale);
   	congratsMap = newTextureHorz(mainSkinSaveState(), 1, 1, 0, 120,384,192,xscale,yscale);
   	blockTiles = newTextureHorzVert(mainSkinSaveState(), 2, 42,3,0,312,1008,72,xscale,yscale);
   	blockTiles2 = newTextureHorzVert(mainSkinSaveState(), 200, 42,3,0,384,1008,72,xscale,yscale);
   	selectorTiles = newTextureHorzVert(mainSkinSaveState(), 400, 42,3,0, 456,1008,72,xscale,yscale);
   	congratsScreenTiles = newTextureHorzVert(mainSkinSaveState(), 600, 42, 3,0,528,1008,72,xscale,yscale);
	switch(mainSkinSaveState())
	{
		case 0:
			backgroundColor = make_color_rgb(0,65,132);
			break;
		case 1:
			backgroundColor = color_black;
			break;
		case 2:
			backgroundColor = make_color_rgb(125,125,125);
			break;
		case 3:
			backgroundColor = make_color_rgb(119,53,0);
			break;
		default:
			backgroundColor = color_black;
	}
}

void unloadImages()
{
	if(titlescreenMap)
    	freeTexture(titlescreenMap);
	if(congratsMap)
		freeTexture(congratsMap);
	if(blockTiles)
   		freeTexture(blockTiles);
	if(blockTiles2)
    	freeTexture(blockTiles2);
	if(selectorTiles)
    	freeTexture(selectorTiles);
	if(congratsScreenTiles)
   	 freeTexture(congratsScreenTiles);
}

void setMainSkin(int value)
{
	if (!((value > 0) && (value < maxMainSkins)))
		value = 0;
	setMainSkinSaveState(value);
	unloadImages();
	preloadImages();
}

void nextMainSkin()
{
	int tmp = mainSkinSaveState();
	tmp++;
	setMainSkin(tmp);
}

#endif