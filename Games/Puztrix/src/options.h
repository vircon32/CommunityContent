#ifndef OPTIONS_H
#define OPTIONS_H


#include "input.h"
#include "string.h"
#include "credits.h"
#include "gamefuncs.h"
#include "main.h"
#include "caudio.h"

void OptionsInit()
{
	optionSelection = 0;
}

void Options()
{
	if (GameState == GSOptionsInit)
	{
		OptionsInit();
		GameState = GSOptions;
	}
    if (GameState == GSOptions)
    {
	    if (gamepad_button_b() == 1)
		{
            GameState = GSTitleScreenInit;
        }

		if(gamepad_up() == 1)
		{
			CAudio_PlaySound( Sounds[SND_LevelEditorSelect], 0);
			optionSelection--;
			if (optionSelection < 0)
				optionSelection = 3;
		}

		if(gamepad_down() == 1)
		{
			CAudio_PlaySound( Sounds[SND_LevelEditorSelect], 0);
			optionSelection++;
			if (optionSelection > 3)
				optionSelection = 0;
		}

		if((optionSelection == 0) && ((gamepad_left() == 1) || (gamepad_right() == 1)))
		{
			CAudio_PlaySound(Sounds[SND_Select], 0);
			bool tmp = CAudio_GetMusicEnabled();
			tmp = !tmp;
			CAudio_SetMusicEnabled(tmp);
			CAudio_PlayMusic(Music, -1);
			SaveSettings();
		}

		if((optionSelection == 1) && ((gamepad_left() == 1) || (gamepad_right() == 1)))
		{
			CAudio_PlaySound(Sounds[SND_Select], 0);
			bool tmp = CAudio_GetSoundEnabled();
			tmp = !tmp;
			CAudio_SetSoundEnabled(tmp);
			SaveSettings();
		}

		if((optionSelection == 2) && ((gamepad_left() == 1) || (gamepad_right() == 1)))
		{
			CAudio_PlaySound(Sounds[SND_Select], 0);
			NextSkin();
			SaveSettings();
		}

		if(gamepad_button_a() == 1)
		{
			CAudio_PlaySound( Sounds[SND_Select], 0);
			switch(optionSelection)
			{
				case 0:
				{
					CAudio_PlaySound(Sounds[SND_Select], 0);
					bool tmp = CAudio_GetMusicEnabled();
					tmp = !tmp;
					CAudio_SetMusicEnabled(tmp);
					CAudio_PlayMusic(Music, -1);
					SaveSettings();
					break;
				}
				case 1:
				{
					CAudio_PlaySound(Sounds[SND_Select], 0);
					bool tmp = CAudio_GetSoundEnabled();
					tmp = !tmp;
					CAudio_SetSoundEnabled(tmp);
					SaveSettings();
					break;
				}
				case 3:
				{
					CAudio_PlaySound(Sounds[SND_Select], 0);
					for (int i = 0; i < MaxHighScores; i++)
					{
						HighScores[i].Score = 0;
						HighScores[i].Level = 0;
					}
					SaveSettings();
					break;
				}
				case 2:
				{
					CAudio_PlaySound(Sounds[SND_Select], 0);
					NextSkin();
					SaveSettings();
					break;
				}
				default:
					break;
			}
			
        }

		
		drawTextureZoomed(IMGTitleScreen, 0, 0, 0);
		int LeftX = 113*xscale;
		int color;
		
		if(optionSelection == 0)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		int[50] Text;
		if(CAudio_GetMusicEnabled())
			strcpy(Text, "Music: On");
		else
			strcpy(Text, "Music: Off");
		drawTextColor(BigFont2, Text, LeftX, 62*yscale, color);

		if(optionSelection == 1)
			color = ColorSelection;
		else
			color = ColorNoSelection;

		if(CAudio_GetSoundEnabled())
			strcpy(Text, "Sound: On");
		else
			strcpy(Text, "Sound: Off");
		drawTextColor(BigFont2, Text, LeftX, 87*yscale, color);

		if(optionSelection == 2)
			color = ColorSelection;
		else
			color = ColorNoSelection;

		if(skin == 1)
			strcpy(Text, "Skin: Default");
		else
			strcpy(Text, "Skin: NES");
		drawTextColor(BigFont2, Text, LeftX,  112*yscale, color);

		if(optionSelection == 3)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		drawTextColor(BigFont2, "Reset High Score", LeftX, 137*yscale, color);
    }
}


#endif