/*
 *    ──▄▄▄▄▄  ▄▄▄   ▄▄▄▄ ▄▄▄▄▄
 *    ╺╺██▄▄  ██▀██ ███▄▄ ██▄▄
 *    ──██▄▄▄ ██▀██ ▄▄██▀ ██▄▄▄
 *      ▄▄    ▄▄ ▄▄▄▄──
 *      ██    ██ ██▄██╺╺
 *      ██▄▄▄ ██ ██▄█▀──
 *
 *  Version: 1.0
 *
 *  A simple yet powerful library designed to produce smooth movements.
 *
 *  Included in this single file is the ease function, which is the
 *  only one needed to make those previously said efects.
 *
 *
 *  usage: ease(t, EASE, EASE)
 *    replace t with a normalized floating number (between 0 and 1)
 *    replace EASE with the easing effect you want.
 *
 *    returns an eased value between 0 and 1.
 *
 *
 *    still don't understand it? there are demos too!
 */



#include "math.h"

#ifndef EASINGS_H
#define EASINGS_H

#define NONE	0
#define LINEAR	1
#define SINE	2
#define CUBIC	3
#define QUINT	4
#define CIRC	5
#define BACK	6


#define c1 1.70158
#define c3 2.70158

float ease(float time, int ease_in, int ease_out){

	float t, eased;

	// these two are used to limit the easing to a normalized float (from 0 to 1)
	// and apparently these help with optimizations too
	if (time <= 0.0) return 0.0;
	else if (time >= 1.0) return 1.0;


	if(time < 0.5 || ease_out==NONE){

		// First half: ease in
		if(ease_out==NONE) t = time;
		else t = time * 2.0;


		if (ease_in == LINEAR) {
			eased = t/2.0;

		}else if(ease_in != NONE){
			switch(ease_in){

				case SINE: eased = 1.0 - cos((t * pi) / 2.0); break;

				case CUBIC: eased = t*t*t; break;

				case QUINT: eased = t*t*t*t*t; break;

				case CIRC: eased = 1.0 - sqrt(1.0 - t*t); break;

				case BACK: eased = c3 * t*t*t - c1 * t*t; break;

			}

			if(ease_out == NONE) return eased;
			else return eased * 0.5;

		}

	}

	if(time >=0.5 || ease_in==NONE){

		// Second half: ease out
		if(ease_in==NONE) t = time;
		else t = (time-0.5) * 2.0;


		if (ease_out == LINEAR) {
			eased = t;

		}else if(ease_out != NONE){
			float t_inv=(1.0-t);

			switch(ease_out){

				case SINE: eased = sin((t * pi) / 2.0); break;

				case CUBIC: eased = 1.0 - t_inv * t_inv * t_inv; break;

				case QUINT: eased = 1.0 - t_inv * t_inv * t_inv * t_inv * t_inv ; break;

				case CIRC: eased = sqrt(1.0 - t_inv * t_inv); break;

				case BACK: eased = 1.0 + c3 * (t-1.0)*(t-1.0)*(t-1.0) + c1 * (t-1.0)*(t-1.0); break;


			}

			if(ease_in == NONE) return eased;
			else return 0.5 + eased * 0.5;
		}

	}

}


#endif
