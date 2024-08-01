#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "input.h"
#include "texture.h"
#include "libs/TextFonts/textfont.h"
#include "fonts/Roboto_Bold_32.h"

void IntroInit()
{
	NeedRedraw = true;
}

void Intro()
{
	if (GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSDiff;
	}
	framecounter++;

	if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) ||
		(gamepad_button_x() == 1) || (gamepad_button_y() == 1) ||
		(gamepad_button_start() == 1))
	{
		GameState = GSTitleScreenInit;
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		if (IntroScreenNr == 4)
			drawTexture(IMGIntroSoleau, 0, 0, 0);
		else
			drawTexture(IMGIntroBackground, 0, 0, 0);		
		int[150] Msg;
		switch (IntroScreenNr)
  		{
    		case 1:
      			strcpy(Msg,"Willems Davy\n\n\nPresents");				
      			break;
    		case 2:
      			strcpy(Msg, "Thanks to\n\nKlas Kroon & Kris Katiesen for the graphics\n\nFusion Power for his skins\n\nKenney for assets\n\nDonskeeto for the music");
      			break;
    		case 3:
      			strcpy(Msg, "And for the\n\n\nBlock man Levels...");
      		break;
  		}
		if(IntroScreenNr < 4)
		{			
			int th = (countChars(Msg, '\n') + 1) * (FontRoboto_Bold_32.character_height + FontRoboto_Bold_32.line_separation);
			set_multiply_color(make_color_rgba(107,128,128,255));
			textfont_print_centered(&FontRoboto_Bold_32, (screen_width ) >> 1, (screen_height - th) >> 1, Msg);
			set_multiply_color(color_white);
		}
	}

	if (framecounter > FRAMERATE * 3.5)
	{
		framecounter = 0;
		IntroScreenNr++;
		NeedRedraw = true;
		if (IntroScreenNr > 4)
			GameState = GSTitleScreenInit;
	}
}

#endif