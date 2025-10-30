#include "video.h"
#include "string.h"
#include "time.h"
#include "misc.h"
#include "input.h"
#include "memcard.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "libs/TextFonts/textfont.h"
#include "Worm.h"
#include "SaveData.h"

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

void drawObstacles()
{
    set_multiply_color(color_cyan);
    for(int i = 0; i < obstacleCount; i++)
        //don't draw not used obstacles
        if((obstacles[i].x > 0) && (obstacles[i].y > 0))
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
                obstacles[obstacleCount-1].y =  tunnelParts[(screen_width / tunnelSectionWidth)*2].h + 10 + randint(0, tunnelPlayableGap - ObstacleHeight - 20);
                obstacles[obstacleCount-1].w = ObstacleWidth;
                obstacles[obstacleCount-1].h = ObstacleHeight;
            }
        }
    }

    //when we have no obstacles or the last added obstacle is smaller than the spacing between obstacles from right side of screen
    if ((obstacleCount == 0) || ((obstacleCount < MaxObstacles) && (obstacles[obstacleCount-1].x < ScreenWidth - (ScreenWidth / MaxObstacles))))
    {
        //add a new obstacles (then 10 and 20 is to always add a spacing between tunnel wall the obstacle)
        obstacles[obstacleCount].x =  ScreenWidth;
        obstacles[obstacleCount].y =  tunnelParts[(screen_width / tunnelSectionWidth)*2].h + 10 + randint(0, tunnelPlayableGap - ObstacleHeight - 20);
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
    if ((collectibleCount == 0) || ((collectibleCount < MaxCollectibles) && (collectibles[collectibleCount-1].x < ScreenWidth - ((ScreenWidth - player_x) / MaxCollectibles))))
    {
        //add a new collectible (then 10 and 20 is to always add a spacing between tunnel wall the collectible)
        collectibles[collectibleCount].x =  ScreenWidth;
        collectibles[collectibleCount].y =  tunnelParts[(screen_width / tunnelSectionWidth)*2].h + 20 + randint(0, tunnelPlayableGap - CollectibleHeight - 40);
        collectibles[collectibleCount].w = CollectibleWidth;
        collectibles[collectibleCount].h = CollectibleHeight;
        collectibleCount++;
    }
}


void drawPlayer()
{
    set_multiply_color(color_magenta);
    draw_filled_rectangle(player_x-2, player_y-2, player_x+2, player_y+2);
    for (int x = 0; x <=  player_x; x++)
    {
        //don't draw not used array pieces
        if ((playerTrail[x].y > 0) && (playerTrail[x].x > 0))
        {
            draw_filled_rectangle((int)playerTrail[x].x-2, (int)playerTrail[x].y-2, (int)playerTrail[x].x+2, (int)playerTrail[x].y+2);
            if (x > 0)
                if ((playerTrail[x-1].y > 0) && (playerTrail[x-1].x > 0))
                    for (int y = 0; y < 6; y++)
                        draw_line((int)playerTrail[x].x, (int)playerTrail[x].y-2+y, (int)playerTrail[x-1].x, (int)playerTrail[x-1].y-2+y);
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

    //player is inside tunnel section
    for (int i = 0; i < ScreenWidth / tunnelSectionWidth*2; i ++)
    {
        if ((player_x -2 >= tunnelParts[i].x) && (player_x + 2 <= tunnelParts[i].x + tunnelParts[i].w) &&
            (player_y -2 >= tunnelParts[i].y) && (player_y +2 <= tunnelParts[i].y + tunnelParts[i].h))
            playing = false;
    }

    //player is inside obstacle
    for (int i = 0; i < MaxObstacles; i++)
    {
        if ((player_x -2 >= obstacles[i].x) && (player_x +2 <= obstacles[i].x + obstacles[i].w) &&
            (player_y -2 >= obstacles[i].y) && (player_y +2 <= obstacles[i].y + obstacles[i].h))
            playing = false;
    }

    
    for (int i = 0; i < MaxCollectibles; i++)
    {
        //player is inside collectible (added )
        if ((player_x >= collectibles[i].x) && (player_x <= collectibles[i].x + collectibles[i].w) &&
            (player_y >= collectibles[i].y) && (player_y <= collectibles[i].y + collectibles[i].h))
        {
            //erase it from the array by moving all other obstalces one position down
            for (int j = 0; j < collectibleCount; j++)
            {
                collectibles[j].x = collectibles[j+1].x;
                collectibles[j].y = collectibles[j+1].y;
            }

            //and create a new obstacle at the right side of the screen
            collectibles[collectibleCount-1].x =  ScreenWidth;
            collectibles[collectibleCount-1].y =  tunnelParts[(screen_width / tunnelSectionWidth)*2].h + 10 + randint(0, tunnelPlayableGap - CollectibleHeight - 20);
            collectibles[collectibleCount-1].w = CollectibleWidth;
            collectibles[collectibleCount-1].h = CollectibleHeight;
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
    int top_height = rand() % (tunnelPlayableGap);
    
    for(int i = 0; i <= ceil(ScreenWidth / tunnelSectionWidth); i++)
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
        if((i * tunnelSectionWidth < player_x) && ((i+1) * tunnelSectionWidth > player_x))
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
    for(int i = 0; i <= ceil(ScreenWidth / tunnelSectionWidth) * 2; i += 2)
    {
        draw_filled_rectangle(tunnelParts[i].x, tunnelParts[i].y, tunnelParts[i].x + tunnelParts[i].w+1, tunnelParts[i].y + tunnelParts[i].h);
        draw_filled_rectangle(tunnelParts[i+1].x, tunnelParts[i+1].y, tunnelParts[i+1].x + tunnelParts[i+1].w, tunnelParts[i+1].y + tunnelParts[i+1].h);
    }
}

void moveTunnel()
{
    //for every tunnel section
    for(int j = 0; j <= ceil(ScreenWidth / tunnelSectionWidth); j++)
    {
        //move top & bottom tunnel part
        tunnelParts[j*2].x = tunnelParts[j*2].x - tunnelSpeed;
        tunnelParts[j*2+1].x = tunnelParts[j*2+1].x - tunnelSpeed;
    }
    
    bool increaseTunnelSpeed = false;

    //for every tunnel section
    for(int j = 0; j <= ceil(ScreenWidth / tunnelSectionWidth); j++)
    {
        //if tunnel section is offscreen on the left
        if (tunnelParts[j*2].x + tunnelSectionWidth <= 0)
        {
            //erase that section from the arrray by moving all other section down in the array
            for (int i = 0; i <= ceil(ScreenWidth / tunnelSectionWidth);i++)
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

            //create new piece at the end of the array
            int lastElement = ceil(ScreenWidth / tunnelSectionWidth)*2;
            int top_height = randint(tunnelParts[lastElement-2].h - tunnelSpacer, tunnelParts[lastElement-2].h + tunnelSpacer);

            //make sure it does not exceed our playable gap
            if (top_height < 0)
                top_height = 0;
            else
            {
                if (top_height > tunnelPlayableGap)
                    top_height = tunnelPlayableGap;
            }

            //top of tunnel
            tunnelParts[lastElement].x = (lastElement/2) * tunnelSectionWidth;
            tunnelParts[lastElement].y = 0;
            tunnelParts[lastElement].w = tunnelSectionWidth + tunnelSpeed;
            tunnelParts[lastElement].h = top_height;

            //bottom of tunnel
            tunnelParts[lastElement+1].x = (lastElement/2) * tunnelSectionWidth;
            tunnelParts[lastElement+1].y = top_height + tunnelPlayableGap;
            tunnelParts[lastElement+1].w = tunnelSectionWidth + tunnelSpeed;
            tunnelParts[lastElement+1].h = ScreenHeight - top_height - tunnelPlayableGap;
            
            //score increases with every section passed
            score += 1;
            if(score > save.highScores[gameMode])
                save.highScores[gameMode] = score; 

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

void startGame(int mode)
{
    if (seed == 0)
        srand(get_time());
    else
        srand(seed);
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
    for(int i = 0; i < ScreenWidth; i++)
    {
        playerTrail[i].x = 0;
        playerTrail[i].y = 0;
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
        draw_rectangle(i,i,screen_width-1-i, screen_height-1-i);
}

void main()
{  
    int[250] Text;
    int[100] Text2;
	memset( &GameSignature, 0, sizeof(game_signature));
    strcpy( GameSignature, "WORM");
	LoadSavedData();
	SetupFont();	
	srand(get_time());
    select_gamepad(0);
    createTunnel();
	while (true) 
    {
        drawBackGround();
        drawTunnel();
        if((gameMode == 0) || (gameMode == 2))
            drawObstacles();
        if((gameMode == 4))
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
                if((gameMode == 4))
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
                    textfont_print_centered(&FontLetters, screen_width / 2, screen_height/3, Text2);
                }
                else
                {
                    if (startDelay > 1)
                        textfont_print_centered(&FontLetters, screen_width / 2, screen_height/2, "GO!");
                }
            
            }
        }
        else
        {
            set_multiply_color(color_white);
            strcpy(Text, "WORM\n\nPress A To Play GAME A");
            Text[27] = (int)'A' + gameMode;
            strcat(Text, "\nPress Direction To Change Mode\nPressing A Repeadetly\nwill keep the worm alive");
            textfont_print_centered(&FontLetters, screen_width / 2, ScreenBorderWidth + 33, Text);
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

            if(gamepad_button_l() == 1)
            {
                seed -= 1;
                if(seed < 0)
                    seed = 0;
            }

            if (gamepad_button_r() == 1)
            {
                seed += 1;
                if(seed > 9999)
                    seed = 9999;
            }

            if(gamepad_button_l() > 30)
            {
                seed -= 15;
                if(seed < 0)
                    seed = 0;
            }

            if (gamepad_button_r() > 30)
            {
                seed += 15;
                if(seed > 9999)
                    seed = 9999;
            }

            if (gamepad_button_start() > 30)
                for (int i = 0; i < MaxGameModes; i++)
                    save.highScores[i] = 0;
                
        }
        int[100] Text;
        strcpy(Text, "Seed:");
        int[100] nr;
        itoa(seed, nr, 10);
        strcat(Text, nr);
        set_multiply_color(color_white);
        textfont_print_from_left(&FontLetters, ScreenBorderWidth + 1, screen_height -2 - ScreenBorderWidth, Text);
        strcpy(Text, "S:");
        itoa(score, nr, 10);
        strcat(Text, nr);
        strcat(Text, " H:");
        itoa(save.highScores[gameMode], nr, 10);
        strcat(Text, nr);
        set_multiply_color(color_white);
        textfont_print_from_right(&FontLetters,screen_width -2 -ScreenBorderWidth,screen_height -2 - ScreenBorderWidth , Text);
        end_frame();
    }
}
