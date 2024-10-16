#ifndef font1_25_H
#define font1_25_H

#include "video.h"
#include "../libs/TextFonts/textfont.h"

#define font1_25_texture_id 4
#define font1_25_region_id 0

textfont Fontfont1_25;

void setupFontfont1_25()
{
select_texture(font1_25_texture_id);
select_region(font1_25_region_id + 0); // 0
define_region(0,0,  -1,24,  0,0);
select_region(font1_25_region_id + 1); // 10
define_region(14,0,  23,24,  14,0);
select_region(font1_25_region_id + 2); // 10
define_region(28,0,  37,24,  28,0);
select_region(font1_25_region_id + 3); // 10
define_region(42,0,  51,24,  42,0);
select_region(font1_25_region_id + 4); // 10
define_region(56,0,  65,24,  56,0);
select_region(font1_25_region_id + 5); // 10
define_region(70,0,  79,24,  70,0);
select_region(font1_25_region_id + 6); // 10
define_region(84,0,  93,24,  84,0);
select_region(font1_25_region_id + 7); // 10
define_region(98,0,  107,24,  98,0);
select_region(font1_25_region_id + 8); // 10
define_region(112,0,  121,24,  112,0);
select_region(font1_25_region_id + 9); // 10
define_region(126,0,  135,24,  126,0);
select_region(font1_25_region_id + 10); // 10
define_region(140,0,  149,24,  140,0);
select_region(font1_25_region_id + 11); // 10
define_region(154,0,  163,24,  154,0);
select_region(font1_25_region_id + 12); // 10
define_region(168,0,  177,24,  168,0);
select_region(font1_25_region_id + 13); // 10
define_region(182,0,  191,24,  182,0);
select_region(font1_25_region_id + 14); // 10
define_region(196,0,  205,24,  196,0);
select_region(font1_25_region_id + 15); // 10
define_region(210,0,  219,24,  210,0);
select_region(font1_25_region_id + 16); // 10
define_region(0,25,  9,49,  0,25);
select_region(font1_25_region_id + 17); // 10
define_region(14,25,  23,49,  14,25);
select_region(font1_25_region_id + 18); // 10
define_region(28,25,  37,49,  28,25);
select_region(font1_25_region_id + 19); // 10
define_region(42,25,  51,49,  42,25);
select_region(font1_25_region_id + 20); // 10
define_region(56,25,  65,49,  56,25);
select_region(font1_25_region_id + 21); // 10
define_region(70,25,  79,49,  70,25);
select_region(font1_25_region_id + 22); // 10
define_region(84,25,  93,49,  84,25);
select_region(font1_25_region_id + 23); // 10
define_region(98,25,  107,49,  98,25);
select_region(font1_25_region_id + 24); // 10
define_region(112,25,  121,49,  112,25);
select_region(font1_25_region_id + 25); // 10
define_region(126,25,  135,49,  126,25);
select_region(font1_25_region_id + 26); // 10
define_region(140,25,  149,49,  140,25);
select_region(font1_25_region_id + 27); // 10
define_region(154,25,  163,49,  154,25);
select_region(font1_25_region_id + 28); // 10
define_region(168,25,  177,49,  168,25);
select_region(font1_25_region_id + 29); // 10
define_region(182,25,  191,49,  182,25);
select_region(font1_25_region_id + 30); // 10
define_region(196,25,  205,49,  196,25);
select_region(font1_25_region_id + 31); // 10
define_region(210,25,  219,49,  210,25);
select_region(font1_25_region_id + 32); //  10
define_region(0,50,  9,74,  0,50);
select_region(font1_25_region_id + 33); //! 10
define_region(14,50,  23,74,  14,50);
select_region(font1_25_region_id + 34); //" 10
define_region(28,50,  37,74,  28,50);
select_region(font1_25_region_id + 35); //# 12
define_region(42,50,  53,74,  42,50);
select_region(font1_25_region_id + 36); //$ 10
define_region(56,50,  65,74,  56,50);
select_region(font1_25_region_id + 37); //% 14
define_region(70,50,  83,74,  70,50);
select_region(font1_25_region_id + 38); //& 12
define_region(84,50,  95,74,  84,50);
select_region(font1_25_region_id + 39); //' 10
define_region(98,50,  107,74,  98,50);
select_region(font1_25_region_id + 40); //( 10
define_region(112,50,  121,74,  112,50);
select_region(font1_25_region_id + 41); //) 10
define_region(126,50,  135,74,  126,50);
select_region(font1_25_region_id + 42); //* 10
define_region(140,50,  149,74,  140,50);
select_region(font1_25_region_id + 43); //+ 10
define_region(154,50,  163,74,  154,50);
select_region(font1_25_region_id + 44); //, 10
define_region(168,50,  177,74,  168,50);
select_region(font1_25_region_id + 45); //- 10
define_region(182,50,  191,74,  182,50);
select_region(font1_25_region_id + 46); //. 10
define_region(196,50,  205,74,  196,50);
select_region(font1_25_region_id + 47); /// 10
define_region(210,50,  219,74,  210,50);
select_region(font1_25_region_id + 48); //0 10
define_region(0,75,  9,99,  0,75);
select_region(font1_25_region_id + 49); //1 10
define_region(14,75,  23,99,  14,75);
select_region(font1_25_region_id + 50); //2 10
define_region(28,75,  37,99,  28,75);
select_region(font1_25_region_id + 51); //3 10
define_region(42,75,  51,99,  42,75);
select_region(font1_25_region_id + 52); //4 10
define_region(56,75,  65,99,  56,75);
select_region(font1_25_region_id + 53); //5 10
define_region(70,75,  79,99,  70,75);
select_region(font1_25_region_id + 54); //6 10
define_region(84,75,  93,99,  84,75);
select_region(font1_25_region_id + 55); //7 10
define_region(98,75,  107,99,  98,75);
select_region(font1_25_region_id + 56); //8 10
define_region(112,75,  121,99,  112,75);
select_region(font1_25_region_id + 57); //9 10
define_region(126,75,  135,99,  126,75);
select_region(font1_25_region_id + 58); //: 10
define_region(140,75,  149,99,  140,75);
select_region(font1_25_region_id + 59); //; 10
define_region(154,75,  163,99,  154,75);
select_region(font1_25_region_id + 60); //< 10
define_region(168,75,  177,99,  168,75);
select_region(font1_25_region_id + 61); //= 10
define_region(182,75,  191,99,  182,75);
select_region(font1_25_region_id + 62); //> 10
define_region(196,75,  205,99,  196,75);
select_region(font1_25_region_id + 63); //? 10
define_region(210,75,  219,99,  210,75);
select_region(font1_25_region_id + 64); //@ 10
define_region(0,100,  9,124,  0,100);
select_region(font1_25_region_id + 65); //A 10
define_region(14,100,  23,124,  14,100);
select_region(font1_25_region_id + 66); //B 10
define_region(28,100,  37,124,  28,100);
select_region(font1_25_region_id + 67); //C 10
define_region(42,100,  51,124,  42,100);
select_region(font1_25_region_id + 68); //D 10
define_region(56,100,  65,124,  56,100);
select_region(font1_25_region_id + 69); //E 10
define_region(70,100,  79,124,  70,100);
select_region(font1_25_region_id + 70); //F 10
define_region(84,100,  93,124,  84,100);
select_region(font1_25_region_id + 71); //G 10
define_region(98,100,  107,124,  98,100);
select_region(font1_25_region_id + 72); //H 10
define_region(112,100,  121,124,  112,100);
select_region(font1_25_region_id + 73); //I 10
define_region(126,100,  135,124,  126,100);
select_region(font1_25_region_id + 74); //J 10
define_region(140,100,  149,124,  140,100);
select_region(font1_25_region_id + 75); //K 10
define_region(154,100,  163,124,  154,100);
select_region(font1_25_region_id + 76); //L 10
define_region(168,100,  177,124,  168,100);
select_region(font1_25_region_id + 77); //M 10
define_region(182,100,  191,124,  182,100);
select_region(font1_25_region_id + 78); //N 10
define_region(196,100,  205,124,  196,100);
select_region(font1_25_region_id + 79); //O 10
define_region(210,100,  219,124,  210,100);
select_region(font1_25_region_id + 80); //P 10
define_region(0,125,  9,149,  0,125);
select_region(font1_25_region_id + 81); //Q 10
define_region(14,125,  23,149,  14,125);
select_region(font1_25_region_id + 82); //R 10
define_region(28,125,  37,149,  28,125);
select_region(font1_25_region_id + 83); //S 10
define_region(42,125,  51,149,  42,125);
select_region(font1_25_region_id + 84); //T 10
define_region(56,125,  65,149,  56,125);
select_region(font1_25_region_id + 85); //U 10
define_region(70,125,  79,149,  70,125);
select_region(font1_25_region_id + 86); //V 10
define_region(84,125,  93,149,  84,125);
select_region(font1_25_region_id + 87); //W 10
define_region(98,125,  107,149,  98,125);
select_region(font1_25_region_id + 88); //X 10
define_region(112,125,  121,149,  112,125);
select_region(font1_25_region_id + 89); //Y 10
define_region(126,125,  135,149,  126,125);
select_region(font1_25_region_id + 90); //Z 10
define_region(140,125,  149,149,  140,125);
select_region(font1_25_region_id + 91); //[ 10
define_region(154,125,  163,149,  154,125);
select_region(font1_25_region_id + 92); // 10
define_region(168,125,  177,149,  168,125);
select_region(font1_25_region_id + 93); //] 10
define_region(182,125,  191,149,  182,125);
select_region(font1_25_region_id + 94); //^ 10
define_region(196,125,  205,149,  196,125);
select_region(font1_25_region_id + 95); //_ 10
define_region(210,125,  219,149,  210,125);
select_region(font1_25_region_id + 96); //` 10
define_region(0,150,  9,174,  0,150);
select_region(font1_25_region_id + 97); //a 10
define_region(14,150,  23,174,  14,150);
select_region(font1_25_region_id + 98); //b 10
define_region(28,150,  37,174,  28,150);
select_region(font1_25_region_id + 99); //c 10
define_region(42,150,  51,174,  42,150);
select_region(font1_25_region_id + 100); //d 10
define_region(56,150,  65,174,  56,150);
select_region(font1_25_region_id + 101); //e 10
define_region(70,150,  79,174,  70,150);
select_region(font1_25_region_id + 102); //f 10
define_region(84,150,  93,174,  84,150);
select_region(font1_25_region_id + 103); //g 10
define_region(98,150,  107,174,  98,150);
select_region(font1_25_region_id + 104); //h 10
define_region(112,150,  121,174,  112,150);
select_region(font1_25_region_id + 105); //i 10
define_region(126,150,  135,174,  126,150);
select_region(font1_25_region_id + 106); //j 10
define_region(140,150,  149,174,  140,150);
select_region(font1_25_region_id + 107); //k 10
define_region(154,150,  163,174,  154,150);
select_region(font1_25_region_id + 108); //l 10
define_region(168,150,  177,174,  168,150);
select_region(font1_25_region_id + 109); //m 10
define_region(182,150,  191,174,  182,150);
select_region(font1_25_region_id + 110); //n 10
define_region(196,150,  205,174,  196,150);
select_region(font1_25_region_id + 111); //o 10
define_region(210,150,  219,174,  210,150);
select_region(font1_25_region_id + 112); //p 10
define_region(0,175,  9,199,  0,175);
select_region(font1_25_region_id + 113); //q 10
define_region(14,175,  23,199,  14,175);
select_region(font1_25_region_id + 114); //r 10
define_region(28,175,  37,199,  28,175);
select_region(font1_25_region_id + 115); //s 10
define_region(42,175,  51,199,  42,175);
select_region(font1_25_region_id + 116); //t 10
define_region(56,175,  65,199,  56,175);
select_region(font1_25_region_id + 117); //u 10
define_region(70,175,  79,199,  70,175);
select_region(font1_25_region_id + 118); //v 10
define_region(84,175,  93,199,  84,175);
select_region(font1_25_region_id + 119); //w 10
define_region(98,175,  107,199,  98,175);
select_region(font1_25_region_id + 120); //x 10
define_region(112,175,  121,199,  112,175);
select_region(font1_25_region_id + 121); //y 10
define_region(126,175,  135,199,  126,175);
select_region(font1_25_region_id + 122); //z 10
define_region(140,175,  149,199,  140,175);
select_region(font1_25_region_id + 123); //{ 10
define_region(154,175,  163,199,  154,175);
select_region(font1_25_region_id + 124); //| 10
define_region(168,175,  177,199,  168,175);
select_region(font1_25_region_id + 125); //} 10
define_region(182,175,  191,199,  182,175);
select_region(font1_25_region_id + 126); //~ 10
define_region(196,175,  205,199,  196,175);
select_region(font1_25_region_id + 127); // 10
define_region(210,175,  219,199,  210,175);

Fontfont1_25.character_height = 25;
Fontfont1_25.use_variable_width = true;
Fontfont1_25.character_separation = 0;
Fontfont1_25.line_separation = 0;

Fontfont1_25.texture_id = font1_25_texture_id;
Fontfont1_25.character_zero_region_id = font1_25_region_id;
textfont_read_region_widths(&Fontfont1_25);

}
#endif
