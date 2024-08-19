#ifndef SOUND_H
#define SOUND_H

#include "audio.h"
#include "commonvars.h"

#define musTitle 0
#define musGame1 1
#define musGame2 2
#define musOldman 3
#define musStage 4

#define  bridgeSound 5
#define  dropBlockSound 6
#define  elfSound 7
#define  errorSound 8
#define  menuSound 9
#define  pickupBlockSound 10
#define  rotateBlockSound 11
#define  flipBlockSound 11
#define  menuSelectSound 12
#define  stageEndSound 13
#define  textSound 14


int prev_music = -1, current_music = -1, music_on = 0, sound_on = 0, force = 0;

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
	for (int i = 1; i < sound_channels; i++)
	{
		select_channel(i);
		set_channel_volume(1.0);
	}
}

void deInitSound()
{
}

void SelectMusic(int musicFile)
{
	if(!music_on)
		return;

	if((musicFile != current_music) || force)
	{
		force = 0;
		prev_music =  current_music;
		current_music = musicFile;
		select_sound(current_music);
		set_sound_loop(true);
		stop_channel(0);		
		play_sound_in_channel(current_music, 0);
	}
}


void initMusic()
{
    prev_music = -1;
	current_music = -1;
	select_channel(0);
	set_channel_volume(0.55);
}

void stopSound()
{
	for (int i = 1; i < sound_channels; i++)
		stop_channel(i);
}

void setSoundOn(int value)
{
    sound_on = value;
	if(!sound_on)
		stopSound();
}

void playSound(int soundID, bool repeat)
{
    if (!sound_on)
    {
        return;
    }

	select_sound(soundID);
	set_sound_loop(repeat);
	play_sound_in_channel(soundID, soundID);
}

void stopTextSound(void)
{
   stop_channel(textSound);
}

void playTextSound(void)
{
	playSound(textSound, 1);
}

void playRotateBlockSound(void)
{
	playSound(rotateBlockSound, 0);
}

void playElfSound(void)
{
   playSound(elfSound, 0);
}

void playStageEndSound(void)
{
    playSound(stageEndSound, 0);
}

void playBridgeSound(void)
{
    playSound(bridgeSound, 0);
}

void playErrorSound(void)
{
	playSound(errorSound, 0);
}

void playMenuSelectSound(void)
{
    playSound(menuSelectSound, 0);
}

void playFlipBlockSound(void)
{
    playSound(flipBlockSound, 0);
}

void playPickupBlockSound(void)
{
    playSound(pickupBlockSound, 0);
}

void playDropBlockSound(void)
{
    playSound(dropBlockSound, 0);
}

void playMenuSound(void)
{
    playSound(menuSound, 0);
}

void stopMusic()
{
	stop_channel(0);
}

void deInitMusic()
{
	stopMusic();	
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
		else
		{
			//for options screen
			if(GameState == GSOptions)
			{
				force = 1;
				SelectMusic(musTitle);
			}
		}
    }
    else
    {
        stopMusic();
    }
}

#endif