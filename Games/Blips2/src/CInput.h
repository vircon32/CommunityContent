
#ifndef CINPUT_H
#define CINPUT_H

#include "input.h"
#include "Defines.h"

#define MAXJOYSTICKBUTTONS 37


struct CInput 
{
    bool[MAXJOYSTICKBUTTONS] JoystickHeld;
	int PNumJoysticks;
    int UpdateCounter;
    int PUpdateCounterDelay;
};


void CInput_Reset(CInput* Input) {
    int y;
    for (y=0;y<MAXJOYSTICKBUTTONS;y++)
	    Input->JoystickHeld[y] = false;
}

void CInput_Destroy(CInput* Input) {
	free(Input);
	Input = NULL;
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

void CInput_Update(CInput* Input) {
    if (Input->UpdateCounter > 0)
        Input->UpdateCounter--;
	Input->JoystickHeld[BUT_UP] = gamepad_up() > 0;
	Input->JoystickHeld[BUT_RIGHT] = gamepad_right() > 0;
	Input->JoystickHeld[BUT_DOWN] = gamepad_down() > 0;
	Input->JoystickHeld[BUT_LEFT] = gamepad_left() > 0;
  	Input->JoystickHeld[BUT_A] = gamepad_button_a() > 0;
	Input->JoystickHeld[BUT_B] = gamepad_button_b() > 0;
	Input->JoystickHeld[BUT_X] = gamepad_button_x() > 0;
	Input->JoystickHeld[BUT_Y] = gamepad_button_y() > 0;
	Input->JoystickHeld[BUT_START] = gamepad_button_start() > 0;
	Input->JoystickHeld[BUT_L] = gamepad_button_l() > 0;
	Input->JoystickHeld[BUT_R] = gamepad_button_r() > 0;
}

bool CInput_HasInput(CInput* Input)
{
	CInput_Update(Input);
	for (int y=0;y<MAXJOYSTICKBUTTONS;y++)
		if(Input->JoystickHeld[y])
			return true;
	return false;
}

CInput* CInput_Create(int UpdateCounterDelay) {
    CInput* Result = (CInput*) malloc(sizeof(CInput));
	CInput_Reset(Result);
    Result->PNumJoysticks = 1;
    Result->PUpdateCounterDelay = UpdateCounterDelay;
    Result->UpdateCounter = 0;
	return Result;
}




#endif
