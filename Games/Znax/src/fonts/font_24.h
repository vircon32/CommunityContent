#ifndef font_24_H
#define font_24_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font_24_texture_id 4
#define font_24_region_id 0

textfont Fontfont_24;

void setupFontfont_24()
{
select_texture(font_24_texture_id);
select_region(font_24_region_id + 0); // 0
define_region(0,0,  -1,29,  0,0);
select_region(font_24_region_id + 1); // 20
define_region(26,0,  45,29,  26,0);
select_region(font_24_region_id + 2); // 24
define_region(52,0,  75,29,  52,0);
select_region(font_24_region_id + 3); // 24
define_region(78,0,  101,29,  78,0);
select_region(font_24_region_id + 4); // 24
define_region(104,0,  127,29,  104,0);
select_region(font_24_region_id + 5); // 10
define_region(130,0,  139,29,  130,0);
select_region(font_24_region_id + 6); // 24
define_region(156,0,  179,29,  156,0);
select_region(font_24_region_id + 7); // 24
define_region(182,0,  205,29,  182,0);
select_region(font_24_region_id + 8); // 24
define_region(208,0,  231,29,  208,0);
select_region(font_24_region_id + 9); // 24
define_region(234,0,  257,29,  234,0);
select_region(font_24_region_id + 10); // 24
define_region(260,0,  283,29,  260,0);
select_region(font_24_region_id + 11); // 24
define_region(286,0,  309,29,  286,0);
select_region(font_24_region_id + 12); // 24
define_region(312,0,  335,29,  312,0);
select_region(font_24_region_id + 13); // 24
define_region(338,0,  361,29,  338,0);
select_region(font_24_region_id + 14); // 24
define_region(364,0,  387,29,  364,0);
select_region(font_24_region_id + 15); // 24
define_region(390,0,  413,29,  390,0);
select_region(font_24_region_id + 16); // 24
define_region(0,30,  23,59,  0,30);
select_region(font_24_region_id + 17); // 24
define_region(26,30,  49,59,  26,30);
select_region(font_24_region_id + 18); // 24
define_region(52,30,  75,59,  52,30);
select_region(font_24_region_id + 19); // 24
define_region(78,30,  101,59,  78,30);
select_region(font_24_region_id + 20); // 24
define_region(104,30,  127,59,  104,30);
select_region(font_24_region_id + 21); // 24
define_region(130,30,  153,59,  130,30);
select_region(font_24_region_id + 22); // 24
define_region(156,30,  179,59,  156,30);
select_region(font_24_region_id + 23); // 24
define_region(182,30,  205,59,  182,30);
select_region(font_24_region_id + 24); // 24
define_region(208,30,  231,59,  208,30);
select_region(font_24_region_id + 25); // 24
define_region(234,30,  257,59,  234,30);
select_region(font_24_region_id + 26); // 24
define_region(260,30,  283,59,  260,30);
select_region(font_24_region_id + 27); // 24
define_region(286,30,  309,59,  286,30);
select_region(font_24_region_id + 28); // 24
define_region(312,30,  335,59,  312,30);
select_region(font_24_region_id + 29); // 24
define_region(338,30,  361,59,  338,30);
select_region(font_24_region_id + 30); // 24
define_region(364,30,  387,59,  364,30);
select_region(font_24_region_id + 31); // 24
define_region(390,30,  413,59,  390,30);
select_region(font_24_region_id + 32); //  8
define_region(0,60,  7,89,  0,60);
select_region(font_24_region_id + 33); //! 9
define_region(26,60,  34,89,  26,60);
select_region(font_24_region_id + 34); //" 11
define_region(52,60,  62,89,  52,60);
select_region(font_24_region_id + 35); //# 20
define_region(78,60,  97,89,  78,60);
select_region(font_24_region_id + 36); //$ 15
define_region(104,60,  118,89,  104,60);
select_region(font_24_region_id + 37); //% 26
define_region(130,60,  155,89,  130,60);
select_region(font_24_region_id + 38); //& 19
define_region(156,60,  174,89,  156,60);
select_region(font_24_region_id + 39); //' 6
define_region(182,60,  187,89,  182,60);
select_region(font_24_region_id + 40); //( 11
define_region(208,60,  218,89,  208,60);
select_region(font_24_region_id + 41); //) 11
define_region(234,60,  244,89,  234,60);
select_region(font_24_region_id + 42); //* 15
define_region(260,60,  274,89,  260,60);
select_region(font_24_region_id + 43); //+ 20
define_region(286,60,  305,89,  286,60);
select_region(font_24_region_id + 44); //, 9
define_region(312,60,  320,89,  312,60);
select_region(font_24_region_id + 45); //- 11
define_region(338,60,  348,89,  338,60);
select_region(font_24_region_id + 46); //. 9
define_region(364,60,  372,89,  364,60);
select_region(font_24_region_id + 47); /// 12
define_region(390,60,  401,89,  390,60);
select_region(font_24_region_id + 48); //0 15
define_region(0,90,  14,119,  0,90);
select_region(font_24_region_id + 49); //1 15
define_region(26,90,  40,119,  26,90);
select_region(font_24_region_id + 50); //2 15
define_region(52,90,  66,119,  52,90);
select_region(font_24_region_id + 51); //3 15
define_region(78,90,  92,119,  78,90);
select_region(font_24_region_id + 52); //4 15
define_region(104,90,  118,119,  104,90);
select_region(font_24_region_id + 53); //5 15
define_region(130,90,  144,119,  130,90);
select_region(font_24_region_id + 54); //6 15
define_region(156,90,  170,119,  156,90);
select_region(font_24_region_id + 55); //7 15
define_region(182,90,  196,119,  182,90);
select_region(font_24_region_id + 56); //8 15
define_region(208,90,  222,119,  208,90);
select_region(font_24_region_id + 57); //9 15
define_region(234,90,  248,119,  234,90);
select_region(font_24_region_id + 58); //: 11
define_region(260,90,  270,119,  260,90);
select_region(font_24_region_id + 59); //; 11
define_region(286,90,  296,119,  286,90);
select_region(font_24_region_id + 60); //< 20
define_region(312,90,  331,119,  312,90);
select_region(font_24_region_id + 61); //= 20
define_region(338,90,  357,119,  338,90);
select_region(font_24_region_id + 62); //> 20
define_region(364,90,  383,119,  364,90);
select_region(font_24_region_id + 63); //? 13
define_region(390,90,  402,119,  390,90);
select_region(font_24_region_id + 64); //@ 24
define_region(0,120,  23,149,  0,120);
select_region(font_24_region_id + 65); //A 17
define_region(26,120,  42,149,  26,120);
select_region(font_24_region_id + 66); //B 16
define_region(52,120,  67,149,  52,120);
select_region(font_24_region_id + 67); //C 17
define_region(78,120,  94,149,  78,120);
select_region(font_24_region_id + 68); //D 19
define_region(104,120,  122,149,  104,120);
select_region(font_24_region_id + 69); //E 15
define_region(130,120,  144,149,  130,120);
select_region(font_24_region_id + 70); //F 14
define_region(156,120,  169,149,  156,120);
select_region(font_24_region_id + 71); //G 19
define_region(182,120,  200,149,  182,120);
select_region(font_24_region_id + 72); //H 18
define_region(208,120,  225,149,  208,120);
select_region(font_24_region_id + 73); //I 10
define_region(234,120,  243,149,  234,120);
select_region(font_24_region_id + 74); //J 11
define_region(260,120,  270,149,  260,120);
select_region(font_24_region_id + 75); //K 17
define_region(286,120,  302,149,  286,120);
select_region(font_24_region_id + 76); //L 14
define_region(312,120,  325,149,  312,120);
select_region(font_24_region_id + 77); //M 20
define_region(338,120,  357,149,  338,120);
select_region(font_24_region_id + 78); //N 18
define_region(364,120,  381,149,  364,120);
select_region(font_24_region_id + 79); //O 19
define_region(390,120,  408,149,  390,120);
select_region(font_24_region_id + 80); //P 14
define_region(0,150,  13,179,  0,150);
select_region(font_24_region_id + 81); //Q 19
define_region(26,150,  44,179,  26,150);
select_region(font_24_region_id + 82); //R 17
define_region(52,150,  68,179,  52,150);
select_region(font_24_region_id + 83); //S 16
define_region(78,150,  93,179,  78,150);
select_region(font_24_region_id + 84); //T 15
define_region(104,150,  118,179,  104,150);
select_region(font_24_region_id + 85); //U 18
define_region(130,150,  147,179,  130,150);
select_region(font_24_region_id + 86); //V 17
define_region(156,150,  172,179,  156,150);
select_region(font_24_region_id + 87); //W 24
define_region(182,150,  205,179,  182,150);
select_region(font_24_region_id + 88); //X 16
define_region(208,150,  223,179,  208,150);
select_region(font_24_region_id + 89); //Y 15
define_region(234,150,  248,179,  234,150);
select_region(font_24_region_id + 90); //Z 16
define_region(260,150,  275,179,  260,150);
select_region(font_24_region_id + 91); //[ 11
define_region(286,150,  296,179,  286,150);
select_region(font_24_region_id + 92); // 12
define_region(312,150,  323,179,  312,150);
select_region(font_24_region_id + 93); //] 11
define_region(338,150,  348,179,  338,150);
select_region(font_24_region_id + 94); //^ 20
define_region(364,150,  383,179,  364,150);
select_region(font_24_region_id + 95); //_ 17
define_region(390,150,  406,179,  390,150);
select_region(font_24_region_id + 96); //` 15
define_region(0,180,  14,209,  0,180);
select_region(font_24_region_id + 97); //a 14
define_region(26,180,  39,209,  26,180);
select_region(font_24_region_id + 98); //b 15
define_region(52,180,  66,209,  52,180);
select_region(font_24_region_id + 99); //c 13
define_region(78,180,  90,209,  78,180);
select_region(font_24_region_id + 100); //d 15
define_region(104,180,  118,209,  104,180);
select_region(font_24_region_id + 101); //e 14
define_region(130,180,  143,209,  130,180);
select_region(font_24_region_id + 102); //f 10
define_region(156,180,  165,209,  156,180);
select_region(font_24_region_id + 103); //g 15
define_region(182,180,  196,209,  182,180);
select_region(font_24_region_id + 104); //h 15
define_region(208,180,  222,209,  208,180);
select_region(font_24_region_id + 105); //i 7
define_region(234,180,  240,209,  234,180);
select_region(font_24_region_id + 106); //j 9
define_region(260,180,  268,209,  260,180);
select_region(font_24_region_id + 107); //k 15
define_region(286,180,  300,209,  286,180);
select_region(font_24_region_id + 108); //l 7
define_region(312,180,  318,209,  312,180);
select_region(font_24_region_id + 109); //m 23
define_region(338,180,  360,209,  338,180);
select_region(font_24_region_id + 110); //n 15
define_region(364,180,  378,209,  364,180);
select_region(font_24_region_id + 111); //o 15
define_region(390,180,  404,209,  390,180);
select_region(font_24_region_id + 112); //p 15
define_region(0,210,  14,239,  0,210);
select_region(font_24_region_id + 113); //q 15
define_region(26,210,  40,239,  26,210);
select_region(font_24_region_id + 114); //r 11
define_region(52,210,  62,239,  52,210);
select_region(font_24_region_id + 115); //s 13
define_region(78,210,  90,239,  78,210);
select_region(font_24_region_id + 116); //t 9
define_region(104,210,  112,239,  104,210);
select_region(font_24_region_id + 117); //u 15
define_region(130,210,  144,239,  130,210);
select_region(font_24_region_id + 118); //v 14
define_region(156,210,  169,239,  156,210);
select_region(font_24_region_id + 119); //w 20
define_region(182,210,  201,239,  182,210);
select_region(font_24_region_id + 120); //x 14
define_region(208,210,  221,239,  208,210);
select_region(font_24_region_id + 121); //y 14
define_region(234,210,  247,239,  234,210);
select_region(font_24_region_id + 122); //z 13
define_region(260,210,  272,239,  260,210);
select_region(font_24_region_id + 123); //{ 15
define_region(286,210,  300,239,  286,210);
select_region(font_24_region_id + 124); //| 11
define_region(312,210,  322,239,  312,210);
select_region(font_24_region_id + 125); //} 15
define_region(338,210,  352,239,  338,210);
select_region(font_24_region_id + 126); //~ 20
define_region(364,210,  383,239,  364,210);
select_region(font_24_region_id + 127); // 24
define_region(390,210,  413,239,  390,210);

Fontfont_24.character_height = 30;
Fontfont_24.use_variable_width = true;
Fontfont_24.character_separation = 0;
Fontfont_24.line_separation = 0;

Fontfont_24.texture_id = font_24_texture_id;
Fontfont_24.character_zero_region_id = font_24_region_id;
textfont_read_region_widths(&Fontfont_24);

}
#endif
