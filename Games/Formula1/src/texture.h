#ifndef TEXTURE_H
#define TEXTURE_H

#include "video.h"
#include "string.h"
#include "misc.h"

//helper class for textures, i define 1 texture per image
struct Texture {
	int textureID;
	int width;
	int height;
};

//create (well define) a new texture based on the texture id.
//it always uses define_region_matrix and calculates it based on numframes and width
//so it assumes if a texture has multiple frames they are next to each other in the original 
//image
Texture*  newTexture(int textureID, int numFrames, int width, int height)
{
	Texture *result = malloc(sizeof(Texture));
	result->textureID = textureID;
	result->width = width;
	result->height = height;
	select_texture(textureID);   
	define_region_matrix(0, 0, 0, width-1, (int)(height / numFrames) -1, 0, 0, 1, numFrames, 0);
	return result;
}

//draws a texture, basically just selects the texture and region and then draws the region
void drawTexture(Texture *texture, int frame, int x, int y)
{
	select_texture(texture->textureID);
	select_region(frame);
	draw_region_at(x, y);
}

//free a texture
void freeTexture(Texture *texture)
{
	if (texture)
		free(texture);
	texture = NULL;
}


#endif