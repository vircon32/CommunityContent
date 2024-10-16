#ifndef font_13_H
#define font_13_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font_13_texture_id 3
#define font_13_region_id 0

textfont Fontfont_13;

void setupFontfont_13()
{
select_texture(font_13_texture_id);
select_region(font_13_region_id + 0); // 0
define_region(0,0,  -1,15,  0,0);
select_region(font_13_region_id + 1); // 11
define_region(14,0,  24,15,  14,0);
select_region(font_13_region_id + 2); // 13
define_region(28,0,  40,15,  28,0);
select_region(font_13_region_id + 3); // 13
define_region(42,0,  54,15,  42,0);
select_region(font_13_region_id + 4); // 13
define_region(56,0,  68,15,  56,0);
select_region(font_13_region_id + 5); // 5
define_region(70,0,  74,15,  70,0);
select_region(font_13_region_id + 6); // 13
define_region(84,0,  96,15,  84,0);
select_region(font_13_region_id + 7); // 13
define_region(98,0,  110,15,  98,0);
select_region(font_13_region_id + 8); // 13
define_region(112,0,  124,15,  112,0);
select_region(font_13_region_id + 9); // 13
define_region(126,0,  138,15,  126,0);
select_region(font_13_region_id + 10); // 13
define_region(140,0,  152,15,  140,0);
select_region(font_13_region_id + 11); // 13
define_region(154,0,  166,15,  154,0);
select_region(font_13_region_id + 12); // 13
define_region(168,0,  180,15,  168,0);
select_region(font_13_region_id + 13); // 13
define_region(182,0,  194,15,  182,0);
select_region(font_13_region_id + 14); // 13
define_region(196,0,  208,15,  196,0);
select_region(font_13_region_id + 15); // 13
define_region(210,0,  222,15,  210,0);
select_region(font_13_region_id + 16); // 13
define_region(0,16,  12,31,  0,16);
select_region(font_13_region_id + 17); // 13
define_region(14,16,  26,31,  14,16);
select_region(font_13_region_id + 18); // 13
define_region(28,16,  40,31,  28,16);
select_region(font_13_region_id + 19); // 13
define_region(42,16,  54,31,  42,16);
select_region(font_13_region_id + 20); // 13
define_region(56,16,  68,31,  56,16);
select_region(font_13_region_id + 21); // 13
define_region(70,16,  82,31,  70,16);
select_region(font_13_region_id + 22); // 13
define_region(84,16,  96,31,  84,16);
select_region(font_13_region_id + 23); // 13
define_region(98,16,  110,31,  98,16);
select_region(font_13_region_id + 24); // 13
define_region(112,16,  124,31,  112,16);
select_region(font_13_region_id + 25); // 13
define_region(126,16,  138,31,  126,16);
select_region(font_13_region_id + 26); // 13
define_region(140,16,  152,31,  140,16);
select_region(font_13_region_id + 27); // 13
define_region(154,16,  166,31,  154,16);
select_region(font_13_region_id + 28); // 13
define_region(168,16,  180,31,  168,16);
select_region(font_13_region_id + 29); // 13
define_region(182,16,  194,31,  182,16);
select_region(font_13_region_id + 30); // 13
define_region(196,16,  208,31,  196,16);
select_region(font_13_region_id + 31); // 13
define_region(210,16,  222,31,  210,16);
select_region(font_13_region_id + 32); //  5
define_region(0,32,  4,47,  0,32);
select_region(font_13_region_id + 33); //! 5
define_region(14,32,  18,47,  14,32);
select_region(font_13_region_id + 34); //" 6
define_region(28,32,  33,47,  28,32);
select_region(font_13_region_id + 35); //# 11
define_region(42,32,  52,47,  42,32);
select_region(font_13_region_id + 36); //$ 8
define_region(56,32,  63,47,  56,32);
select_region(font_13_region_id + 37); //% 14
define_region(70,32,  83,47,  70,32);
select_region(font_13_region_id + 38); //& 10
define_region(84,32,  93,47,  84,32);
select_region(font_13_region_id + 39); //' 3
define_region(98,32,  100,47,  98,32);
select_region(font_13_region_id + 40); //( 6
define_region(112,32,  117,47,  112,32);
select_region(font_13_region_id + 41); //) 6
define_region(126,32,  131,47,  126,32);
select_region(font_13_region_id + 42); //* 8
define_region(140,32,  147,47,  140,32);
select_region(font_13_region_id + 43); //+ 11
define_region(154,32,  164,47,  154,32);
select_region(font_13_region_id + 44); //, 5
define_region(168,32,  172,47,  168,32);
select_region(font_13_region_id + 45); //- 6
define_region(182,32,  187,47,  182,32);
select_region(font_13_region_id + 46); //. 5
define_region(196,32,  200,47,  196,32);
select_region(font_13_region_id + 47); /// 7
define_region(210,32,  216,47,  210,32);
select_region(font_13_region_id + 48); //0 8
define_region(0,48,  7,63,  0,48);
select_region(font_13_region_id + 49); //1 8
define_region(14,48,  21,63,  14,48);
select_region(font_13_region_id + 50); //2 8
define_region(28,48,  35,63,  28,48);
select_region(font_13_region_id + 51); //3 8
define_region(42,48,  49,63,  42,48);
select_region(font_13_region_id + 52); //4 8
define_region(56,48,  63,63,  56,48);
select_region(font_13_region_id + 53); //5 8
define_region(70,48,  77,63,  70,48);
select_region(font_13_region_id + 54); //6 8
define_region(84,48,  91,63,  84,48);
select_region(font_13_region_id + 55); //7 8
define_region(98,48,  105,63,  98,48);
select_region(font_13_region_id + 56); //8 8
define_region(112,48,  119,63,  112,48);
select_region(font_13_region_id + 57); //9 8
define_region(126,48,  133,63,  126,48);
select_region(font_13_region_id + 58); //: 6
define_region(140,48,  145,63,  140,48);
select_region(font_13_region_id + 59); //; 6
define_region(154,48,  159,63,  154,48);
select_region(font_13_region_id + 60); //< 11
define_region(168,48,  178,63,  168,48);
select_region(font_13_region_id + 61); //= 11
define_region(182,48,  192,63,  182,48);
select_region(font_13_region_id + 62); //> 11
define_region(196,48,  206,63,  196,48);
select_region(font_13_region_id + 63); //? 7
define_region(210,48,  216,63,  210,48);
select_region(font_13_region_id + 64); //@ 13
define_region(0,64,  12,79,  0,64);
select_region(font_13_region_id + 65); //A 9
define_region(14,64,  22,79,  14,64);
select_region(font_13_region_id + 66); //B 9
define_region(28,64,  36,79,  28,64);
select_region(font_13_region_id + 67); //C 9
define_region(42,64,  50,79,  42,64);
select_region(font_13_region_id + 68); //D 10
define_region(56,64,  65,79,  56,64);
select_region(font_13_region_id + 69); //E 8
define_region(70,64,  77,79,  70,64);
select_region(font_13_region_id + 70); //F 8
define_region(84,64,  91,79,  84,64);
select_region(font_13_region_id + 71); //G 10
define_region(98,64,  107,79,  98,64);
select_region(font_13_region_id + 72); //H 10
define_region(112,64,  121,79,  112,64);
select_region(font_13_region_id + 73); //I 5
define_region(126,64,  130,79,  126,64);
select_region(font_13_region_id + 74); //J 6
define_region(140,64,  145,79,  140,64);
select_region(font_13_region_id + 75); //K 9
define_region(154,64,  162,79,  154,64);
select_region(font_13_region_id + 76); //L 8
define_region(168,64,  175,79,  168,64);
select_region(font_13_region_id + 77); //M 11
define_region(182,64,  192,79,  182,64);
select_region(font_13_region_id + 78); //N 10
define_region(196,64,  205,79,  196,64);
select_region(font_13_region_id + 79); //O 10
define_region(210,64,  219,79,  210,64);
select_region(font_13_region_id + 80); //P 8
define_region(0,80,  7,95,  0,80);
select_region(font_13_region_id + 81); //Q 10
define_region(14,80,  23,95,  14,80);
select_region(font_13_region_id + 82); //R 10
define_region(28,80,  37,95,  28,80);
select_region(font_13_region_id + 83); //S 9
define_region(42,80,  50,95,  42,80);
select_region(font_13_region_id + 84); //T 9
define_region(56,80,  64,95,  56,80);
select_region(font_13_region_id + 85); //U 10
define_region(70,80,  79,95,  70,80);
select_region(font_13_region_id + 86); //V 9
define_region(84,80,  92,95,  84,80);
select_region(font_13_region_id + 87); //W 13
define_region(98,80,  110,95,  98,80);
select_region(font_13_region_id + 88); //X 9
define_region(112,80,  120,95,  112,80);
select_region(font_13_region_id + 89); //Y 8
define_region(126,80,  133,95,  126,80);
select_region(font_13_region_id + 90); //Z 9
define_region(140,80,  148,95,  140,80);
select_region(font_13_region_id + 91); //[ 6
define_region(154,80,  159,95,  154,80);
select_region(font_13_region_id + 92); // 7
define_region(168,80,  174,95,  168,80);
select_region(font_13_region_id + 93); //] 6
define_region(182,80,  187,95,  182,80);
select_region(font_13_region_id + 94); //^ 11
define_region(196,80,  206,95,  196,80);
select_region(font_13_region_id + 95); //_ 10
define_region(210,80,  219,95,  210,80);
select_region(font_13_region_id + 96); //` 8
define_region(0,96,  7,111,  0,96);
select_region(font_13_region_id + 97); //a 8
define_region(14,96,  21,111,  14,96);
select_region(font_13_region_id + 98); //b 8
define_region(28,96,  35,111,  28,96);
select_region(font_13_region_id + 99); //c 7
define_region(42,96,  48,111,  42,96);
select_region(font_13_region_id + 100); //d 8
define_region(56,96,  63,111,  56,96);
select_region(font_13_region_id + 101); //e 8
define_region(70,96,  77,111,  70,96);
select_region(font_13_region_id + 102); //f 5
define_region(84,96,  88,111,  84,96);
select_region(font_13_region_id + 103); //g 8
define_region(98,96,  105,111,  98,96);
select_region(font_13_region_id + 104); //h 8
define_region(112,96,  119,111,  112,96);
select_region(font_13_region_id + 105); //i 4
define_region(126,96,  129,111,  126,96);
select_region(font_13_region_id + 106); //j 5
define_region(140,96,  144,111,  140,96);
select_region(font_13_region_id + 107); //k 8
define_region(154,96,  161,111,  154,96);
select_region(font_13_region_id + 108); //l 4
define_region(168,96,  171,111,  168,96);
select_region(font_13_region_id + 109); //m 13
define_region(182,96,  194,111,  182,96);
select_region(font_13_region_id + 110); //n 8
define_region(196,96,  203,111,  196,96);
select_region(font_13_region_id + 111); //o 8
define_region(210,96,  217,111,  210,96);
select_region(font_13_region_id + 112); //p 8
define_region(0,112,  7,127,  0,112);
select_region(font_13_region_id + 113); //q 8
define_region(14,112,  21,127,  14,112);
select_region(font_13_region_id + 114); //r 6
define_region(28,112,  33,127,  28,112);
select_region(font_13_region_id + 115); //s 7
define_region(42,112,  48,127,  42,112);
select_region(font_13_region_id + 116); //t 5
define_region(56,112,  60,127,  56,112);
select_region(font_13_region_id + 117); //u 8
define_region(70,112,  77,127,  70,112);
select_region(font_13_region_id + 118); //v 8
define_region(84,112,  91,127,  84,112);
select_region(font_13_region_id + 119); //w 11
define_region(98,112,  108,127,  98,112);
select_region(font_13_region_id + 120); //x 8
define_region(112,112,  119,127,  112,112);
select_region(font_13_region_id + 121); //y 8
define_region(126,112,  133,127,  126,112);
select_region(font_13_region_id + 122); //z 7
define_region(140,112,  146,127,  140,112);
select_region(font_13_region_id + 123); //{ 8
define_region(154,112,  161,127,  154,112);
select_region(font_13_region_id + 124); //| 6
define_region(168,112,  173,127,  168,112);
select_region(font_13_region_id + 125); //} 8
define_region(182,112,  189,127,  182,112);
select_region(font_13_region_id + 126); //~ 11
define_region(196,112,  206,127,  196,112);
select_region(font_13_region_id + 127); // 13
define_region(210,112,  222,127,  210,112);

Fontfont_13.character_height = 16;
Fontfont_13.use_variable_width = true;
Fontfont_13.character_separation = 0;
Fontfont_13.line_separation = 0;

Fontfont_13.texture_id = font_13_texture_id;
Fontfont_13.character_zero_region_id = font_13_region_id;
textfont_read_region_widths(&Fontfont_13);

}
#endif
