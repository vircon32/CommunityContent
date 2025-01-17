#ifndef STATEGETHIGHSCORENAME_H
#define STATEGETHIGHSCORENAME_H


#include "texture.h"
#include "gamefuncs.h"
#include "common.h"

void GetHighScoreName(int* NameIn,int Place, int PScore)
{
    end_frame();
	int[21] Name;
	int[500] Text;
    int[20] Nr;
	bool End=false,SubmitChanges=false;
	int Teller,MaxSelection=0, Selection = 0, asci=97;
	int TextColor = make_color_rgba(102,115,152,255);
    int TextColor1 = make_color_rgba(255,115,152,255);
    memset(&Name[0], 0, 21 * sizeof(int));
	strcpy(Name, NameIn);
	MaxSelection = strlen(NameIn);
	Name[Selection+1]= 0;
	if (MaxSelection == 0)
		Name[MaxSelection]= asci;
	while (!End)
	{
        if(gamepad_left() == 1)
        {
            if (Selection > 0)
            {	Selection--;
                asci = Name[Selection];
            }
        }

        if(gamepad_right() == 1)
        {
            if (Selection < 19)
            {
                Selection++;
                if (Selection > MaxSelection)
                {
                    Name[Selection] = 97;
                    Name[Selection+1] = 0;
                    MaxSelection=Selection;
                }
                asci = Name[Selection];
            }
        }
        if(gamepad_up() == 1)
        {
            asci++;
            if (asci==123)
            {
                asci=32;
            }
            if (asci==33)
            {
                (asci=48);
            }
            if (asci==58)
            {
                asci=97;
            }
            Name[Selection] = asci;
        }
        if(gamepad_down() == 1)
        {
            asci--;
            if(asci==96)
            {
                asci=57;
            }
            if(asci==47)
            {
                asci=32;
            }
            if(asci==31)
            {
                asci=122;
            }
            Name[Selection] = asci;
        }

		if((gamepad_button_a() == 1) || (gamepad_button_x() == 1) || (gamepad_button_y() == 1) || (gamepad_button_start() == 1))
        {
            CAudio_PlaySound(Sounds[SND_SELECT],0);
            End = true;
            SubmitChanges=true;
        }

        if(gamepad_button_b() == 1)
        {
            End=true;
            SubmitChanges=false;
  		}
        
        drawTexture(IMGHighScores, 0, 0, 0);

        for(Teller = 0;Teller<9;Teller++)
        {
            if(Teller < Place)
            {
                Text[0] = 0;
                if (Teller+1 < 10)
                    strcat(Text, " ");
                itoa(Teller+1, Nr, 10);
                strcat(Text, Nr);
                strcat(Text, ".");
                strcat(Text,HighScores[GameType][Teller].PName);
                WriteText(MonoFont,Text,100*SCALE,(62+Teller*16)*SCALE,TextColor);
                itoa(HighScores[GameType][Teller].PScore, Nr, 10);
                strcpy(Text, Nr);
                WriteText(MonoFont,Text,280*SCALE + ((7 - strlen(Nr)) * textfont_get_character_width( MonoFont, *"0" )),(62+Teller*16)*SCALE,TextColor);
            }
            else
            {
                Text[0] = 0;
                if (Teller+2 < 10)
                    strcat(Text, " ");
                itoa(Teller+2, Nr, 10);
                strcat(Text, Nr);
                strcat(Text, ".");
                strcat(Text,HighScores[GameType][Teller].PName);
                WriteText(MonoFont,Text,100*SCALE,(62+(Teller+1)*16)*SCALE,TextColor);
                itoa(HighScores[GameType][Teller].PScore, Nr, 10);
                strcpy(Text, Nr);
                WriteText(MonoFont,Text,280*SCALE + ((7 - strlen(Nr)) * textfont_get_character_width( MonoFont, *"0" )),(62+(Teller+1)*16)*SCALE,TextColor);
            }
        }
		
        Text[0] = 0;
        if (Place+1 < 10)
            strcat(Text, " ");
        itoa(Place+1, Nr, 10);
        strcat(Text, Nr);
        strcat(Text, ".");
        strcat(Text,Name);
        WriteText(MonoFont,Text,100*SCALE,(62+Place*16)*SCALE,TextColor1);
        itoa(PScore, Nr, 10);
        strcpy(Text, Nr);
        WriteText(MonoFont,Text,280*SCALE + ((7 - strlen(Nr)) * textfont_get_character_width( MonoFont, *"0" )),(62+Place*16)*SCALE,TextColor1);
		if (Selection > 0)
		{
			strcpy(Text,"    ");
			for (Teller=1;Teller<Selection;Teller++)
				strcat(Text, " ");
			strcat(Text,"_");
		}
		else
			strcpy(Text,"   _");
		WriteText(MonoFont,Text,100*SCALE,(62+(Place)*16)*SCALE,TextColor1);
		strcpy(Text,"Use Up,Down,Left,right. A = Ok X = Cancel" );
		WriteText(font,Text,105*SCALE,227*SCALE,TextColor);
        end_frame();
	}
	Name[MaxSelection+1] = 0;
	while ((Name[0] == ' ') && (MaxSelection>-1))
	{
		for (Teller=0;Teller<MaxSelection;Teller++)
			Name[Teller] = Name[Teller+1];
		MaxSelection--;
	}
	if (MaxSelection>-1)
		while ((Name[MaxSelection] == ' ') && (MaxSelection>0))
		{
			Name[MaxSelection] = 0;
			MaxSelection--;
		}
	if (!SubmitChanges)
    {
		strcpy(NameIn," ");
        NameIn[1] = 0;
    }
    else
    {
        strcpy(NameIn, Name);
        NameIn[strlen(Name)] = 0;
    }
}


#endif