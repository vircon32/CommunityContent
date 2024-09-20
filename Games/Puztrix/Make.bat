@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\puztrix.c -o obj\puztrix.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\puztrix.asm -o obj\puztrix.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\skins\nes\nes.png -o obj\nes.vtex || goto :failed

png2vircon assets\skins\default\default.png -o obj\default.vtex || goto :failed

png2vircon src\fonts\bigfont_14.png -o obj\bigfont_14.vtex || goto :failed
png2vircon src\fonts\bigfont2_14.png -o obj\bigfont2_14.vtex || goto :failed
png2vircon src\fonts\font_14.png -o obj\font_14.vtex || goto :failed


echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\music.wav -o obj\music.vsnd || goto :failed
wav2vircon assets\sound\destroy.wav -o obj\destroy.vsnd || goto :failed
wav2vircon assets\sound\leveleditorselect.wav -o obj\leveleditorselect.vsnd || goto :failed
wav2vircon assets\sound\score.wav -o obj\score.vsnd || goto :failed
wav2vircon assets\sound\winexit.wav -o obj\winexit.vsnd || goto :failed
wav2vircon assets\sound\directionmove.wav -o obj\directionmove.vsnd || goto :failed
wav2vircon assets\sound\gameover.wav -o obj\gameover.vsnd || goto :failed
wav2vircon assets\sound\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sound\win.wav -o obj\win.vsnd || goto :failed
wav2vircon assets\sound\nomoves.wav -o obj\nomoves.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Puztrix.xml -o "bin\Puztrix.v32" || goto :failed
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