#ifndef VEC2F_H
#define VEC2F_H

#include "math.h"

struct Vec2F {
	float x;
	float y;
};

float clampFloat(float value, float min, float max)
{
	float tmpmin;
	if(max > value)
		tmpmin = value;
	else 
		tmpmin = max;
	if(min > tmpmin)
		return min;
	else 
		return tmpmin;
}

Vec2F* clampVec2F(Vec2F* value, Vec2F* min, Vec2F* max)
{
	Vec2F *Result = (Vec2F*) malloc(sizeof(Vec2F));
	Result->x = clampFloat(value->x, min->x, max->x);
	Result->y = clampFloat(value->y, min->y, max->y);
	return Result;
}

float length(Vec2F* value)
{
	return (float)sqrt(value->x*value->x + value->y*value->y);
}

#endif