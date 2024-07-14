#ifndef MAZETHINGIE_H
#define MAZETHINGIE_H

#include "libs/TextFonts/textfont.h"

#define GSGame 0
#define GSTitleScreen 1

#define BoxWidth 10
#define BoxHeight 10

#define MaxMazeWidth ((int)((screen_width / BoxWidth) -2))
#define MaxMazeHeight ((int)((screen_height / BoxHeight) -2))
#define MaxMazeSize (MaxMazeWidth * MaxMazeHeight)

#define PlayerSpeedTickVal 10
#define MenuSpeedTickVal 5


// names for textures
#define TextureFullFont 0

// texture regions for full font texture
#define FirstRegionFullFont 0

textfont FontLetters;
int GameState = GSTitleScreen;
int MazeWidth=MaxMazeWidth, MazeHeight=MaxMazeHeight, PlayerPosX=32, PlayerPosY=32, Selection = 1, xoffset = 0, yoffset = 0, framecount = 0, GameWon = 0;
int[MaxMazeSize] Maze;

#endif