mkdir obj
mkdir bin
png2vircon Texture.png -o obj/Texture.vtex
wav2vircon Sound.wav -o obj/Sound.vsnd
compile main.c -b -o obj/main.asm
assemble obj/main.asm -b -o obj/main.vbin
packrom Rdef.xml -o bin/AltBios.v32