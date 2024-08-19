#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG 0

//original game on playdate was 400x240@30fps
#define ORIGINAL_FRAMERATE 30.0
#define ORIGINAL_WIDTH 400
#define ORIGINAL_HEIGHT 240

//we take 600 to evenly scale 400x240 to 600x360
#define xscale ((float)600 / (float)ORIGINAL_WIDTH )
#define yscale ((float)screen_height / (float)ORIGINAL_HEIGHT)
//to center the screen as we don't use 40 pixels
#define screenxoffset 20

#define MaxLevelPacks 101
#define NrOfSounds 10
#define SND_Destroy 0
#define SND_NoMoves 1
#define SND_Win 2
#define SND_WinExit 3
#define SND_DirectionMove 4
#define SND_GameOver 5
#define SND_Score 6
#define SND_LevelEditorSelect 7
#define SND_Select 8
#define SND_Error 9
#define MaxHighScores 5

#define GSNone 0
#define GSGameOver 1
#define GSTitleScreen 2
#define GSOptions 3
#define GSLevelpackDone 4
#define GSHighScores 5
#define GSCredits 6
#define GSQuit 7
#define GSGame 8
#define GSStageClear 9
#define GSGameOverInit 10
#define GSTitleScreenInit 11
#define GSOptionsInit 12
#define GSLevelpackDoneInit 13
#define GSHighScoresInit 14
#define GSCreditsInit 15
#define GSGameInit 16
#define GSStageClearInit 17

#define showFPS 0
#define MNone 4
#define MUp 0
#define MRight 1
#define MDown 2
#define MLeft 3


#define NrOfRows 12
#define NrOfCols 10
#define IDBox1 1
#define IDBox2 2
#define IDBox3 3
#define IDBox4 4
#define TileWidth 20 * xscale
#define TileHeight 20 * yscale
#define MaxLevels 80
#define Xoffset (int)(175 * xscale)
#define Yoffset 0

#endif