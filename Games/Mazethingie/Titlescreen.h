#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "libs/DrawPrimitives/draw_primitives.h"
#include "video.h"
#include "string.h"
#include "input.h"
#include "Mazethingie.h"
#include "SaveData.h"
#include "Maze.h"
#include "Player.h"
void TitleScreen()
{
	int MenuXPos = 200;
	int MenuYPos = 120;
	clear_screen(color_black);	
    textfont_print_centered(&FontLetters,screen_width>>1,40,"MAZE THINGIE");
    if (Selection==1)
	{
		set_multiply_color(color_red);
        textfont_print_from_left(&FontLetters,MenuXPos,MenuYPos,"Play");
	}
    else
	{
		set_multiply_color(color_white);
        textfont_print_from_left(&FontLetters, MenuXPos,MenuYPos,"Play");
	}

    int[50] Text;
    itoa(MazeWidth, &Text[0], 10);
    if(Selection == 2)
	{
		set_multiply_color(color_red);
	    textfont_print_from_left(&FontLetters,MenuXPos,MenuYPos  + 35,"Maze Width:");
		textfont_print_from_left(&FontLetters,MenuXPos+textfont_get_line_width(&FontLetters,"Maze Width:"), MenuYPos + 35,&Text[0]);
	}
    else
    {
		set_multiply_color(color_white);
	    textfont_print_from_left(&FontLetters,MenuXPos,MenuYPos + 35,"Maze Width:");
		textfont_print_from_left(&FontLetters,MenuXPos+textfont_get_line_width(&FontLetters,"Maze Width:"),MenuYPos + 35,&Text[0]);
	}

	itoa(MazeHeight, &Text[0], 10);
    if(Selection == 3)
	{
		set_multiply_color(color_red);
	    textfont_print_from_left(&FontLetters,MenuXPos,MenuYPos + 70,"Maze Height:");
		textfont_print_from_left(&FontLetters,MenuXPos+textfont_get_line_width(&FontLetters,"Maze Height:"),MenuYPos + 70,&Text[0]);
	}
    else
    {
		set_multiply_color(color_white);
	    textfont_print_from_left(&FontLetters,MenuXPos,MenuYPos + 70,"Maze Height:");
		textfont_print_from_left(&FontLetters,MenuXPos+textfont_get_line_width(&FontLetters,"Maze Height:"),MenuYPos + 70,&Text[0]);
	}

	set_multiply_color(color_white);
    textfont_print_centered(&FontLetters,screen_width>>1,300,"Created by\nWillems Davy - 2024");

	if(gamepad_up() == 1)
   		if (Selection > 1)
    	    Selection--;
        
	if(gamepad_down() == 1)
		if (Selection < 3)
        	Selection++;

	if(gamepad_button_a() == 1 || gamepad_button_start() == 1)
	{
		SaveSettings();
		GenerateMaze();
		clear_screen(color_black);
		DrawMaze();
		DrawPlayer();
	    GameState = GSGame;
	}

	if(Selection == 2)
    {
	    if (gamepad_right() % MenuSpeedTickVal == 1)
    	    if (MazeWidth < MaxMazeWidth)
            {
				MazeWidth++;
				SaveSettings();	
			}

        if (gamepad_left() % MenuSpeedTickVal == 1)
	        if(MazeWidth > 10 )
			{
    	        MazeWidth--;
				SaveSettings();
			}
        
	}

    if(Selection == 3)
    {
		if (gamepad_right() % MenuSpeedTickVal == 1)
			if (MazeHeight < MaxMazeHeight)
				MazeHeight++;
		if (gamepad_left() % MenuSpeedTickVal == 1)
			if(MazeHeight > 10 )
				MazeHeight--;
	}
}
#endif