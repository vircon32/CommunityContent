#ifndef UTILFUNCS_H
#define UTILFUNCS_H

#include "time.h"

float getCurrentTimeMilliseconds()
{
	return get_frame_counter() * 1000.0/60.0;
}

#endif