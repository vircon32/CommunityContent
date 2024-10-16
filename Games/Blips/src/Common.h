#ifndef COMMON_H
#define COMMON_H

#include "libs/TextFonts/textfont.h"
#include "Texture.h"
#include "Defines.h"
#include "memcard.h"

bool GlobalSoundEnabled = true;
int[NrOfSounds] Sounds;
int Music;

game_signature GameSignature;

Texture* IMGBackground=NULL,IMGFloor=NULL,IMGPlayer=NULL,IMGBox=NULL,IMGEmpty=NULL,IMGTitleScreen=NULL,IMGWall=NULL,
        IMGIntro1=NULL,IMGIntro2=NULL,IMGIntro3=NULL,IMGBomb=NULL,IMGDiamond=NULL,IMGExplosion=NULL,IMGGrid=NULL;

textfont* font, BigFont,MonoFont;
int GameState = GSIntro;
int InstalledLevelPacksCount=0,InstalledLevels=0,SelectedLevel=0,SelectedLevelPack=0,UnlockedLevels=1;
int MenuBoxColor, MenuBoxBorderColor, MenuTextColor;
int[21] LevelPackName;
int[MaxLevelPacks][21] InstalledLevelPacks;
#endif