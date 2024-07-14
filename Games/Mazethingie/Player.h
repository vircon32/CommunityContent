#ifndef PLAYER_H
#define PLAYER_H

#include "Mazethingie.h"
#include "video.h"
#include "libs/DrawPrimitives/draw_primitives.h"

void DrawPlayer()
{
	set_multiply_color(color_red);
    draw_filled_rectangle((xoffset + ((PlayerPosX+1) * BoxWidth)), (yoffset + ((PlayerPosY + 1) * BoxHeight)+1), 
		(xoffset + ((PlayerPosX+2) * BoxWidth)-2), (yoffset + ((PlayerPosY + 2) * BoxHeight)-1));
}

void ErasePlayer()
{
	set_multiply_color(color_black);
    draw_filled_rectangle((xoffset + ((PlayerPosX+1) * BoxWidth)), (yoffset + ((PlayerPosY + 1) * BoxHeight)+1), 
		(xoffset + ((PlayerPosX+2) * BoxWidth)-2), (yoffset + ((PlayerPosY + 2) * BoxHeight)-1));
}

#endif