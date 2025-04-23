@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Assemble the ASM code
echo --------------------------
assemble SkywardEscape.asm       -o obj\SkywardEscape.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\Background.png -o obj\Background.vtex    || goto :failed
png2vircon assets\green.png      -o obj\green.vtex         || goto :failed
png2vircon assets\red.png        -o obj\red.vtex           || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\song.wav       -o obj\song.vsnd          || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom SkywardEscape.xml        -o bin\SkywardEscape.v32  || goto :failed
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
