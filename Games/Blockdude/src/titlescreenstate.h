#ifndef TITLESCREENSTATE_H
#define TITLESCREENSTATE_H

#include "input.h"
#include "fonts/Roboto_Bold_32.h"

void TitleScreenInit()
{
	SelectMusic(musTitle);
	NeedRedraw = true;	
}

void TitleScreen()
{

	if (GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSDiff;
	}

	if (!AskingQuestion)
	{
		if(gamepad_button_r() == 1)
		{
			playMenuSelectSound();
			int i = skinSaveState();
			i++;
			if (i == MAXSKINS)
				i = 0;
			setSkinSaveState(i);
			LoadGraphics();
			NeedRedraw = true;
		}


		if (gamepad_left() == 1)
		{
			int i;
			switch (titleStep)
			{
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(true);
						setSoundOnSaveState(true);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(true);
							setSoundOnSaveState(true);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(false);
								setSoundOnSaveState(false);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(false);
								setSoundOnSaveState(false);
							}
						}
					}
					
					NeedRedraw = true;
    				break;
				case opSkin:
					playMenuSelectSound();
					i = skinSaveState();
					i--;
					if (i == -1)
						i = MAXSKINS - 1;
					setSkinSaveState(i);
					LoadGraphics();
					
					NeedRedraw = true;
					break;
				case opHelpBar:
					playMenuSelectSound();
					setGameHelpBarSaveState(!gameHelpBarSaveState());
					NeedRedraw = true;
					break;
				}
				break;
			case tsMainMenu:
				switch (titleSelection)
				{
				case mmPack:
					CurrentLevelPackIndex--;
					if (CurrentLevelPackIndex == -1)
						CurrentLevelPackIndex = FoundLevelPacks-1;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		if (gamepad_right() == 1)
		{
			int i;
			switch (titleStep)
			{
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(false);
						setSoundOnSaveState(false);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(false);
							setSoundOnSaveState(false);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
						}
					}

					
					NeedRedraw = true;
					break;
				case opSkin:
					playMenuSelectSound();
					i = skinSaveState();
					i++;
					if (i == MAXSKINS)
						i = 0;
					setSkinSaveState(i);
					LoadGraphics();
					
					NeedRedraw = true;
					break;
				case opHelpBar:
					playMenuSelectSound();
					setGameHelpBarSaveState(!gameHelpBarSaveState());
					NeedRedraw = true;
					break;
				}
				break;
			case tsMainMenu:
				switch (titleSelection)
				{
				case mmPack:
					CurrentLevelPackIndex++;
					if (CurrentLevelPackIndex == FoundLevelPacks)
						CurrentLevelPackIndex = 0;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}


		if (gamepad_down() == 1 )
		{
			switch (titleStep)
			{
			case tsMainMenu:
				if (titleSelection < mmCount - 1)
				{
					titleSelection++;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			case tsOptions:
				if (titleSelection < opCount - 1)
				{
					titleSelection++;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			}
		}

		if (gamepad_up() == 1)
		{
			switch (titleStep)
			{
			case tsMainMenu:
			case tsOptions:
				if (titleSelection > 0)
				{
					titleSelection--;
					playMenuSound();
					NeedRedraw = true;
				}
				break;
			}
		}

		if (gamepad_button_b() == 1)
		{
			switch (titleStep)
			{
			case tsOptions:
				titleStep = tsMainMenu;
				titleSelection = mmOptions;
				playMenuBackSound();
				NeedRedraw = true;
				break;
			case tsCredits:
				break;
			}
		}

		if ((gamepad_button_a() == 1) || (gamepad_button_start() == 1))
		{
			int i;
			switch (titleStep)
			{
			case tsMainMenu:
				switch (titleSelection)
				{
				case mmStartGame:
					if (MaxLevels[CurrentLevelPackIndex] > 0)
					{
						SelectedLevel = lastUnlockedLevel();
						GameState = GSStageSelectInit;
						playMenuSelectSound();
					}
					break;
				case mmPack:
					CurrentLevelPackIndex++;
					if (CurrentLevelPackIndex == FoundLevelPacks)
						CurrentLevelPackIndex = 0;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				case mmCredits:
					playMenuSelectSound();
					AskQuestion(qsCredits, "Blockdude was created by Willems Davy.\nRoboto Fonts by Google.\nTech skin and Default skin by Fusion Power.\nFlat skin by Klas Kroon & Kris Katiesen.\nKenney's skin by Kenney.\nMusic By DonSkeeto.\nLevels from blockman by Soleau Software.");
					break;
				case mmOptions:
					titleStep = tsOptions;
					titleSelection = opMusicSound;
					playMenuSelectSound();
					NeedRedraw = true;
					break;
				}
				break;
			case tsOptions:
				switch (titleSelection)
				{
				case opMusicSound:
					if (isMusicOn() && isSoundOn())
					{
						setMusicOn(false);
						setMusicOnSaveState(false);
						setSoundOn(false);
						setSoundOnSaveState(false);
					}
					else
					{
						if (!isMusicOn() && !isSoundOn())
						{
							setMusicOn(true);
							setMusicOnSaveState(true);
							setSoundOn(false);
							setSoundOnSaveState(false);
						}
						else
						{
							if (isMusicOn() && !isSoundOn())
							{
								setMusicOn(false);
								setMusicOnSaveState(false);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
							else
							{
								setMusicOn(true);
								setMusicOnSaveState(true);
								setSoundOn(true);
								setSoundOnSaveState(true);
							}
						}
					}

					playMenuSelectSound();
					NeedRedraw = true;
					break;
				case opSkin:
					playMenuSelectSound();
					i = skinSaveState();
					i++;
					if (i == MAXSKINS)
						i = 0;
					setSkinSaveState(i);
					LoadGraphics();
					NeedRedraw = true;
					break;
				case opHelpBar:
					playMenuSelectSound();
					setGameHelpBarSaveState(!gameHelpBarSaveState());
					NeedRedraw = true;
					break;
				case opBack:
					titleStep = tsMainMenu;
					titleSelection = mmOptions;
					playMenuBackSound();
					NeedRedraw = true;
					break;
				}
				break;
			case tsCredits:
				break;
			}
		}
	}

	if (NeedRedraw)
	{
		NeedRedraw = false;
		drawTexture(IMGTitleScreen, 0, 0, 0);
		set_multiply_color(TitleTextColor);
		int[100] Msg;
		int MenuX = 220;
		int MenuY = 85;
		switch (titleStep)
		{
		case tsMainMenu:
			strcpy(Msg, "Start Game\n");
			if (FoundLevelPacks > 0)
			{
				strcat(Msg, "Pack:");
				strcat(Msg, LevelPacks[CurrentLevelPackIndex]);
			}
			strcat(Msg, "\nOptions\nCredits\n");
			
			textfont_print_from_left(&FontRoboto_Bold_32,MenuX + 20,MenuY,Msg);
		
			switch (titleSelection)
			{
			case mmStartGame:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, ">");
				break;
			case mmPack:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n>");
				break;
			case mmOptions:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n\n>");
				break;
			case mmCredits:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n\n\n>");
				break;
			}
			break;
		case tsCredits:
			break;
		case tsOptions:
			strcpy(Msg, "Audio ");
			if(isMusicOn())
				strcat(Msg, "M ");
			else
				strcat(Msg, "  ");
			
			if(isSoundOn())
				strcat(Msg, "S");
			else
				strcat(Msg, " ");
			
			
			
			strcat(Msg, "\n");
			strcat(Msg, skins[skinSaveState()]);
			strcat(Msg, " skin\n");

			if(gameHelpBarSaveState())
				strcat(Msg, "Game HelpBar\n");
			else
				strcat(Msg, "No Game HelpBar\n");
			
			strcat(Msg, "Back");

			textfont_print_from_left(&FontRoboto_Bold_32,MenuX + 20,MenuY, Msg);
			
			switch (titleSelection)
			{
			case opMusicSound:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, ">");
				break;			
			case opSkin:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n>");
				break;
			case opHelpBar:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n\n>");
				break;
			case opBack:
				textfont_print_from_left(&FontRoboto_Bold_32,MenuX,MenuY, "\n\n\n>");
				break;
			}
			break;

		}
		textfont_print_centered(&FontRoboto_Bold_12, screen_width >> 1,240, "Use dpad to select, button A to confirm, B for back");
		set_multiply_color(color_white);
	}

	int id = -1;
	bool answered = false;

	id = -1;
	answered = false;
	AskQuestionUpdate(&id, &answered, AskingQuestionID);
}


#endif