#!/bin/bash
##
## Make.sh: build script for debuggerBIOS
##
########################################################################################

########################################################################################
##
## define an abort function to call on error
##
abort_build()
{
    echo
    echo BUILD FAILED
    exit 1
}

########################################################################################
##
## create obj and bin folders if non exiting, since
## the development tools will not create them themselves
##
mkdir -p obj
mkdir -p bin

########################################################################################
##
## compilation of a BIOS requires argument -b
##
echo
echo Compile the C code
echo --------------------------
compile  -g         debuggerBIOS.c       -o obj/debuggerBIOS.asm  -b || abort_build

########################################################################################
##
## assembly of a BIOS requires argument -b
##
echo
echo Assemble the ASM code
echo --------------------------
assemble -g program obj/debuggerBIOS.asm -o obj/debuggerBIOS.vbin -b || abort_build

########################################################################################
##
## Convert the PNG to VTEX
##
echo
echo Convert the PNG texture
echo --------------------------
png2vircon          BiosTexture.png      -o obj/BiosTexture.vtex     || abort_build

########################################################################################
##
## Convert the WAV to VSND
##
echo
echo Convert the WAV sound
echo --------------------------
wav2vircon          BiosSound.wav        -o obj/BiosSound.vsnd       || abort_build

########################################################################################
##
## pack up all the processed assets into the final BIOS ROM
##
echo
echo Pack the ROM
echo --------------------------
packrom             debuggerBIOS.xml     -o bin/debuggerBIOS.v32     || abort_build

########################################################################################
##
## If we get this far, the build is presumed successful
##
echo
echo BUILD SUCCESSFUL
