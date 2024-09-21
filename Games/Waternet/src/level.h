#ifndef level_h
#define level_h

#include "misc.h"
#include "level.h"
#include "commonvars.h"
#include "helperfuncs.h"

#define NorthBit 0
#define EastBit 1
#define SouthBit 2
#define WestBit 3

void ClearBit(int* bitFlag, int bit)
{
	(*bitFlag) &=  ~(1<< bit);
}

void SetBit(int* bitFlag, int bit)
{
	(*bitFlag) |= (1<< bit);
}

int BitSet(int bitFlag, int bit) 
{
	return bitFlag & (1 << bit);
}

void drawLevel()
{
    //background
    for (int x = 0; x != maxBoardBgWidth; x++)
    {
        for (int y = 0; y != maxBoardBgHeight; y++)
        {
            set_bkg_tile_xy(x, y, emptyFloor);
        }
    }

    //Draw arrows for vertical / horizontal movement
    if (gameMode != gmRotate)
    {
        for (int x = 0; x != boardWidth; x++)
        {
            set_bkg_tile_xy(boardX + x, boardY - 1, arrowDown);
            set_bkg_tile_xy(boardX + x, boardY + boardHeight, arrowUp);
        }

        for (int y = 0; y != boardHeight; y++)
        {
            set_bkg_tile_xy(boardX - 1, boardY + y, arrowRight);
            set_bkg_tile_xy(boardX + boardWidth, boardY + y, arrowLeft);
        }
    }

    //level    

    int i16 = 0;
    for (int y = 0; y < boardHeight; y++)
    {
        for (int x = 0; x < boardWidth; x++)
        {
            set_bkg_tile_xy(boardX + x, boardY + y, level[i16 + x]);
        }
        i16 += boardWidth;
    }
}

void moveBlockDown(int aTile)
{
    int tmp = level[aTile + boardSize - boardWidth];
    for (int i= boardSize - boardWidth; i != 0 ; i -= boardWidth)
    {
        level[aTile + i] = level[aTile + i -boardWidth];
    }
    level[aTile] = tmp;
}

void moveBlockUp(int aTile)
{
    int tmp = level[aTile - boardSize + boardWidth];
    for (int i= boardSize - boardWidth; i != 0; i -= boardWidth)
    {
        level[aTile - i] = level[aTile - i + boardWidth];
    }
    level[aTile] = tmp;
}

void moveBlockRight(int aTile)
{
    int tmp = level[aTile + boardWidth - 1];
    for (int i= aTile + boardWidth - 1; i != aTile; i--)
    {
        level[i] = level[i -1];
    }
    level[aTile] = tmp;
}

void moveBlockLeft(int aTile)
{
    int tmp = level[aTile - boardWidth + 1];
    for (int i= aTile - boardWidth + 1; i != aTile; i++)
    {
        level[i] = level[i +1];
    }
    level[aTile] = tmp;
}

//rotates a tile by change the tilenr in the level
//there are 16 tiles per set and there are 3 sets no water, water filled, and special start tiles
void rotateBlock(int aTile)
{
    switch (level[aTile])
    {
        case 1:
        case 17:
        case 33:
            level[aTile] = 2;
            break;
        case 2:
        case 18:
        case 34:
            level[aTile] = 4;
            break;
        case 3:
        case 19:
        case 35:
            level[aTile] = 6;
            break;
        case 4:
        case 20:
        case 36:
            level[aTile] = 8;
            break;
        case 5:
        case 21:
        case 37:
            level[aTile] = 10;
            break;
        case 6:
        case 22:
        case 38:
            level[aTile] = 12;
            break;
        case 7:
        case 23:
        case 39:
            level[aTile] = 14;
            break;
        case 8:
        case 24:
        case 40:
            level[aTile] = 1;
            break;
        case 9:
        case 25:
        case 41:
            level[aTile] = 3;
            break;
        case 10:
        case 26:
        case 42:
            level[aTile] = 5;
            break;
        case 11:
        case 27:
        case 43:
            level[aTile] = 7;
            break;
        case 12:
        case 28:
        case 44:
            level[aTile] = 9;
            break;
        case 13:
        case 29:
        case 45:
            level[aTile] = 11;
            break;
        case 14:
        case 30:
        case 46:
            level[aTile] = 13;
            break;
        default:
            break;
    }
}

void shuffleSlide(int aTile)
{
    int rnd = rand() % 4;
    if (rnd == 0)
    {
        moveBlockUp((aTile % boardWidth) + boardSize - boardWidth);
    }
    else
    {
        if (rnd == 1)
        {
            moveBlockDown((aTile % boardWidth));
        }
        else
        {
            if(rnd == 2)
            {
                moveBlockLeft(boardWidth - 1 + aTile -(aTile % boardWidth));
            }
            else
            {
                moveBlockRight(aTile - (aTile % boardWidth));
            }
        }
    }
}

void shuffleRotate(int aTile)
{
    int rnd = rand() % 4;
    for (int i = 0; i < rnd; i++)
    {
        rotateBlock(aTile);
    }
}

void shuffleLevel()
{
    int rnd;
    int j = 0;
    while(j < boardSize)
    {
        if(gameMode == gmRotate)
        {
            shuffleRotate(j);
            j++;
        }
        else
        {
            if(gameMode == gmSlide)
            {
                shuffleSlide(j);
                //for speed up it should be fine as all slide levels are uneven in width / height (except random)
                j+=2;
            }
            else
            {
                if(gameMode == gmRotateSlide)
                {
                    rnd = rand() %2;
                    if(rnd == 0)
                    {
                        shuffleSlide(j);
                        //for speed up
                        j+=2;
                    }
                    else
                    {
                        shuffleRotate(j);
                        j++;
                    }
                }
            }
        }
    }
}

void handleConnectPoint(int aCurrentPoint, int* cellStack, int* cc)
{

    int lookUpX = aCurrentPoint % boardWidth;
    int lookUpY = aCurrentPoint / boardWidth;
    
    if ((lookUpY> 0) && (!BitSet(level[aCurrentPoint],NorthBit)))
    {
        int tmp = aCurrentPoint - boardWidth;
        int tmp2 = level[tmp];
        if (((tmp2 < 16) && (!BitSet(tmp2, SouthBit)) ) || 
        ((tmp2 > 15) && (!BitSet(tmp2 - 16,SouthBit))))
        {
            //adapt tile to filled tile
            if(level[aCurrentPoint] < 16)
            { 
                level[aCurrentPoint] += 16;
            }

            //add neighbour to cellstack of to handle tiles
            if (tmp2 < 16)
            {
                cellStack[(*cc)++] = tmp;
            }
        }
        
    }

    //if tile has passage to the east and east neigbour passage to the west 
    if  ((lookUpX  + 1 < boardWidth) && (!BitSet(level[aCurrentPoint],EastBit)))
    {
        int tmp = aCurrentPoint + 1;
        int tmp2 = level[tmp];
        if (((tmp2 < 16) && (!BitSet(tmp2,WestBit))) || 
        ((tmp2 > 15) && (!BitSet(tmp2 - 16, WestBit) )))
        {
            //adapt tile to filled tile
            if(level[aCurrentPoint] < 16)
            { 
                level[aCurrentPoint] += 16;
            }

            //add neighbour to cellstack of to handle tiles
            if (tmp2 < 16)
            {
                cellStack[(*cc)++] = tmp;
            }

        }
    }

    //if tile has passage to the south and south neigbour passage to the north 
    if ((lookUpY + 1 < boardHeight) && (!BitSet(level[aCurrentPoint],SouthBit)))
    {
        int tmp = aCurrentPoint + boardWidth;
        int tmp2 = level[tmp];
        if (((tmp2 < 16) && (!BitSet(tmp2,NorthBit))) || 
        ((tmp2 > 15) && (!BitSet(tmp2 - 16, NorthBit))))
        {
            //adapt tile to filled tile
            if(level[aCurrentPoint] < 16)
            { 
                level[aCurrentPoint] += 16;
            }

            //add neighbour to cellstack of to handle tiles
            if (tmp2 < 16)
            {
                cellStack[(*cc)++] = tmp; 
            }
        } 
    }

    //if tile has passage to the west and west neigbour passage to the east 
    if  ((lookUpX > 0) && (!BitSet(level[aCurrentPoint], WestBit)))
    {
        int tmp = aCurrentPoint - 1;
        int tmp2 = level[tmp];
        if (((tmp2 < 16) && (!BitSet(tmp2, EastBit))) ||
        ((tmp2 > 15) && (!BitSet(tmp2 - 16, EastBit))))
        {
            //adapt tile to filled tile
            if(level[aCurrentPoint] < 16)
            { 
                level[aCurrentPoint] += 16;
            }

            //add neighbour to cellstack of to handle tiles
            if(tmp2 < 16)
            {
                cellStack[(*cc)++] = tmp;
            }
        }  
    }

}

void updateConnected()
{
    int[maxBoardSize+1] cellStack;
    //reset all tiles to default not filled one
    for (int i= 0; i != boardSize; i++)
    {
        if (level[i] > 31)
        {
            level[i] -= 32;
        }
        else
        {
            if (level[i] > 15)
            {
                level[i] -= 16;
            }
        }
    } 

    //start with start tile
    int cc = 1;
    handleConnectPoint(startPos, cellStack, &cc);
    while(--cc > 0)
    {
        //if tile is bigger then 15 we already handled this one, continue with next one
        if ((level[cellStack[cc]] < 16))
        {
            handleConnectPoint(cellStack[cc], cellStack, &cc);
        }
    }

    //add start pos special tile
    if (level[startPos] > 15)
    {
        level[startPos] += 16;
    }
    else 
    {
        if (level[startPos] < 16)
        {
            level[startPos] += 32;
        }
    }

}

void generateLevel()
{
    int[4] neighbours = { 0,0,0,0 };
    int[maxBoardSize+5] cellStack;
    int currentPoint = 0;
    int visitedRooms = 1;
    int tmp, tmp2;
    int selectedNeighbour;
    int neighboursFound;
    int lookUpX, lookUpY;
    int rnd;
    int cc = 4;

    
    memset(cellStack, 0, maxBoardSize + 4);
    //generate a lookup table so we don't have to use modulus or divide constantly
    //generateLookupTable(boardWidth, boardHeight);
    
    //intial all walls value in every room we will remove bits of this value to remove walls
    memset(level, 0xf, boardSize);

    while (visitedRooms != boardSize)
    {
        neighboursFound = 0;
        lookUpX = currentPoint % boardWidth;
        lookUpY = currentPoint / boardWidth;

        tmp  = currentPoint+1; 
        //tile has neighbour to the right which we did not handle yet
        if ((level[tmp] == 0xf) && ( lookUpX + 1 < boardWidth))
        {
            neighbours[neighboursFound++] = tmp;
        }
    
        tmp = currentPoint-1; 
        //tile has neighbour to the left which we did not handle yet
        if ((level[tmp] == 0xf) && (lookUpX > 0))
        {
            neighbours[neighboursFound++] = tmp;
        }

        tmp = currentPoint - boardWidth; 
        //tile has neighbour the north which we did not handle yet
        if ((level[tmp] == 0xf) && (lookUpY > 0))
        {
            neighbours[neighboursFound++] = tmp;
        }

        tmp = currentPoint + boardWidth; 
        //tile has neighbour the south which we did not handle yet
        if ((level[tmp] == 0xf) && (lookUpY + 1 < boardHeight))
        {
            neighbours[neighboursFound++] = tmp;
        }

        switch (neighboursFound)
        {
            case 0:
                currentPoint = cellStack[--cc];
                continue;
                break;
            default:
                rnd = rand() % neighboursFound;
                break;
        }
        selectedNeighbour = neighbours[rnd];      
        tmp = (selectedNeighbour % boardWidth);
        //tile has neighbour to the east
        if(tmp > lookUpX)
        {
            //remove west wall neighbour
			ClearBit(&level[selectedNeighbour], WestBit);
            //level[selectedNeighbour] &= ~(8);
            //remove east wall tile
            //level[currentPoint] &= ~(2);
			ClearBit(&level[currentPoint], EastBit);
        }
        else // tile has neighbour to the west
        {
            if(tmp < lookUpX)
            {
                //remove east wall neighbour
                //level[selectedNeighbour] &= ~(2);
				ClearBit(&level[selectedNeighbour], EastBit);
                //remove west wall tile
                //level[currentPoint] &= ~(8);
				ClearBit(&level[currentPoint], WestBit);
            }
            else // tile has neighbour to the north
            {
                tmp2 = selectedNeighbour / boardWidth;
                if(tmp2 < lookUpY)
                {
                    //remove south wall neighbour
                    //level[selectedNeighbour] &= ~(4);
					ClearBit(&level[selectedNeighbour], SouthBit);
                    //remove north wall tile
                    //level[currentPoint] &= ~(1);
					ClearBit(&level[currentPoint], NorthBit);
                }
                else // tile has neighbour to the south
                {
                    if(tmp2 > lookUpY)
                    {
                        //remove north wall neighbour
                        //level[selectedNeighbour] &= ~(1);
						ClearBit(&level[selectedNeighbour], NorthBit);
                        //remove south wall tile
                        //level[currentPoint] &= ~(4);
						ClearBit(&level[currentPoint], SouthBit);
                    }
                }
            }
        }
        
        //add tile to the cellstack
        if(neighboursFound > 1)
        {
            cellStack[cc++] = currentPoint;
        } 
        //set tile to the neighbour   
        currentPoint = selectedNeighbour;
        visitedRooms++;
    }
}

//when all board tiles are not below 16, the level is cleared
//as there are 16 tiles per tilegroup (no water, water, special start with water) 
int isLevelDone()
{
    for (int i=0; i != boardSize; i++)
    {
        if(level[i] < 16)
        {
            return 0;
        }
    }
    return 1;
}

void initLevel(int aRandomSeed)
{
    
    levelDone = 0;
    moves = 0;
    if(difficulty != diffRandom)
    { 
        //use level number + fixed value based on difficulty as seed for the random function
        //this makes sure every level from a difficulty will remain the same
        srand(selectedLevel + (difficulty * 500) + (gameMode * 50));
    }
    else
    {
        srand(aRandomSeed); 
    }
    //set boardsize and max level based on difficulty
    switch (difficulty)
    {
        case diffVeryEasy:
            boardWidth = 5;
            boardHeight = 5;
            maxLevel = levelCount;
            break;
        case diffEasy:
            boardWidth = 6;
            boardHeight = 6;
            maxLevel = levelCount;
            break;
        case diffNormal:
            boardWidth = 7;
            boardHeight = 7;
            maxLevel = levelCount;
            break;
        case diffHard:
            boardWidth = 8;
            boardHeight = 8;
            maxLevel = levelCount;
            break;
        case diffVeryHard:
            boardWidth = 10;
            boardHeight = 8;
            maxLevel = levelCount;
            break;    
        case diffRandom:
            boardWidth = 5 + (rand() % 6);
            boardHeight = 5 + (rand() % 4);
            maxLevel = 0; //special value with random
            break;
    }
    //add space for arrows based on same posadd value (1 or 0 depending if sliding is allowed)
    boardWidth -= posAdd + posAdd;
    boardHeight -= posAdd + posAdd;
    boardSize = boardWidth * boardHeight;
    //generate the level
    generateLevel();
    //startpoint of of level in center of screen
    boardX = (maxBoardBgWidth - boardWidth) >> 1;
    boardY = (maxBoardBgHeight  - boardHeight) >> 1;
    startPos = (boardWidth >> 1) + (boardHeight >> 1) * (boardWidth);
    //startpoint of tile with water and our cursor
    selectionX = boardWidth >> 1;
    selectionY = boardHeight >> 1;

    //level is currently the solution so we still need to shuffle it
    shuffleLevel();
    //update possibly connected tiles already starting from startpoint
    updateConnected();
}

#endif