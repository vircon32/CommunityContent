#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include "defines.h"
#include "cworldparts.h"
#include "string.h"
#include "caudio.h"
#include "sdl_helpertypes.h"
#include "main.h"
#include "texture.h"
#include "libs/TextFonts/textfont.h"

#define HighScoresSavePosition 100
#define SoundSavePosition (sizeof(game_signature))
#define MusicSavePosition (SoundSavePosition + sizeof(bool))
#define SkinSavePosition (MusicSavePosition + sizeof(bool))

int chr(int ascii)
{
	return(ascii);
}

int ord(int chr)
{
	return(chr);
}


void UnLoadGraphics()
{
    if(IMGArrows1)
		freeTexture(IMGArrows1);
	if(IMGArrows2)
		freeTexture(IMGArrows2);
	if(IMGBackground)
		freeTexture(IMGBackground);
    if(IMGLevelDone)
		freeTexture(IMGLevelDone);
	if(IMGBlocks)
		freeTexture(IMGBlocks);
    if(IMGFloor)
        freeTexture(IMGFloor);
    if(IMGGameOver)
        freeTexture(IMGGameOver);
    if(IMGLevelpackDone)
		freeTexture(IMGLevelpackDone);
    if(IMGTitleScreen)
		freeTexture(IMGTitleScreen);
    if(IMGGrid)
        freeTexture(IMGGrid);
    if(IMGBackgroundLevelEditor)
		freeTexture(IMGBackgroundLevelEditor);
}

void LoadGraphics()
{
	UnLoadGraphics();
	IMGBackground = newTextureHorz(skin, 0, 1, 0, 0, 400,240,xscale,yscale);    
	IMGGameOver = newTextureHorz(skin, 1, 1, 400, 0, 400,240,xscale,yscale);
    IMGLevelDone = newTextureHorz(skin, 2, 1, 0, 240, 400,240,xscale,yscale);
    IMGLevelpackDone = newTextureHorz(skin, 3, 1, 400, 240, 400,240,xscale,yscale);
	IMGTitleScreen = newTextureHorz(skin, 4, 1, 0, 480, 400,240,xscale,yscale);
    IMGArrows1 = newTextureVert(skin, 5, 4, 400, 480, 44,176,xscale,yscale);
    IMGArrows2 = newTextureVert(skin, 10, 4,444, 480, 44,176,xscale,yscale);
    IMGBlocks = newTextureHorzVert(skin,20,2,6,488,480,40,120,xscale,yscale);
	IMGFloor = newTextureHorz(skin,40, 1, 528, 480, 20,20,xscale,yscale);
    
	if(skin == 0)
	{
		ColorSelection = color_white;
		ColorNoSelection = color_gray;
	}
	else
	{
		ColorSelection = make_color_rgb(230,40,0);
		ColorNoSelection = make_color_rgb(233,120,0);
	}
}

void SetSkin(int val)
{
	if((val < 0) || (val >=2))
		skin = 0;
	else
		skin = val;
	LoadGraphics();
	CWorldParts_AssignImage(WorldParts, IMGBlocks);
}

void NextSkin()
{
	SetSkin(++skin);
}

void LoadSettings()
{
	for (int i = 0; i < MaxHighScores; i++)
	{
		HighScores[i].Level = 0;
		HighScores[i].Score = 0;
	}
	bool MusicEnabled = true;
	bool SoundEnabled = true;
	int skin = 1;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&MusicEnabled, MusicSavePosition, sizeof (MusicEnabled));
			card_read_data(&SoundEnabled, SoundSavePosition, sizeof (SoundEnabled));
			card_read_data(&skin, SkinSavePosition, sizeof (skin));
			card_read_data(&HighScores[0], HighScoresSavePosition, MaxHighScores *sizeof (HighScores[0]));
		}
	SetSkin(skin);	
	CAudio_SetMusicEnabled(MusicEnabled);
	CAudio_SetSoundEnabled(SoundEnabled);
}

void SaveSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			int SoundEnabled = CAudio_GetSoundEnabled();
			int MusicEnabled = CAudio_GetMusicEnabled();
			card_write_data(&MusicEnabled, MusicSavePosition, sizeof (MusicEnabled));
			card_write_data(&SoundEnabled, SoundSavePosition, sizeof (SoundEnabled));
			card_write_data(&skin, SkinSavePosition, sizeof (skin));
			card_write_data(&HighScores[0], HighScoresSavePosition, MaxHighScores *sizeof (HighScores[0]));
		}
}

bool AddHighScore(int Score, int Level)
{
	for (int i = 0; i < MaxHighScores ; i++)
	{
		if (Score > HighScores[i].Score)
		{
			for (int y = MaxHighScores -1; y > i; y--)
			{
				HighScores[y].Level = HighScores[y-1].Level;
				HighScores[y].Score = HighScores[y-1].Score;
			}

			HighScores[i].Score = Score;
			HighScores[i].Level = Level;
			SaveSettings();
			return true;
		}
	}
	return false;
}


void UnloadMusic()
{
	CAudio_UnLoadMusic(Music);
}

void LoadSounds()
{
    Sounds[SND_Destroy] = CAudio_LoadSound("destroy");
	Sounds[SND_NoMoves] = CAudio_LoadSound("nomoves");
	Sounds[SND_Win] = CAudio_LoadSound("win");
	Sounds[SND_WinExit] = CAudio_LoadSound("winexit");
	Sounds[SND_DirectionMove] = CAudio_LoadSound("directionmove");
	Sounds[SND_GameOver] = CAudio_LoadSound("gameover");
	Sounds[SND_Score] = CAudio_LoadSound("score");
	Sounds[SND_LevelEditorSelect] = CAudio_LoadSound("leveleditorselect");
	Sounds[SND_Select] = CAudio_LoadSound("select");
	Sounds[SND_Error] = CAudio_LoadSound("error");
	Music = CAudio_LoadMusic("music");
}


void UnloadSounds()
{
	int Teller;
	for (Teller=0;Teller<NrOfSounds;Teller++)
		CAudio_UnLoadSound(Sounds[Teller]);
}


void RemoveBlocks(CWorldParts *aWorldParts)
{
    CWorldPart* Box;
    int Teller;
    for (Teller=0;Teller<aWorldParts->ItemCount;Teller++)
    {
        Box = aWorldParts->Items[Teller];
        if(Box->Remove)
        {
            CWorldParts_Remove(aWorldParts, Box->PlayFieldX, Box->PlayFieldY);
            Teller--;
        }
    }
}

bool DeathBlocks(CWorldParts *aWorldParts)
{
    CWorldPart* Box;
    int Teller;
    for (Teller=0;Teller<aWorldParts->ItemCount;Teller++)
    {
        Box = aWorldParts->Items[Teller];
        if(Box->Death || Box->Remove)
            return true;
    }
    return false;
}

// Recursive Floodfill function
void FloodFill(CWorldParts *aWorldParts, Texture* Surface, bool **visited, int X, int Y)
{
    // Check bounds and whether the tile has been visited
    if (X < 0 || X >= NrOfCols || Y < 0 || Y >= NrOfRows || visited[Y][X])
        return;

    CWorldPart* Part = CWorldParts_GetItemFromPosPlayField(aWorldParts, X, Y);

    if (Part->Type == 5)
        return;

    // Mark the tile as visited
    visited[Y][X] = true;

    // Draw the floor tile
    drawTextureZoomed(IMGFloor, 0,  (X * TileWidth) + Xoffset, (Y * TileWidth) + Yoffset);

    // Recur for neighboring tiles
    FloodFill(aWorldParts, Surface, visited, X + 1, Y);
    FloodFill(aWorldParts, Surface, visited, X - 1, Y);
    FloodFill(aWorldParts, Surface, visited, X, Y + 1);
    FloodFill(aWorldParts, Surface, visited, X, Y - 1);
}

void DrawFloor(CWorldParts *aWorldParts, Texture* Surface)
{
    // Allocate memory for the visited array using malloc
    bool **visited = (bool**)malloc(NrOfRows * sizeof(bool*));
    for (int i = 0; i < NrOfRows; ++i)
    {
        visited[i] = (bool*)malloc(NrOfCols * sizeof(bool));
        for (int j = 0; j < NrOfCols; ++j)
            visited[i][j] = false; // Initialize the array to false
    }

    for (int Y = 0; Y < NrOfRows; Y++)
    {
        for (int X = 0; X < NrOfCols; X++)
        {
            // If the tile has not been visited
            if (!visited[Y][X])
            {
                CWorldPart* Part = CWorldParts_GetItemFromPosPlayField(aWorldParts, X, Y);

                // Only start floodfill if the tile is not NULL
                if (Part != NULL && Part->Type != 5)
                {
                    FloodFill(aWorldParts, Surface, visited, X, Y);
                }
            }
        }
    }

    // Free the allocated memory for the visited array
    for (int i = 0; i < NrOfRows; ++i)
        free(visited[i]);
    free(visited);
}


int EraseBlocks(CWorldParts *aWorldParts,int X,int Y)
{
    CWorldPart *Start,Down,Up,Left,Right;
    int Result = 0;

    Start = CWorldParts_GetItemFromPosPlayField(aWorldParts, X,Y) ;
    if(Start != NULL)
    {
        Result +=1;
        if((Start->Type !=5) && (Start->Type !=4) && !Start->Death)
        {
            Left = CWorldParts_GetItemFromPosPlayField(aWorldParts, X-1,Y);
            if((Left != NULL))
            if((Left->Type == Start->Type))
            {
                Result +=1;
                Left->Death = true;
                Start->Death = true;
                Result += EraseBlocks(WorldParts,X-2,Y);
            }

            Down = CWorldParts_GetItemFromPosPlayField(aWorldParts,X,Y+1);
            if((Down != NULL))
            if(Down->Type == Start->Type)
            {
                Result +=1;
                Down->Death = true;
                Start->Death = true;
                Result +=  EraseBlocks(WorldParts,X,Y+2);
            }

            Up = CWorldParts_GetItemFromPosPlayField(aWorldParts,X,Y-1);
            if((Up != NULL))
            if(Up->Type == Start->Type)
            {

                Result +=1;
                Up->Death = true;
                Start->Death = true;
                Result +=  EraseBlocks(WorldParts,X,Y-2);
            }


            Right = CWorldParts_GetItemFromPosPlayField(aWorldParts, X+1,Y);
            if((Right != NULL))
            if(Right->Type == Start->Type)
            {
                Result +=1;
                Right->Death = true;
                Start->Death = true;
                Result +=  EraseBlocks(WorldParts,X+2,Y);
            }

        }
    }
    return Result;
}

bool LevelWon(CWorldParts *aWorldParts)
{
    int Teller;
    for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
    {
        if((aWorldParts->Items[Teller]->Type > 0) && (aWorldParts->Items[Teller]->Type < 4))
            return false;
    }
    return true;
}

bool NoMovesLeft(CWorldParts *aWorldParts)
{
    int Teller,NumBlock1=0,NumBlock2=0,NumBlock3=0;
    for(Teller=0;Teller<aWorldParts->ItemCount;Teller++)
    {
        if(aWorldParts->Items[Teller]->Type == 1)
            NumBlock1++;
        if(aWorldParts->Items[Teller]->Type == 2)
            NumBlock2++;
        if(aWorldParts->Items[Teller]->Type == 3)
            NumBlock3++;

    }
    return ((NumBlock1 == 1) || (NumBlock2 == 1) || (NumBlock3 ==1));

}

void DrawArrows()
{
	SDL_Rect[4] DestRectsArrows = {{58*xscale,110*yscale,44*xscale,44*yscale}, 
		{98*xscale,145*yscale,44*xscale,44*yscale},{58*xscale,179*yscale,44*xscale,44*yscale},{16*xscale,145*yscale,44*xscale,44*yscale}};
    int Teller;
    for(Teller=0;Teller<4;Teller++)
    {
        if(Teller != Movement)
        {
			drawTextureZoomed(IMGArrows1, Teller, DestRectsArrows[Teller].x, DestRectsArrows[Teller].y);
        }
        else
            if(Movement != MNone)
            {
				drawTextureZoomed(IMGArrows2, Teller, DestRectsArrows[Teller].x, DestRectsArrows[Teller].y);
            }
    }
}

void drawTextColor(textfont* font, int* text, int x, int y, int color)
{
	if(!font)
		return;

	if(*text == 0)
		return;

	set_multiply_color(color);
	set_drawing_scale(xscale, yscale);
	textfont_print_from_left(font, screenxoffset + x, y, text);
	set_drawing_scale(1.0,1.0);
	set_multiply_color(color_white);
}


#endif