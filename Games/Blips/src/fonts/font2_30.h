#ifndef font2_30_H
#define font2_30_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font2_30_texture_id 5
#define font2_30_region_id 0

textfont Fontfont2_30;

void setupFontfont2_30()
{
select_texture(font2_30_texture_id);
select_region(font2_30_region_id + 0); // 0
define_region(0,0,  -1,18,  0,0);
select_region(font2_30_region_id + 1); // 17
define_region(23,0,  39,18,  23,0);
select_region(font2_30_region_id + 2); // 23
define_region(46,0,  68,18,  46,0);
select_region(font2_30_region_id + 3); // 19
define_region(69,0,  87,18,  69,0);
select_region(font2_30_region_id + 4); // 23
define_region(92,0,  114,18,  92,0);
select_region(font2_30_region_id + 5); // 5
define_region(115,0,  119,18,  115,0);
select_region(font2_30_region_id + 6); // 23
define_region(138,0,  160,18,  138,0);
select_region(font2_30_region_id + 7); // 23
define_region(161,0,  183,18,  161,0);
select_region(font2_30_region_id + 8); // 23
define_region(184,0,  206,18,  184,0);
select_region(font2_30_region_id + 9); // 23
define_region(207,0,  229,18,  207,0);
select_region(font2_30_region_id + 10); // 23
define_region(230,0,  252,18,  230,0);
select_region(font2_30_region_id + 11); // 23
define_region(253,0,  275,18,  253,0);
select_region(font2_30_region_id + 12); // 23
define_region(276,0,  298,18,  276,0);
select_region(font2_30_region_id + 13); // 23
define_region(299,0,  321,18,  299,0);
select_region(font2_30_region_id + 14); // 23
define_region(322,0,  344,18,  322,0);
select_region(font2_30_region_id + 15); // 23
define_region(345,0,  367,18,  345,0);
select_region(font2_30_region_id + 16); // 23
define_region(0,19,  22,37,  0,19);
select_region(font2_30_region_id + 17); // 23
define_region(23,19,  45,37,  23,19);
select_region(font2_30_region_id + 18); // 23
define_region(46,19,  68,37,  46,19);
select_region(font2_30_region_id + 19); // 23
define_region(69,19,  91,37,  69,19);
select_region(font2_30_region_id + 20); // 23
define_region(92,19,  114,37,  92,19);
select_region(font2_30_region_id + 21); // 23
define_region(115,19,  137,37,  115,19);
select_region(font2_30_region_id + 22); // 23
define_region(138,19,  160,37,  138,19);
select_region(font2_30_region_id + 23); // 23
define_region(161,19,  183,37,  161,19);
select_region(font2_30_region_id + 24); // 23
define_region(184,19,  206,37,  184,19);
select_region(font2_30_region_id + 25); // 23
define_region(207,19,  229,37,  207,19);
select_region(font2_30_region_id + 26); // 23
define_region(230,19,  252,37,  230,19);
select_region(font2_30_region_id + 27); // 23
define_region(253,19,  275,37,  253,19);
select_region(font2_30_region_id + 28); // 23
define_region(276,19,  298,37,  276,19);
select_region(font2_30_region_id + 29); // 23
define_region(299,19,  321,37,  299,19);
select_region(font2_30_region_id + 30); // 23
define_region(322,19,  344,37,  322,19);
select_region(font2_30_region_id + 31); // 23
define_region(345,19,  367,37,  345,19);
select_region(font2_30_region_id + 32); //  7
define_region(0,38,  6,56,  0,38);
select_region(font2_30_region_id + 33); //! 6
define_region(23,38,  28,56,  23,38);
select_region(font2_30_region_id + 34); //" 6
define_region(46,38,  51,56,  46,38);
select_region(font2_30_region_id + 35); //# 11
define_region(69,38,  79,56,  69,38);
select_region(font2_30_region_id + 36); //$ 11
define_region(92,38,  102,56,  92,38);
select_region(font2_30_region_id + 37); //% 17
define_region(115,38,  131,56,  115,38);
select_region(font2_30_region_id + 38); //& 14
define_region(138,38,  151,56,  138,38);
select_region(font2_30_region_id + 39); //' 5
define_region(161,38,  165,56,  161,38);
select_region(font2_30_region_id + 40); //( 5
define_region(184,38,  188,56,  184,38);
select_region(font2_30_region_id + 41); //) 5
define_region(207,38,  211,56,  207,38);
select_region(font2_30_region_id + 42); //* 9
define_region(230,38,  238,56,  230,38);
select_region(font2_30_region_id + 43); //+ 12
define_region(253,38,  264,56,  253,38);
select_region(font2_30_region_id + 44); //, 5
define_region(276,38,  280,56,  276,38);
select_region(font2_30_region_id + 45); //- 6
define_region(299,38,  304,56,  299,38);
select_region(font2_30_region_id + 46); //. 5
define_region(322,38,  326,56,  322,38);
select_region(font2_30_region_id + 47); /// 8
define_region(345,38,  352,56,  345,38);
select_region(font2_30_region_id + 48); //0 11
define_region(0,57,  10,75,  0,57);
select_region(font2_30_region_id + 49); //1 11
define_region(23,57,  33,75,  23,57);
select_region(font2_30_region_id + 50); //2 11
define_region(46,57,  56,75,  46,57);
select_region(font2_30_region_id + 51); //3 11
define_region(69,57,  79,75,  69,57);
select_region(font2_30_region_id + 52); //4 12
define_region(92,57,  103,75,  92,57);
select_region(font2_30_region_id + 53); //5 11
define_region(115,57,  125,75,  115,57);
select_region(font2_30_region_id + 54); //6 11
define_region(138,57,  148,75,  138,57);
select_region(font2_30_region_id + 55); //7 11
define_region(161,57,  171,75,  161,57);
select_region(font2_30_region_id + 56); //8 11
define_region(184,57,  194,75,  184,57);
select_region(font2_30_region_id + 57); //9 11
define_region(207,57,  217,75,  207,57);
select_region(font2_30_region_id + 58); //: 5
define_region(230,57,  234,75,  230,57);
select_region(font2_30_region_id + 59); //; 5
define_region(253,57,  257,75,  253,57);
select_region(font2_30_region_id + 60); //< 12
define_region(276,57,  287,75,  276,57);
select_region(font2_30_region_id + 61); //= 12
define_region(299,57,  310,75,  299,57);
select_region(font2_30_region_id + 62); //> 12
define_region(322,57,  333,75,  322,57);
select_region(font2_30_region_id + 63); //? 10
define_region(345,57,  354,75,  345,57);
select_region(font2_30_region_id + 64); //@ 15
define_region(0,76,  14,94,  0,76);
select_region(font2_30_region_id + 65); //A 13
define_region(23,76,  35,94,  23,76);
select_region(font2_30_region_id + 66); //B 12
define_region(46,76,  57,94,  46,76);
select_region(font2_30_region_id + 67); //C 13
define_region(69,76,  81,94,  69,76);
select_region(font2_30_region_id + 68); //D 15
define_region(92,76,  106,94,  92,76);
select_region(font2_30_region_id + 69); //E 10
define_region(115,76,  124,94,  115,76);
select_region(font2_30_region_id + 70); //F 10
define_region(138,76,  147,94,  138,76);
select_region(font2_30_region_id + 71); //G 15
define_region(161,76,  175,94,  161,76);
select_region(font2_30_region_id + 72); //H 15
define_region(184,76,  198,94,  184,76);
select_region(font2_30_region_id + 73); //I 5
define_region(207,76,  211,94,  207,76);
select_region(font2_30_region_id + 74); //J 6
define_region(230,76,  235,94,  230,76);
select_region(font2_30_region_id + 75); //K 12
define_region(253,76,  264,94,  253,76);
select_region(font2_30_region_id + 76); //L 10
define_region(276,76,  285,94,  276,76);
select_region(font2_30_region_id + 77); //M 17
define_region(299,76,  315,94,  299,76);
select_region(font2_30_region_id + 78); //N 15
define_region(322,76,  336,94,  322,76);
select_region(font2_30_region_id + 79); //O 16
define_region(345,76,  360,94,  345,76);
select_region(font2_30_region_id + 80); //P 11
define_region(0,95,  10,113,  0,95);
select_region(font2_30_region_id + 81); //Q 16
define_region(23,95,  38,113,  23,95);
select_region(font2_30_region_id + 82); //R 12
define_region(46,95,  57,113,  46,95);
select_region(font2_30_region_id + 83); //S 10
define_region(69,95,  78,113,  69,95);
select_region(font2_30_region_id + 84); //T 11
define_region(92,95,  102,113,  92,95);
select_region(font2_30_region_id + 85); //U 15
define_region(115,95,  129,113,  115,95);
select_region(font2_30_region_id + 86); //V 13
define_region(138,95,  150,113,  138,95);
select_region(font2_30_region_id + 87); //W 19
define_region(161,95,  179,113,  161,95);
select_region(font2_30_region_id + 88); //X 12
define_region(184,95,  195,113,  184,95);
select_region(font2_30_region_id + 89); //Y 12
define_region(207,95,  218,113,  207,95);
select_region(font2_30_region_id + 90); //Z 12
define_region(230,95,  241,113,  230,95);
select_region(font2_30_region_id + 91); //[ 6
define_region(253,95,  258,113,  253,95);
select_region(font2_30_region_id + 92); // 10
define_region(276,95,  285,113,  276,95);
select_region(font2_30_region_id + 93); //] 6
define_region(299,95,  304,113,  299,95);
select_region(font2_30_region_id + 94); //^ 12
define_region(322,95,  333,113,  322,95);
select_region(font2_30_region_id + 95); //_ 10
define_region(345,95,  354,113,  345,95);
select_region(font2_30_region_id + 96); //` 6
define_region(0,114,  5,132,  0,114);
select_region(font2_30_region_id + 97); //a 10
define_region(23,114,  32,132,  23,114);
select_region(font2_30_region_id + 98); //b 11
define_region(46,114,  56,132,  46,114);
select_region(font2_30_region_id + 99); //c 10
define_region(69,114,  78,132,  69,114);
select_region(font2_30_region_id + 100); //d 11
define_region(92,114,  102,132,  92,114);
select_region(font2_30_region_id + 101); //e 10
define_region(115,114,  124,132,  115,114);
select_region(font2_30_region_id + 102); //f 6
define_region(138,114,  143,132,  138,114);
select_region(font2_30_region_id + 103); //g 10
define_region(161,114,  170,132,  161,114);
select_region(font2_30_region_id + 104); //h 11
define_region(184,114,  194,132,  184,114);
select_region(font2_30_region_id + 105); //i 5
define_region(207,114,  211,132,  207,114);
select_region(font2_30_region_id + 106); //j 5
define_region(230,114,  234,132,  230,114);
select_region(font2_30_region_id + 107); //k 10
define_region(253,114,  262,132,  253,114);
select_region(font2_30_region_id + 108); //l 5
define_region(276,114,  280,132,  276,114);
select_region(font2_30_region_id + 109); //m 16
define_region(299,114,  314,132,  299,114);
select_region(font2_30_region_id + 110); //n 11
define_region(322,114,  332,132,  322,114);
select_region(font2_30_region_id + 111); //o 11
define_region(345,114,  355,132,  345,114);
select_region(font2_30_region_id + 112); //p 11
define_region(0,133,  10,151,  0,133);
select_region(font2_30_region_id + 113); //q 11
define_region(23,133,  33,151,  23,133);
select_region(font2_30_region_id + 114); //r 7
define_region(46,133,  52,151,  46,133);
select_region(font2_30_region_id + 115); //s 7
define_region(69,133,  75,151,  69,133);
select_region(font2_30_region_id + 116); //t 6
define_region(92,133,  97,151,  92,133);
select_region(font2_30_region_id + 117); //u 11
define_region(115,133,  125,151,  115,133);
select_region(font2_30_region_id + 118); //v 10
define_region(138,133,  147,151,  138,133);
select_region(font2_30_region_id + 119); //w 15
define_region(161,133,  175,151,  161,133);
select_region(font2_30_region_id + 120); //x 10
define_region(184,133,  193,151,  184,133);
select_region(font2_30_region_id + 121); //y 10
define_region(207,133,  216,151,  207,133);
select_region(font2_30_region_id + 122); //z 10
define_region(230,133,  239,151,  230,133);
select_region(font2_30_region_id + 123); //{ 6
define_region(253,133,  258,151,  253,133);
select_region(font2_30_region_id + 124); //| 6
define_region(276,133,  281,151,  276,133);
select_region(font2_30_region_id + 125); //} 6
define_region(299,133,  304,151,  299,133);
select_region(font2_30_region_id + 126); //~ 12
define_region(322,133,  333,151,  322,133);
select_region(font2_30_region_id + 127); // 23
define_region(345,133,  367,151,  345,133);

Fontfont2_30.character_height = 19;
Fontfont2_30.use_variable_width = true;
Fontfont2_30.character_separation = 0;
Fontfont2_30.line_separation = 2;

Fontfont2_30.texture_id = font2_30_texture_id;
Fontfont2_30.character_zero_region_id = font2_30_region_id;
textfont_read_region_widths(&Fontfont2_30);

}
#endif
