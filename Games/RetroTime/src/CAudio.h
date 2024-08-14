#ifndef CAUDIO_H
#define CAUDIO_H

#include "audio.h"
#include "string.h"
#include "CAudio.h"

#define SND_Max 100
#define MUS_Max 20

int CAudio_SoundSlotsUsed =0;
int CAudio_MusicSlotsUsed = 0;
int CAudio_VolumeMusic = 128, CAudio_VolumeSound = 128;
int*[SND_Max] CAudio_Sounds;
int*[MUS_Max] CAudio_Music;
bool CAudio_GlobalSoundEnabled = true;

int* filenameToAudio(int* FileName)
{
	int* result = NULL;
	//music 
	if (strcmp(FileName, "main/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 0;
	}
	
	if (strcmp(FileName, "blockstacker/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 1;
	}
	
	if (strcmp(FileName, "breakout/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 2;
	}
	
	if (strcmp(FileName, "fasterdave/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 3;
	}

	if (strcmp(FileName, "frog/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 4;
	}

	if (strcmp(FileName, "invaders/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 5;
	}

	if (strcmp(FileName, "pang/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 6;
	}
	
	if (strcmp(FileName, "ramit/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 7;
	}
	
	if (strcmp(FileName, "snakey/music") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 8;
	}

	//sound 
	if (strcmp(FileName, "blockstacker/drop") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 9;
	}

	if (strcmp(FileName, "blockstacker/lineclear") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 10;
	}

	if (strcmp(FileName, "blockstacker/rotate") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 11;
	}

	if (strcmp(FileName, "breakout/bat") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 12;
	}

	if (strcmp(FileName, "breakout/brick") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 13;
	}

	if (strcmp(FileName, "frog/move") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 14;
	}

	if (strcmp(FileName, "invaders/enemydeath") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 15;
	}

	if (strcmp(FileName, "invaders/enemyshoot") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 16;
	}

	if (strcmp(FileName, "invaders/playerdeath") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 17;
	}

	if (strcmp(FileName, "invaders/playershoot") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 18;
	}

	if (strcmp(FileName, "pang/pop") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 19;
	}

	if (strcmp(FileName, "pang/shoot") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 20;
	}

	if (strcmp(FileName, "ramit/hit") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 21;
	}

	if (strcmp(FileName, "ramit/shoot") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 22;
	}

	if (strcmp(FileName, "snakey/food") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 23;
	}

	if (strcmp(FileName, "common/coin") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 24;
	}

	if (strcmp(FileName, "common/die") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 25;
	}

	if (strcmp(FileName, "common/one") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 26;
	}

	if (strcmp(FileName, "common/oneminute") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 27;
	}

	if (strcmp(FileName, "common/readygo") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 28;
	}

	if (strcmp(FileName, "common/succes") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 29;
	}

	if (strcmp(FileName, "common/three") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 30;
	}

	if (strcmp(FileName, "common/timeover") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 31;
	}

	if (strcmp(FileName, "common/two") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 32;
	}

	if (strcmp(FileName, "main/back") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 33;
	}

	if (strcmp(FileName, "main/confirm") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 34;
	}

	if (strcmp(FileName, "main/score") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 35;
	}

	if (strcmp(FileName, "main/select") == 0)
	{
		result = (int*) malloc(sizeof(int));
		*result = 36;
	}

	return result;
}

void CAudio_Init()
{
	CAudio_GlobalSoundEnabled = true;
	CAudio_SoundSlotsUsed = 0;
	CAudio_MusicSlotsUsed = 0;
	for (int i=0; i < SND_Max; i++)
		CAudio_Sounds[i] = NULL;

	for (int i=0; i < MUS_Max; i++)
		CAudio_Music[i] = NULL;
	
	for(int i=0; i < sound_channels; i++)
	{
		select_channel(i);
		set_channel_volume(1.0);
	}
}


// set the volume of the music
void CAudio_SetVolumeMusic(int VolumeIn)
{
	if (CAudio_GlobalSoundEnabled)
	{
		CAudio_VolumeMusic = VolumeIn;
		select_channel(0);
		set_channel_volume(VolumeIn / 128.0);
	}
}

// set the volume of sound
void CAudio_SetVolumeSound(int VolumeIn)
{
	if (CAudio_GlobalSoundEnabled)
	{
		CAudio_VolumeSound = VolumeIn;
		for (int i = 1; i < sound_channels; i++)
		{
			select_channel(i);
			set_channel_volume(VolumeIn / 128.0);
		}
	}
}

// increase the music volume with 4
void CAudio_IncVolumeMusic()
{
	if (CAudio_GlobalSoundEnabled)
	{
		if (CAudio_VolumeMusic < 128)
		{
			CAudio_VolumeMusic += 4;
			CAudio_SetVolumeMusic(CAudio_VolumeMusic);
		}
	}
}

// increase the sound volume with 4
void CAudio_IncVolumeSound()
{
	if (CAudio_GlobalSoundEnabled)
	{
		if (CAudio_VolumeSound < 128)
		{
			CAudio_VolumeSound += 4;
			CAudio_SetVolumeSound(CAudio_VolumeSound);
		}
	}
}

// decrease the volume with 4
void CAudio_DecVolumeMusic()
{
	if (CAudio_GlobalSoundEnabled)
	{
		if (CAudio_VolumeMusic > 0)
		{
			CAudio_VolumeMusic -= 4;
			CAudio_SetVolumeMusic(CAudio_VolumeMusic);
		}
	}
}

// decrease the volume with 4
void CAudio_DecVolumeSound()
{
	if (CAudio_GlobalSoundEnabled)
	{
		if (CAudio_VolumeSound > 0)
		{
			CAudio_VolumeSound -= 4;
			CAudio_SetVolumeSound(CAudio_VolumeSound);
		}
	}
}

void CAudio_StopMusic()
{
	if (CAudio_GlobalSoundEnabled)
		stop_channel(0);
}

bool CAudio_IsMusicPlaying()
{
	if(!CAudio_GlobalSoundEnabled)
		return false;

	return get_channel_state(0) == channel_playing;
}

void CAudio_UnLoadMusic(int MusicdID)
{
	if ((MusicdID < 0) || (MusicdID > MUS_Max) || !CAudio_GlobalSoundEnabled)
		return;

	if (CAudio_Music[MusicdID] == NULL)
		return;
	else
	{
		free(CAudio_Music[MusicdID]);
		CAudio_Music[MusicdID] = NULL;
		CAudio_MusicSlotsUsed--;
	}
}

void CAudio_UnloadMusics()
{
	CAudio_StopMusic();
	for (int i=0; i < MUS_Max; i++)
		CAudio_UnLoadMusic(i);
}

int CAudio_LoadMusic(int* FileName)
{
	int result = -1;
	
	if (CAudio_GlobalSoundEnabled)
		for (int i=0; i < MUS_Max; i++)
			if(CAudio_Music[i] == NULL)
			{
				CAudio_Music[i] = filenameToAudio(FileName);
				if(CAudio_Music[i])
				{
					CAudio_MusicSlotsUsed++;
					result = i;
				}
				break;
			}
	return result;
}


void CAudio_PlayMusic(int MusicID, int loops)
{
	if ((MusicID < 0) || (MusicID > MUS_Max) || !CAudio_GlobalSoundEnabled)
		return;

	if(CAudio_Music[MusicID] == NULL)
		return;

	CAudio_StopMusic();
	select_sound(*CAudio_Music[MusicID]);
	set_sound_loop(loops == -1);
	assign_channel_sound(0, *CAudio_Music[MusicID]);
	play_channel(0);
}

int CAudio_GetVolumeMusic()
{
	return CAudio_VolumeMusic;
}


void CAudio_PlaySound(int SoundID, int loops)
{
	if ((SoundID < 0) || (SoundID > SND_Max) || !CAudio_GlobalSoundEnabled)
		return;

	if (CAudio_Sounds[SoundID] == NULL)
		return;

	for (int i = 1; i < sound_channels; i++)
		if(get_channel_state(i) == channel_stopped)
		{
			select_sound(*CAudio_Sounds[SoundID]);
			set_sound_loop(loops == -1);
			assign_channel_sound(i, *CAudio_Sounds[SoundID]);
			play_channel(i);
			break;
		}
}

int CAudio_LoadSound(int* FileName)
{
	int result = -1;
	
	if (CAudio_GlobalSoundEnabled)
		for (int i=0; i < SND_Max; i++)
			if(CAudio_Sounds[i] == NULL)
			{
				CAudio_Sounds[i] = filenameToAudio(FileName);
				if(CAudio_Sounds[i])
				{
					CAudio_SoundSlotsUsed++;
					result = i;
				}
				break;
			}
	return result;
}

void CAudio_UnLoadSound(int SoundID)
{
	if ((SoundID < 0) || (SoundID > SND_Max) || !CAudio_GlobalSoundEnabled)
		return;

	if (CAudio_Sounds[SoundID] == NULL)
		return;
	else
	{
		free(CAudio_Sounds[SoundID]);
		CAudio_SoundSlotsUsed--;
		CAudio_Sounds[SoundID] = NULL;
	}
}


int CAudio_GetVolumeSound()
{
	return CAudio_VolumeSound;
}

void CAudio_StopSound()
{
	if(CAudio_GlobalSoundEnabled)
	 	for (int i = 1; i < sound_channels; i++)
	 		stop_channel(i);
}

void CAudio_UnloadSounds()
{
	CAudio_StopSound();

	for (int i=0; i < SND_Max; i++)
		CAudio_UnLoadSound(i);
}


void CAudio_DeInit()
{
	CAudio_UnloadSounds();
	CAudio_UnloadMusics();
	if (CAudio_GlobalSoundEnabled)
		CAudio_GlobalSoundEnabled = false;
		
}

#endif
