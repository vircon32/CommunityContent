#ifndef SOUND_H
#define SOUND_H

#include "commonvars.h"
#include "audio.h"

#define musGame 0
#define musTitle 1
#define musLevelClear 2
#define musAllLevelsClear 3

//I (joyrider3774) created the music in this tool : https://onlinesequencer.net
//levels cleared: https://onlinesequencer.net/2498607
//level done:     https://onlinesequencer.net/2484974
//game music:     https://onlinesequencer.net/2485064
//title music:    https://onlinesequencer.net/2484977

int prev_music = -1, music_on = 0, sound_on = 0, force = 0;

int gameMoveSound;
int errorSound;
int menuSelectSound;
int menuBackSound;
int gameAction;
int menuAcknowledge;


void stopMusic()
{
	stop_channel(0);
}


void setSoundOn(int value)
{
    sound_on = value;
}

int isMusicOn()
{
    return music_on;
}

int isSoundOn()
{
    return sound_on;
}

void initSound()
{
    gameMoveSound = 4;
    errorSound = 5;
    menuSelectSound = 6;
    menuBackSound = 7;
    gameAction = 8;
    menuAcknowledge = 9;
}

void deInitSound()
{

}

void playMusicFile(int Music, int repeat)
{
	stopMusic();
	select_channel(0);
	select_sound(Music);
	set_sound_loop(repeat == 0);
	assign_channel_sound(0, Music);
	set_channel_volume(0.5);
	play_channel(0);
}

void SelectMusic(int musicFile)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        force = 0;
        prev_music = musicFile;
		if((musicFile == musTitle) || (musicFile == musGame) || (musicFile == musAllLevelsClear))
        	playMusicFile(musicFile, 0);
		else
			playMusicFile(musicFile, 1);
    }
    else
    {
        //still need to remember last music we tried to play in case music was off & we reenable
        if (!music_on)
        {
            prev_music = musicFile;
        }
    }
}

void setMusicOn(int value)
{
    music_on = value;
    if(music_on)
    {
        if (prev_music != -1)
        {
            force = 1;
            SelectMusic(prev_music);
        }
        else if (gameState == gsTitle)
        {
            force = 1;
            SelectMusic(musTitle);
        }
    }
    else
    {
        stopMusic();
    }
}

void initMusic()
{
    prev_music = -1;
}

void deInitMusic()
{

}


void playSound(int soundPlayer)
{
	select_channel(soundPlayer);
	select_sound(soundPlayer);
	set_channel_volume(0.75);
	assign_channel_sound(soundPlayer, soundPlayer);
	play_channel(soundPlayer);

}

void playGameMoveSound()
{
    if(!sound_on)
    {
        return;
    }
    playSound(gameMoveSound);
}

void playErrorSound()
{
    if(!sound_on)
    {
        return;
    }
    playSound(errorSound);
}

void playMenuSelectSound()
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuSelectSound);
}

void playMenuBackSound()
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuBackSound);
}

void playMenuAcknowlege()
{
    if(!sound_on)
    {
        return;
    }
    playSound(menuAcknowledge);
}

void playGameAction()
{
    if(!sound_on)
    {
        return;
    }
    playSound(gameAction);
}


#endif