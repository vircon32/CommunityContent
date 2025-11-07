#include "video.h"
#include "string.h"
#include "time.h"
#include "misc.h"
#include "input.h"
#include "memcard.h"
#include "math.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "libs/TextFonts/textfont.h"
#include "Worm.h"
#include "SaveData.h"

//this is just the drawline function with y drawingscale set to tickness
//and y position ofsetted to half tickness
void draw_line_tickness( int x1, int y1, int x2, int y2, int tickness )
{
    // select the bios's white pixel region
    asm{ "out GPU_SelectedTexture, -1"
         "out GPU_SelectedRegion, 256" }
    
    // careful with this case or atan2
    // will produce a hardware error
    if( x1 == x2 && y1 == y2 )
    {
        set_drawing_scale( tickness, tickness );
        draw_region_at( x1, y1 + (tickness >> 1));
        return;
    }
    
    // convert line to polar coordinates
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    float line_distance = 1 + sqrt( delta_x * delta_x + delta_y * delta_y );
    float line_angle = atan2( delta_y, delta_x );
    
    // draw the line
    set_drawing_angle( line_angle );
    set_drawing_scale( line_distance, tickness );
    draw_region_rotozoomed_at( x1, y1 + (tickness >> 1) );
}


void SetupFont()
{
	select_texture( TextureFullFont );
    
    // First we define define 128 consecutive regions (i.e. standard ASCII only)
    // with the same size and hotspot position, as for a constant-width font
    define_region_matrix( FirstRegionFullFont,  0,0,  21,31,  0,31,  16,8,  0 );
    
    // then we redefine some characters to have different widths
    // (note that, for this font, upper and lowercase letters are the same)
    select_region( FirstRegionFullFont + 'M' );
    define_region( 22,0,  46,31,  22,31 );
    select_region( FirstRegionFullFont + 'm' );
    define_region( 22,0,  46,31,  22,31 );
    
    select_region( FirstRegionFullFont + 'W' );
    define_region( 66,0,  90,31,  66,31 );
    select_region( FirstRegionFullFont + 'w' );
    define_region( 66,0,  90,31,  66,31 );
    
    select_region( FirstRegionFullFont + 'I' );
    define_region( 110,0,  121,31,  110,31 );
    select_region( FirstRegionFullFont + 'i' );
    define_region( 110,0,  121,31,  110,31 );
    
    select_region( FirstRegionFullFont + ' ' );
    define_region( 0,64,  15,95,  0,95 );

    FontLetters.character_height = 31;
    FontLetters.use_variable_width = true;
        
    // 2 pixels overlap between characters, 15 pixels between lines
    FontLetters.character_separation = -2;
    FontLetters.line_separation = 15;
    
    // define texture and regions for our characters
    FontLetters.texture_id = TextureFullFont;
    FontLetters.character_zero_region_id = FirstRegionFullFont;

    textfont_read_region_widths( &FontLetters );
}

int randint(int min, int max)
{
    return (rand() % (max - min)) + min;
}

//intersection check instead of fully inside
int checkCollision(Rect* r1, Rect* r2) 
{
    int x_left = max(r1->x, r2->x);
    int x_right = min(r1->x + r1->w, r2->x + r2->w);
    
    int y_top = max(r1->y, r2->y);
    int y_bottom = min(r1->y + r1->h, r2->y + r2->h);

    return ((x_right >= x_left) && (y_bottom >= y_top)); 
}

void drawObstacles()
{
    set_multiply_color(color_cyan);
    for(int i = 0; i < obstacleCount; i++)
        //don't draw not used obstacles
        if((obstacles[i].x > -ObstacleWidth) && (obstacles[i].y > 0))
            draw_filled_rectangle(obstacles[i].x, obstacles[i].y, obstacles[i].x + obstacles[i].w, obstacles[i].y + obstacles[i].h);
}

void moveObstacles()
{
    //for each obstacle
    for (int i = 0; i < obstacleCount; i++)
        //move it at tunnelSpeed
        obstacles[i].x -= tunnelSpeed;
    
    //when have all obstacles on screen
    if (obstacleCount == MaxObstacles)
    {
        //for each obstacle
        for (int i = 0; i < obstacleCount; i++)
        {
            //if obstacle goes of screen to the left
            if(obstacles[i].x + obstacles[i].w < 0 )
            {
                //erase it from the array by moving all other obstalces one position down
                for (int j = 0; j < obstacleCount; j++)
                {
                    obstacles[j].x = obstacles[j+1].x;
                    obstacles[j].y = obstacles[j+1].y;
                }

                //and create a new obstacle at the right side of the screen
                obstacles[obstacleCount-1].x =  ScreenWidth;
                obstacles[obstacleCount-1].y =  tunnelParts[numVisibleTunnelSections*2].h + randint(ObstacleSpaceFromTunnel, tunnelPlayableGap - ObstacleHeight - 2*ObstacleSpaceFromTunnel);
                obstacles[obstacleCount-1].w = ObstacleWidth;
                obstacles[obstacleCount-1].h = ObstacleHeight;
            }
        }
    }

    //when we have no obstacles or the last added obstacle is smaller than the spacing between obstacles from right side of screen
    if ((obstacleCount == 0) || ((obstacleCount > 0) && (obstacleCount < MaxObstacles) && (obstacles[obstacleCount-1].x < ScreenWidth - (ScreenWidth / MaxObstacles))))
    {
        //add a new obstacles
        obstacles[obstacleCount].x =  ScreenWidth;
        obstacles[obstacleCount].y =  tunnelParts[numVisibleTunnelSections*2].h + randint(ObstacleSpaceFromTunnel, tunnelPlayableGap - ObstacleHeight - 2* ObstacleSpaceFromTunnel);
        obstacles[obstacleCount].w = ObstacleWidth;
        obstacles[obstacleCount].h = ObstacleHeight;
        obstacleCount++;
    }
}

void drawCollectibles()
{
    set_multiply_color(color_yellow);
    for(int i = 0; i < collectibleCount; i++)
        //don't draw not used collectible
        if((collectibles[i].x > 0) && (collectibles[i].y > 0))
            draw_filled_rectangle(collectibles[i].x, collectibles[i].y, collectibles[i].x + collectibles[i].w, collectibles[i].y + collectibles[i].h);
  
}

void moveCollectibles()
{
    //for each collectible
    for (int i = 0; i < collectibleCount; i++)
        //move it at tunnelSpeed
        collectibles[i].x -= tunnelSpeed;

    //when we have no collectible or the last added collectible is smaller than the spacing between collectible from right side of screen
    if ((collectibleCount == 0) || ((collectibleCount > 0) && (collectibleCount < MaxCollectibles) && (collectibles[collectibleCount-1].x < ScreenWidth - ((ScreenWidth - player_x) / MaxCollectibles))))
    {
        //add a new collectible (then 10 and 20 is to always add a spacing between tunnel wall the collectible)
        collectibles[collectibleCount].x =  ScreenWidth;
        collectibles[collectibleCount].y =  tunnelParts[numVisibleTunnelSections*2].h + randint(CollectibleSpaceFromTunnel, tunnelPlayableGap - CollectibleHeight - 2 * CollectibleSpaceFromTunnel);
        collectibles[collectibleCount].w = CollectibleWidth;
        collectibles[collectibleCount].h = CollectibleHeight;
        collectibleCount++;
    }
}

void drawPlayer()
{
    set_multiply_color(color_magenta);
    draw_filled_rectangle(player_x-2, player_y-2, player_x+2, player_y+2);
    for (int x = 0; x <= player_x; x++)
    {
        //don't draw not used array pieces
        if ((playerTrail[x].y > 0) && (playerTrail[x].x > 0))
        {
            draw_filled_rectangle((int)playerTrail[x].x-2, (int)playerTrail[x].y-2, (int)playerTrail[x].x+2, (int)playerTrail[x].y+2);
            if (x > 0)
                if ((playerTrail[x-1].y > 0) && (playerTrail[x-1].x > 0))
                    draw_line_tickness((int)playerTrail[x].x, (int)playerTrail[x].y, (int)playerTrail[x-1].x, (int)playerTrail[x-1].y, PlayerWidthHeight);
                    //for (int y = 0; y < PlayerWidthHeight+1; y++)
                    //    draw_line((int)playerTrail[x].x, (int)playerTrail[x].y-2+y, (int)playerTrail[x-1].x, (int)playerTrail[x-1].y-2+y);
        }
    }
}

void movePlayer()
{
    if (gamepad_button_a() > 0)
        playerSpeed += Gravity;

    if (gamepad_button_a() < 0)
        playerSpeed -= Gravity;
    
    player_y -= playerSpeed;
    
    //add position to player trail
    for (int x = 0; x <=  player_x; x++)
    {
        playerTrail[x].x = playerTrail[x+1].x-tunnelSpeed;
        playerTrail[x].y = playerTrail[x+1].y;
    }
    playerTrail[player_x].x = player_x;
    playerTrail[player_x].y = player_y;

    Rect playerRect;
    playerRect.x = player_x -2;
    playerRect.y = player_y -2;
    playerRect.w = PlayerWidthHeight;
    playerRect.h = PlayerWidthHeight;
    

    int playerTunnelSection = player_x / tunnelSectionWidth*2;
    //player is inside tunnel section
    for (int i = playerTunnelSection -4; i <= playerTunnelSection + 4; i++)
    {
        if (checkCollision(&playerRect, &tunnelParts[i]))
            playing = false;
    }

    //player is inside obstacle
    for (int i = 0; i < MaxObstacles; i++)
    {
        if (checkCollision(&playerRect, &obstacles[i]))
            playing = false;
    }

    
    for (int i = 0; i < MaxCollectibles; i++)
    {
        //player is inside collectible (added )
        if (checkCollision(&playerRect, &collectibles[i]))
        //debug
        //if (player_x > collectibles[i].x + collectibles[i].w)
        {
            //erase it from the array by moving all other obstalces one position down
            for (int j = 0; j < collectibleCount; j++)
            {
                collectibles[j].x = collectibles[j+1].x;
                collectibles[j].y = collectibles[j+1].y;
            }

            //and create a new obstacle at the right side of the screen
            if (collectibleCount > 0)
            {
                collectibles[collectibleCount - 1].x = ScreenWidth;
                collectibles[collectibleCount - 1].y = tunnelParts[numVisibleTunnelSections * 2].h + randint(CollectibleSpaceFromTunnel, tunnelPlayableGap - CollectibleHeight - 2 * CollectibleSpaceFromTunnel);
                collectibles[collectibleCount - 1].w = CollectibleWidth;
                collectibles[collectibleCount - 1].h = CollectibleHeight;
            }
        }

        //collectible is futher away than playerx (player missed to pick it up)
        if (player_x - 10 > collectibles[i].x + collectibles[i].w)
            playing = false;
    }

    //player is out of bounds
    if ((player_y < 0) || (player_y > ScreenHeight))
        playing = false;

    //debug
    //playing = true;
}

void createTunnel()
{
    //grab a height
    int top_height =  randint(0, tunnelPlayableGap);
    
    for(int i = 0; i <= numTunnelSections; i++)
    {
        //grab a height based on previous height with tunnelSpacer deviation of height
        top_height = randint(top_height - tunnelSpacer, top_height + tunnelSpacer);        
        
        //make sure it does not exceed our playable gap
        if (top_height < 0)
            top_height = 0;
        else
        {
            if (top_height > tunnelPlayableGap)
                top_height = tunnelPlayableGap;
        }
        
        //set player y position based on tunnel section where player is
        if((i * tunnelSectionWidth <= player_x) && ((i+1) * tunnelSectionWidth >= player_x))
            player_y = top_height + tunnelPlayableGap / 2;

        //top of tunnel
        tunnelParts[i*2].x = i * tunnelSectionWidth;
        tunnelParts[i*2].y = 0;
        tunnelParts[i*2].w = tunnelSectionWidth;
        tunnelParts[i*2].h = top_height;

        //bottom of tunnel
        tunnelParts[i*2+1].x = i * tunnelSectionWidth;
        tunnelParts[i*2+1].y = top_height + tunnelPlayableGap;
        tunnelParts[i*2+1].w = tunnelSectionWidth;
        tunnelParts[i*2+1].h = ScreenHeight - top_height - tunnelPlayableGap;
    }
}

void drawTunnel()
{
    set_multiply_color(color_green);
    for(int i = 0; i <= numTunnelSections * 2; i += 2)
    {
        draw_filled_rectangle(tunnelParts[i].x, tunnelParts[i].y, tunnelParts[i].x + tunnelParts[i].w, tunnelParts[i].y + tunnelParts[i].h);
        draw_filled_rectangle(tunnelParts[i+1].x, tunnelParts[i+1].y, tunnelParts[i+1].x + tunnelParts[i+1].w, tunnelParts[i+1].y + tunnelParts[i+1].h);
    }
}

void moveTunnel()
{
    //for every tunnel section
    for(int j = 0; j <= numTunnelSections; j++)
    {
        //move top & bottom tunnel part
        tunnelParts[j*2].x = tunnelParts[j*2].x - tunnelSpeed;
        tunnelParts[j*2+1].x = tunnelParts[j*2+1].x - tunnelSpeed;
    }
    
    bool increaseTunnelSpeed = false;

    for (int i = 0; i < numTunnelSections * 2; i++)
    {
        
        //if tunnel section are back on screen, break out of loop
        //tunnel sections are kept from left to right (lowest x)
        if (tunnelParts[i].x + tunnelSectionWidth >= 0)
            break;
        else
        //if left most tunnel sections is offscreen on the left
        {
            //erase that section from the arrray by moving all other section down in the array
            for (int i = 0; i <= numTunnelSections;i++)
            {
                tunnelParts[i*2].x = tunnelParts[i*2+2].x;
                tunnelParts[i*2].y = tunnelParts[i*2+2].y;
                tunnelParts[i*2].w = tunnelParts[i*2+2].w;
                tunnelParts[i*2].h = tunnelParts[i*2+2].h;
                tunnelParts[i*2+1].x = tunnelParts[i*2+3].x;
                tunnelParts[i*2+1].y = tunnelParts[i*2+3].y;
                tunnelParts[i*2+1].w = tunnelParts[i*2+3].w;
                tunnelParts[i*2+1].h = tunnelParts[i*2+3].h;
            }

            // create new piece at the end of the array
            int lastElement = numTunnelSections * 2;
            
            // place the new section exactly after the current rightmost
            int newX = tunnelParts[lastElement - 2].x + tunnelSectionWidth;

            // --- randomize top height (clamped as before) ---
            int top_height = randint(
                tunnelParts[lastElement - 2].h - tunnelSpacer,
                tunnelParts[lastElement - 2].h + tunnelSpacer
            );

            if (top_height < 0)
                top_height = 0;
            else
            {
                if (top_height > tunnelPlayableGap)
                    top_height = tunnelPlayableGap;
            }

            // --- assign new top & bottom tunnel parts ---
            tunnelParts[lastElement].x = newX;
            tunnelParts[lastElement].y = 0;
            tunnelParts[lastElement].w = tunnelSectionWidth;
            tunnelParts[lastElement].h = top_height;

            //bottom of tunnel
            tunnelParts[lastElement + 1].x = newX;
            tunnelParts[lastElement + 1].y = top_height + tunnelPlayableGap;
            tunnelParts[lastElement + 1].w = tunnelSectionWidth;
            tunnelParts[lastElement + 1].h = ScreenHeight - top_height - tunnelPlayableGap;

            //score increases with every section passed
            score += 1;
            if (seed < maxSeed)
            {
                if (score > save.highScores[gameMode * maxSeed + seed])
                    save.highScores[gameMode * maxSeed + seed] = score;
            }
            else if (score > save.highScores[gameMode * maxSeed])
                save.highScores[gameMode * maxSeed] = score;

            //make tunnel smaller
            if((gameMode == 0) || (gameMode == 3))
                if(tunnelPlayableGap > TunnelMinimumPlayableGap)
                    if(score % 4 == 0)
                        tunnelPlayableGap -= 1;
            
            //need to increase speed ?
            if((gameMode == 1) || (gameMode == 2) || (gameMode == 3))
                //if(tunnelSpeed < MaxTunnelSpeed)
                    if(score % (speedTarget) == 0)
                        increaseTunnelSpeed = true;
        }
    }

    if(increaseTunnelSpeed)
    {                        
        tunnelSpeed += 1;
        speedTarget *=2;
    }  
}

//vircon32 gives back the seed passed to srand back the 1st time rand() is called
//calling rand() once after having called srand fixed that
void fixed_srand(int seed)
{
    srand(seed);
    rand();
}

void startGame(int mode)
{
    if (selSeed == 0)
    {
        fixed_srand(get_frame_counter());
        seed = randint(2, maxSeed);
    }
    else
    {
        if (selSeed == 1)
        {
            fixed_srand(get_frame_counter());
            seed = randint(2, get_time());
        }
        else
            seed = selSeed;
    }
    fixed_srand(seed);
    playerSpeed = 0;
    tunnelPlayableGap = StartTunnelPlayableGap;
    score = 0;
    obstacleCount = 0;
    collectibleCount = 0;
    playing = true;
    tunnelSpeed = StartTunnelSpeed;
    speedTarget = StartSpeedTarget;
    gameMode = mode;
    startDelay = 60;
    if (gameMode == 0)
        MaxObstacles = 4;
    if (gameMode == 2)
        MaxObstacles = 2;
    if (gameMode == 4)
        MaxCollectibles = 3;
    //set some defaults in the arrays
    for(int i = 0; i < ScreenWidth + OffScreenTunnelSections; i++)
    {
        if(i < ScreenWidth)
        {
            playerTrail[i].x = 0;
            playerTrail[i].y = 0;
        }
        tunnelParts[i*2].x = 0;
        tunnelParts[i*2+1].x = 0;
        tunnelParts[i*2].w = 0;
        tunnelParts[i*2+1].w = 0;
        tunnelParts[i*2].h = 0;
        tunnelParts[i*2+1].h = 0;
        tunnelParts[i*2].y = 0;
        tunnelParts[i*2+1].y = 0;
    }

    for(int i = 0 ; i < MaxObstacles; i++)
    {
        obstacles[i].x = ScreenWidth;
        obstacles[i].y = 0;
        obstacles[i].w = 0;
        obstacles[i].h = 0;
    }

    for(int i = 0 ; i < MaxCollectibles; i++)
    {
        collectibles[i].x = ScreenWidth;
        collectibles[i].y = 0;
        collectibles[i].w = 0;
        collectibles[i].h = 0;
    }
    createTunnel();
}

void drawBackGround()
{
    clear_screen(color_black);
}

void drawScreenBorder()
{
    //A Darker green
    set_multiply_color(0xFF006600);
    for (int i = 0; i < ScreenBorderWidth; i++)
        draw_rectangle(i,i,ScreenWidth-1-i, ScreenHeight-1-i);
}

void main()
{  
    int[250] Text;
    int[100] Text2;
	memset( &GameSignature, 0, sizeof(game_signature));
    strcpy( GameSignature, "WORM");
	LoadSavedData();
	SetupFont();	
	fixed_srand(get_time());
    select_gamepad(0);
    //these never change and are used a lot in above functions
    numVisibleTunnelSections = ceil(ScreenWidth / tunnelSectionWidth);
    numTunnelSections = numVisibleTunnelSections + OffScreenTunnelSections;
    createTunnel();
	while (true) 
    {
        drawBackGround();
        drawTunnel();
        if((gameMode == 0) || (gameMode == 2))
            drawObstacles();
        if(gameMode == 4)
            drawCollectibles();
        drawPlayer();
        drawScreenBorder();
        if(playing)
        {
            if(startDelay == 0)
            {
                moveTunnel();
                if((gameMode == 0) || (gameMode == 2))
                    moveObstacles();
                if(gameMode == 4)
                    moveCollectibles();
                movePlayer();
                if (!playing)
                    SaveSavedData();
            }
            else
            {
                set_multiply_color(color_white);
                startDelay--;
                if(startDelay > 20)
                {
                    strcpy(Text2, "Playing GAME A\n\nREADY");
                    Text2[13] = (int)'A' + gameMode;
                    textfont_print_centered(&FontLetters, ScreenWidth / 2, ScreenHeight/3, Text2);
                }
                else
                {
                    if (startDelay > 1)
                        textfont_print_centered(&FontLetters, ScreenWidth / 2, ScreenHeight/2, "GO!");
                }
            
            }
        }
        else
        {
            set_multiply_color(color_white);
            strcpy(Text, "WORM\n\nPress A To Play GAME A");
            Text[27] = (int)'A' + gameMode;
            strcat(Text, "\nPress Direction To Change Mode\nPressing A Repeadetly\nwill keep the worm alive");
            textfont_print_centered(&FontLetters, ScreenWidth / 2, ScreenBorderWidth + 33, Text);
            if(gamepad_button_a() == 1)
                startGame(gameMode);

            if(gamepad_left() == 1)
            {
                gameMode--;
                if (gameMode < 0)
                    gameMode = MaxGameModes -1;
            }

            if(gamepad_right() == 1)
            {
                gameMode++;
                if (gameMode > MaxGameModes -1)
                    gameMode = 0;
            }

            if(gamepad_down() == 1)
            {
            	selSeed -= 1;
            	if(selSeed < 0)
                	selSeed = maxSeed-1;
            }

            if (gamepad_up() == 1)
            {
            	selSeed += 1;
            	if(selSeed > maxSeed-1)
                	selSeed = 0;
            }

            if(gamepad_button_l() == 1)
            {
                selSeed -= 10;
                if(selSeed < 0)
                    selSeed =  maxSeed-1;
            }

            if (gamepad_button_r() == 1)
            {
                selSeed += 10;
                if(selSeed > maxSeed-1)
                    selSeed = 0; 
            }

            if (gamepad_button_start() > 30)
                for (int i = 0; i < MaxGameModes*maxSeed; i++)
                    save.highScores[i] = 0;
                
        }
        int[100] nr;
		int[100] Text;
	    strcpy(Text, "LVL:");
       
        if (selSeed == 0)
		{
			itoa(seed-1, nr, 10);
			strcat(Text, nr);
			strcat(Text, " RND1");
		}
		else
	    {
	        if (selSeed == 1)
			{
		    	itoa(seed-1, nr, 10);
	    		strcat(Text, nr);
    			strcat(Text, " RND2");
			}
	        else
	        {
		    	itoa(selSeed-1, nr, 10);
	    		strcat(Text, nr);
			}
	    }
        set_multiply_color(color_white);
        textfont_print_from_left(&FontLetters, ScreenBorderWidth + 1, ScreenHeight -2 - ScreenBorderWidth, Text);
        strcpy(Text, "S:");
        itoa(score, nr, 10);
        strcat(Text, nr);
        strcat(Text, " H:");
        if (selSeed <= 1)
	    {
	        if (seed >= maxSeed)
	            itoa(save.highScores[gameMode * maxSeed], nr, 10);
	        else
	            itoa(save.highScores[gameMode * maxSeed + seed], nr, 10);
	    }
	    else if (selSeed > 1)
       		itoa(save.highScores[gameMode * maxSeed + selSeed], nr, 10);
        strcat(Text, nr);
        set_multiply_color(color_white);
        textfont_print_from_right(&FontLetters,ScreenWidth -2 -ScreenBorderWidth, ScreenHeight -2 - ScreenBorderWidth , Text);
        end_frame();
    }
}
