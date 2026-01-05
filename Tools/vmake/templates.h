#ifndef TEMPLATES
#define TEMPLATES


string help_info = R"(

  Vmake: simple build system for Vircon32 games


  Usage: Vmake [command] [directory]
  Commands:
    -v --verbose   Displays extra information.
    -c --create    Creates all files and folders needed to
                   work with Vmake.
    -b --bios      Compile as a bios.
    -a --assembly  Skips compilation process
    -t --test      Opens the rom with the vircon32 emulator.
    -p --purge     Removes all cached building resources.
    -s --silent    Hides all logs except error messages.
    -V --version   Shows current version
    -l --license   Shows licensing details
    -h --help      Shows this message.
)";

string template_main_c = R"(
// #include "video.h";
// #include "audio.h"
// #include "input.h"
// #include "math.h"
// #include "string.h"
// #include "time.h"
// #include "memcard.h"
// #include "misc.h"

void main(void){

	/* Your code goes here! */

}
)";





string template_main_c_b = R"(
// #include "video.h";
// #include "audio.h"
// #include "input.h"
// #include "math.h"
// #include "string.h"
// #include "time.h"
// #include "memcard.h"
// #include "misc.h"

# include "biosutils.h" // <-- check this too.

void main(void){

	/* Your code goes here! */

}
)";





string template_main_asm = R"(

__main:

	hlt

)";





string template_main_asm_b = R"(
%define cartridge_adress 0x20000000



__run_cartridge:
	mov R0, 1
	out GPU_DrawingScaleY, R0

	mov R0, 0xFFFFFFFF
	out GPU_MultiplyColor, R0

	mov R0, 0
	out GPU_DrawingPointX, R0
	out GPU_DrawingPointY, R0

	out GPU_DrawingAngle, R0

	out GPU_SelectedRegion, R0
	jmp 0x20000000



__error_handler:

	hlt



__main:

	call __run_cartridge

	hlt

)";





string template_romdef_xml = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<rom-definition version="1.0">

<rom type="cartridge" title="Game" version="1.0" />
	<binary path= "./build/obj/main.vbin" />


	<textures>

		<!--texture path="build/texture.vtex"/-->

		</textures>


	<sounds>

		<!--sound path="build/sound.vsnd"/-->

	</sounds>

</rom-definition>
)";

string template_romdef_xml_b = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<rom-definition version="1.0">

<rom type="bios" title="custom-bios" version="1.2" />
	<binary path= "./build/obj/main.vbin" />


	<textures>

		<texture path="build/texture.vtex"/>

		</textures>


	<sounds>

		<sound path="build/sound.vsnd"/>

	</sounds>

</rom-definition>
)";




// took these values from real files

const uint8_t wav_file[82] = {
	0x52, 0x49, 0x46, 0x46, 0x46, 0x10, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
	0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
	0x04, 0x00, 0x10, 0x00, 0x4C, 0x49, 0x53, 0x54, 0x1A, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x46, 0x4F,
	0x49, 0x53, 0x46, 0x54, 0x0D, 0x00, 0x00, 0x00, 0x4C, 0x61, 0x76, 0x66, 0x36, 0x32, 0x2E, 0x33,
	0x2E, 0x31, 0x30, 0x30, 0x00, 0x00, 0x64, 0x61, 0x74, 0x61, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF,
};


const uint8_t png_file[90] = {
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
	0xDE, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x4F, 0x25, 0xC4, 0xD6, 0x00, 0x00, 0x00, 0x0C, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9C,
	0x63, 0xFC, 0xFF, 0xFF, 0x3F, 0x00, 0x06, 0x02, 0x02, 0xFF, 0x89, 0x6F, 0x02, 0x78, 0x00, 0x00,
	0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82,
};





string license_info = R"(

MIT License

Copyright (c) 2026 Palta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
)";





string template_biosutils_h =R"(
/*--------------------------------------┐
|                                       |
|             BIOS UTILS                |
|  Basic util functions to make a bios  |
|                                       |
|     Functions:                        |
|         - cartridge check             |
|         - jump to cartridge           |
|         - error handler               |
|                                       |
└--------------------------------------*/


#ifndef BIOSUTILS_H
#define BIOSUTILS_H

#define error_memory_read       0
#define error_memory_write      1
#define error_port_read         2
#define error_port_write        3
#define error_stack_overflow    4
#define error_stack_underflow   5
#define error_division          6
#define error_arc_cosine        7
#define error_arc_tangent_2     8
#define error_logarithm         9
#define error_power            10
#define error_unknown          11



//====================================
// Check if a cartridge is connected
//====================================

bool cartridge_connected(){
	asm{ "in R0, CAR_Connected" }
}



//========================
// Jump to the cartridge
//========================

void run_cartridge(){

	asm{

	"mov R0, 1"
	"out GPU_DrawingScaleY, R0"

	"mov R0, 0xFFFFFFFF"
    "out GPU_MultiplyColor, R0"

	"mov R0, 0"
	"out GPU_DrawingPointX, R0"
	"out GPU_DrawingPointY, R0"

	"out GPU_DrawingAngle, R0"

	"out GPU_SelectedRegion, R0"
	"jmp 0x20000000"

	}
}



//==================
// Error handeling
//==================

void error_handler() {
	// do not initialize!

	int error_code;
	int instruction_pointer;
	int instruction;
	int immediate_value;

	// save registers to variables
	asm{
		"mov {error_code}, R0"
		"mov {instruction_pointer}, R1"
		"mov {instruction}, R2"
		"mov {immediate_value}, R3"
	}


	// your code goes here!


}

#endif)";


string template_biosutils_asm=R"(




)";

#endif
