#ifndef font_14_H
#define font_14_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font_14_texture_id 4
#define font_14_region_id 0

textfont Fontfont_14;

void setupFontfont_14()
{
select_texture(font_14_texture_id);
select_region(font_14_region_id + 0); // 0
define_region(0,0,  -1,12,  0,0);
select_region(font_14_region_id + 1); // 10
define_region(13,0,  22,12,  13,0);
select_region(font_14_region_id + 2); // 7
define_region(26,0,  32,12,  26,0);
select_region(font_14_region_id + 3); // 12
define_region(39,0,  50,12,  39,0);
select_region(font_14_region_id + 4); // 7
define_region(52,0,  58,12,  52,0);
select_region(font_14_region_id + 5); // 6
define_region(65,0,  70,12,  65,0);
select_region(font_14_region_id + 6); // 7
define_region(78,0,  84,12,  78,0);
select_region(font_14_region_id + 7); // 7
define_region(91,0,  97,12,  91,0);
select_region(font_14_region_id + 8); // 7
define_region(104,0,  110,12,  104,0);
select_region(font_14_region_id + 9); // 7
define_region(117,0,  123,12,  117,0);
select_region(font_14_region_id + 10); // 7
define_region(130,0,  136,12,  130,0);
select_region(font_14_region_id + 11); // 7
define_region(143,0,  149,12,  143,0);
select_region(font_14_region_id + 12); // 7
define_region(156,0,  162,12,  156,0);
select_region(font_14_region_id + 13); // 7
define_region(169,0,  175,12,  169,0);
select_region(font_14_region_id + 14); // 7
define_region(182,0,  188,12,  182,0);
select_region(font_14_region_id + 15); // 7
define_region(195,0,  201,12,  195,0);
select_region(font_14_region_id + 16); // 7
define_region(0,13,  6,25,  0,13);
select_region(font_14_region_id + 17); // 7
define_region(13,13,  19,25,  13,13);
select_region(font_14_region_id + 18); // 7
define_region(26,13,  32,25,  26,13);
select_region(font_14_region_id + 19); // 7
define_region(39,13,  45,25,  39,13);
select_region(font_14_region_id + 20); // 7
define_region(52,13,  58,25,  52,13);
select_region(font_14_region_id + 21); // 7
define_region(65,13,  71,25,  65,13);
select_region(font_14_region_id + 22); // 7
define_region(78,13,  84,25,  78,13);
select_region(font_14_region_id + 23); // 7
define_region(91,13,  97,25,  91,13);
select_region(font_14_region_id + 24); // 7
define_region(104,13,  110,25,  104,13);
select_region(font_14_region_id + 25); // 7
define_region(117,13,  123,25,  117,13);
select_region(font_14_region_id + 26); // 7
define_region(130,13,  136,25,  130,13);
select_region(font_14_region_id + 27); // 7
define_region(143,13,  149,25,  143,13);
select_region(font_14_region_id + 28); // 7
define_region(156,13,  162,25,  156,13);
select_region(font_14_region_id + 29); // 7
define_region(169,13,  175,25,  169,13);
select_region(font_14_region_id + 30); // 7
define_region(182,13,  188,25,  182,13);
select_region(font_14_region_id + 31); // 7
define_region(195,13,  201,25,  195,13);
select_region(font_14_region_id + 32); //  4
define_region(0,26,  3,38,  0,26);
select_region(font_14_region_id + 33); //! 5
define_region(13,26,  17,38,  13,26);
select_region(font_14_region_id + 34); //" 6
define_region(26,26,  31,38,  26,26);
select_region(font_14_region_id + 35); //# 9
define_region(39,26,  47,38,  39,26);
select_region(font_14_region_id + 36); //$ 8
define_region(52,26,  59,38,  52,26);
select_region(font_14_region_id + 37); //% 13
define_region(65,26,  77,38,  65,26);
select_region(font_14_region_id + 38); //& 9
define_region(78,26,  86,38,  78,26);
select_region(font_14_region_id + 39); //' 4
define_region(91,26,  94,38,  91,26);
select_region(font_14_region_id + 40); //( 6
define_region(104,26,  109,38,  104,26);
select_region(font_14_region_id + 41); //) 6
define_region(117,26,  122,38,  117,26);
select_region(font_14_region_id + 42); //* 8
define_region(130,26,  137,38,  130,26);
select_region(font_14_region_id + 43); //+ 9
define_region(143,26,  151,38,  143,26);
select_region(font_14_region_id + 44); //, 4
define_region(156,26,  159,38,  156,26);
select_region(font_14_region_id + 45); //- 5
define_region(169,26,  173,38,  169,26);
select_region(font_14_region_id + 46); //. 4
define_region(182,26,  185,38,  182,26);
select_region(font_14_region_id + 47); /// 7
define_region(195,26,  201,38,  195,26);
select_region(font_14_region_id + 48); //0 8
define_region(0,39,  7,51,  0,39);
select_region(font_14_region_id + 49); //1 8
define_region(13,39,  20,51,  13,39);
select_region(font_14_region_id + 50); //2 8
define_region(26,39,  33,51,  26,39);
select_region(font_14_region_id + 51); //3 8
define_region(39,39,  46,51,  39,39);
select_region(font_14_region_id + 52); //4 8
define_region(52,39,  59,51,  52,39);
select_region(font_14_region_id + 53); //5 8
define_region(65,39,  72,51,  65,39);
select_region(font_14_region_id + 54); //6 8
define_region(78,39,  85,51,  78,39);
select_region(font_14_region_id + 55); //7 8
define_region(91,39,  98,51,  91,39);
select_region(font_14_region_id + 56); //8 8
define_region(104,39,  111,51,  104,39);
select_region(font_14_region_id + 57); //9 8
define_region(117,39,  124,51,  117,39);
select_region(font_14_region_id + 58); //: 5
define_region(130,39,  134,51,  130,39);
select_region(font_14_region_id + 59); //; 5
define_region(143,39,  147,51,  143,39);
select_region(font_14_region_id + 60); //< 9
define_region(156,39,  164,51,  156,39);
select_region(font_14_region_id + 61); //= 9
define_region(169,39,  177,51,  169,39);
select_region(font_14_region_id + 62); //> 9
define_region(182,39,  190,51,  182,39);
select_region(font_14_region_id + 63); //? 7
define_region(195,39,  201,51,  195,39);
select_region(font_14_region_id + 64); //@ 10
define_region(0,52,  9,64,  0,52);
select_region(font_14_region_id + 65); //A 8
define_region(13,52,  20,64,  13,52);
select_region(font_14_region_id + 66); //B 8
define_region(26,52,  33,64,  26,52);
select_region(font_14_region_id + 67); //C 8
define_region(39,52,  46,64,  39,52);
select_region(font_14_region_id + 68); //D 9
define_region(52,52,  60,64,  52,52);
select_region(font_14_region_id + 69); //E 7
define_region(65,52,  71,64,  65,52);
select_region(font_14_region_id + 70); //F 7
define_region(78,52,  84,64,  78,52);
select_region(font_14_region_id + 71); //G 9
define_region(91,52,  99,64,  91,52);
select_region(font_14_region_id + 72); //H 9
define_region(104,52,  112,64,  104,52);
select_region(font_14_region_id + 73); //I 6
define_region(117,52,  122,64,  117,52);
select_region(font_14_region_id + 74); //J 6
define_region(130,52,  135,64,  130,52);
select_region(font_14_region_id + 75); //K 8
define_region(143,52,  150,64,  143,52);
select_region(font_14_region_id + 76); //L 7
define_region(156,52,  162,64,  156,52);
select_region(font_14_region_id + 77); //M 10
define_region(169,52,  178,64,  169,52);
select_region(font_14_region_id + 78); //N 9
define_region(182,52,  190,64,  182,52);
select_region(font_14_region_id + 79); //O 9
define_region(195,52,  203,64,  195,52);
select_region(font_14_region_id + 80); //P 8
define_region(0,65,  7,77,  0,65);
select_region(font_14_region_id + 81); //Q 9
define_region(13,65,  21,77,  13,65);
select_region(font_14_region_id + 82); //R 8
define_region(26,65,  33,77,  26,65);
select_region(font_14_region_id + 83); //S 8
define_region(39,65,  46,77,  39,65);
select_region(font_14_region_id + 84); //T 7
define_region(52,65,  58,77,  52,65);
select_region(font_14_region_id + 85); //U 9
define_region(65,65,  73,77,  65,65);
select_region(font_14_region_id + 86); //V 8
define_region(78,65,  85,77,  78,65);
select_region(font_14_region_id + 87); //W 12
define_region(91,65,  102,77,  91,65);
select_region(font_14_region_id + 88); //X 8
define_region(104,65,  111,77,  104,65);
select_region(font_14_region_id + 89); //Y 8
define_region(117,65,  124,77,  117,65);
select_region(font_14_region_id + 90); //Z 7
define_region(130,65,  136,77,  130,65);
select_region(font_14_region_id + 91); //[ 6
define_region(143,65,  148,77,  143,65);
select_region(font_14_region_id + 92); // 7
define_region(156,65,  162,77,  156,65);
select_region(font_14_region_id + 93); //] 6
define_region(169,65,  174,77,  169,65);
select_region(font_14_region_id + 94); //^ 9
define_region(182,65,  190,77,  182,65);
select_region(font_14_region_id + 95); //_ 8
define_region(195,65,  202,77,  195,65);
select_region(font_14_region_id + 96); //` 8
define_region(0,78,  7,90,  0,78);
select_region(font_14_region_id + 97); //a 7
define_region(13,78,  19,90,  13,78);
select_region(font_14_region_id + 98); //b 7
define_region(26,78,  32,90,  26,78);
select_region(font_14_region_id + 99); //c 6
define_region(39,78,  44,90,  39,78);
select_region(font_14_region_id + 100); //d 7
define_region(52,78,  58,90,  52,78);
select_region(font_14_region_id + 101); //e 7
define_region(65,78,  71,90,  65,78);
select_region(font_14_region_id + 102); //f 5
define_region(78,78,  82,90,  78,78);
select_region(font_14_region_id + 103); //g 7
define_region(91,78,  97,90,  91,78);
select_region(font_14_region_id + 104); //h 8
define_region(104,78,  111,90,  104,78);
select_region(font_14_region_id + 105); //i 4
define_region(117,78,  120,90,  117,78);
select_region(font_14_region_id + 106); //j 5
define_region(130,78,  134,90,  130,78);
select_region(font_14_region_id + 107); //k 7
define_region(143,78,  149,90,  143,78);
select_region(font_14_region_id + 108); //l 4
define_region(156,78,  159,90,  156,78);
select_region(font_14_region_id + 109); //m 11
define_region(169,78,  179,90,  169,78);
select_region(font_14_region_id + 110); //n 8
define_region(182,78,  189,90,  182,78);
select_region(font_14_region_id + 111); //o 7
define_region(195,78,  201,90,  195,78);
select_region(font_14_region_id + 112); //p 7
define_region(0,91,  6,103,  0,91);
select_region(font_14_region_id + 113); //q 7
define_region(13,91,  19,103,  13,91);
select_region(font_14_region_id + 114); //r 5
define_region(26,91,  30,103,  26,91);
select_region(font_14_region_id + 115); //s 6
define_region(39,91,  44,103,  39,91);
select_region(font_14_region_id + 116); //t 5
define_region(52,91,  56,103,  52,91);
select_region(font_14_region_id + 117); //u 8
define_region(65,91,  72,103,  65,91);
select_region(font_14_region_id + 118); //v 7
define_region(78,91,  84,103,  78,91);
select_region(font_14_region_id + 119); //w 10
define_region(91,91,  100,103,  91,91);
select_region(font_14_region_id + 120); //x 7
define_region(104,91,  110,103,  104,91);
select_region(font_14_region_id + 121); //y 7
define_region(117,91,  123,103,  117,91);
select_region(font_14_region_id + 122); //z 6
define_region(130,91,  135,103,  130,91);
select_region(font_14_region_id + 123); //{ 8
define_region(143,91,  150,103,  143,91);
select_region(font_14_region_id + 124); //| 6
define_region(156,91,  161,103,  156,91);
select_region(font_14_region_id + 125); //} 8
define_region(169,91,  176,103,  169,91);
select_region(font_14_region_id + 126); //~ 9
define_region(182,91,  190,103,  182,91);
select_region(font_14_region_id + 127); // 7
define_region(195,91,  201,103,  195,91);

Fontfont_14.character_height = 13;
Fontfont_14.use_variable_width = true;
Fontfont_14.character_separation = 0;
Fontfont_14.line_separation = 6;

Fontfont_14.texture_id = font_14_texture_id;
Fontfont_14.character_zero_region_id = font_14_region_id;
textfont_read_region_widths(&Fontfont_14);

}
#endif
