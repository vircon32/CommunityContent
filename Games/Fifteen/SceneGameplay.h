// ---------------------------------------------------------
//   GAMEPLAY: STATE MANAGEMENT
// ---------------------------------------------------------


int Gameplay_ElapsedFrames;

// ---------------------------------------------------------

void Gameplay_ChangeState( int NewState )
{
    int OldState = GameState;
    GameState = NewState;
    Gameplay_ElapsedFrames = 0;
    
    // some transitions have specific actions
    if( OldState == Gameplay_Initialize )
      play_sound_in_channel( MusicGameplay, ChannelMusic );
}


// ---------------------------------------------------------
//   GAMEPLAY: STATE-SPECIFIC UPDATES
// ---------------------------------------------------------


void Gameplay_RunState_Initialize()
{
    // create a new game
    ResetGameState();
    
    // transition immediately
    Gameplay_ChangeState( Gameplay_Waiting );
}

// ---------------------------------------------------------

void Gameplay_RunState_Waiting()
{
    // check for a player move
    bool PlayerMoved = false;
    
    if( gamepad_left() == 1 )
    {
        PlayerMoved = true;
        MoveX = -1;
        MoveY = 0;
    }
    
    else if( gamepad_right() == 1 )
    {
        PlayerMoved = true;
        MoveX = 1;
        MoveY = 0;
    }
    
    else if( gamepad_up() == 1 )
    {
        PlayerMoved = true;
        MoveX = 0;
        MoveY = -1;
    }
    
    else if( gamepad_down() == 1 )
    {
        PlayerMoved = true;
        MoveX = 0;
        MoveY = 1;
    }
    
    if( PlayerMoved )
    {
        ExecuteMove();
        play_sound( SoundMoveBoard );
        DirectionHighlightFrames = 15;
        
        if( LastMoveWasValid )
          Gameplay_ChangeState( Gameplay_Transition );
    }
    
    // check if game was aborted
    else if( gamepad_button_a() == 1 )
    {
        GameScene = Scene_QuitGame;
        GameState = Dialog_Initialize;
    }
    
    // draw scene
    DrawBackground();
    DrawGUI();
    DrawBoard();
}

// ---------------------------------------------------------

void Gameplay_RunState_Transition()
{
    play_sound( SoundTileCollision );
    
    // new tiles that were merged need to be
    // highlighted and counted as points
    TileHighlightFrames = 10;
    DetermineScoreIncrease();
        
    if( LastScoreIncrease < 0 )
      ScoreHighlightFrames = 30;
    
    if(isWinningGame())
    {
      GameScene = Scene_WinFifteen;
      Gameplay_ChangeState( Dialog_Initialize);
    }
    else
      Gameplay_ChangeState( Gameplay_Waiting );
   
    // draw scene
    DrawBackground();
    DrawGUI();
    DrawBoard();
}


// ---------------------------------------------------------
//   GAMEPLAY: GENERAL UPDATE FUNCTION
// ---------------------------------------------------------


void Gameplay_RunStateMachine()
{
    if( GameState == Gameplay_Initialize )
      Gameplay_RunState_Initialize();
    
    else if( GameState == Gameplay_Waiting )
      Gameplay_RunState_Waiting();
    
    else if( GameState == Gameplay_Transition )
      Gameplay_RunState_Transition();
           
    // count the frames in current state
    Gameplay_ElapsedFrames++;
    
    // decrease remaining frames for highlight effects
    DirectionHighlightFrames--;
    TileHighlightFrames--;
    ScoreHighlightFrames--;
    
    // keep count of the played time
    // (which includes all gameplay states)
    PlayedFrames++;
}
