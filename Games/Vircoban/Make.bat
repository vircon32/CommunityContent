@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\Vircoban.c -o obj\vircoban.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\vircoban.asm -o obj\vircoban.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------

REM Fpdefault skin
png2vircon assets\graphics\sokoban.png -o obj\sokoban.vtex || goto :failed

png2vircon src\fonts\Roboto_Black_20.png -o obj\Roboto_Black_20.vtex || goto :failed
png2vircon src\fonts\Roboto_Black_30.png -o obj\Roboto_Black_30.vtex || goto :failed
png2vircon src\fonts\Roboto_Black_60.png -o obj\Roboto_Black_60.vtex || goto :failed
png2vircon src\fonts\Roboto_Light_15.png -o obj\Roboto_Light_15.vtex || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed
wav2vircon assets\music\041415calmbgm.wav -o obj\041415calmbgm.vsnd || goto :failed
wav2vircon assets\music\periwinkle.wav -o obj\periwinkle.vsnd || goto :failed
wav2vircon "assets\music\Puzzle Game 3.wav" -o "obj\Puzzle Game 3.vsnd" || goto :failed

wav2vircon assets\sound\back.wav -o obj\back.vsnd || goto :failed
wav2vircon assets\sound\error.wav -o obj\error.vsnd || goto :failed
wav2vircon assets\sound\menu.wav -o obj\menu.vsnd || goto :failed
wav2vircon assets\sound\move.wav -o obj\move.vsnd || goto :failed
wav2vircon assets\sound\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sound\stageend.wav -o obj\stageend.vsnd || goto :failed


echo.
echo Pack the ROM
echo --------------------------
packrom Vircoban.xml -o "bin\Vircoban.v32" || goto :failed
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