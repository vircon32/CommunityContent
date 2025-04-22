#!/bin/bash

# define an abort function to call on error
abort_build()
{
    echo
    echo BUILD FAILED
    exit 1
}

# create obj and bin folders if non exiting, since
# the development tools will not create them themselves
mkdir -p obj
mkdir -p bin

echo
echo "Assemble the ASM code"
echo "=========================="
assemble -v SkywardEscape.asm -o obj/SkywardEscape.vbin  || abort_build

echo
echo "Convert the PNG textures"
echo "=========================="
for image in Background green red; do
    png2vircon -v assets/${image}.png -o obj/${image}.vtex || abort_build
    echo "--------------------------"
done

echo
echo "Convert the Wav Sounds"
echo "=========================="
wav2vircon -v assets/song.wav -o obj/song.vsnd           || abort_build

echo
echo "Pack the ROM"
echo "=========================="
packrom -v SkywardEscape.xml  -o bin/Skyward_Escape.v32  || abort_build
echo "=========================="

echo
echo "BUILD SUCCESSFUL"
echo

exit 0
