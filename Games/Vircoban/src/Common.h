#ifndef COMMON_H
#define COMMON_H

#include "Texture.h"
#include "libs/TextFonts/textfont.h"
#include "memcard.h"
#include "Defines.h"

Texture *IMGBackground=NULL,IMGFloor=NULL,IMGPlayer=NULL,IMGBox=NULL,IMGSpot=NULL,IMGEmpty=NULL,IMGWall=NULL,IMGTitleScreen=NULL;
textfont* font,RobotoBig,RobotoMedium,RobotoSmall;
int GameState = GSTitleScreen;
int MusicCount=0,SelectedMusic=0,InstalledLevelPacksCount=0,InstalledLevels=0,SelectedLevel=0,SelectedLevelPack=0,UnlockedLevels=1;
bool GlobalSoundEnabled = true;
int MenuBoxColor, MenuBoxBorderColor, MenuTextColor;
int[MaxLevelPackNameLength] LevelPackName = "";
int[MaxLevelPacks][MaxLevelPackNameLength] InstalledLevelPacks;
int[MaxMusicFiles] Music;
int[NrOfSounds] Sounds;
bool isCustomnTitleScreen;
game_signature GameSignature;

#endif