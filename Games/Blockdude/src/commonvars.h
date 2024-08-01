#ifndef commonvars_h
#define commonvars_h

#define zoomlevel 1.5

#define FRAMERATE 60
#define GameMoveSpeed 2					//dec if fps increases
#define PlayerAnimDelay 10				//inc if fps increases
#define FrameDelayInput 1				
#define ViewportMove 4				//dec if fps increases

#define DebugInfoDefault false
#define ShowFpsDefault false
#define BatteryMonitoring false

#define MAXSKINS 5
#define WINDOW_WIDTH 648
#define WINDOW_HEIGHT 360
#define WINDOW_OFFSET -4
#define HALFWINDOWWIDTH 320
#define HALFWINDOWHEIGHT 180
#define TileWidth (int)(16 * zoomlevel)
#define TileHeight (int)(16 * zoomlevel)
#define TileWidthOriginal 16
#define TileHeightOriginal 16

#define NrOfRowsVisible (int)((WINDOW_HEIGHT / TileHeight))
#define NrOfColsVisible (int)((WINDOW_WIDTH / TileWidth))
#define NrOfRows 50
#define NrOfCols 50
#define MaxLevelPacks 2
#define InternalLevelPackCount 1
#define MaxLenLevelPackName 6

#define IDEmpty 1
#define IDPlayer 2
#define IDBox 3
#define IDFloor 4
#define IDExit 5
#define IDEarthGrassLeft 6
#define IDEarthGrassRight 7
#define IDEarthLeft 8
#define IDEarthMiddle 9
#define IDEarthRight 10
#define IDFloatingFloor 11
#define IDFloatingFloorLeft 12
#define IDFloatingFloorMiddle 13
#define IDFloatingFloorRight 14
#define IDFloorLeft 15
#define IDFloorRight 16
#define IDTower 17
#define IDStartTower 18
#define IDTowerShaft 19
#define IDRoof1 20
#define IDRoof2 21
#define IDRoofCornerLeft 22
#define IDRoofCornerRight 23
#define IDRoofCornerBoth 24
#define IDRoofDownRight 25
#define IDRoofDownLeft 26
//not used in engine but have id's for defining the region
#define IDBackground 901
#define IDTitlescreen 902
#define IDIntrobackground 801
#define IDIntroSoleau 802

//these groups also define drawing order for all logic
#define GroupNone 10 //special used in level editor
#define GroupExit 0
#define GroupFloor 1
#define GroupBox 2
#define GroupPlayer 3 //has to be drawn and moved last for logic to work
#define NrOfGroups 4 //group none is ignored



#define AnimBaseLeft 0
#define AnimBaseRight 4
#define AnimBaseLeftJump 8
#define AnimBaseRightJump 12

#define errNoError 0
#define errNoPlayer 1
#define errNoExit 2
#define errBlocksPlayerNotOnAFloor 3
#define errBlocksOnPlayerNotOne 4

#define mmStartGame 0
#define mmPack 1
#define mmOptions 2
#define mmCredits 3
#define mmCount 4

#define opMusicSound 0
#define opSkin 1
#define opHelpBar 2
#define opBack 3
#define opCount 4

#define tsMainMenu 0
#define tsOptions 1
#define tsCredits 2

#define GSDiff 50

#define GSTitleScreen 0
#define GSIntro 1
#define GSGame 2
#define GSStageClear 3
#define GSStageSelect 4

#define GSIntroInit GSIntro + GSDiff
#define GSGameInit GSGame + GSDiff
#define GSStageClearInit GSStageClear + GSDiff
#define GSTitleScreenInit GSTitleScreen + GSDiff
#define GSStageSelectInit GSStageSelect + GSDiff

#define qsErrPlayer 1
#define qsErrExit 2
#define qsErrBlocksOrPlayerNotOnAFloor 3
#define qsErrBlocksOnPlayerNotOne 4
#define qsNotSaved 5
#define qsNotUnlocked 6
#define qsSolvedNotLastLevel 7
#define qsSolvedLastLevel 8
#define qsSolvedLevel 9
#define qsQuitPlaying 10
#define qsRestartLevel 11
#define qsAllDone 12
#define qsCredits 15

#define MOVEQUESIZE 100

#include "texture.h"

Texture* IMGFloor = NULL, IMGPlayer = NULL, IMGBox = NULL, IMGEmpty = NULL, IMGExit = NULL, IMGFloorLeft = NULL, IMGFloorRight = NULL,
    IMGEarthGrassRight = NULL, IMGEarthGrassLeft = NULL, IMGEarthLeft = NULL, IMGEarthRight = NULL, IMGEarthMiddle = NULL, IMGFloatingFloor = NULL,
    IMGFloatingFloorLeft = NULL, IMGFloatingFloorRight = NULL, IMGFloatingFloorMiddle = NULL, IMGTower = NULL, IMGStartTower = NULL, IMGTowerShaft = NULL,
    IMGRoof1 = NULL, IMGRoof2 = NULL, IMGRoofCornerLeft = NULL,IMGRoofCornerRight = NULL, IMGRoofDownRight = NULL, IMGRoofDownLeft = NULL,
    IMGRoofCornerBoth = NULL, IMGBackground = NULL, IMGIntroBackground = NULL, IMGIntroSoleau = NULL, IMGTitleScreen = NULL;


int*[5] skins = { "Default", "Tech", "Flat", "Ti-83", "Kenney"};
int*[MaxLevelPacks] LevelPacks;

int[MaxLevelPacks] MaxLevels = { 21, 4};

int GameState = GSIntroInit;
int SelectedLevel = 0, NeedRedraw = 1, AskingQuestionID = -1, titleStep = tsMainMenu, titleSelection = 0, Option = opMusicSound, CurrentLevelPackIndex = 0, FoundLevelPacks = 0 ;
bool JustAsked = false, AskingQuestion = false, FreeView = false, NeedToReloadGraphics = false;
int IntroScreenNr = 1;
int framecounter = 0;
int Color1 = 0; 
int Color2 = 0;
int TitleTextColor = 0;


#endif