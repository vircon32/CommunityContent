// ---------------------------------------------------------
//   GAME SESSION DATA
// ---------------------------------------------------------


// board states
int[ 4 ][ 4 ] CurrentBoard;

// indicates which tiles are the result of
// a merge in the last move (this is used
// to determine points and draw highlights)
int[ 4 ][ 4 ] MergedTiles;

// information about the move being made
int MoveX = 0, MoveY = 0;
int LastMoveWasValid = false;

// general game statistics
int PlayedFrames;
int Score;
int Moves;

// specific game information
int LastScoreIncrease;  // will be displayed at the score counter


// ---------------------------------------------------------
//   GAME LOGIC: BASIC FUNCTIONS
// ---------------------------------------------------------

// ---------------------------------------------------------

// determines game win

bool isWinningGame()
{
  for (int i = 0; i < 15; i++)
      if (CurrentBoard[i/4][i%4] != i+1)
        return false;

  return true;
}

// ---------------------------------------------------------

// calculates points corresponding to all merged tiles in the last move
void DetermineScoreIncrease()
{
    LastScoreIncrease = 0;
    
    for( int y = 0; y < 4; y++ )
      for( int x = 0; x < 4; x++ )
        if( MergedTiles[y][x] > 0 )
          LastScoreIncrease += -4;
    
    // now, actually score those points
    Score += LastScoreIncrease;
    if(Score < 0)
      Score = 0;
}

// ---------------------------------------------------------
// ---------------------------------------------------------
//   GAME LOGIC: MOVE RESOLUTION FUNCTIONS
// ---------------------------------------------------------


void ExecuteMoveRight()
{
    for (int y = 0; y < 4; y++)
      for (int x = 0; x < 4; x ++)
        if(CurrentBoard[ y ][ x ] == 0)
        {
          if(x > 0)
          {
            int tmp = CurrentBoard[y][ x - 1 ];
            CurrentBoard[y][ x - 1 ] = CurrentBoard[y][ x ];
            CurrentBoard[y][ x ] = tmp;
            MergedTiles[ y ][ x  ] = 1;
            LastMoveWasValid = true;
            return;
          }
        }
}

// ---------------------------------------------------------

void ExecuteMoveLeft()
{
    for (int y = 0; y < 4; y++)
      for (int x = 0; x < 4; x ++)
        if(CurrentBoard[ y ][ x ] == 0)
        {
          if(x < 3)
          {
            int tmp = CurrentBoard[y][ x + 1 ];
            CurrentBoard[y][ x + 1 ] = CurrentBoard[y][ x ];
            CurrentBoard[y][ x ] = tmp;
            MergedTiles[ y ][ x  ] = 1;
            LastMoveWasValid = true;
            return;
          }
        }

}

// ---------------------------------------------------------

void ExecuteMoveDown()
{
    for (int y = 0; y < 4; y++)
      for (int x = 0; x < 4; x ++)
        if(CurrentBoard[ y ][ x ] == 0)
        {
          if(y > 0)
          {
            int tmp = CurrentBoard[y - 1][ x ];
            CurrentBoard[y - 1 ][ x ] = CurrentBoard[y][ x ];
            CurrentBoard[y][ x ] = tmp;
            MergedTiles[ y ][ x  ] = 1;
            LastMoveWasValid = true;
            return;
          }
        }

}

// ---------------------------------------------------------

void ExecuteMoveUp()
{
    for (int y = 0; y < 4; y++)
      for (int x = 0; x < 4; x ++)
        if(CurrentBoard[ y ][ x ] == 0)
        {
          if(y < 3)
          {
            int tmp = CurrentBoard[y + 1][ x ];
            CurrentBoard[y + 1 ][ x ] = CurrentBoard[y][ x ];
            CurrentBoard[y][ x ] = tmp;
            MergedTiles[ y ][ x  ] = 1;
            LastMoveWasValid = true;
            return;
          }
        }
}

// ---------------------------------------------------------

// this is the general move function, that will delegate its
// work to the specific direction move and do general processing
void ExecuteMove()
{
    LastMoveWasValid = false;
    // first, clear the next board state
    memset( &MergedTiles[0][0], 0, sizeof(MergedTiles) );
       
    
    // Movement
    if( MoveX < 0 )
      ExecuteMoveLeft();
    
    else if( MoveX > 0 )
      ExecuteMoveRight();
    
    else if( MoveY < 0 )
      ExecuteMoveUp();
    
    else // MoveY > 0
      ExecuteMoveDown();
    
    
    // increase move counter only when a move was valid
    // (if no tiles have moved, it is not considered a move)
    if( LastMoveWasValid )
      Moves++;
}

// ---------------------------------------------------------

// sets the initial game state for a new game
void ResetGameState()
{
    // randomize
    srand( get_time() );
    
    // clear any board contents
    memset( &CurrentBoard, 0, sizeof(CurrentBoard) );

    // populate board to winning state
    for( int i = 0; i < 15; i++ )
    {
        CurrentBoard[ i / 4 ][ i % 4 ] = i+1;
    }

    //move randomly away from winning state
    for (int i = 0; i < 1000; i++)
    {
      LastMoveWasValid = false;
      while(!LastMoveWasValid)
      {
        int dir = rand() % 4;
        if( dir == 0 )
          ExecuteMoveLeft();
        else if( dir == 1 )
          ExecuteMoveRight();
        else if( dir == 2 )
          ExecuteMoveUp();
        else // dir == 3
          ExecuteMoveDown();
      }
    }

    //now reset Mergedtiles as the random movements had set values there
    memset( &MergedTiles, 0, sizeof(MergedTiles) );
       
    // reset game session data
    PlayedFrames = 0;
    Score = 999999;
    Moves = 0;
    LastScoreIncrease = 0;
    LastMoveWasValid = false;
    
}
