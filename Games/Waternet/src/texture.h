#ifndef TEXTURE_H
#define TEXTURE_H

#include "math.h"
#include "misc.h"
#include "video.h"
#include "string.h"

//helper class for textures, i define 1 texture per image
struct Texture {
	int framesVert;
	int framesHorz;
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
Texture*  newTextureHorz(int textureID, int regionID, int numFrames, int startx, int starty, int width, int height, float zoomx, float zoomy)
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
	result->framesVert = 1;
	result->framesHorz = numFrames;
	select_texture(textureID);   
	define_region_matrix(regionID, startx, starty, startx+ (int)(width / numFrames)-1, starty + height -1, startx, starty, numFrames, 1, 0);
	return result;
}

Texture*  newTextureVert(int textureID, int regionID, int numFrames, int startx, int starty, int width, int height, float zoomx, float zoomy)
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
	result->framesHorz = 1;
	result->framesVert = numFrames;
	select_texture(textureID);   
	define_region_matrix(regionID, startx, starty, startx + width -1, starty + (int)(height / numFrames) -1, startx, starty, 1,numFrames, 0);
	return result;
}

Texture*  newTextureHorzVert(int textureID, int regionID, int numFramesHorz, int numFramesVert, int startx, int starty, int width, int height, float zoomx, float zoomy)
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
	result->framesHorz = numFramesHorz;
	result->framesVert = numFramesVert;
	select_texture(textureID);   
	define_region_matrix(regionID, startx, starty, startx + (int)(width / numFramesHorz) -1, starty + (int)(height / numFramesVert) -1, startx, starty, numFramesHorz, numFramesVert, 0);
	return result;
}

void setSingleFrameClipRect(Texture *texture, int x, int y, int width, int height)
{
	select_texture(texture->textureID);
	select_region(texture->regionID);
	define_region(texture->startx + x,texture->starty + y,texture->startx + x+width-1,texture->starty+ y+height-1, texture->startx,texture->starty);
}

//draws a texture, basically just selects the texture and region and then draws the region
void drawTexture(Texture *texture, int frame, int x, int y)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	draw_region_at(x, y);
}

void drawTextureZoomed(Texture *texture, int frame, int x, int y)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	set_drawing_scale(texture->zoomx,texture->zoomy);
	draw_region_zoomed_at(x, y);
	set_drawing_scale(1.0,1.0);
}

//draws a texture with overriden zoom, basically just selects the texture and region and then draws the region 
void drawTextureZoomedOverride(Texture *texture, int frame, int x, int y, float zoomx, float zoomy)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	set_drawing_scale(zoomx,zoomy);
	draw_region_zoomed_at(x, y);
	set_drawing_scale(1.0,1.0);
}

//draws a texture, basically just selects the texture and region and then draws the region
void drawTextureRotatedZoomed(Texture *texture, int frame, int x, int y, float zoomx, float zoomy, float Angle)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	set_drawing_scale(zoomx,zoomy);
	set_drawing_angle(Angle * pi/180);
	draw_region_rotozoomed_at( x, y);
	set_drawing_scale(1.0,1.0);
	set_drawing_angle(0);
}

//draws a texture, basically just selects the texture and region and then draws the region
void drawTextureRotated(Texture *texture, int frame, int x, int y, float Angle)
{
	select_texture(texture->textureID);
	select_region(texture->regionID + frame);
	set_drawing_angle(Angle * pi/180);
	draw_region_rotated_at(x, y);
	set_drawing_angle(0);
}

//free a texture
void freeTexture(Texture *texture)
{
	if (texture)
		free(texture);
	texture = NULL;
}


#endif