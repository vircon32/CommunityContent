// ---------------------------------------------------------
//   WIN Fifteen: STATE MANAGEMENT
// ---------------------------------------------------------


// state variables
int WinFifteen_ElapsedFrames;
int WinFifteen_SelectedOption;

// ---------------------------------------------------------

void WinFifteen_ChangeState( int NewState )
{
    GameState = NewState;
    WinFifteen_ElapsedFrames = 0;
    
    // some transitions have specific actions
    if( NewState == Dialog_Highlight )
    {
        stop_channel( ChannelMusic );
        play_sound( SoundWin );
    }
    
    else if( NewState == Dialog_FadeOut )
      play_sound( SoundMenuCancel );
}


// ---------------------------------------------------------
//   WIN Fifteen: DRAWING FUNCTIONS
// ---------------------------------------------------------


void DrawWinFifteenDialog( bool DrawCursor )
{
    select_region( RegionDialogWin );
    draw_region_at( 76,103 );
    
    select_region( RegionDialogYesNo );
    draw_region_at( 76,195 );
    
    select_region( RegionTile2 + 14 );
    draw_region_at( 124,151 );
    
    select_region( RegionTextContinue );
    draw_region_at( 178,169 );
    
    if( DrawCursor )
    {
        // draw cursor animation at the correct option
        int CursorFrame = (WinFifteen_ElapsedFrames / 3) % 8;
        select_region( FirstRegionCursor + CursorFrame );
        
        if( WinFifteen_SelectedOption == 1 )
          draw_region_at( 271,224 );
        else
          draw_region_at( 119,224 );
    }
}


// ---------------------------------------------------------
//   WIN Fifteen: STATE-SPECIFIC UPDATES
// ---------------------------------------------------------


void WinFifteen_RunState_Initialize()
{
    // disable any other highlights
    DirectionHighlightFrames = 0;
    TileHighlightFrames = 0;
    ScoreHighlightFrames = 0;
    
    // initialize selection
    // (set continue by default, to avoid mistakes)
    WinFifteen_SelectedOption = 1;
    
    // transition immediately
    WinFifteen_ChangeState( Dialog_Highlight );
}

// ---------------------------------------------------------

void WinFifteen_RunState_Highlight()
{
    // draw the scene
    DrawBackground();
    DrawGUI();
    DrawBoard();
    
    // do a blinking highlight for all 15 tiles
    if( WinFifteen_ElapsedFrames & 16 )
    {
        set_blending_mode( blending_add );
        select_region( RegionTileHighlight );
        
        for( int y = 0; y < 4; y++ )
          for( int x = 0; x < 4; x++ )
            if( CurrentBoard[ y ][ x ] == 15 ) 
              draw_region_at( 100 + 75*x, 67 + 75*y );
              
        set_blending_mode( blending_alpha );
    }
    
    // when finished, transition
    if( WinFifteen_ElapsedFrames >= 125 )
      WinFifteen_ChangeState( Dialog_Choose );
}

// ---------------------------------------------------------

void WinFifteen_RunState_Choose()
{   
   
    // buttons A or Start confirm selection
    if( gamepad_button_a() == 1 || gamepad_button_start() == 1 )
    {
             
        // apply end of game
        WinFifteen_ChangeState( Dialog_FadeOut );
    }
    
    // draw the scene
    DrawBackground();
    DrawGUI();
    DrawWinFifteenDialog( true );
}

// ---------------------------------------------------------

void WinFifteen_RunState_FadeOut()
{
    // when fade-out ends, apply selection
    if( WinFifteen_ElapsedFrames >= 45 )
    {
        // apply end of game
        GameScene = Scene_Title;
        GameState = Title_Initialize;
    }
    
    // draw scene
    DrawBackground();
    DrawGUI();
    DrawWinFifteenDialog( false );
    
    // fade out to black
    int AlphaLevel = min( 255, 255 * WinFifteen_ElapsedFrames / 45 );
    clear_screen( make_color_rgba( 0,0,0,AlphaLevel ) );
}


// ---------------------------------------------------------
//   WIN Fifteen: GENERAL UPDATE FUNCTION
// ---------------------------------------------------------


void WinFifteen_RunStateMachine()
{
    if( GameState == Dialog_Initialize )
      WinFifteen_RunState_Initialize();
    
    else if( GameState == Dialog_Highlight )
      WinFifteen_RunState_Highlight();
    
    else if( GameState == Dialog_Choose )
      WinFifteen_RunState_Choose();
    
    else if( GameState == Dialog_FadeOut )
      WinFifteen_RunState_FadeOut();
    
    // count the frames in current state
    WinFifteen_ElapsedFrames++;
}
