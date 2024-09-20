#ifndef PRINTFUNCS_H
#define PRINTFUNCS_H


#include "commonvars.h"
#include "helperfuncs.h"

// function provided by @Pharap
// If the array is not big enough,
int formatInteger(int *array, int integer)
{
    int maxDigits = 10;
    int maxintacters = (maxDigits + 1);
    int lastIndex = (maxintacters - 1);

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
void printNumber(int ax, int ay, int aNumber, int maxDigits)
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

        set_bkg_tile_xy(ax + (maxDigits - digits) + c, ay, number[buffSize - digits + c] + 32);
    }
}

//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(int ax, int ay, int* amsg)
{
    // based on input from @Pharap
    int *p = amsg;
    int index = 0;

    while (1)
    {
        int fint = *(p++);
        int tile = 61;
        switch (fint)
        {
        case 0:
            return;

        case '[':
            tile = 70;
            break;

        case ']':
            tile = 64;
            break;

        case '<':
            tile = 73;
            break;

        case '>':
            tile = 67;
            break;

        case '+':
            tile = 63;
            break;

        case '*':
            tile = 62;
            break;

        case '|':
            tile = 69;
            break;

        case '#':
            tile = 65;
            break;

        case ':':
            tile = 116;
            break;

        case 'a':
            tile = 119;
            break;

        case 'b':
            tile = 117;
            break;

        default:
            if ((fint >= 'A') && (fint <= 'Z'))
                tile = fint + 25;

            if ((fint >= '0') && (fint <= '9'))
                tile = fint + 32;
            break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}


void printCongratsScreen(int ax, int ay, int* amsg)
{
    int* p = amsg;
    int index = 0;
    while (1)
    {
        int fint = *(p++);
        int tile = 64;
        switch (fint)
        {
            case 0:
                return;

            default:
                if ((fint >= 'A') && (fint <= 'Z'))
                    tile = fint;
                break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}


#endif