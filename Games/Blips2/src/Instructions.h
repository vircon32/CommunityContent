#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "CInput.h"
#include "Common.h"
#include "GameFuncs.h"


void Instructions()
{
	CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		sleep(1);
	while (GameState == GSInstructions)
	{
		drawTexture(IMGInstructions,0,0,0);

		CInput_Update(Input);

		//BUT_X BUT_Y BUT_A BUT_B
		if(Input->JoystickHeld[BUT_X] || Input->JoystickHeld[BUT_Y] || Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_B]|| Input->JoystickHeld[BUT_START])
        {
            GameState=GSTitleScreen;
			CAudio_PlaySound(Sounds[SND_BACK],0);
        }

        end_frame();
	}
	CInput_Destroy(Input);
}

#endif