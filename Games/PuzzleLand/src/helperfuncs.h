#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include "string.h"
#include "texture.h"

Texture* loadImageAtPath(int* file)
{
	if( strcmp(file, "graphics/betweenstage") == 0)
		return newTextureHorz(0,0,1,0,0,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/betweenstagelevel1") == 0)
		return newTextureHorz(0,1,1,320,0,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/blockactiveimage") == 0)
		return newTextureHorz(0,2,1,332,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/blockimage") == 0)
		return newTextureHorz(0,3,1,320,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border1") == 0)
		return newTextureHorz(0,4,1,344,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border2") == 0)
		return newTextureHorz(0,5,1,356,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border3") == 0)
		return newTextureHorz(0,6,1,368,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border4") == 0)
		return newTextureHorz(0,7,1,380,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border5") == 0)
		return newTextureHorz(0,8,1,392,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border6") == 0)
		return newTextureHorz(0,9,1,404,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/border7") == 0)
		return newTextureHorz(0,10,1,416,480,12,12,xscale,yscale);
	
	if( strcmp(file, "graphics/bridge") == 0)
		return newTextureHorz(0,11,1,346,520,113,16,xscale,yscale);
	
	if( strcmp(file, "graphics/hand") == 0)
		return newTextureHorz(0,12,1,320,520,26,14,xscale,yscale);
	
	if( strcmp(file, "graphics/intro") == 0)
		return newTextureHorz(0,13,1,0,240,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/oldman") == 0)
		return newTextureHorz(0,14,1,0,480	,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/optionsselect") == 0)
		return newTextureHorz(0,15,1,320,536,26,26,xscale,yscale);
	
	if( strcmp(file, "graphics/paper") == 0)
		return newTextureHorz(0,16,1,640,240,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/roombackground") == 0)
		return newTextureHorz(0,17,1,640,0,320,240,xscale,yscale);
	
	if( strcmp(file, "graphics/ryf-cloud") == 0)
		return newTextureHorz(0,18,1,400,536,60,28,xscale,yscale);
	
	if( strcmp(file, "graphics/ryf-fairy") == 0)
		return newTextureHorz(0,19,2,346,536,54,33,xscale,yscale);
	
	if( strcmp(file, "graphics/ryf-player") == 0)
		return newTextureHorz(0,21,19,320,492,437,28,xscale,yscale);
	
	if( strcmp(file, "graphics/ryf-shadow") == 0)
		return newTextureHorz(0,40,1,459,520,20,4,xscale,yscale);
	
	if( strcmp(file, "graphics/ryf-smallcloud") == 0)
		return newTextureHorz(0,41,1,479,520,30,14,xscale,yscale);
	
	if( strcmp(file, "graphics/select") == 0)
		return newTextureHorz(0,42,1,373,569,26,26,xscale,yscale);

	if( strcmp(file, "graphics/spaceship") == 0)
		return newTextureHorz(0,43,1,320,569,53,38,xscale,yscale);

	if( strcmp(file, "graphics/stageblock1") == 0)
		return newTextureHorz(0,44,1,320,607,25,37,xscale,yscale);

	if( strcmp(file, "graphics/stageblock10") == 0)
		return newTextureHorz(0,45,1,679,607,25,25,xscale,yscale);

	if( strcmp(file, "graphics/stageblock2") == 0)
		return newTextureHorz(0,46,1,345,607,62,12,xscale,yscale);

	if( strcmp(file, "graphics/stageblock3") == 0)
		return newTextureHorz(0,47,1,407,607,37,37,xscale,yscale);

	if( strcmp(file, "graphics/stageblock4") == 0)
		return newTextureHorz(0,48,1,444,607,37,25,xscale,yscale);

	if( strcmp(file, "graphics/stageblock5") == 0)
		return newTextureHorz(0,49,1,481,607,50,25,xscale,yscale);

	if( strcmp(file, "graphics/stageblock6") == 0)
		return newTextureHorz(0,50,1,531,607,37,37,xscale,yscale);

	if( strcmp(file, "graphics/stageblock7") == 0)
		return newTextureHorz(0,51,1,568,607,37,37,xscale,yscale);

	if( strcmp(file, "graphics/stageblock8") == 0)
		return newTextureHorz(0,52,1,605,607,37,37,xscale,yscale);

	if( strcmp(file, "graphics/stageblock9") == 0)
		return newTextureHorz(0,53,1,642,607,37,37,xscale,yscale);

	if( strcmp(file, "graphics/stageclearkader") == 0)
		return newTextureHorz(0,54,1,0,720,250,95,xscale,yscale);

	if( strcmp(file, "graphics/title") == 0)
		return newTextureHorz(0,55,1,320,240,320,240,xscale,yscale);

	if( strcmp(file, "graphics/titleselector") == 0)
		return newTextureHorz(0,56,1,509,520,185,14,xscale,yscale);

	if( strcmp(file, "graphics/border") == 0)
		return newTextureHorz(0,57,1,384,664,640,360,1.0,1.0);

	return NULL;
}

#endif