#ifndef bigfont_14_H
#define bigfont_14_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define bigfont_14_texture_id 2
#define bigfont_14_region_id 0

textfont Fontbigfont_14;

void setupFontbigfont_14()
{
select_texture(bigfont_14_texture_id);
select_region(bigfont_14_region_id + 0); // 0
define_region(0,0,  -1,19,  0,0);
select_region(bigfont_14_region_id + 1); // 16
define_region(21,0,  36,19,  21,0);
select_region(bigfont_14_region_id + 2); // 11
define_region(42,0,  52,19,  42,0);
select_region(bigfont_14_region_id + 3); // 19
define_region(63,0,  81,19,  63,0);
select_region(bigfont_14_region_id + 4); // 11
define_region(84,0,  94,19,  84,0);
select_region(bigfont_14_region_id + 5); // 9
define_region(105,0,  113,19,  105,0);
select_region(bigfont_14_region_id + 6); // 11
define_region(126,0,  136,19,  126,0);
select_region(bigfont_14_region_id + 7); // 11
define_region(147,0,  157,19,  147,0);
select_region(bigfont_14_region_id + 8); // 11
define_region(168,0,  178,19,  168,0);
select_region(bigfont_14_region_id + 9); // 11
define_region(189,0,  199,19,  189,0);
select_region(bigfont_14_region_id + 10); // 11
define_region(210,0,  220,19,  210,0);
select_region(bigfont_14_region_id + 11); // 11
define_region(231,0,  241,19,  231,0);
select_region(bigfont_14_region_id + 12); // 11
define_region(252,0,  262,19,  252,0);
select_region(bigfont_14_region_id + 13); // 11
define_region(273,0,  283,19,  273,0);
select_region(bigfont_14_region_id + 14); // 11
define_region(294,0,  304,19,  294,0);
select_region(bigfont_14_region_id + 15); // 11
define_region(315,0,  325,19,  315,0);
select_region(bigfont_14_region_id + 16); // 11
define_region(0,20,  10,39,  0,20);
select_region(bigfont_14_region_id + 17); // 11
define_region(21,20,  31,39,  21,20);
select_region(bigfont_14_region_id + 18); // 11
define_region(42,20,  52,39,  42,20);
select_region(bigfont_14_region_id + 19); // 11
define_region(63,20,  73,39,  63,20);
select_region(bigfont_14_region_id + 20); // 11
define_region(84,20,  94,39,  84,20);
select_region(bigfont_14_region_id + 21); // 11
define_region(105,20,  115,39,  105,20);
select_region(bigfont_14_region_id + 22); // 11
define_region(126,20,  136,39,  126,20);
select_region(bigfont_14_region_id + 23); // 11
define_region(147,20,  157,39,  147,20);
select_region(bigfont_14_region_id + 24); // 11
define_region(168,20,  178,39,  168,20);
select_region(bigfont_14_region_id + 25); // 11
define_region(189,20,  199,39,  189,20);
select_region(bigfont_14_region_id + 26); // 11
define_region(210,20,  220,39,  210,20);
select_region(bigfont_14_region_id + 27); // 11
define_region(231,20,  241,39,  231,20);
select_region(bigfont_14_region_id + 28); // 11
define_region(252,20,  262,39,  252,20);
select_region(bigfont_14_region_id + 29); // 11
define_region(273,20,  283,39,  273,20);
select_region(bigfont_14_region_id + 30); // 11
define_region(294,20,  304,39,  294,20);
select_region(bigfont_14_region_id + 31); // 11
define_region(315,20,  325,39,  315,20);
select_region(bigfont_14_region_id + 32); //  6
define_region(0,40,  5,59,  0,40);
select_region(bigfont_14_region_id + 33); //! 7
define_region(21,40,  27,59,  21,40);
select_region(bigfont_14_region_id + 34); //" 10
define_region(42,40,  51,59,  42,40);
select_region(bigfont_14_region_id + 35); //# 14
define_region(63,40,  76,59,  63,40);
select_region(bigfont_14_region_id + 36); //$ 12
define_region(84,40,  95,59,  84,40);
select_region(bigfont_14_region_id + 37); //% 21
define_region(105,40,  125,59,  105,40);
select_region(bigfont_14_region_id + 38); //& 14
define_region(126,40,  139,59,  126,40);
select_region(bigfont_14_region_id + 39); //' 6
define_region(147,40,  152,59,  147,40);
select_region(bigfont_14_region_id + 40); //( 9
define_region(168,40,  176,59,  168,40);
select_region(bigfont_14_region_id + 41); //) 9
define_region(189,40,  197,59,  189,40);
select_region(bigfont_14_region_id + 42); //* 12
define_region(210,40,  221,59,  210,40);
select_region(bigfont_14_region_id + 43); //+ 14
define_region(231,40,  244,59,  231,40);
select_region(bigfont_14_region_id + 44); //, 6
define_region(252,40,  257,59,  252,40);
select_region(bigfont_14_region_id + 45); //- 8
define_region(273,40,  280,59,  273,40);
select_region(bigfont_14_region_id + 46); //. 6
define_region(294,40,  299,59,  294,40);
select_region(bigfont_14_region_id + 47); /// 12
define_region(315,40,  326,59,  315,40);
select_region(bigfont_14_region_id + 48); //0 12
define_region(0,60,  11,79,  0,60);
select_region(bigfont_14_region_id + 49); //1 12
define_region(21,60,  32,79,  21,60);
select_region(bigfont_14_region_id + 50); //2 12
define_region(42,60,  53,79,  42,60);
select_region(bigfont_14_region_id + 51); //3 12
define_region(63,60,  74,79,  63,60);
select_region(bigfont_14_region_id + 52); //4 12
define_region(84,60,  95,79,  84,60);
select_region(bigfont_14_region_id + 53); //5 12
define_region(105,60,  116,79,  105,60);
select_region(bigfont_14_region_id + 54); //6 12
define_region(126,60,  137,79,  126,60);
select_region(bigfont_14_region_id + 55); //7 12
define_region(147,60,  158,79,  147,60);
select_region(bigfont_14_region_id + 56); //8 12
define_region(168,60,  179,79,  168,60);
select_region(bigfont_14_region_id + 57); //9 12
define_region(189,60,  200,79,  189,60);
select_region(bigfont_14_region_id + 58); //: 7
define_region(210,60,  216,79,  210,60);
select_region(bigfont_14_region_id + 59); //; 7
define_region(231,60,  237,79,  231,60);
select_region(bigfont_14_region_id + 60); //< 14
define_region(252,60,  265,79,  252,60);
select_region(bigfont_14_region_id + 61); //= 14
define_region(273,60,  286,79,  273,60);
select_region(bigfont_14_region_id + 62); //> 14
define_region(294,60,  307,79,  294,60);
select_region(bigfont_14_region_id + 63); //? 10
define_region(315,60,  324,79,  315,60);
select_region(bigfont_14_region_id + 64); //@ 16
define_region(0,80,  15,99,  0,80);
select_region(bigfont_14_region_id + 65); //A 13
define_region(21,80,  33,99,  21,80);
select_region(bigfont_14_region_id + 66); //B 13
define_region(42,80,  54,99,  42,80);
select_region(bigfont_14_region_id + 67); //C 12
define_region(63,80,  74,99,  63,80);
select_region(bigfont_14_region_id + 68); //D 14
define_region(84,80,  97,99,  84,80);
select_region(bigfont_14_region_id + 69); //E 11
define_region(105,80,  115,99,  105,80);
select_region(bigfont_14_region_id + 70); //F 11
define_region(126,80,  136,99,  126,80);
select_region(bigfont_14_region_id + 71); //G 13
define_region(147,80,  159,99,  147,80);
select_region(bigfont_14_region_id + 72); //H 14
define_region(168,80,  181,99,  168,80);
select_region(bigfont_14_region_id + 73); //I 9
define_region(189,80,  197,99,  189,80);
select_region(bigfont_14_region_id + 74); //J 9
define_region(210,80,  218,99,  210,80);
select_region(bigfont_14_region_id + 75); //K 13
define_region(231,80,  243,99,  231,80);
select_region(bigfont_14_region_id + 76); //L 11
define_region(252,80,  262,99,  252,80);
select_region(bigfont_14_region_id + 77); //M 16
define_region(273,80,  288,99,  273,80);
select_region(bigfont_14_region_id + 78); //N 14
define_region(294,80,  307,99,  294,80);
select_region(bigfont_14_region_id + 79); //O 14
define_region(315,80,  328,99,  315,80);
select_region(bigfont_14_region_id + 80); //P 12
define_region(0,100,  11,119,  0,100);
select_region(bigfont_14_region_id + 81); //Q 14
define_region(21,100,  34,119,  21,100);
select_region(bigfont_14_region_id + 82); //R 13
define_region(42,100,  54,119,  42,100);
select_region(bigfont_14_region_id + 83); //S 12
define_region(63,100,  74,119,  63,100);
select_region(bigfont_14_region_id + 84); //T 11
define_region(84,100,  94,119,  84,100);
select_region(bigfont_14_region_id + 85); //U 13
define_region(105,100,  117,119,  105,100);
select_region(bigfont_14_region_id + 86); //V 13
define_region(126,100,  138,119,  126,100);
select_region(bigfont_14_region_id + 87); //W 19
define_region(147,100,  165,119,  147,100);
select_region(bigfont_14_region_id + 88); //X 13
define_region(168,100,  180,119,  168,100);
select_region(bigfont_14_region_id + 89); //Y 12
define_region(189,100,  200,119,  189,100);
select_region(bigfont_14_region_id + 90); //Z 12
define_region(210,100,  221,119,  210,100);
select_region(bigfont_14_region_id + 91); //[ 9
define_region(231,100,  239,119,  231,100);
select_region(bigfont_14_region_id + 92); // 12
define_region(252,100,  263,119,  252,100);
select_region(bigfont_14_region_id + 93); //] 9
define_region(273,100,  281,119,  273,100);
select_region(bigfont_14_region_id + 94); //^ 14
define_region(294,100,  307,119,  294,100);
select_region(bigfont_14_region_id + 95); //_ 12
define_region(315,100,  326,119,  315,100);
select_region(bigfont_14_region_id + 96); //` 12
define_region(0,120,  11,139,  0,120);
select_region(bigfont_14_region_id + 97); //a 11
define_region(21,120,  31,139,  21,120);
select_region(bigfont_14_region_id + 98); //b 12
define_region(42,120,  53,139,  42,120);
select_region(bigfont_14_region_id + 99); //c 10
define_region(63,120,  72,139,  63,120);
select_region(bigfont_14_region_id + 100); //d 12
define_region(84,120,  95,139,  84,120);
select_region(bigfont_14_region_id + 101); //e 11
define_region(105,120,  115,139,  105,120);
select_region(bigfont_14_region_id + 102); //f 7
define_region(126,120,  132,139,  126,120);
select_region(bigfont_14_region_id + 103); //g 12
define_region(147,120,  158,139,  147,120);
select_region(bigfont_14_region_id + 104); //h 12
define_region(168,120,  179,139,  168,120);
select_region(bigfont_14_region_id + 105); //i 6
define_region(189,120,  194,139,  189,120);
select_region(bigfont_14_region_id + 106); //j 7
define_region(210,120,  216,139,  210,120);
select_region(bigfont_14_region_id + 107); //k 11
define_region(231,120,  241,139,  231,120);
select_region(bigfont_14_region_id + 108); //l 6
define_region(252,120,  257,139,  252,120);
select_region(bigfont_14_region_id + 109); //m 17
define_region(273,120,  289,139,  273,120);
select_region(bigfont_14_region_id + 110); //n 12
define_region(294,120,  305,139,  294,120);
select_region(bigfont_14_region_id + 111); //o 11
define_region(315,120,  325,139,  315,120);
select_region(bigfont_14_region_id + 112); //p 12
define_region(0,140,  11,159,  0,140);
select_region(bigfont_14_region_id + 113); //q 12
define_region(21,140,  32,159,  21,140);
select_region(bigfont_14_region_id + 114); //r 8
define_region(42,140,  49,159,  42,140);
select_region(bigfont_14_region_id + 115); //s 10
define_region(63,140,  72,159,  63,140);
select_region(bigfont_14_region_id + 116); //t 8
define_region(84,140,  91,159,  84,140);
select_region(bigfont_14_region_id + 117); //u 12
define_region(105,140,  116,159,  105,140);
select_region(bigfont_14_region_id + 118); //v 11
define_region(126,140,  136,159,  126,140);
select_region(bigfont_14_region_id + 119); //w 16
define_region(147,140,  162,159,  147,140);
select_region(bigfont_14_region_id + 120); //x 11
define_region(168,140,  178,159,  168,140);
select_region(bigfont_14_region_id + 121); //y 11
define_region(189,140,  199,159,  189,140);
select_region(bigfont_14_region_id + 122); //z 10
define_region(210,140,  219,159,  210,140);
select_region(bigfont_14_region_id + 123); //{ 12
define_region(231,140,  242,159,  231,140);
select_region(bigfont_14_region_id + 124); //| 9
define_region(252,140,  260,159,  252,140);
select_region(bigfont_14_region_id + 125); //} 12
define_region(273,140,  284,159,  273,140);
select_region(bigfont_14_region_id + 126); //~ 14
define_region(294,140,  307,159,  294,140);
select_region(bigfont_14_region_id + 127); // 11
define_region(315,140,  325,159,  315,140);

Fontbigfont_14.character_height = 20;
Fontbigfont_14.use_variable_width = true;
Fontbigfont_14.character_separation = 0;
Fontbigfont_14.line_separation = 15;

Fontbigfont_14.texture_id = bigfont_14_texture_id;
Fontbigfont_14.character_zero_region_id = bigfont_14_region_id;
textfont_read_region_widths(&Fontbigfont_14);

}
#endif
