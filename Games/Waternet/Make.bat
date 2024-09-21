@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\waternet.c -o obj\waternet.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\waternet.asm -o obj\waternet.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\skins\blue_green\blue_green.png -o obj\blue_green.vtex || goto :failed
png2vircon assets\skins\black_white\black_white.png -o obj\black_white.vtex || goto :failed
png2vircon assets\skins\fp_aquaduct\fp_aquaduct.png -o obj\fp_aquaduct.vtex || goto :failed
png2vircon assets\skins\fp_brix\fp_brix.png -o obj\fp_brix.vtex || goto :failed


echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\game.wav -o obj\game.vsnd || goto :failed
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed
wav2vircon assets\music\leveldone.wav -o obj\leveldone.vsnd || goto :failed
wav2vircon assets\music\levelscleared.wav -o obj\levelscleared.vsnd || goto :failed

wav2vircon assets\sound\gamemove.wav -o obj\gamemove.vsnd || goto :failed
wav2vircon assets\sound\error.wav -o obj\error.vsnd || goto :failed
wav2vircon assets\sound\menuselect.wav -o obj\menuselect.vsnd || goto :failed
wav2vircon assets\sound\menuback.wav -o obj\menuback.vsnd || goto :failed
wav2vircon assets\sound\gameaction.wav -o obj\gameaction.vsnd || goto :failed
wav2vircon assets\sound\menuacknowledge.wav -o obj\menuacknowledge.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Waternet.xml -o "bin\Waternet.v32" || goto :failed
goto :succeeded

:failed
echo.
echo BUILD FAILED
exit /b %errorlevel%

:succeeded
echo.
echo BUILD SUCCESSFUL
exit /b

@echo on