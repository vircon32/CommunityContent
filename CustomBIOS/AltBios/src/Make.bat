compile main.c -b -o obj/main.asm
assemble obj/main.asm -b -o obj/main.vbin
packrom Rdef.xml -o StandardBios.v32