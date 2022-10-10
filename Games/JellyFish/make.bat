@echo off

if not exist obj mkdir obj
if not exist bin mkdir bin

png2vircon srcAssets\player.png -o obj\player.vtex
png2vircon srcAssets\fish.png -o obj\fish.vtex
png2vircon srcAssets\bg1.png -o obj\bg1.vtex
png2vircon srcAssets\lives.png -o obj\lives.vtex
png2vircon srcAssets\sfont.png -o obj\sfont.vtex
png2vircon srcAssets\vignette.png -o obj\vignette.vtex
png2vircon srcAssets\dead.png -o obj\dead.vtex
png2vircon srcAssets\turtle.png -o obj\turtle.vtex
png2vircon srcAssets\LupFish.png -o obj\LupFish.vtex
png2vircon srcAssets\shark.png -o obj\shark.vtex
png2vircon srcAssets\intro.png -o obj\intro.vtex
png2vircon srcAssets\nomem.png -o obj\nomem.vtex

wav2vircon srcAssets\bgs.wav -o obj\bgs.vsnd
wav2vircon srcAssets\bubles.wav -o obj\bubles.vsnd
wav2vircon srcAssets\Hit.wav -o obj\Hit.vsnd
wav2vircon srcAssets\shark_sound.wav -o obj\shark_sound.vsnd
wav2vircon srcAssets\intro.wav -o obj\intro.vsnd

compile main.c -o obj\main.asm
assemble obj\main.asm -o obj\main.vbin
packrom RomDefinition.xml -o bin\JellyFish.v32

@echo on
