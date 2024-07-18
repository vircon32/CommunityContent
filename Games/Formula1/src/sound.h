#ifndef SOUND_H
#define SOUND_H

#include "audio.h"
#include "commonvars.h"

#define musTitle 6

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

	if(musicFile != current_music)
	{
		prev_music =  current_music;
		current_music = musicFile;
		select_sound(current_music);
		set_sound_loop(true);		
		play_sound_in_channel(current_music, 0);
	}
}


void initMusic()
{
    prev_music = -1;
	current_music = -1;
	select_channel(0);
	set_channel_volume(0.85);
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
	play_sound(soundID);
}

void playGameOverSound()
{
    playSound(3, false);
}

void playStartSound()
{
    playSound(2, false);
}

void playTickSound()
{
    playSound(1, false);
}

void playCrashSound()
{
  	playSound(0, false);
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
    }
    else
    {
        stopMusic();
    }
}

#endif