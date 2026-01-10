#ifndef Retro_Gaming_11_H
#define Retro_Gaming_11_H

#include "video.h"


#define Retro_Gaming_11_texture_id 2
#define Retro_Gaming_11_region_id 0

textfont FontRetro_Gaming_11;

void setupFontRetro_Gaming_11()
{
select_texture(Retro_Gaming_11_texture_id);
select_region(Retro_Gaming_11_region_id + 0); // 0
define_region(0,0,  -1,13,  0,0);
select_region(Retro_Gaming_11_region_id + 1); // 9
define_region(12,0,  20,13,  12,0);
select_region(Retro_Gaming_11_region_id + 2); // 7
define_region(24,0,  30,13,  24,0);
select_region(Retro_Gaming_11_region_id + 3); // 10
define_region(36,0,  45,13,  36,0);
select_region(Retro_Gaming_11_region_id + 4); // 7
define_region(48,0,  54,13,  48,0);
select_region(Retro_Gaming_11_region_id + 5); // 8
define_region(60,0,  67,13,  60,0);
select_region(Retro_Gaming_11_region_id + 6); // 7
define_region(72,0,  78,13,  72,0);
select_region(Retro_Gaming_11_region_id + 7); // 7
define_region(84,0,  90,13,  84,0);
select_region(Retro_Gaming_11_region_id + 8); // 7
define_region(96,0,  102,13,  96,0);
select_region(Retro_Gaming_11_region_id + 9); // 7
define_region(108,0,  114,13,  108,0);
select_region(Retro_Gaming_11_region_id + 10); // 7
define_region(120,0,  126,13,  120,0);
select_region(Retro_Gaming_11_region_id + 11); // 7
define_region(132,0,  138,13,  132,0);
select_region(Retro_Gaming_11_region_id + 12); // 7
define_region(144,0,  150,13,  144,0);
select_region(Retro_Gaming_11_region_id + 13); // 7
define_region(156,0,  162,13,  156,0);
select_region(Retro_Gaming_11_region_id + 14); // 7
define_region(168,0,  174,13,  168,0);
select_region(Retro_Gaming_11_region_id + 15); // 7
define_region(180,0,  186,13,  180,0);
select_region(Retro_Gaming_11_region_id + 16); // 7
define_region(0,14,  6,27,  0,14);
select_region(Retro_Gaming_11_region_id + 17); // 7
define_region(12,14,  18,27,  12,14);
select_region(Retro_Gaming_11_region_id + 18); // 7
define_region(24,14,  30,27,  24,14);
select_region(Retro_Gaming_11_region_id + 19); // 7
define_region(36,14,  42,27,  36,14);
select_region(Retro_Gaming_11_region_id + 20); // 7
define_region(48,14,  54,27,  48,14);
select_region(Retro_Gaming_11_region_id + 21); // 7
define_region(60,14,  66,27,  60,14);
select_region(Retro_Gaming_11_region_id + 22); // 7
define_region(72,14,  78,27,  72,14);
select_region(Retro_Gaming_11_region_id + 23); // 7
define_region(84,14,  90,27,  84,14);
select_region(Retro_Gaming_11_region_id + 24); // 7
define_region(96,14,  102,27,  96,14);
select_region(Retro_Gaming_11_region_id + 25); // 7
define_region(108,14,  114,27,  108,14);
select_region(Retro_Gaming_11_region_id + 26); // 7
define_region(120,14,  126,27,  120,14);
select_region(Retro_Gaming_11_region_id + 27); // 7
define_region(132,14,  138,27,  132,14);
select_region(Retro_Gaming_11_region_id + 28); // 7
define_region(144,14,  150,27,  144,14);
select_region(Retro_Gaming_11_region_id + 29); // 7
define_region(156,14,  162,27,  156,14);
select_region(Retro_Gaming_11_region_id + 30); // 7
define_region(168,14,  174,27,  168,14);
select_region(Retro_Gaming_11_region_id + 31); // 7
define_region(180,14,  186,27,  180,14);
select_region(Retro_Gaming_11_region_id + 32); //  4
define_region(0,28,  3,41,  0,28);
select_region(Retro_Gaming_11_region_id + 33); //! 4
define_region(12,28,  15,41,  12,28);
select_region(Retro_Gaming_11_region_id + 34); //" 7
define_region(24,28,  30,41,  24,28);
select_region(Retro_Gaming_11_region_id + 35); //# 12
define_region(36,28,  47,41,  36,28);
select_region(Retro_Gaming_11_region_id + 36); //$ 9
define_region(48,28,  56,41,  48,28);
select_region(Retro_Gaming_11_region_id + 37); //% 9
define_region(60,28,  68,41,  60,28);
select_region(Retro_Gaming_11_region_id + 38); //& 10
define_region(72,28,  81,41,  72,28);
select_region(Retro_Gaming_11_region_id + 39); //' 4
define_region(84,28,  87,41,  84,28);
select_region(Retro_Gaming_11_region_id + 40); //( 6
define_region(96,28,  101,41,  96,28);
select_region(Retro_Gaming_11_region_id + 41); //) 6
define_region(108,28,  113,41,  108,28);
select_region(Retro_Gaming_11_region_id + 42); //* 10
define_region(120,28,  129,41,  120,28);
select_region(Retro_Gaming_11_region_id + 43); //+ 8
define_region(132,28,  139,41,  132,28);
select_region(Retro_Gaming_11_region_id + 44); //, 4
define_region(144,28,  147,41,  144,28);
select_region(Retro_Gaming_11_region_id + 45); //- 6
define_region(156,28,  161,41,  156,28);
select_region(Retro_Gaming_11_region_id + 46); //. 4
define_region(168,28,  171,41,  168,28);
select_region(Retro_Gaming_11_region_id + 47); /// 9
define_region(180,28,  188,41,  180,28);
select_region(Retro_Gaming_11_region_id + 48); //0 9
define_region(0,42,  8,55,  0,42);
select_region(Retro_Gaming_11_region_id + 49); //1 6
define_region(12,42,  17,55,  12,42);
select_region(Retro_Gaming_11_region_id + 50); //2 9
define_region(24,42,  32,55,  24,42);
select_region(Retro_Gaming_11_region_id + 51); //3 9
define_region(36,42,  44,55,  36,42);
select_region(Retro_Gaming_11_region_id + 52); //4 9
define_region(48,42,  56,55,  48,42);
select_region(Retro_Gaming_11_region_id + 53); //5 9
define_region(60,42,  68,55,  60,42);
select_region(Retro_Gaming_11_region_id + 54); //6 9
define_region(72,42,  80,55,  72,42);
select_region(Retro_Gaming_11_region_id + 55); //7 9
define_region(84,42,  92,55,  84,42);
select_region(Retro_Gaming_11_region_id + 56); //8 9
define_region(96,42,  104,55,  96,42);
select_region(Retro_Gaming_11_region_id + 57); //9 9
define_region(108,42,  116,55,  108,42);
select_region(Retro_Gaming_11_region_id + 58); //: 4
define_region(120,42,  123,55,  120,42);
select_region(Retro_Gaming_11_region_id + 59); //; 4
define_region(132,42,  135,55,  132,42);
select_region(Retro_Gaming_11_region_id + 60); //< 7
define_region(144,42,  150,55,  144,42);
select_region(Retro_Gaming_11_region_id + 61); //= 7
define_region(156,42,  162,55,  156,42);
select_region(Retro_Gaming_11_region_id + 62); //> 7
define_region(168,42,  174,55,  168,42);
select_region(Retro_Gaming_11_region_id + 63); //? 9
define_region(180,42,  188,55,  180,42);
select_region(Retro_Gaming_11_region_id + 64); //@ 9
define_region(0,56,  8,69,  0,56);
select_region(Retro_Gaming_11_region_id + 65); //A 9
define_region(12,56,  20,69,  12,56);
select_region(Retro_Gaming_11_region_id + 66); //B 9
define_region(24,56,  32,69,  24,56);
select_region(Retro_Gaming_11_region_id + 67); //C 9
define_region(36,56,  44,69,  36,56);
select_region(Retro_Gaming_11_region_id + 68); //D 9
define_region(48,56,  56,69,  48,56);
select_region(Retro_Gaming_11_region_id + 69); //E 9
define_region(60,56,  68,69,  60,56);
select_region(Retro_Gaming_11_region_id + 70); //F 9
define_region(72,56,  80,69,  72,56);
select_region(Retro_Gaming_11_region_id + 71); //G 9
define_region(84,56,  92,69,  84,56);
select_region(Retro_Gaming_11_region_id + 72); //H 9
define_region(96,56,  104,69,  96,56);
select_region(Retro_Gaming_11_region_id + 73); //I 8
define_region(108,56,  115,69,  108,56);
select_region(Retro_Gaming_11_region_id + 74); //J 9
define_region(120,56,  128,69,  120,56);
select_region(Retro_Gaming_11_region_id + 75); //K 9
define_region(132,56,  140,69,  132,56);
select_region(Retro_Gaming_11_region_id + 76); //L 8
define_region(144,56,  151,69,  144,56);
select_region(Retro_Gaming_11_region_id + 77); //M 9
define_region(156,56,  164,69,  156,56);
select_region(Retro_Gaming_11_region_id + 78); //N 9
define_region(168,56,  176,69,  168,56);
select_region(Retro_Gaming_11_region_id + 79); //O 9
define_region(180,56,  188,69,  180,56);
select_region(Retro_Gaming_11_region_id + 80); //P 9
define_region(0,70,  8,83,  0,70);
select_region(Retro_Gaming_11_region_id + 81); //Q 9
define_region(12,70,  20,83,  12,70);
select_region(Retro_Gaming_11_region_id + 82); //R 9
define_region(24,70,  32,83,  24,70);
select_region(Retro_Gaming_11_region_id + 83); //S 9
define_region(36,70,  44,83,  36,70);
select_region(Retro_Gaming_11_region_id + 84); //T 9
define_region(48,70,  56,83,  48,70);
select_region(Retro_Gaming_11_region_id + 85); //U 9
define_region(60,70,  68,83,  60,70);
select_region(Retro_Gaming_11_region_id + 86); //V 9
define_region(72,70,  80,83,  72,70);
select_region(Retro_Gaming_11_region_id + 87); //W 10
define_region(84,70,  93,83,  84,70);
select_region(Retro_Gaming_11_region_id + 88); //X 9
define_region(96,70,  104,83,  96,70);
select_region(Retro_Gaming_11_region_id + 89); //Y 9
define_region(108,70,  116,83,  108,70);
select_region(Retro_Gaming_11_region_id + 90); //Z 9
define_region(120,70,  128,83,  120,70);
select_region(Retro_Gaming_11_region_id + 91); //[ 6
define_region(132,70,  137,83,  132,70);
select_region(Retro_Gaming_11_region_id + 92); // 9
define_region(144,70,  152,83,  144,70);
select_region(Retro_Gaming_11_region_id + 93); //] 6
define_region(156,70,  161,83,  156,70);
select_region(Retro_Gaming_11_region_id + 94); //^ 9
define_region(168,70,  176,83,  168,70);
select_region(Retro_Gaming_11_region_id + 95); //_ 7
define_region(180,70,  186,83,  180,70);
select_region(Retro_Gaming_11_region_id + 96); //` 6
define_region(0,84,  5,97,  0,84);
select_region(Retro_Gaming_11_region_id + 97); //a 9
define_region(12,84,  20,97,  12,84);
select_region(Retro_Gaming_11_region_id + 98); //b 9
define_region(24,84,  32,97,  24,84);
select_region(Retro_Gaming_11_region_id + 99); //c 9
define_region(36,84,  44,97,  36,84);
select_region(Retro_Gaming_11_region_id + 100); //d 9
define_region(48,84,  56,97,  48,84);
select_region(Retro_Gaming_11_region_id + 101); //e 9
define_region(60,84,  68,97,  60,84);
select_region(Retro_Gaming_11_region_id + 102); //f 7
define_region(72,84,  78,97,  72,84);
select_region(Retro_Gaming_11_region_id + 103); //g 9
define_region(84,84,  92,97,  84,84);
select_region(Retro_Gaming_11_region_id + 104); //h 9
define_region(96,84,  104,97,  96,84);
select_region(Retro_Gaming_11_region_id + 105); //i 4
define_region(108,84,  111,97,  108,84);
select_region(Retro_Gaming_11_region_id + 106); //j 7
define_region(120,84,  126,97,  120,84);
select_region(Retro_Gaming_11_region_id + 107); //k 8
define_region(132,84,  139,97,  132,84);
select_region(Retro_Gaming_11_region_id + 108); //l 5
define_region(144,84,  148,97,  144,84);
select_region(Retro_Gaming_11_region_id + 109); //m 9
define_region(156,84,  164,97,  156,84);
select_region(Retro_Gaming_11_region_id + 110); //n 9
define_region(168,84,  176,97,  168,84);
select_region(Retro_Gaming_11_region_id + 111); //o 9
define_region(180,84,  188,97,  180,84);
select_region(Retro_Gaming_11_region_id + 112); //p 9
define_region(0,98,  8,111,  0,98);
select_region(Retro_Gaming_11_region_id + 113); //q 9
define_region(12,98,  20,111,  12,98);
select_region(Retro_Gaming_11_region_id + 114); //r 8
define_region(24,98,  31,111,  24,98);
select_region(Retro_Gaming_11_region_id + 115); //s 9
define_region(36,98,  44,111,  36,98);
select_region(Retro_Gaming_11_region_id + 116); //t 7
define_region(48,98,  54,111,  48,98);
select_region(Retro_Gaming_11_region_id + 117); //u 9
define_region(60,98,  68,111,  60,98);
select_region(Retro_Gaming_11_region_id + 118); //v 9
define_region(72,98,  80,111,  72,98);
select_region(Retro_Gaming_11_region_id + 119); //w 9
define_region(84,98,  92,111,  84,98);
select_region(Retro_Gaming_11_region_id + 120); //x 9
define_region(96,98,  104,111,  96,98);
select_region(Retro_Gaming_11_region_id + 121); //y 9
define_region(108,98,  116,111,  108,98);
select_region(Retro_Gaming_11_region_id + 122); //z 9
define_region(120,98,  128,111,  120,98);
select_region(Retro_Gaming_11_region_id + 123); //{ 6
define_region(132,98,  137,111,  132,98);
select_region(Retro_Gaming_11_region_id + 124); //| 4
define_region(144,98,  147,111,  144,98);
select_region(Retro_Gaming_11_region_id + 125); //} 6
define_region(156,98,  161,111,  156,98);
select_region(Retro_Gaming_11_region_id + 126); //~ 8
define_region(168,98,  175,111,  168,98);
select_region(Retro_Gaming_11_region_id + 127); // 7
define_region(180,98,  186,111,  180,98);

FontRetro_Gaming_11.character_height = 14;
FontRetro_Gaming_11.use_variable_width = true;
FontRetro_Gaming_11.character_separation = 0;
FontRetro_Gaming_11.line_separation = 0;

FontRetro_Gaming_11.texture_id = Retro_Gaming_11_texture_id;
FontRetro_Gaming_11.character_zero_region_id = Retro_Gaming_11_region_id;
textfont_read_region_widths(&FontRetro_Gaming_11);

}
#endif
