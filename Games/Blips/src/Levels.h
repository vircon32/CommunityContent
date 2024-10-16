#ifndef LEVELS_H
#define LEVELS_H

embedded int[50*50*6] blipslevel1 = "assets\\levelpacks\\bips\\u32_level1.lev";
embedded int[50*50*6] blipslevel2 = "assets\\levelpacks\\bips\\u32_level2.lev";
embedded int[50*50*6] blipslevel3 = "assets\\levelpacks\\bips\\u32_level3.lev";
embedded int[50*50*6] blipslevel4 = "assets\\levelpacks\\bips\\u32_level4.lev";
embedded int[50*50*6] blipslevel5 = "assets\\levelpacks\\bips\\u32_level5.lev";
embedded int[50*50*6] blipslevel6 = "assets\\levelpacks\\bips\\u32_level6.lev";
embedded int[50*50*6] blipslevel7 = "assets\\levelpacks\\bips\\u32_level7.lev";
embedded int[50*50*6] blipslevel8 = "assets\\levelpacks\\bips\\u32_level8.lev";
embedded int[50*50*6] blipslevel9 = "assets\\levelpacks\\bips\\u32_level9.lev";
embedded int[50*50*6] blipslevel10 = "assets\\levelpacks\\bips\\u32_level10.lev";
embedded int[50*50*6] blipslevel11 = "assets\\levelpacks\\bips\\u32_level11.lev";
embedded int[50*50*6] blipslevel12 = "assets\\levelpacks\\bips\\u32_level12.lev";
embedded int[50*50*6] blipslevel13 = "assets\\levelpacks\\bips\\u32_level13.lev";
embedded int[50*50*6] blipslevel14 = "assets\\levelpacks\\bips\\u32_level14.lev";
embedded int[50*50*6] blipslevel15 = "assets\\levelpacks\\bips\\u32_level15.lev";
embedded int[50*50*6] blipslevel16 = "assets\\levelpacks\\bips\\u32_level16.lev";
embedded int[50*50*6] blipslevel17 = "assets\\levelpacks\\bips\\u32_level17.lev";
embedded int[50*50*6] blipslevel18 = "assets\\levelpacks\\bips\\u32_level18.lev";
embedded int[50*50*6] blipslevel19 = "assets\\levelpacks\\bips\\u32_level19.lev";
embedded int[50*50*6] blipslevel20 = "assets\\levelpacks\\bips\\u32_level20.lev";
embedded int[50*50*6] blipslevel21 = "assets\\levelpacks\\bips\\u32_level21.lev";
embedded int[50*50*6] blipslevel22 = "assets\\levelpacks\\bips\\u32_level22.lev";
embedded int[50*50*6] blipslevel23 = "assets\\levelpacks\\bips\\u32_level23.lev";
embedded int[50*50*6] blipslevel24 = "assets\\levelpacks\\bips\\u32_level24.lev";
embedded int[50*50*6] blipslevel25 = "assets\\levelpacks\\bips\\u32_level25.lev";
embedded int[50*50*6] blipslevel26 = "assets\\levelpacks\\bips\\u32_level26.lev";

int*[1][26] Levels;

void setupLevels()
{
	Levels[0][0] = blipslevel1;
	Levels[0][1] = blipslevel2;
	Levels[0][2] = blipslevel3;
	Levels[0][3] = blipslevel4;
	Levels[0][4] = blipslevel5;
	Levels[0][5] = blipslevel6;
	Levels[0][6] = blipslevel7;
	Levels[0][7] = blipslevel8;
	Levels[0][8] = blipslevel9;
	Levels[0][9] = blipslevel10;
	Levels[0][10] = blipslevel11;
	Levels[0][11] = blipslevel12;
	Levels[0][12] = blipslevel13;
	Levels[0][13] = blipslevel14;
	Levels[0][14] = blipslevel15;
	Levels[0][15] = blipslevel16;
	Levels[0][16] = blipslevel17;
	Levels[0][17] = blipslevel18;
	Levels[0][18] = blipslevel19;
	Levels[0][19] = blipslevel20;
	Levels[0][20] = blipslevel21;
	Levels[0][21] = blipslevel22;
	Levels[0][22] = blipslevel23;
	Levels[0][23] = blipslevel24;
	Levels[0][24] = blipslevel25;
	Levels[0][25] = blipslevel26;

}

#endif