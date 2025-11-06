#ifndef WORM_H
#define WORM_H

#include "libs/TextFonts/textfont.h"

#define ScreenWidth 640
#define ScreenHeight 360

#define ObstacleWidth 12
#define ObstacleHeight 35
#define ObstacleSpaceFromTunnel 10

#define PlayerWidthHeight 5

#define CollectibleWidth 20
#define CollectibleHeight 20
#define CollectibleSpaceFromTunnel 30

#define StartTunnelSpeed 2
#define StartTunnelPlayableGap 180
#define TunnelMinimumPlayableGap 120
#define MaxTunnelSpeed 7
#define OffScreenTunnelSections 3

#define tunnelSectionWidth 8
#define tunnelSpacer 16
#define StartSpeedTarget 50

#define ScreenBorderWidth 7

#define Gravity 0.20

#define player_x 250

#define MaxGameModes 5

#define maxSeed 101

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
int score = 0, numTunnelSections = 0, numVisibleTunnelSections = 0, selSeed = 0, seed = 1, tunnelPlayableGap = StartTunnelPlayableGap, obstacleCount = 0, collectibleCount = 0, tunnelSpeed = StartTunnelSpeed;
int gameMode = 0, speedTarget = StartSpeedTarget, startDelay=0, MaxObstacles = 4, MaxCollectibles = 3;
float player_y = 250, playerSpeed = 0;
Rect[ScreenWidth*2] tunnelParts; // in case spacing is 1
Point[ScreenWidth] playerTrail;
Rect[10] obstacles;
Rect[10] collectibles;
bool playing = false;

#endif