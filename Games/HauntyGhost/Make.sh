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
assemble -v HauntyGhost.asm -o obj/HauntyGhost.vbin  || abort_build

echo
echo "Convert the PNG textures"
echo "=========================="
for image in alpha bottomBorder brickBackani1 brickBackani2 brickBackani3 mainMenuani1 mainMenuani2 mainMenuani3; do
    png2vircon -v assets/${image}.png -o obj/${image}.vtex || abort_build
    echo "--------------------------"
done

echo
echo "Pack the ROM"
echo "=========================="
packrom -v HauntyGhost.xml  -o bin/HauntyGhost.v32  || abort_build
echo "=========================="

echo
echo "BUILD SUCCESSFUL"
echo

exit 0
