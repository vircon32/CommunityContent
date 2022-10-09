compile -o obj/main.asm main.c
assemble -o obj/main.vbin obj/main.asm
packrom -o main.v32 romdefinition.xml
main.v32