#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include "string.h"
#include "../sound.h"
#include "../gameobjects/cpasswordselector.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "passwordentry.h"


int CharNr;
int[5] Password;
CPasswordSelector* PasswordSelector;

void PasswordEntryInit()
{
	PasswordEntryCoolDown = 0;
	CharNr = 0;
	Password[0] = ' ';
	Password[1] = ' ';
	Password[2] = ' ';
	Password[3] = ' ';
	Password[4] = 0;
	PasswordSelector = CPasswordSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void PassWordEntryDeInit()
{
	freeTexture(Background);
	CPasswordSelector_Destroy(PasswordSelector);
}

void PasswordEntry()
{
	
	if(GameState == GSPasswordEntryInit)
	{
		PasswordEntryInit();
		GameState -= GSInitDiff;
	}
	
	if (Password[3] != ' ')
	{
		if (PasswordEntryCoolDown > 0)
			PasswordEntryCoolDown--;
		if (PasswordEntryCoolDown == 0)
		{
			if (GetLevel(Password) == -1)
			{
				Password[0] = ' ';
				Password[1] = ' ';
				Password[2] = ' ';
				Password[3] = ' ';
				playErrorSound();
			}
			else
				if (GetLevel(Password) == 0)
				{
					GameState = GSStageSelectInit;
				}
				else
				{
					Level = GetLevel(Password);
					GameState = GSOldManSpeakingInit;
				}
		}
	}

	if(GameState == GSPasswordEntry)
	{
		if (PasswordEntryCoolDown == 0)
		{
			if (gamepad_button_b() == 1)
				GameState = GSTitleScreenInit;

			if(gamepad_button_start() == 1)
				GameState = GSTitleScreenInit;


			if (gamepad_button_a() == 1)
			{
				Password[CharNr] = Letters[CPasswordSelector_GetY(PasswordSelector)][CPasswordSelector_GetX(PasswordSelector)];
				playMenuSelectSound();
				CharNr++;
				if (CharNr > 3)
				{
					PasswordEntryCoolDown = (int)(15 * fpsscale);
					CharNr = 0;
				}
			}

			if (gamepad_up() == 1)
				CPasswordSelector_MoveUp(PasswordSelector);

			if (gamepad_down() == 1)
				CPasswordSelector_MoveDown(PasswordSelector);

			if (gamepad_left() == 1)
				CPasswordSelector_MoveLeft(PasswordSelector);

			if (gamepad_right() == 1)
				CPasswordSelector_MoveRight(PasswordSelector);
		}

		drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);

		set_multiply_color(color_black);
		int textw = textfont_get_line_width(Mini2X, Password);
		textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + ((int)(WINDOW_WIDTH-textw >> 1))*xscale, 37 * yscale, Password, xscale, yscale);
		int LetterX,LetterY;
		for (LetterY = 0 ;LetterY < LetterRows;LetterY++)
			for (LetterX = 0;LetterX < LetterCols;LetterX++)
			{
				if(Letters[LetterY][LetterX] != '0')
				{
					int[2] Letter;
					Letter[0] = Letters[LetterY][LetterX];
					Letter[1] = 0;
					textfont_print_from_left_zoomed(Mini2X, ScreenXOffset + XOffsetPassword + ((LetterX * 35) * xscale), YOffsetPassword + ((LetterY * 35) * yscale), Letter, xscale, yscale);
				}
			}
		set_multiply_color(color_white);
		CPasswordSelector_Draw(PasswordSelector);
	}
	
	if(GameState != GSPasswordEntry)
		PassWordEntryDeInit();
}


#endif