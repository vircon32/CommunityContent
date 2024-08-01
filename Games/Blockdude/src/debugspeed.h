#ifndef DEBUGSPEED_H
#define DEBUGSPEED_H

#include "string.h"
#include "time.h"
#include "video.h"
#include "libs/DrawPrimitives/draw_primitives.h"

#define MAXDEBUGSPEEDS 100
#define MAXDEBUGSPEEDSENABLED false

int[MAXDEBUGSPEEDS] DebugSpeedMaxValues;
int[MAXDEBUGSPEEDS] DebugSpeedValues;
int[MAXDEBUGSPEEDS] DebugSpeedCycles;
int[MAXDEBUGSPEEDS] DebugSpeedFrames;
int[MAXDEBUGSPEEDS] DebugSpeedsPrevLenText;


void printDebugSpeed(int Nr, int x, int y, int* prefix)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if(Nr < MAXDEBUGSPEEDS)
	{
		int[10] debugNr;
		int[50] Msg;
		itoa(DebugSpeedValues[Nr], debugNr, 10);
		strcpy(Msg, prefix);
		strcat(Msg, debugNr);
		strcat(Msg, "/");
		itoa(DebugSpeedMaxValues[Nr], debugNr, 10);
		strcat(Msg, debugNr);
		if(DebugSpeedMaxValues[Nr] > 0)
		{
			set_multiply_color(color_white);
			if(DebugSpeedsPrevLenText[Nr] > 0)
			{
				draw_filled_rectangle(x-1,y-1, x -1 + 2 + DebugSpeedsPrevLenText[Nr] * bios_character_width , y-1 + 2 + bios_character_height);	
			}
			draw_filled_rectangle(x-1,y-1, x -1 + 2 + strlen(Msg) * bios_character_width , y-1 + 2 + bios_character_height);
			set_multiply_color(color_black);
			print_at(x,y, Msg);
			set_multiply_color(color_white);
			DebugSpeedsPrevLenText[Nr] = strlen(Msg);
		}
	}
}

void initDebugSpeed()
{
	for (int i = 0; i < MAXDEBUGSPEEDS; i++)
	{
		DebugSpeedMaxValues[i] = 0;
		DebugSpeedCycles[i] = 0;
		DebugSpeedValues[i] = 0;
		DebugSpeedFrames[i] = 0;
		DebugSpeedsPrevLenText[i] = 0;
	}
}

void StartDebugSpeed(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		DebugSpeedFrames[Nr] = get_frame_counter();
   	 	DebugSpeedCycles[Nr] = get_cycle_counter();	
		DebugSpeedValues[Nr] = 0;
	}
}

void StopDebugSpeed(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		int endframes = get_frame_counter();
		int endcycles = get_cycle_counter();
		if(endframes - DebugSpeedFrames[Nr] > 0)
		{
			DebugSpeedValues[Nr] = 250000 - DebugSpeedCycles[Nr];
			DebugSpeedValues[Nr] += 250000 * (endframes - DebugSpeedFrames[Nr]-1) ;
			DebugSpeedValues[Nr] += endcycles;
		}
		else
		{
			DebugSpeedValues[Nr] = endcycles - DebugSpeedCycles[Nr];
		}
		if(DebugSpeedValues[Nr] > DebugSpeedMaxValues[Nr])
			DebugSpeedMaxValues[Nr] = DebugSpeedValues[Nr];		
	}
}

void ResetDebugSpeedMaxValue(int Nr)
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	if (Nr < MAXDEBUGSPEEDS)
	{
		DebugSpeedMaxValues[Nr] = 0;
	}	
}

void ResetAllDebugSpeedMaxValues()
{
	if(!MAXDEBUGSPEEDSENABLED)
		return;
	for (int i=0; i < MAXDEBUGSPEEDS; i++)
		DebugSpeedMaxValues[i] = 0;
}

#endif