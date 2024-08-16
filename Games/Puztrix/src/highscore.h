#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "input.h"
#include "string.h"
#include "highscore.h"
#include "gamefuncs.h"
#include "main.h"
#include "libs/DrawPrimitives/draw_primitives.h"
void ShowHighScoresInit()
{

}

void ShowHighScores()
{
	if (GameState == GSHighScoresInit)
	{
		ShowHighScoresInit();
		GameState = GSHighScores;
	}
    if (GameState == GSHighScores)
    {
	    if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
		{
            GameState = GSTitleScreenInit;
        }

        drawTextureZoomed(IMGTitleScreen, 0, 0, 0);
		int[50] Text;
		int[10] Nr;
 		strcpy(Text,"#  score");
        drawTextColor(BigFont, Text, 115*xscale, (87 + (-1* 20))*yscale, ColorSelection);

		strcpy(Text,"lvl");
        drawTextColor(BigFont, Text, 260*xscale, (87 + (-1* 20))*yscale, ColorSelection);
		
		set_multiply_color(ColorSelection);
		draw_line(screenxoffset + 110*xscale,87*yscale, screenxoffset + (287)*xscale, 87*yscale);
		set_multiply_color(color_white);

		for (int i = 0; i < MaxHighScores; i++)
		{
			itoa(i+1, Nr, 10);
			strcpy(Text, Nr);
			strcat(Text,". ");
			itoa(HighScores[i].Score, Nr, 10);
			strcat(Text, Nr);
			
        	drawTextColor(BigFont, Text, 115*xscale, (87 + (i* 20))*yscale, ColorSelection);

			itoa(HighScores[i].Level, Nr, 10);
			strcpy(Text, Nr);
        	drawTextColor(BigFont, Text, 260*xscale, (87 + (i* 20))*yscale, ColorSelection);
		}
    }
}


#endif