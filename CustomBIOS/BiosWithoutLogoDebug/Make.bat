@echo off

REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
REM compilation of a BIOS requires argument -b
compile BiosWithoutLogoDebug.c -o obj\BiosWithoutLogoDebug.asm -b || goto :failed

echo.
echo Assemble the ASM code
echo --------------------------
REM assembly of a BIOS requires argument -b
assemble obj\BiosWithoutLogoDebug.asm -o obj\BiosWithoutLogoDebug.vbin -b || goto :failed

echo.
echo Convert the PNG texture
echo --------------------------
png2vircon BiosNoLogoTexture.png -o obj\BiosNoLogoTexture.vtex || goto :failed

echo.
echo Convert the WAV sound
echo --------------------------
wav2vircon DummyBiosSound.wav -o obj\DummyBiosSound.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom BiosWithoutLogoDebug.xml -o bin\BiosWithoutLogoDebug.v32 || goto :failed

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
