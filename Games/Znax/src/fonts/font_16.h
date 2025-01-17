#ifndef font_16_H
#define font_16_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font_16_texture_id 3
#define font_16_region_id 0

textfont Fontfont_16;

void setupFontfont_16()
{
select_texture(font_16_texture_id);
select_region(font_16_region_id + 0); // 0
define_region(0,0,  -1,19,  0,0);
select_region(font_16_region_id + 1); // 13
define_region(17,0,  29,19,  17,0);
select_region(font_16_region_id + 2); // 16
define_region(34,0,  49,19,  34,0);
select_region(font_16_region_id + 3); // 16
define_region(51,0,  66,19,  51,0);
select_region(font_16_region_id + 4); // 16
define_region(68,0,  83,19,  68,0);
select_region(font_16_region_id + 5); // 7
define_region(85,0,  91,19,  85,0);
select_region(font_16_region_id + 6); // 16
define_region(102,0,  117,19,  102,0);
select_region(font_16_region_id + 7); // 16
define_region(119,0,  134,19,  119,0);
select_region(font_16_region_id + 8); // 16
define_region(136,0,  151,19,  136,0);
select_region(font_16_region_id + 9); // 16
define_region(153,0,  168,19,  153,0);
select_region(font_16_region_id + 10); // 16
define_region(170,0,  185,19,  170,0);
select_region(font_16_region_id + 11); // 16
define_region(187,0,  202,19,  187,0);
select_region(font_16_region_id + 12); // 16
define_region(204,0,  219,19,  204,0);
select_region(font_16_region_id + 13); // 16
define_region(221,0,  236,19,  221,0);
select_region(font_16_region_id + 14); // 16
define_region(238,0,  253,19,  238,0);
select_region(font_16_region_id + 15); // 16
define_region(255,0,  270,19,  255,0);
select_region(font_16_region_id + 16); // 16
define_region(0,20,  15,39,  0,20);
select_region(font_16_region_id + 17); // 16
define_region(17,20,  32,39,  17,20);
select_region(font_16_region_id + 18); // 16
define_region(34,20,  49,39,  34,20);
select_region(font_16_region_id + 19); // 16
define_region(51,20,  66,39,  51,20);
select_region(font_16_region_id + 20); // 16
define_region(68,20,  83,39,  68,20);
select_region(font_16_region_id + 21); // 16
define_region(85,20,  100,39,  85,20);
select_region(font_16_region_id + 22); // 16
define_region(102,20,  117,39,  102,20);
select_region(font_16_region_id + 23); // 16
define_region(119,20,  134,39,  119,20);
select_region(font_16_region_id + 24); // 16
define_region(136,20,  151,39,  136,20);
select_region(font_16_region_id + 25); // 16
define_region(153,20,  168,39,  153,20);
select_region(font_16_region_id + 26); // 16
define_region(170,20,  185,39,  170,20);
select_region(font_16_region_id + 27); // 16
define_region(187,20,  202,39,  187,20);
select_region(font_16_region_id + 28); // 16
define_region(204,20,  219,39,  204,20);
select_region(font_16_region_id + 29); // 16
define_region(221,20,  236,39,  221,20);
select_region(font_16_region_id + 30); // 16
define_region(238,20,  253,39,  238,20);
select_region(font_16_region_id + 31); // 16
define_region(255,20,  270,39,  255,20);
select_region(font_16_region_id + 32); //  6
define_region(0,40,  5,59,  0,40);
select_region(font_16_region_id + 33); //! 6
define_region(17,40,  22,59,  17,40);
select_region(font_16_region_id + 34); //" 7
define_region(34,40,  40,59,  34,40);
select_region(font_16_region_id + 35); //# 13
define_region(51,40,  63,59,  51,40);
select_region(font_16_region_id + 36); //$ 10
define_region(68,40,  77,59,  68,40);
select_region(font_16_region_id + 37); //% 17
define_region(85,40,  101,59,  85,40);
select_region(font_16_region_id + 38); //& 13
define_region(102,40,  114,59,  102,40);
select_region(font_16_region_id + 39); //' 4
define_region(119,40,  122,59,  119,40);
select_region(font_16_region_id + 40); //( 7
define_region(136,40,  142,59,  136,40);
select_region(font_16_region_id + 41); //) 7
define_region(153,40,  159,59,  153,40);
select_region(font_16_region_id + 42); //* 10
define_region(170,40,  179,59,  170,40);
select_region(font_16_region_id + 43); //+ 13
define_region(187,40,  199,59,  187,40);
select_region(font_16_region_id + 44); //, 6
define_region(204,40,  209,59,  204,40);
select_region(font_16_region_id + 45); //- 7
define_region(221,40,  227,59,  221,40);
select_region(font_16_region_id + 46); //. 6
define_region(238,40,  243,59,  238,40);
select_region(font_16_region_id + 47); /// 8
define_region(255,40,  262,59,  255,40);
select_region(font_16_region_id + 48); //0 10
define_region(0,60,  9,79,  0,60);
select_region(font_16_region_id + 49); //1 10
define_region(17,60,  26,79,  17,60);
select_region(font_16_region_id + 50); //2 10
define_region(34,60,  43,79,  34,60);
select_region(font_16_region_id + 51); //3 10
define_region(51,60,  60,79,  51,60);
select_region(font_16_region_id + 52); //4 10
define_region(68,60,  77,79,  68,60);
select_region(font_16_region_id + 53); //5 10
define_region(85,60,  94,79,  85,60);
select_region(font_16_region_id + 54); //6 10
define_region(102,60,  111,79,  102,60);
select_region(font_16_region_id + 55); //7 10
define_region(119,60,  128,79,  119,60);
select_region(font_16_region_id + 56); //8 10
define_region(136,60,  145,79,  136,60);
select_region(font_16_region_id + 57); //9 10
define_region(153,60,  162,79,  153,60);
select_region(font_16_region_id + 58); //: 7
define_region(170,60,  176,79,  170,60);
select_region(font_16_region_id + 59); //; 7
define_region(187,60,  193,79,  187,60);
select_region(font_16_region_id + 60); //< 13
define_region(204,60,  216,79,  204,60);
select_region(font_16_region_id + 61); //= 13
define_region(221,60,  233,79,  221,60);
select_region(font_16_region_id + 62); //> 13
define_region(238,60,  250,79,  238,60);
select_region(font_16_region_id + 63); //? 9
define_region(255,60,  263,79,  255,60);
select_region(font_16_region_id + 64); //@ 16
define_region(0,80,  15,99,  0,80);
select_region(font_16_region_id + 65); //A 11
define_region(17,80,  27,99,  17,80);
select_region(font_16_region_id + 66); //B 11
define_region(34,80,  44,99,  34,80);
select_region(font_16_region_id + 67); //C 11
define_region(51,80,  61,99,  51,80);
select_region(font_16_region_id + 68); //D 12
define_region(68,80,  79,99,  68,80);
select_region(font_16_region_id + 69); //E 10
define_region(85,80,  94,99,  85,80);
select_region(font_16_region_id + 70); //F 9
define_region(102,80,  110,99,  102,80);
select_region(font_16_region_id + 71); //G 12
define_region(119,80,  130,99,  119,80);
select_region(font_16_region_id + 72); //H 12
define_region(136,80,  147,99,  136,80);
select_region(font_16_region_id + 73); //I 7
define_region(153,80,  159,99,  153,80);
select_region(font_16_region_id + 74); //J 7
define_region(170,80,  176,99,  170,80);
select_region(font_16_region_id + 75); //K 11
define_region(187,80,  197,99,  187,80);
select_region(font_16_region_id + 76); //L 9
define_region(204,80,  212,99,  204,80);
select_region(font_16_region_id + 77); //M 13
define_region(221,80,  233,99,  221,80);
select_region(font_16_region_id + 78); //N 12
define_region(238,80,  249,99,  238,80);
select_region(font_16_region_id + 79); //O 13
define_region(255,80,  267,99,  255,80);
select_region(font_16_region_id + 80); //P 10
define_region(0,100,  9,119,  0,100);
select_region(font_16_region_id + 81); //Q 13
define_region(17,100,  29,119,  17,100);
select_region(font_16_region_id + 82); //R 12
define_region(34,100,  45,119,  34,100);
select_region(font_16_region_id + 83); //S 11
define_region(51,100,  61,119,  51,100);
select_region(font_16_region_id + 84); //T 10
define_region(68,100,  77,119,  68,100);
select_region(font_16_region_id + 85); //U 12
define_region(85,100,  96,119,  85,100);
select_region(font_16_region_id + 86); //V 11
define_region(102,100,  112,119,  102,100);
select_region(font_16_region_id + 87); //W 16
define_region(119,100,  134,119,  119,100);
select_region(font_16_region_id + 88); //X 11
define_region(136,100,  146,119,  136,100);
select_region(font_16_region_id + 89); //Y 10
define_region(153,100,  162,119,  153,100);
select_region(font_16_region_id + 90); //Z 11
define_region(170,100,  180,119,  170,100);
select_region(font_16_region_id + 91); //[ 7
define_region(187,100,  193,119,  187,100);
select_region(font_16_region_id + 92); // 8
define_region(204,100,  211,119,  204,100);
select_region(font_16_region_id + 93); //] 7
define_region(221,100,  227,119,  221,100);
select_region(font_16_region_id + 94); //^ 13
define_region(238,100,  250,119,  238,100);
select_region(font_16_region_id + 95); //_ 12
define_region(255,100,  266,119,  255,100);
select_region(font_16_region_id + 96); //` 10
define_region(0,120,  9,139,  0,120);
select_region(font_16_region_id + 97); //a 10
define_region(17,120,  26,139,  17,120);
select_region(font_16_region_id + 98); //b 10
define_region(34,120,  43,139,  34,120);
select_region(font_16_region_id + 99); //c 8
define_region(51,120,  58,139,  51,120);
select_region(font_16_region_id + 100); //d 10
define_region(68,120,  77,139,  68,120);
select_region(font_16_region_id + 101); //e 10
define_region(85,120,  94,139,  85,120);
select_region(font_16_region_id + 102); //f 7
define_region(102,120,  108,139,  102,120);
select_region(font_16_region_id + 103); //g 10
define_region(119,120,  128,139,  119,120);
select_region(font_16_region_id + 104); //h 10
define_region(136,120,  145,139,  136,120);
select_region(font_16_region_id + 105); //i 4
define_region(153,120,  156,139,  153,120);
select_region(font_16_region_id + 106); //j 7
define_region(170,120,  176,139,  170,120);
select_region(font_16_region_id + 107); //k 10
define_region(187,120,  196,139,  187,120);
select_region(font_16_region_id + 108); //l 4
define_region(204,120,  207,139,  204,120);
select_region(font_16_region_id + 109); //m 16
define_region(221,120,  236,139,  221,120);
select_region(font_16_region_id + 110); //n 10
define_region(238,120,  247,139,  238,120);
select_region(font_16_region_id + 111); //o 10
define_region(255,120,  264,139,  255,120);
select_region(font_16_region_id + 112); //p 10
define_region(0,140,  9,159,  0,140);
select_region(font_16_region_id + 113); //q 10
define_region(17,140,  26,159,  17,140);
select_region(font_16_region_id + 114); //r 7
define_region(34,140,  40,159,  34,140);
select_region(font_16_region_id + 115); //s 8
define_region(51,140,  58,159,  51,140);
select_region(font_16_region_id + 116); //t 6
define_region(68,140,  73,159,  68,140);
select_region(font_16_region_id + 117); //u 10
define_region(85,140,  94,159,  85,140);
select_region(font_16_region_id + 118); //v 9
define_region(102,140,  110,159,  102,140);
select_region(font_16_region_id + 119); //w 13
define_region(119,140,  131,159,  119,140);
select_region(font_16_region_id + 120); //x 9
define_region(136,140,  144,159,  136,140);
select_region(font_16_region_id + 121); //y 9
define_region(153,140,  161,159,  153,140);
select_region(font_16_region_id + 122); //z 8
define_region(170,140,  177,159,  170,140);
select_region(font_16_region_id + 123); //{ 10
define_region(187,140,  196,159,  187,140);
select_region(font_16_region_id + 124); //| 7
define_region(204,140,  210,159,  204,140);
select_region(font_16_region_id + 125); //} 10
define_region(221,140,  230,159,  221,140);
select_region(font_16_region_id + 126); //~ 13
define_region(238,140,  250,159,  238,140);
select_region(font_16_region_id + 127); // 16
define_region(255,140,  270,159,  255,140);

Fontfont_16.character_height = 20;
Fontfont_16.use_variable_width = true;
Fontfont_16.character_separation = 0;
Fontfont_16.line_separation = 0;

Fontfont_16.texture_id = font_16_texture_id;
Fontfont_16.character_zero_region_id = font_16_region_id;
textfont_read_region_widths(&Fontfont_16);

}
#endif
