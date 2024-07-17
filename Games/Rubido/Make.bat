@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\rubido.c -o obj\rubido.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\rubido.asm -o obj\rubido.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\graphics\background.png -o obj\background.vtex || goto :failed
png2vircon assets\graphics\credits.png -o obj\credits.vtex || goto :failed
png2vircon assets\graphics\infoveryeasy.png -o obj\infoveryeasy.vtex || goto :failed
png2vircon assets\graphics\infoeasy.png -o obj\infoeasy.vtex || goto :failed
png2vircon assets\graphics\infohard.png -o obj\infohard.vtex || goto :failed
png2vircon assets\graphics\infoveryhard.png -o obj\infoveryhard.vtex || goto :failed
png2vircon assets\graphics\titlescreen.png -o obj\titlescreen.vtex || goto :failed
png2vircon assets\graphics\peg.png -o obj\peg.vtex || goto :failed
png2vircon assets\graphics\newgame1.png -o obj\newgame1.vtex || goto :failed
png2vircon assets\graphics\newgame2.png -o obj\newgame2.vtex || goto :failed
png2vircon assets\graphics\credits1.png -o obj\credits1.vtex || goto :failed
png2vircon assets\graphics\credits2.png -o obj\credits2.vtex || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\sounds\good.wav -o obj\good.vsnd || goto :failed
wav2vircon assets\sounds\loser.wav -o obj\loser.vsnd || goto :failed
wav2vircon assets\sounds\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sounds\start.wav -o obj\start.vsnd || goto :failed
wav2vircon assets\sounds\winner.wav -o obj\winner.vsnd || goto :failed
wav2vircon assets\sounds\wrong.wav -o obj\wrong.vsnd || goto :failed
wav2vircon assets\music\rubido.wav -o obj\rubido.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Rubido.xml -o "bin\Rubido.v32" || goto :failed
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