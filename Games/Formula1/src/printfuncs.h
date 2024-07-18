#ifndef PRINTFUNCS_H
#define PRINTFUNCS_H

#include "texture.h"

// function provided by @Pharap
// If the array is not big enough,
int formatInteger(int *array, int integer)
{
    int maxDigits = 10;
    int maxCharacters = (maxDigits + 1);
    int lastIndex = (maxCharacters - 1);

    array[lastIndex] = 0;

    if (integer == 0)
    {
        array[lastIndex - 1] = '0';
        return 1;
    }

    int digits = 0;

    do
    {
        int digit = integer % 10;
        integer /= 10;

        ++digits;

        array[lastIndex - digits] = ('0' + digit);
    } while (integer > 0);

    return digits;
}

//print a number on levelselect or game screen
void printNumber(Texture* texture, int ax, int ay, int offsetx, int offsety, int tileSize, int aNumber, int maxDigits)
{
    int buffSize = 10;
    int[10 + 1] number; //buffsize + 1
    int digits = formatInteger(number, aNumber);
    int maxFor = digits;
    if (digits > maxDigits)
        maxFor = maxDigits;
    for (int c = 0; c < maxFor; c++)
    {
        if (number[buffSize - digits + c] == 0)
            return;

        if (texture)
        {
            drawTexture(texture, number[buffSize - digits + c] - 47, offsetx + (ax + (maxDigits - digits) + c) * tileSize, offsety + ay* tileSize);
        }
    }
}

//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(Texture* texture, int ax, int ay, int offsetx, int offsety, int tileSize, int* amsg)
{
    // based on input from @Pharap
    int *p = amsg;
    int index = 0;

    while (1)
    {
        int fChar = *(p++);
        int tile = 61;
        switch (fChar)
        {
			
			case 0:
				return;

			case ':':
            	tile = 37;
            	break;	
			
			case '/':
            	tile = 38;
            	break;	

			case '.':
            	tile = 39;
            	break;

			default:
				if ((fChar >= 'A') && (fChar <= 'Z'))
					tile = fChar - 54;

				if ((fChar >= '0') && (fChar <= '9'))
					tile = fChar - 47;
			
				break;
        }
        
        if (texture)
        {
        	drawTexture(texture, tile, offsetx + (ax + index) * tileSize, offsety + ay * tileSize);
        }
        ++index;
    }
}




#endif