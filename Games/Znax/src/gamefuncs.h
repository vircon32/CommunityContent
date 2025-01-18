#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include "string.h"
#include "texture.h"
#include "caudio.h"
#include "common.h"
#include "defines.h"
#include "libs/TextFonts/textfont.h"
#include "fonts/font_16.h"
#include "fonts/font_24.h"
#include "fonts/font1_25.h"
#include "cworldparts.h"

#define HighScoreSavePosition 100

void LoadSounds()
{
    MusicCount = 1;
	Music[0] = CAudio_LoadMusic("title");

    Sounds[SND_READYGO] = CAudio_LoadSound("readygo");
    Sounds[SND_1] = CAudio_LoadSound("one");
    Sounds[SND_2] = CAudio_LoadSound("two");
    Sounds[SND_3] = CAudio_LoadSound("three");
    Sounds[SND_1MINUTE] = CAudio_LoadSound("oneminute");
    Sounds[SND_TIMEOVER] = CAudio_LoadSound("timeover");
    Sounds[SND_MENU] = CAudio_LoadSound("menu");
    Sounds[SND_SELECT] = CAudio_LoadSound("select");
    Sounds[SND_WELCOME] = CAudio_LoadSound("welcome");
    Sounds[SND_DELETE] = CAudio_LoadSound("delete");
    Sounds[SND_BLOCKSELECT] = CAudio_LoadSound("blockselect");
    Sounds[SND_ERROR] = CAudio_LoadSound("error");
}

void UnloadSounds()
{
    CAudio_StopSound();
    int Teller;
    for (Teller=0;Teller<NrOfSounds;Teller++)
        if(Sounds[Teller])
            CAudio_UnLoadSound(Sounds[Teller]);
}


void LoadHighScores()
{
    for (int Teller = 0;Teller<10;Teller++)
    {
        strcpy(HighScores[Fixed][Teller].PName,"joyrider");
        strcpy(HighScores[Relative][Teller].PName,"joyrider");
        HighScores[Fixed][Teller].PScore = 0;
        HighScores[Relative][Teller].PScore = 0;
    }
    if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(HighScores[Fixed], HighScoreSavePosition, sizeof(HighScores[Fixed][0]) * 10);
            card_read_data(HighScores[Relative], HighScoreSavePosition + (sizeof(HighScores[Fixed][0]) * 10), sizeof(HighScores[Relative][0]) * 10);		
		}
}

void SaveHighScores()
{
    if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			card_write_data(HighScores[Fixed], HighScoreSavePosition, sizeof(HighScores[Fixed][0]) * 10);	
            card_write_data(HighScores[Relative], HighScoreSavePosition + (sizeof(HighScores[Fixed][0]) * 10), sizeof(HighScores[Relative][0]) * 10);
		}
}


void UnloadMusic()
{
	CAudio_UnLoadMusic(Music[0]);
}

void setupFonts()
{
   setupFontfont_16();
   font = &Fontfont_16; 
   setupFontfont_24();
   BigFont = &Fontfont_24; 
   setupFontfont1_25();
   MonoFont = &Fontfont1_25;
}

void UnLoadGraphics()
{
    if(IMGHighScores)
        freeTexture(IMGHighScores);
    if(IMGSelectGame)
        freeTexture(IMGSelectGame);
    if(IMGFixedTimer2)
        freeTexture(IMGFixedTimer2);
    if(IMGRelativeTimer2)
        freeTexture(IMGRelativeTimer2);
    if(IMGFixedTimer1)
        freeTexture(IMGFixedTimer1);
    if(IMGRelativeTimer1)
        freeTexture(IMGRelativeTimer1);
    if(IMGIntro1)
        freeTexture(IMGIntro1);
    if(IMGIntro2)
        freeTexture(IMGIntro2);
    if(IMGIntro3)
        freeTexture(IMGIntro3);
    if(IMGTimeOver)
        freeTexture(IMGTimeOver);
    if(IMGBlocks1)
        freeTexture(IMGBlocks1);
    if(IMGBlocks2)
        freeTexture(IMGBlocks2);
    if(IMGBlocks3)
        freeTexture(IMGBlocks3);
    if(IMGBlocks4)
        freeTexture(IMGBlocks4);
    if(IMGBlocks5)
        freeTexture(IMGBlocks5);
    if(IMGBackground)
        freeTexture(IMGBackground);
    if(IMGCursor)
        freeTexture(IMGCursor);
    if(IMGReady)
        freeTexture(IMGReady);
    if(IMGGo)
        freeTexture(IMGGo);
    if(IMGPlay1)
        freeTexture(IMGPlay1);
    if(IMGPlay2)
        freeTexture(IMGPlay2);
    if(IMGCredits1)
        freeTexture(IMGCredits1);
    if(IMGCredits2)
        freeTexture(IMGCredits2);
    if(IMGHighScores1)
        freeTexture(IMGHighScores1);
    if(IMGHighScores2)
        freeTexture(IMGHighScores2);
    if(IMGTitleScreen)
        freeTexture(IMGTitleScreen);
    if(IMGCredits)
        freeTexture(IMGCredits);
}

void LoadGraphics()
{
    IMGIntro1 = newTextureHorz(0, 1, 1, 0, 0, 640, 360, 1.0, 1.0);
    IMGIntro2 = newTextureHorz(0, 2, 1, 0, 360, 640, 360, 1.0, 1.0);
    IMGBlocks1 = newTextureHorz(0, 3, 7, 640, 0, 245, 35, 1.0, 1.0);
    IMGBlocks2 = newTextureHorz(0, 11, 7, 640, 35, 245, 35, 1.0, 1.0);
    IMGBlocks3 = newTextureHorz(0, 21, 7, 640, 70, 245, 35, 1.0, 1.0);
    IMGBlocks4 = newTextureHorz(0, 31, 7, 640, 105, 245, 35, 1.0, 1.0);
    IMGBlocks5 = newTextureHorz(0, 41, 7, 640, 140, 245, 35, 1.0, 1.0);
    IMGGo = newTextureHorz(0, 48, 1, 885, 0, 107, 104, 1.0, 1.0);
    IMGReady = newTextureHorz(0, 49, 1, 640, 175, 246, 119, 1.0, 1.0);
    IMGTimeOver = newTextureHorz(0, 50, 1, 640, 294, 318, 111, 1.0, 1.0);
    IMGCursor = newTextureHorz(0, 51, 1, 885, 104, 35, 35, 1.0, 1.0);
    IMGPlay1 = newTextureHorz(0, 52, 1, 640, 405, 185, 48, 1.0, 1.0);
    IMGPlay2 = newTextureHorz(0, 53, 1, 640, 453, 185, 48, 1.0, 1.0);
    IMGHighScores1 = newTextureHorz(0, 54, 1, 640, 501, 185, 48, 1.0, 1.0);
    IMGHighScores2 = newTextureHorz(0, 55, 1, 640, 549, 185, 48, 1.0, 1.0);
    IMGCredits1 = newTextureHorz(0, 56, 1, 640, 596, 185, 48, 1.0, 1.0);
    IMGCredits2 = newTextureHorz(0, 57, 1, 640, 644, 185, 48, 1.0, 1.0);
    IMGSelectGame = newTextureHorz(0, 58, 1, 0, 720, 312, 57, 1.0, 1.0);
    IMGFixedTimer1 = newTextureHorz(0, 59, 1, 0, 777, 312, 56, 1.0, 1.0);
    IMGFixedTimer2 = newTextureHorz(0, 60, 1, 0, 833, 312, 56, 1.0, 1.0);
    IMGRelativeTimer1 = newTextureHorz(0, 61, 1, 0, 889, 312, 56, 1.0, 1.0);
    IMGRelativeTimer2 = newTextureHorz(0, 62, 1, 0, 945, 312, 56, 1.0, 1.0);
    IMGCredits = newTextureHorz(0, 63, 1, 382, 720, 313, 191, 1.0, 1.0);

    IMGIntro3 = newTextureHorz(1, 1, 1, 0, 0, 640, 360, 1.0, 1.0);
    IMGTitleScreen = newTextureHorz(1, 2, 1, 0, 360, 640, 360, 1.0, 1.0);
    
    IMGBackground = newTextureHorz(2, 1, 1, 0, 0, 640, 360, 1.0, 1.0);
    IMGHighScores = newTextureHorz(2, 2, 1, 0, 360, 640, 360, 1.0, 1.0);
    
}

void WriteText(textfont* font, int* text, int x, int y, int color)
{
	if(!font)
		return;

	if(*text == 0)
		return;

	set_multiply_color(color);
	textfont_print_from_left(font, x, y, text);
	set_multiply_color(color_white);
}

void drawStatusBar()
{
    int[100] Text;
    int[20] Nr;
    int TextColor = make_color_rgba(255,255,255,255);
    strcpy(Text, "Timer:\n");
    if(Timer / 60 < 10)
        strcat(Text, "0");
    itoa(Timer / 60, Nr, 10);
    strcat(Text, Nr);
    strcat(Text, ":");
    if(Timer % 60 < 10)
        strcat(Text, "0");
    itoa(Timer % 60, Nr, 10);
    strcat(Text, Nr);
    strcat(Text, "\n\nScore:\n");
    itoa(Score, Nr, 10);
    strcat(Text, Nr);
    strcat(Text, "\n\n\nLeft:\n");
    itoa(movesLeft, Nr, 10);
    strcat(Text, Nr);
    WriteText(BigFont,Text,345*SCALE,10*SCALE,TextColor);
}

#endif