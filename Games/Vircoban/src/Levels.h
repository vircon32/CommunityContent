#ifndef LEVELS_H
#define LEVELS_H

#include "Defines.h"

#define MaxLevelFileSize 38000

int*[MaxLevelPacks] LevelPacks;

embedded int[MaxLevelFileSize] level1 = "assets\\levelpacks\\696.sok";
embedded int[MaxLevelFileSize] level2 = "assets\\levelpacks\\696 Part 2.sok";
embedded int[MaxLevelFileSize] level3 = "assets\\levelpacks\\Cosmonotes.sok";
embedded int[MaxLevelFileSize] level4 = "assets\\levelpacks\\Cosmopoly.sok";
embedded int[MaxLevelFileSize] level5 = "assets\\levelpacks\\Erim Sever Collection.sok";
embedded int[MaxLevelFileSize] level6 = "assets\\levelpacks\\GRIGoRusha 2001.sok";
embedded int[MaxLevelFileSize] level7 = "assets\\levelpacks\\GRIGoRusha 2002.sok";
embedded int[MaxLevelFileSize] level8 = "assets\\levelpacks\\GRIGoRusha Remodel Club.sok";
embedded int[MaxLevelFileSize] level9 = "assets\\levelpacks\\GRIGoRusha Special.sok";
embedded int[MaxLevelFileSize] level10 = "assets\\levelpacks\\GRIGoRusha Star.sok";
embedded int[MaxLevelFileSize] level11 = "assets\\levelpacks\\GRIGoRusha Sun.sok";
embedded int[MaxLevelFileSize] level12 = "assets\\levelpacks\\LOMA.sok";
embedded int[MaxLevelFileSize] level13 = "assets\\levelpacks\\Microcosmos.sok";
embedded int[MaxLevelFileSize] level14 = "assets\\levelpacks\\Minicosmos.sok";
embedded int[MaxLevelFileSize] level15 = "assets\\levelpacks\\Myriocosmos.sok";
embedded int[MaxLevelFileSize] level16 = "assets\\levelpacks\\Nabokosmos.sok";
embedded int[MaxLevelFileSize] level17 = "assets\\levelpacks\\Picokosmos.sok";
embedded int[MaxLevelFileSize] level18 = "assets\\levelpacks\\SokEvo.sok";
embedded int[MaxLevelFileSize] level19 = "assets\\levelpacks\\SokHard.sok";
embedded int[MaxLevelFileSize] level20 = "assets\\levelpacks\\SokWhole.sok";

void setupLevels()
{
	LevelPacks[0] = level1;
	LevelPacks[1] = level2;
	LevelPacks[2] = level3;
	LevelPacks[3] = level4;
	LevelPacks[4] = level5;
	LevelPacks[5] = level6;
	LevelPacks[6] = level7;
	LevelPacks[7] = level8;
	LevelPacks[8] = level9;
	LevelPacks[9] = level10;
	LevelPacks[10] = level11;
	LevelPacks[11] = level12;
	LevelPacks[12] = level13;
	LevelPacks[13] = level14;
	LevelPacks[14] = level15;
	LevelPacks[15] = level16;
	LevelPacks[16] = level17;
	LevelPacks[17] = level18;
	LevelPacks[18] = level19;
	LevelPacks[19] = level20;
}

#endif