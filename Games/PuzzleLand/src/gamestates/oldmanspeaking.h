#ifndef OLDMANSPEAKING_H
#define OLDMANSPEAKING_H

#include "string.h"
#include "../texture.h"
#include "../sound.h"
#include "../gameobjects/cfairy.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "oldmanspeaking.h"

int*[5] Tekst = {"Welcome to the world of\npuzzle land!\nIn level one we'll start with\nsimple three-block\ncombinations ...$When you've mastered level\none, we'll add another block.\nHang in there!",
								  "Congratulations you made it!\nNow we'll boggle your mind,\nthere are 2339 diffrent\nconfigurations in this stage!$Don't give up!\nRelax!",
								  "Hah! This next stage will\nsurprise you!\nYou now have 12 diffrent\nshapes to work with ...$Show me how far you can\ngo dude!",
								  "Well, well, well.\nYou seem to have made it all\nthis way! As a token of our\nappreciation for your skill,...$Here's another square block!\nTake the square block, and try\nit for the last level!$It looks simple, but there are\n16146 configurations!\n\nHey dude, you're on it again.",
          						  "Congratulations you made it!\nYou've earned the password\nfor the level select!\nthe password is 'davy'"};
int Lines,Chars,TextDelay,PageNr,TekstNr;
int NrOfChars;
int Teller;
int[100][255] List;


    
void OldManSpeakingInit()
{
	Background = NULL;
	Fairy = CFairy_Create(240*xscale,175*yscale,6*fpsscale);
	switch (Level)
	{
		case 0:
		case 11:
		case 12:
		case 35:
		case 36:
			SelectMusic(musOldman);
			TextDelay = 0;
			NrOfChars = 0;
			Lines = 0;
			Chars =0;
			PageNr = 0;
			switch (Level)
			{
				case 0:
					TekstNr = 0;
					break;
				case 11:
					TekstNr = 1;
					break;
				case 12:
					TekstNr = 2;
					break;
				case 35:
					TekstNr = 3;
					break;
				case 36:
					TekstNr = 4;
					break;
				default: TekstNr = 0;
			}
			Background = loadImageAtPath("graphics/oldman");
			for(Teller=0;Teller<strlen(Tekst[TekstNr]);Teller++)
			{
				if (Tekst[TekstNr][Teller] == '$')
				{
					List[Lines][Chars] = 0;
					Lines++;
					Chars=0;
				}
				else
				{
					List[Lines][Chars] = Tekst[TekstNr][Teller];
					Chars++;
				}
			}
			List[Lines][Chars] = 0;
			playTextSound();
		break;
		default:
			GameState = GSNextStageInit;
			break;
	}
}

void OldManSpeakingDeInit()
{
	stopTextSound();
	if(Background)
		freeTexture(Background);
	CFairy_Destroy(Fairy);
}


void OldManSpeaking()
{
	if(GameState == GSOldManSpeakingInit)
	{
		OldManSpeakingInit();
		if(GameState == GSOldManSpeakingInit)
			GameState -= GSInitDiff;
	}

	if (GameState == GSOldManSpeaking)
	{

		if (gamepad_button_a() == 1)
		{
			if (PageNr < Lines)
			{
				PageNr++;
				NrOfChars = 0;
				playTextSound();
			}
			else
				if (Level < 36)
					GameState = GSNextStageInit;
				else
					GameState = GSCreditsInit;
		}
			/*			case SDLK_ESCAPE:
							Mix_HaltMusic();
							GameState = GSTitleScreenInit;
							break;
			*/
		
		if (gamepad_button_b() == 1)
		{
			if (Level < 36)
				GameState = GSNextStageInit;
			else
				GameState = GSCreditsInit;
		}

		if(gamepad_button_start() == 1)
			GameState = GSTitleScreenInit;
			
		drawTextureZoomed(Background, 0, ScreenXOffset + 0, 0);

		CFairy_Draw(Fairy);
		TextDelay++;
		if (TextDelay == 2)
		{
			if (NrOfChars < strlen(List[PageNr]))
				NrOfChars++;
			else
				stopTextSound();
			TextDelay = 0;
		}
		set_multiply_color(color_black);
		int[255] Text;
		memset(Text, 0, 255);
		strncpy(Text, List[PageNr], NrOfChars); 
		textfont_print_from_left_zoomed(Ash, ScreenXOffset + 50 * xscale, 50 *yscale, Text, xscale, yscale);
		set_multiply_color(color_white);
	}
	
	if(GameState != GSOldManSpeaking)
		OldManSpeakingDeInit();
}


#endif