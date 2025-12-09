@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\Blips.c -o obj\blips.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\blips.asm -o obj\blips.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------

REM Fpdefault skin
png2vircon assets\graphics\blips_1.png -o obj\blips_1.vtex || goto :failed
png2vircon assets\graphics\blips_2.png -o obj\blips_2.vtex || goto :failed
png2vircon assets\graphics\blips_3.png -o obj\blips_3.vtex || goto :failed
png2vircon assets\graphics\blips_4.png -o obj\blips_4.vtex || goto :failed
png2vircon src\fonts\font_13.png -o obj\font_13.vtex || goto :failed
png2vircon src\fonts\font1_25.png -o obj\font1_25.vtex || goto :failed
png2vircon src\fonts\font2_30.png -o obj\font2_30.vtex || goto :failed



echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed

wav2vircon assets\sound\collect.wav -o obj\collect.vsnd || goto :failed
wav2vircon assets\sound\error.wav -o obj\error.vsnd || goto :failed
wav2vircon assets\sound\explode.wav -o obj\explode.vsnd || goto :failed
wav2vircon assets\sound\menu.wav -o obj\menu.vsnd || goto :failed
wav2vircon assets\sound\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sound\stageend.wav -o obj\stageend.vsnd || goto :failed
wav2vircon assets\sound\menuback.wav -o obj\menuback.vsnd || goto :failed
wav2vircon assets\sound\move.wav -o obj\move.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Blips.xml -o "bin\Blips2.v32" || goto :failed
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