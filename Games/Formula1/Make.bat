@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\formula1.c -o obj\formula1.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\formula1.asm -o obj\formula1.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\graphics\background.png -o obj\background.vtex || goto :failed
png2vircon assets\graphics\bigfont.png -o obj\bigfont.vtex || goto :failed
png2vircon assets\graphics\lcdfont.png -o obj\lcdfont.vtex || goto :failed
png2vircon assets\graphics\enemy.png -o obj\enemy.vtex || goto :failed
png2vircon assets\graphics\player.png -o obj\player.vtex || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\sounds\crash.wav -o obj\crash.vsnd || goto :failed
wav2vircon assets\sounds\tick.wav -o obj\tick.vsnd || goto :failed
wav2vircon assets\sounds\start.wav -o obj\start.vsnd || goto :failed
wav2vircon assets\sounds\gameover.wav -o obj\gameover.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Formula1.xml -o "bin\Formula1.v32" || goto :failed
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