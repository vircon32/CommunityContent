#!/usr/bin/env bash
##
## Creation of Variables.
##
######################################################################
NAME="${1%.*}"
codeFile="${1}"
xmlFile="${2}"

##
## Checks variables 1 and 2 to see if they are the correct files.
##
######################################################################
if [ "${1##*.}" != "c" ]; then
	echo "ERROR: First Variable is NOT a C File!"
	echo Command Usage: ./makerom [C code] [xml file] [OPT: PNG]
	exit 1
fi

if [ "${2##*.}" != "xml" ]; then
	echo "ERROR: Second Variable is NOT a XML File!"
	echo Command Usage: ./makerom [C code] [xml file] [OPT: PNG]
	exit 2
fi

if [ "${1%.*}" != "${2%.*}" ]; then
	echo "ERROR: File names do NOT match!"
	echo Command Usage: ./makerom [C code] [xml file] [OPT: PNG]
	exit 3
fi

##
## Creates the abort_build function to call upon an error.
##
######################################################################
abort_build() {
	echo
	echo ERROR: Build Failed!
	echo Command Usage: ./makerom [C code] [xml file] [OPT: PNG]
	exit 4
}

##
## Runs the Compile > Assemble > Pack ROM process for Vircon32.
##
######################################################################
compile ${codeFile} -o obj/${NAME}.asm || abort_build

assemble obj/${NAME}.asm -o obj/${NAME}.vbin || abort_build

png2vircon textures/${NAME}_Assets.png -o obj/${NAME}_Assets.vtex || abort_build
png2vircon textures/${NAME}_Foreground.png -o obj/${NAME}_Foreground.vtex || abort_build
png2vircon textures/${NAME}_DeathScreen.png -o obj/${NAME}_DeathScreen.vtex || abort_build
png2vircon textures/${NAME}_StartScreen.png -o obj/${NAME}_StartScreen.vtex || abort_build

wav2vircon sounds/savannaSFX.wav -o obj/savannaSFX.vsnd || abort_build 
wav2vircon sounds/textSFX.wav -o obj/textSFX.vsnd || abort_build 
wav2vircon sounds/grassSFX.wav -o obj/grassSFX.vsnd || abort_build 
wav2vircon sounds/metalSFX.wav -o obj/metalSFX.vsnd || abort_build 
wav2vircon sounds/deadSFX.wav -o obj/deadSFX.vsnd || abort_build 

##
## In case of font textures being supplied, the following command runs.
##
######################################################################
if [ "${3}" != "" ]; then
	png2vircon textures/alleyFontSheet.png -o obj/alleyFontSheet.vtex || abort_build
fi

packrom ${xmlFile} -o bin/${NAME}.v32 || abort_build

rm -f obj/*

exit 0
