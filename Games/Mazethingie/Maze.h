#ifndef MAZE_H
#define MAZE_H

#include "Mazethingie.h"

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

void DrawMaze()
{
	
    int X,Y,I;
	//clear_screen (color_red);
    set_multiply_color(color_white);
    for (Y= 0;Y< MazeHeight;Y++)
        for(X = 0;X < MazeWidth;X++)
        {
			I = (Y*MazeWidth) + X;
            //north wall
			if (BitSet(Maze[I], 0))
            {
                draw_line(xoffset + (X+1) * BoxWidth,yoffset + (Y+1) * BoxHeight,xoffset + (X+2)*BoxWidth-1,yoffset + (Y+1)*BoxHeight);
            }

			//east wall
			if(BitSet(Maze[I], 1))
            {
                draw_line(xoffset + (X+2) * BoxWidth,yoffset + (Y+1) * BoxHeight,xoffset + (X+2)*BoxWidth,yoffset + (Y+2)*BoxHeight);
            }

			//south wall
            if(BitSet(Maze[I], 2))
            {
                draw_line(xoffset + (X+1) * BoxWidth,yoffset + (Y+2) * BoxHeight,xoffset + (X+2)*BoxWidth-1,yoffset + (Y+2)*BoxHeight);
            }

			//west wall
            if(BitSet(Maze[I], 3))
            {
                draw_line(xoffset + (X+1) * BoxWidth,yoffset + (Y+1) * BoxHeight,xoffset + (X+1)*BoxWidth,yoffset + (Y+2)*BoxHeight);
            }
        }
}

void GenerateMaze()
{
    int[4] neighbours;
    int[MaxMazeSize] cellStack;
    int cc = 0;
    int currentPoint = 0;
    int visitedRooms = 1;
    int tmp2;
    int selectedNeighbour;
    int rnd;
    
    //intial all walls value in every room we will remove bits of this value to remove walls
    memset(Maze, 0xf, MaxMazeSize);

	while (visitedRooms != MazeHeight*MazeWidth)
    {
        int neighboursFound = 0;
        int lookUpX = currentPoint % MazeWidth;
        int lookUpY = currentPoint / MazeWidth;
        int tmp  = currentPoint+1; 
        //tile has neighbour to the right which we did not handle yet
        if (( lookUpX + 1 < MazeWidth) && (Maze[tmp] == 0xf))
            neighbours[neighboursFound++] = tmp;
    
        tmp = currentPoint-1; 
        //tile has neighbour to the left which we did not handle yet
        if ((lookUpX > 0) && (Maze[tmp] == 0xf))
            neighbours[neighboursFound++] = tmp;

        tmp = currentPoint - MazeWidth; 
        //tile has neighbour the north which we did not handle yet
        if ((lookUpY > 0) && (Maze[tmp] == 0xf))
            neighbours[neighboursFound++] = tmp;

        tmp = currentPoint + MazeWidth; 
        //tile has neighbour the south which we did not handle yet
        if ((lookUpY + 1 < MazeHeight) && (Maze[tmp] == 0xf))
            neighbours[neighboursFound++] = tmp;

        switch (neighboursFound)
        {
            case 0:
                currentPoint = cellStack[--cc];
                continue;
                break;
            default:
                rnd = (int)(rand() % neighboursFound);
                break;
        }
        selectedNeighbour = neighbours[rnd];      
        tmp = (selectedNeighbour % MazeWidth);
        //tile has neighbour to the east
        if(tmp > lookUpX)
        {
            //remove west wall neighbour
            ClearBit(&Maze[selectedNeighbour], 3);
            //remove east wall tile
            ClearBit(&Maze[currentPoint], 1);
        }
        else // tile has neighbour to the west
        {
            if(tmp < lookUpX)
            {
                //remove east wall neighbour
                ClearBit(&Maze[selectedNeighbour], 1);
                //remove west wall tile
                ClearBit(&Maze[currentPoint], 3);
            }
            else // tile has neighbour to the north
            {
                tmp2 = selectedNeighbour / MazeWidth;
                if(tmp2 < lookUpY)
                {
                    //remove south wall neighbour
                    ClearBit(&Maze[selectedNeighbour], 2);
                    //remove north wall tile
                    ClearBit(&Maze[currentPoint], 0);
                }
                else // tile has neighbour to the south
                {
                    if(tmp2 > lookUpY)
                    {
                        //remove north wall neighbour
                        ClearBit(&Maze[selectedNeighbour], 0);
                        //remove south wall tile
                        ClearBit(&Maze[currentPoint], 2);
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
	ClearBit(&Maze[0], 0);
    ClearBit(&Maze[(MazeWidth)*(MazeHeight)-1], 2);
    PlayerPosX = MazeWidth -1;
    PlayerPosY = MazeHeight - 1;
	xoffset = (((screen_width/BoxWidth) - (MazeWidth+2)) * BoxWidth) >> 1;
	yoffset = (((screen_height/BoxHeight) - (MazeHeight+2)) * BoxHeight) >> 1;
}

#endif