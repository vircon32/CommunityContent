#ifndef CINPUT_H
#define CINPUT_H

#define MAXJOYSTICKBUTTONS 12
#define MAXJOYSTICKS 1

#include "input.h"

struct CInput 
{
    bool[MAXJOYSTICKS][MAXJOYSTICKBUTTONS] JoystickHeld;
    int PNumJoysticks;
    int UpdateCounter;
    int PUpdateCounterDelay;
};

bool CInput_HasInput(CInput* Input)
{
	return (Input->JoystickHeld[0][BUT_UP] || Input->JoystickHeld[0][BUT_RIGHT] || Input->JoystickHeld[0][BUT_DOWN] || Input->JoystickHeld[0][BUT_LEFT] ||
		Input->JoystickHeld[0][BUT_A] || Input->JoystickHeld[0][BUT_B] || Input->JoystickHeld[0][BUT_X] || Input->JoystickHeld[0][BUT_Y] ||
		Input->JoystickHeld[0][BUT_L] || Input->JoystickHeld[0][BUT_R] || Input->JoystickHeld[0][BUT_START] || Input->JoystickHeld[0][BUT_SELECT]);
}

void CInput_Reset(CInput* Input) 
{
	Input->JoystickHeld[0][BUT_UP] = false;
	Input->JoystickHeld[0][BUT_RIGHT] = false;
	Input->JoystickHeld[0][BUT_DOWN] = false;
	Input->JoystickHeld[0][BUT_LEFT] = false;
	Input->JoystickHeld[0][BUT_A] = false;
	Input->JoystickHeld[0][BUT_B] = false;
	Input->JoystickHeld[0][BUT_X] = false;
	Input->JoystickHeld[0][BUT_Y] = false;
	Input->JoystickHeld[0][BUT_L] = false;
	Input->JoystickHeld[0][BUT_R] = false;
	Input->JoystickHeld[0][BUT_START] = false;
	Input->JoystickHeld[0][BUT_SELECT] = false;
}

CInput* CInput_Create(int UpdateCounterDelay) 
{
    CInput* Result = (CInput*) malloc(sizeof(CInput));
	CInput_Reset(Result);
    Result->PNumJoysticks = 1;
    Result->PUpdateCounterDelay = UpdateCounterDelay;
    Result->UpdateCounter = 0;
	return Result;
}

void CInput_Destroy(CInput* Input) 
{
	if(Input)
	{
		free(Input);
		Input = NULL;
	}
}


void CInput_Update(CInput* Input) 
{
    if (Input->UpdateCounter > 0)
        Input->UpdateCounter--;
    
	Input->JoystickHeld[0][BUT_UP] = gamepad_up() > 0;
	Input->JoystickHeld[0][BUT_RIGHT] = gamepad_right() > 0;
	Input->JoystickHeld[0][BUT_DOWN] = gamepad_down() > 0;
	Input->JoystickHeld[0][BUT_LEFT] = gamepad_left() > 0;
	Input->JoystickHeld[0][BUT_A] = gamepad_button_a() > 0;
	Input->JoystickHeld[0][BUT_B] = gamepad_button_b() > 0;
	Input->JoystickHeld[0][BUT_X] = gamepad_button_x() > 0;
	Input->JoystickHeld[0][BUT_Y] = gamepad_button_y() > 0;
	Input->JoystickHeld[0][BUT_L] = gamepad_button_l() > 0;
	Input->JoystickHeld[0][BUT_R] = gamepad_button_r() > 0;
	Input->JoystickHeld[0][BUT_START] = gamepad_button_start() > 0;
	Input->JoystickHeld[0][BUT_SELECT] = false;
}

bool CInput_Ready(CInput* Input)
{
	return (Input->UpdateCounter == 0);
}

void CInput_Delay(CInput* Input)
{
	Input->UpdateCounter = Input->PUpdateCounterDelay;
}

int CInput_NumJoysticks(CInput* Input)
{
	return Input->PNumJoysticks;
}


void CInput_WaitNoInput(CInput *Input)
{
	CInput_Update(Input);
	while(CInput_HasInput(Input))
	{
		CInput_Update(Input);
		end_frame();
	}
}


#endif
