#ifndef TEXTURE_H
#define TEXTURE_H

#include "misc.h"
#include "video.h"
#include "string.h"

//helper class for textures, i define 1 texture per image
struct Texture {
	int textureID;
	int regionID;
	int width;
	int height;
	int startx;
	int starty;
	float zoomx;
	float zoomy;
};

//create (well define) a new texture based on the texture id.
//it always uses define_region_matrix and calculates it based on numframes and width
//so it assumes if a texture has multiple frames they are next to each other in the original 
//image
Texture*  newTexture(int textureID, int regionID, int numFrames, int startx, int starty, int width, int height, float zoomx, float zoomy)
{
	Texture *result = malloc(sizeof(Texture));
	result->textureID = textureID;
	result->regionID = regionID;
	result->width = width;
	result->height = height;
	result->zoomx = zoomx;
	result->zoomy = zoomy;
	result->startx = startx;
	result->starty = starty;
	select_texture(textureID);   
	define_region_matrix(regionID, startx, starty, startx+ (int)(width / numFrames)-1, starty + height -1, startx, starty, numFrames, 1, 0);
	return result;
}

//draws a texture, basically just selects the texture and region and then draws the region
void drawTexture(Texture *texture, int frame, int x, int y)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	set_drawing_scale(texture->zoomx,texture->zoomy);
	draw_region_zoomed_at(x, y);
	set_drawing_scale(1.0,1.0);
}

//free a texture
void freeTexture(Texture *texture)
{
	if (texture)
		free(texture);
	texture = NULL;
}


#endif