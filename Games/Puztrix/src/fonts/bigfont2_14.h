#ifndef bigfont2_14_H
#define bigfont2_14_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define bigfont2_14_texture_id 3
#define bigfont2_14_region_id 0

textfont Fontbigfont2_14;

void setupFontbigfont2_14()
{
select_texture(bigfont2_14_texture_id);
select_region(bigfont2_14_region_id + 0); // 0
define_region(0,0,  -1,20,  0,0);
select_region(bigfont2_14_region_id + 1); // 17
define_region(22,0,  38,20,  22,0);
select_region(bigfont2_14_region_id + 2); // 12
define_region(44,0,  55,20,  44,0);
select_region(bigfont2_14_region_id + 3); // 20
define_region(66,0,  85,20,  66,0);
select_region(bigfont2_14_region_id + 4); // 12
define_region(88,0,  99,20,  88,0);
select_region(bigfont2_14_region_id + 5); // 10
define_region(110,0,  119,20,  110,0);
select_region(bigfont2_14_region_id + 6); // 12
define_region(132,0,  143,20,  132,0);
select_region(bigfont2_14_region_id + 7); // 12
define_region(154,0,  165,20,  154,0);
select_region(bigfont2_14_region_id + 8); // 12
define_region(176,0,  187,20,  176,0);
select_region(bigfont2_14_region_id + 9); // 12
define_region(198,0,  209,20,  198,0);
select_region(bigfont2_14_region_id + 10); // 12
define_region(220,0,  231,20,  220,0);
select_region(bigfont2_14_region_id + 11); // 12
define_region(242,0,  253,20,  242,0);
select_region(bigfont2_14_region_id + 12); // 12
define_region(264,0,  275,20,  264,0);
select_region(bigfont2_14_region_id + 13); // 12
define_region(286,0,  297,20,  286,0);
select_region(bigfont2_14_region_id + 14); // 12
define_region(308,0,  319,20,  308,0);
select_region(bigfont2_14_region_id + 15); // 12
define_region(330,0,  341,20,  330,0);
select_region(bigfont2_14_region_id + 16); // 12
define_region(0,21,  11,41,  0,21);
select_region(bigfont2_14_region_id + 17); // 12
define_region(22,21,  33,41,  22,21);
select_region(bigfont2_14_region_id + 18); // 12
define_region(44,21,  55,41,  44,21);
select_region(bigfont2_14_region_id + 19); // 12
define_region(66,21,  77,41,  66,21);
select_region(bigfont2_14_region_id + 20); // 12
define_region(88,21,  99,41,  88,21);
select_region(bigfont2_14_region_id + 21); // 12
define_region(110,21,  121,41,  110,21);
select_region(bigfont2_14_region_id + 22); // 12
define_region(132,21,  143,41,  132,21);
select_region(bigfont2_14_region_id + 23); // 12
define_region(154,21,  165,41,  154,21);
select_region(bigfont2_14_region_id + 24); // 12
define_region(176,21,  187,41,  176,21);
select_region(bigfont2_14_region_id + 25); // 12
define_region(198,21,  209,41,  198,21);
select_region(bigfont2_14_region_id + 26); // 12
define_region(220,21,  231,41,  220,21);
select_region(bigfont2_14_region_id + 27); // 12
define_region(242,21,  253,41,  242,21);
select_region(bigfont2_14_region_id + 28); // 12
define_region(264,21,  275,41,  264,21);
select_region(bigfont2_14_region_id + 29); // 12
define_region(286,21,  297,41,  286,21);
select_region(bigfont2_14_region_id + 30); // 12
define_region(308,21,  319,41,  308,21);
select_region(bigfont2_14_region_id + 31); // 12
define_region(330,21,  341,41,  330,21);
select_region(bigfont2_14_region_id + 32); //  6
define_region(0,42,  5,62,  0,42);
select_region(bigfont2_14_region_id + 33); //! 7
define_region(22,42,  28,62,  22,42);
select_region(bigfont2_14_region_id + 34); //" 10
define_region(44,42,  53,62,  44,42);
select_region(bigfont2_14_region_id + 35); //# 15
define_region(66,42,  80,62,  66,42);
select_region(bigfont2_14_region_id + 36); //$ 13
define_region(88,42,  100,62,  88,42);
select_region(bigfont2_14_region_id + 37); //% 22
define_region(110,42,  131,62,  110,42);
select_region(bigfont2_14_region_id + 38); //& 15
define_region(132,42,  146,62,  132,42);
select_region(bigfont2_14_region_id + 39); //' 6
define_region(154,42,  159,62,  154,42);
select_region(bigfont2_14_region_id + 40); //( 10
define_region(176,42,  185,62,  176,42);
select_region(bigfont2_14_region_id + 41); //) 10
define_region(198,42,  207,62,  198,42);
select_region(bigfont2_14_region_id + 42); //* 13
define_region(220,42,  232,62,  220,42);
select_region(bigfont2_14_region_id + 43); //+ 15
define_region(242,42,  256,62,  242,42);
select_region(bigfont2_14_region_id + 44); //, 7
define_region(264,42,  270,62,  264,42);
select_region(bigfont2_14_region_id + 45); //- 9
define_region(286,42,  294,62,  286,42);
select_region(bigfont2_14_region_id + 46); //. 7
define_region(308,42,  314,62,  308,42);
select_region(bigfont2_14_region_id + 47); /// 12
define_region(330,42,  341,62,  330,42);
select_region(bigfont2_14_region_id + 48); //0 13
define_region(0,63,  12,83,  0,63);
select_region(bigfont2_14_region_id + 49); //1 13
define_region(22,63,  34,83,  22,63);
select_region(bigfont2_14_region_id + 50); //2 13
define_region(44,63,  56,83,  44,63);
select_region(bigfont2_14_region_id + 51); //3 13
define_region(66,63,  78,83,  66,63);
select_region(bigfont2_14_region_id + 52); //4 13
define_region(88,63,  100,83,  88,63);
select_region(bigfont2_14_region_id + 53); //5 13
define_region(110,63,  122,83,  110,63);
select_region(bigfont2_14_region_id + 54); //6 13
define_region(132,63,  144,83,  132,63);
select_region(bigfont2_14_region_id + 55); //7 13
define_region(154,63,  166,83,  154,63);
select_region(bigfont2_14_region_id + 56); //8 13
define_region(176,63,  188,83,  176,63);
select_region(bigfont2_14_region_id + 57); //9 13
define_region(198,63,  210,83,  198,63);
select_region(bigfont2_14_region_id + 58); //: 7
define_region(220,63,  226,83,  220,63);
select_region(bigfont2_14_region_id + 59); //; 7
define_region(242,63,  248,83,  242,63);
select_region(bigfont2_14_region_id + 60); //< 15
define_region(264,63,  278,83,  264,63);
select_region(bigfont2_14_region_id + 61); //= 15
define_region(286,63,  300,83,  286,63);
select_region(bigfont2_14_region_id + 62); //> 15
define_region(308,63,  322,83,  308,63);
select_region(bigfont2_14_region_id + 63); //? 11
define_region(330,63,  340,83,  330,63);
select_region(bigfont2_14_region_id + 64); //@ 17
define_region(0,84,  16,104,  0,84);
select_region(bigfont2_14_region_id + 65); //A 14
define_region(22,84,  35,104,  22,84);
select_region(bigfont2_14_region_id + 66); //B 13
define_region(44,84,  56,104,  44,84);
select_region(bigfont2_14_region_id + 67); //C 13
define_region(66,84,  78,104,  66,84);
select_region(bigfont2_14_region_id + 68); //D 15
define_region(88,84,  102,104,  88,84);
select_region(bigfont2_14_region_id + 69); //E 12
define_region(110,84,  121,104,  110,84);
select_region(bigfont2_14_region_id + 70); //F 12
define_region(132,84,  143,104,  132,84);
select_region(bigfont2_14_region_id + 71); //G 14
define_region(154,84,  167,104,  154,84);
select_region(bigfont2_14_region_id + 72); //H 15
define_region(176,84,  190,104,  176,84);
select_region(bigfont2_14_region_id + 73); //I 10
define_region(198,84,  207,104,  198,84);
select_region(bigfont2_14_region_id + 74); //J 10
define_region(220,84,  229,104,  220,84);
select_region(bigfont2_14_region_id + 75); //K 14
define_region(242,84,  255,104,  242,84);
select_region(bigfont2_14_region_id + 76); //L 11
define_region(264,84,  274,104,  264,84);
select_region(bigfont2_14_region_id + 77); //M 17
define_region(286,84,  302,104,  286,84);
select_region(bigfont2_14_region_id + 78); //N 15
define_region(308,84,  322,104,  308,84);
select_region(bigfont2_14_region_id + 79); //O 15
define_region(330,84,  344,104,  330,84);
select_region(bigfont2_14_region_id + 80); //P 13
define_region(0,105,  12,125,  0,105);
select_region(bigfont2_14_region_id + 81); //Q 15
define_region(22,105,  36,125,  22,105);
select_region(bigfont2_14_region_id + 82); //R 14
define_region(44,105,  57,125,  44,105);
select_region(bigfont2_14_region_id + 83); //S 13
define_region(66,105,  78,125,  66,105);
select_region(bigfont2_14_region_id + 84); //T 12
define_region(88,105,  99,125,  88,105);
select_region(bigfont2_14_region_id + 85); //U 14
define_region(110,105,  123,125,  110,105);
select_region(bigfont2_14_region_id + 86); //V 13
define_region(132,105,  144,125,  132,105);
select_region(bigfont2_14_region_id + 87); //W 20
define_region(154,105,  173,125,  154,105);
select_region(bigfont2_14_region_id + 88); //X 13
define_region(176,105,  188,125,  176,105);
select_region(bigfont2_14_region_id + 89); //Y 13
define_region(198,105,  210,125,  198,105);
select_region(bigfont2_14_region_id + 90); //Z 12
define_region(220,105,  231,125,  220,105);
select_region(bigfont2_14_region_id + 91); //[ 10
define_region(242,105,  251,125,  242,105);
select_region(bigfont2_14_region_id + 92); // 12
define_region(264,105,  275,125,  264,105);
select_region(bigfont2_14_region_id + 93); //] 10
define_region(286,105,  295,125,  286,105);
select_region(bigfont2_14_region_id + 94); //^ 15
define_region(308,105,  322,125,  308,105);
select_region(bigfont2_14_region_id + 95); //_ 13
define_region(330,105,  342,125,  330,105);
select_region(bigfont2_14_region_id + 96); //` 13
define_region(0,126,  12,146,  0,126);
select_region(bigfont2_14_region_id + 97); //a 12
define_region(22,126,  33,146,  22,126);
select_region(bigfont2_14_region_id + 98); //b 12
define_region(44,126,  55,146,  44,126);
select_region(bigfont2_14_region_id + 99); //c 11
define_region(66,126,  76,146,  66,126);
select_region(bigfont2_14_region_id + 100); //d 12
define_region(88,126,  99,146,  88,126);
select_region(bigfont2_14_region_id + 101); //e 12
define_region(110,126,  121,146,  110,126);
select_region(bigfont2_14_region_id + 102); //f 8
define_region(132,126,  139,146,  132,126);
select_region(bigfont2_14_region_id + 103); //g 12
define_region(154,126,  165,146,  154,126);
select_region(bigfont2_14_region_id + 104); //h 13
define_region(176,126,  188,146,  176,126);
select_region(bigfont2_14_region_id + 105); //i 6
define_region(198,126,  203,146,  198,126);
select_region(bigfont2_14_region_id + 106); //j 7
define_region(220,126,  226,146,  220,126);
select_region(bigfont2_14_region_id + 107); //k 12
define_region(242,126,  253,146,  242,126);
select_region(bigfont2_14_region_id + 108); //l 6
define_region(264,126,  269,146,  264,126);
select_region(bigfont2_14_region_id + 109); //m 18
define_region(286,126,  303,146,  286,126);
select_region(bigfont2_14_region_id + 110); //n 13
define_region(308,126,  320,146,  308,126);
select_region(bigfont2_14_region_id + 111); //o 12
define_region(330,126,  341,146,  330,126);
select_region(bigfont2_14_region_id + 112); //p 12
define_region(0,147,  11,167,  0,147);
select_region(bigfont2_14_region_id + 113); //q 12
define_region(22,147,  33,167,  22,147);
select_region(bigfont2_14_region_id + 114); //r 9
define_region(44,147,  52,167,  44,147);
select_region(bigfont2_14_region_id + 115); //s 11
define_region(66,147,  76,167,  66,147);
select_region(bigfont2_14_region_id + 116); //t 8
define_region(88,147,  95,167,  88,147);
select_region(bigfont2_14_region_id + 117); //u 13
define_region(110,147,  122,167,  110,147);
select_region(bigfont2_14_region_id + 118); //v 12
define_region(132,147,  143,167,  132,147);
select_region(bigfont2_14_region_id + 119); //w 17
define_region(154,147,  170,167,  154,147);
select_region(bigfont2_14_region_id + 120); //x 12
define_region(176,147,  187,167,  176,147);
select_region(bigfont2_14_region_id + 121); //y 12
define_region(198,147,  209,167,  198,147);
select_region(bigfont2_14_region_id + 122); //z 11
define_region(220,147,  230,167,  220,147);
select_region(bigfont2_14_region_id + 123); //{ 13
define_region(242,147,  254,167,  242,147);
select_region(bigfont2_14_region_id + 124); //| 10
define_region(264,147,  273,167,  264,147);
select_region(bigfont2_14_region_id + 125); //} 13
define_region(286,147,  298,167,  286,147);
select_region(bigfont2_14_region_id + 126); //~ 15
define_region(308,147,  322,167,  308,147);
select_region(bigfont2_14_region_id + 127); // 12
define_region(330,147,  341,167,  330,147);

Fontbigfont2_14.character_height = 21;
Fontbigfont2_14.use_variable_width = true;
Fontbigfont2_14.character_separation = 0;
Fontbigfont2_14.line_separation = 15;

Fontbigfont2_14.texture_id = bigfont2_14_texture_id;
Fontbigfont2_14.character_zero_region_id = bigfont2_14_region_id;
textfont_read_region_widths(&Fontbigfont2_14);

}
#endif
