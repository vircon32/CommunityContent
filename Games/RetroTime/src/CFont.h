#ifndef CFONT_H
#define CFONT_H

#include "SDL_HelperTypes.h"
#include "string.h"
#include "libs/TextFonts/textfont.h"
#include "fonts/Roboto_Regular_40.h"
#include "fonts/Roboto_Regular_30.h"
#include "fonts/Roboto_Regular_25.h"
#include "fonts/Roboto_Regular_22.h"
#include "fonts/Roboto_Regular_20.h"
#include "fonts/Roboto_Regular_19.h"
#include "fonts/Roboto_Regular_17.h"
#include "fonts/Roboto_Regular_14.h"

#define FontCacheMax 50
#define MaxLines 20
#define MaxCharsPerLine 255

bool CFont_GlobalFontEnabled = true;

textfont* getFont(int* FontName, int FontSize)
{
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 30))
		return &FontRoboto_Regular_30;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 40))
		return &FontRoboto_Regular_40;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 25))
		return &FontRoboto_Regular_25;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 22))
		return &FontRoboto_Regular_22;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 20))
		return &FontRoboto_Regular_20;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 19))
		return &FontRoboto_Regular_19;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 17))
		return &FontRoboto_Regular_17;
	if((strcmp(FontName, "Roboto-Regular") == 0) && (FontSize == 14))
		return &FontRoboto_Regular_14;
	return NULL;
}

void CFont_Init()
{
	CFont_GlobalFontEnabled = true;
	setupFontRoboto_Regular_14();
	setupFontRoboto_Regular_17();
	setupFontRoboto_Regular_19();
	setupFontRoboto_Regular_25();
	setupFontRoboto_Regular_20();
	setupFontRoboto_Regular_22();
	setupFontRoboto_Regular_30();
	setupFontRoboto_Regular_40();
}

void CFont_DeInit()
{
	if(CFont_GlobalFontEnabled)
	{
	}
}

SDL_Point* CFont_TextSize(int* Font, int FontSize, int* Tekst)
{
	SDL_Point* Result = (SDL_Point*) malloc(sizeof(SDL_Point));
	Result->x = 0;
	Result->y = 0; 
	if (!CFont_GlobalFontEnabled || (*Tekst == 0))
		return Result;
	
	textfont* FontIn = getFont(Font, FontSize);
	if(FontIn != NULL)
	{
		while( *Tekst )
		{
			// calculate this line's position
			int line_width = textfont_get_line_width( FontIn, Tekst );
			if(line_width > Result->x)
				Result->x = line_width;	
						
			while((*Tekst != '\n') && (*Tekst != 0))
				Tekst++;

			Result->y += FontIn->character_height + FontIn->line_separation;
			
			// then detect and skip the '\n' character
			// since it is not counted as part of the line
			if( *Tekst == '\n' )
			Tekst++;
		}

		return Result;
	}
}

int CFont_TextWidth(int* Font, int FontSize, int* Tekst)
{
	if(!CFont_GlobalFontEnabled)
		return 0;
	SDL_Point* Tmp = CFont_TextSize(Font, FontSize, Tekst);
	int result = Tmp->x;
	free(Tmp);
	return result;
}

void drawTextColor(textfont* font, int* text, int x, int y, int color)
{
	if(!font)
		return;

	if(*text == 0)
		return;

	set_multiply_color(color);
	textfont_print_from_left(font, x, y, text);
	set_multiply_color(color_white);
}

void CFont_WriteTextBitmap(int* Font, int FontSize, int* Tekst, int X, int Y, int ColorIn)
{
	if(!CFont_GlobalFontEnabled)
		return;
	textfont* FontIn = getFont(Font, FontSize);
	if (FontIn)
	{
		drawTextColor(FontIn, Tekst, X, Y, ColorIn);
	}
}

void CFont_WriteText(int* Font, int FontSize, int* Tekst, int X, int Y, int ColorIn)
{
	if(!CFont_GlobalFontEnabled)
		return;

	CFont_WriteTextBitmap(Font, FontSize, Tekst, X, Y, ColorIn);
}

#endif