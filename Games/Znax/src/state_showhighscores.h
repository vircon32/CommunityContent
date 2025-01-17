#ifndef STATESHOWHIGHSCORES
#define STATESHOWHIGHSCORES

#include "input.h"
#include "texture.h"
#include "gamefuncs.h"
#include "common.h"

void ShowHighScores()
{
    end_frame();
    int TextColor = make_color_rgba(102,115,152,255);
    int Teller = 0;
    int[250] Text;
    int[20] Nr;
    int ScoreType = GameType;
    while (GameState == GSShowHighScores)
    {
        if((gamepad_button_x() == 1) || (gamepad_button_y() == 1) || (gamepad_button_a() == 1) || (gamepad_button_start() == 1))
        {
            if (ScoreType == Fixed)
                ScoreType = Relative;
            else
            {
                if(ScoreType == Relative)
                    GameState = GSTitleScreen;
            }
        }
        if(gamepad_button_b() == 1)
            GameState = GSTitleScreen;

        drawTexture(IMGHighScores, 0, 0, 0);
        switch(ScoreType)
        {
            case Fixed :
                strcpy(Text,"Gametype: Fixed Timer" );
                break;
            case Relative :
                strcpy(Text,"Gametype: Relative Timer" );
                break;
        }
		WriteText(font,Text,145*SCALE,227*SCALE,TextColor);
        for(Teller = 0;Teller<10;Teller++)
        {
            Text[0] = 0;
            if (Teller+1 < 10)
                strcat(Text, " ");
            itoa(Teller+1, Nr, 10);
            strcat(Text, Nr);
            strcat(Text, ".");
            strcat(Text, HighScores[ScoreType][Teller].PName);
            WriteText(MonoFont,Text,100*SCALE,(62+Teller*16)*SCALE,TextColor);
            itoa(HighScores[ScoreType][Teller].PScore, Nr, 10);
            strcpy(Text, Nr);
            WriteText(MonoFont,Text,280*SCALE + ((7 - strlen(Nr)) * textfont_get_character_width( MonoFont, *"0" )),(62+Teller*16)*SCALE,TextColor);
        }
        end_frame();
    }
}


#endif