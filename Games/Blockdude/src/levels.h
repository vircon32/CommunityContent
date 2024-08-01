#ifndef LEVELS_H
#define LEVELS_H

embedded int[50*50*3] blockmanlevel1 = "assets\\levels\\blockman\\level1.bin";
embedded int[50*50*3] blockmanlevel2 = "assets\\levels\\blockman\\level2.bin";
embedded int[50*50*3] blockmanlevel3 = "assets\\levels\\blockman\\level3.bin";
embedded int[50*50*3] blockmanlevel4 = "assets\\levels\\blockman\\level4.bin";
embedded int[50*50*3] blockmanlevel5 = "assets\\levels\\blockman\\level5.bin";
embedded int[50*50*3] blockmanlevel6 = "assets\\levels\\blockman\\level6.bin";
embedded int[50*50*3] blockmanlevel7 = "assets\\levels\\blockman\\level7.bin";
embedded int[50*50*3] blockmanlevel8 = "assets\\levels\\blockman\\level8.bin";
embedded int[50*50*3] blockmanlevel9 = "assets\\levels\\blockman\\level9.bin";
embedded int[50*50*3] blockmanlevel10 = "assets\\levels\\blockman\\level10.bin";
embedded int[50*50*3] blockmanlevel11 = "assets\\levels\\blockman\\level11.bin";
embedded int[50*50*3] blockmanlevel12 = "assets\\levels\\blockman\\level12.bin";
embedded int[50*50*3] blockmanlevel13 = "assets\\levels\\blockman\\level13.bin";
embedded int[50*50*3] blockmanlevel14 = "assets\\levels\\blockman\\level14.bin";
embedded int[50*50*3] blockmanlevel15 = "assets\\levels\\blockman\\level15.bin";
embedded int[50*50*3] blockmanlevel16 = "assets\\levels\\blockman\\level16.bin";
embedded int[50*50*3] blockmanlevel17 = "assets\\levels\\blockman\\level17.bin";
embedded int[50*50*3] blockmanlevel18 = "assets\\levels\\blockman\\level18.bin";
embedded int[50*50*3] blockmanlevel19 = "assets\\levels\\blockman\\level19.bin";
embedded int[50*50*3] blockmanlevel20 = "assets\\levels\\blockman\\level20.bin";
embedded int[50*50*3] blockmanlevel21 = "assets\\levels\\blockman\\level21.bin";

embedded int[50*50*3] davylevel1 = "assets\\levels\\davy\\level1.bin";
embedded int[50*50*3] davylevel2 = "assets\\levels\\davy\\level2.bin";
embedded int[50*50*3] davylevel3 = "assets\\levels\\davy\\level3.bin";
embedded int[50*50*3] davylevel4 = "assets\\levels\\davy\\level4.bin";

int*[2][21] Levels;

void setupLevels()
{
	Levels[0][0] = blockmanlevel1;
	Levels[0][1] = blockmanlevel2;
	Levels[0][2] = blockmanlevel3;
	Levels[0][3] = blockmanlevel4;
	Levels[0][4] = blockmanlevel5;
	Levels[0][5] = blockmanlevel6;
	Levels[0][6] = blockmanlevel7;
	Levels[0][7] = blockmanlevel8;
	Levels[0][8] = blockmanlevel9;
	Levels[0][9] = blockmanlevel10;
	Levels[0][10] = blockmanlevel11;
	Levels[0][11] = blockmanlevel12;
	Levels[0][12] = blockmanlevel13;
	Levels[0][13] = blockmanlevel14;
	Levels[0][14] = blockmanlevel15;
	Levels[0][15] = blockmanlevel16;
	Levels[0][16] = blockmanlevel17;
	Levels[0][17] = blockmanlevel18;
	Levels[0][18] = blockmanlevel19;
	Levels[0][19] = blockmanlevel20;
	Levels[0][20] = blockmanlevel21;
	Levels[1][0] = davylevel1;
	Levels[1][1] = davylevel2;
	Levels[1][2] = davylevel3;
	Levels[1][3] = davylevel4;
}

#endif