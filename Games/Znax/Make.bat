@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\znax.c -o obj\znax.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\znax.asm -o obj\znax.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------

REM Fpdefault skin
png2vircon assets\graphics\znax1.png -o obj\znax1.vtex || goto :failed
png2vircon assets\graphics\znax2.png -o obj\znax2.vtex || goto :failed
png2vircon assets\graphics\znax3.png -o obj\znax3.vtex || goto :failed

png2vircon src\fonts\font_16.png -o obj\font_16.vtex || goto :failed
png2vircon src\fonts\font_24.png -o obj\font_24.vtex || goto :failed
png2vircon src\fonts\font1_25.png -o obj\font1_25.vtex || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed

wav2vircon assets\sound\blockselect.wav -o obj\blockselect.vsnd || goto :failed
wav2vircon assets\sound\delete.wav -o obj\delete.vsnd || goto :failed
wav2vircon assets\sound\error.wav -o obj\error.vsnd || goto :failed
wav2vircon assets\sound\menu.wav -o obj\menu.vsnd || goto :failed
wav2vircon assets\sound\one.wav -o obj\one.vsnd || goto :failed
wav2vircon assets\sound\oneminute.wav -o obj\oneminute.vsnd || goto :failed
wav2vircon assets\sound\readygo.wav -o obj\readygo.vsnd || goto :failed
wav2vircon assets\sound\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sound\three.wav -o obj\three.vsnd || goto :failed
wav2vircon assets\sound\timeover.wav -o obj\timeover.vsnd || goto :failed
wav2vircon assets\sound\two.wav -o obj\two.vsnd || goto :failed
wav2vircon assets\sound\welcome.wav -o obj\welcome.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Znax.xml -o "bin\Znax.v32" || goto :failed
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