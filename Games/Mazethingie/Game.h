#ifndef GAME_H
#define GAME_H

#include "Mazethingie.h"
#include "Player.h"
#include "Maze.h"
#include "video.h"
#include "libs/DrawPrimitives/draw_primitives.h"

void Game()
{
	if(gamepad_button_a() == 1 || gamepad_button_start() == 1)
	{
		GameWon = 0;
		clear_screen(color_black);
		GenerateMaze();
		DrawMaze();
		DrawPlayer();
	}

    if(gamepad_button_b() == 1)
		GameState = GSTitleScreen;

	if(!GameWon)
	{	
		if(gamepad_button_x() > 0)
		{
			int regen = 0;
			if (gamepad_left() % MenuSpeedTickVal == 1)
	        	if(MazeWidth > 10 )
				{
    	        	MazeWidth--;
					regen = 1;
				}

			if (gamepad_right() % MenuSpeedTickVal == 1)
				if (MazeWidth < MaxMazeWidth)
				{
            		MazeWidth++;
					regen = 1;
				}

			if (gamepad_down() % MenuSpeedTickVal == 1)
				if (MazeHeight < MaxMazeHeight)
				{
					MazeHeight++;
					regen = 1;
				}

			if (gamepad_up() % MenuSpeedTickVal == 1)
				if(MazeHeight > 10 )
				{
					MazeHeight--;
					regen = 1;
				}					
			
			if(regen)
			{
				SaveSettings();
				GameWon = 0;
				clear_screen(color_black);
				GenerateMaze();
				DrawMaze();
				DrawPlayer();
			}
		}
		else
		{
			if (gamepad_right() % PlayerSpeedTickVal == 1)
				if (!(Maze[(PlayerPosY*MazeWidth) + PlayerPosX] & 2))
				{
					ErasePlayer();
					PlayerPosX++;
					DrawPlayer();
				}
			if (gamepad_left() % PlayerSpeedTickVal == 1)
				if (!(Maze[(PlayerPosY*MazeWidth) + PlayerPosX] & 8))
				{
					ErasePlayer();
					PlayerPosX--;
					DrawPlayer();
				}

			if (gamepad_up() % PlayerSpeedTickVal == 1)
			{    
				if((PlayerPosX == 0) && (PlayerPosY == 0))
				{
					GameWon = 1;                                                         
					int tw = textfont_get_line_width(&FontLetters, "let's try another one");
					int th = (FontLetters.character_height + FontLetters.line_separation) * 3;
					set_multiply_color(color_black);
					draw_filled_rectangle(((screen_width - tw) >> 1) - 10, ((screen_height - th ) >> 1) - 10, ((screen_width + tw ) >> 1) + 10, ((screen_height + th ) >> 1 ) + 10);
					set_multiply_color(color_red);
					draw_rectangle(((screen_width - tw) >> 1) - 10 + 3 , ((screen_height - th) >> 1) - 10 + 3, ((screen_width + tw) >> 1) + 10 -3, ((screen_height + th) >> 1) + 10 - 3);
					set_multiply_color(color_white);
					textfont_print_centered(&FontLetters, screen_width >> 1, ((screen_height - th +20 + FontLetters.character_height) >> 1) + 10,"Congratulations !!!\nYou solved the maze,\nlet's try another one");
				}
				else
					if (!(Maze[(PlayerPosY*MazeWidth) + PlayerPosX] & 1))
					{
						ErasePlayer();
						PlayerPosY--;
						DrawPlayer();
					}
			}

			if (gamepad_down() % PlayerSpeedTickVal == 1)
				if((PlayerPosX != MazeWidth-1) || (PlayerPosY !=MazeHeight -1))
					if (!(Maze[(PlayerPosY*MazeWidth) + PlayerPosX] & 4))
					{
						ErasePlayer();
						PlayerPosY++;
						DrawPlayer();
					}
		}
	}
}

#endif