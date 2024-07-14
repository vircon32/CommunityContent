#include "video.h"
#include "string.h"
#include "time.h"
#include "misc.h"
#include "input.h"
#include "memcard.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "libs/TextFonts/textfont.h"
#include "Mazethingie.h"
#include "Titlescreen.h"
#include "SaveData.h"
#include "Maze.h"
#include "Player.h"
#include "Game.h"

void SetupFont()
{
	select_texture( TextureFullFont );
    
    // First we define define 128 consecutive regions (i.e. standard ASCII only)
    // with the same size and hotspot position, as for a constant-width font
    define_region_matrix( FirstRegionFullFont,  0,0,  21,31,  0,31,  16,8,  0 );
    
    // then we redefine some characters to have different widths
    // (note that, for this font, upper and lowercase letters are the same)
    select_region( FirstRegionFullFont + 'M' );
    define_region( 22,0,  46,31,  22,31 );
    select_region( FirstRegionFullFont + 'm' );
    define_region( 22,0,  46,31,  22,31 );
    
    select_region( FirstRegionFullFont + 'W' );
    define_region( 66,0,  90,31,  66,31 );
    select_region( FirstRegionFullFont + 'w' );
    define_region( 66,0,  90,31,  66,31 );
    
    select_region( FirstRegionFullFont + 'I' );
    define_region( 110,0,  121,31,  110,31 );
    select_region( FirstRegionFullFont + 'i' );
    define_region( 110,0,  121,31,  110,31 );
    
    select_region( FirstRegionFullFont + ' ' );
    define_region( 0,64,  15,95,  0,95 );

	FontLetters.character_height = 31;
    FontLetters.use_variable_width = true;
    textfont_read_region_widths( &FontLetters );
    
    // 2 pixels overlap between characters, 15 pixels between lines
    FontLetters.character_separation = -2;
    FontLetters.line_separation = 15;
    
    // define texture and regions for our characters
    FontLetters.texture_id = TextureFullFont;
    FontLetters.character_zero_region_id = FirstRegionFullFont;
}

void main()
{  
	memset( &GameSignature, 0, sizeof(game_signature));
    strcpy( GameSignature, "MAZETHINGIE");
	LoadSettings();
	SetupFont();	
	srand(get_time());
    select_gamepad(0);
	while (true) 
    {
      switch (GameState) 
	  {
		case GSTitleScreen:
			TitleScreen();
			break;
		case GSGame:
			Game();
			break;
		default:
			break;
	  }
      end_frame();
    }
	framecount++;
	if (framecount >= 60000)
		framecount = 0;
}