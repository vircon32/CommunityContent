#ifndef WORM_H
#define WORM_H

#include "libs/TextFonts/textfont.h"

#define ScreenWidth 640
#define ScreenHeight 360

#define ObstacleWidth 10
#define ObstacleHeight 35

#define CollectibleWidth 20
#define CollectibleHeight 20

#define StartTunnelSpeed 2
#define StartTunnelPlayableGap 180
#define TunnelMinimumPlayableGap 120
#define MaxTunnelSpeed 7

#define StartSpeedTarget 50

#define ScreenBorderWidth 7

#define Gravity 0.20

#define player_x 250

#define MaxGameModes 5

// names for textures
#define TextureFullFont 0

// texture regions for full font texture
#define FirstRegionFullFont 0

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

struct Point {
    float x;
    float y;
};

textfont FontLetters;
int score = 0, seed = 0, tunnelPlayableGap = StartTunnelPlayableGap, obstacleCount = 0, collectibleCount = 0, tunnelSpeed = StartTunnelSpeed;
int tunnelSectionWidth = 8, tunnelSpacer = 16, gameMode = 0, speedTarget = StartSpeedTarget, startDelay=0, MaxObstacles = 4, MaxCollectibles = 3;
float player_y = 0, playerSpeed = 0;
Rect[ScreenWidth*2] tunnelParts; // in case spacing is 1
Point[ScreenWidth] playerTrail;
Rect[10] obstacles;
Rect[10] collectibles;
bool playing = false;

#endif