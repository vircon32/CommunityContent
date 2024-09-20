@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\puzzleland.c -o obj\puzzleland.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\puzzleland.asm -o obj\puzzleland.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\graphics\puzzleland.png -o obj\puzzleland.vtex || goto :failed

png2vircon src\fonts\Asheville_Sans_14_Bold_14.png -o obj\Asheville_Sans_14_Bold_14.vtex || goto :failed
png2vircon src\fonts\Mini_Sans_2X_14.png -o obj\Mini_Sans_2X_14.vtex || goto :failed

echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed
wav2vircon assets\music\game1.wav -o obj\game1.vsnd || goto :failed
wav2vircon assets\music\game2.wav -o obj\game2.vsnd || goto :failed
wav2vircon assets\music\oldman.wav -o obj\oldman.vsnd || goto :failed
wav2vircon assets\music\stage.wav -o obj\stage.vsnd || goto :failed

wav2vircon assets\sounds\bridge.wav -o obj\bridge.vsnd || goto :failed
wav2vircon assets\sounds\drop.wav -o obj\drop.vsnd || goto :failed
wav2vircon assets\sounds\elf.wav -o obj\elf.vsnd || goto :failed
wav2vircon assets\sounds\error.wav -o obj\error.vsnd || goto :failed
wav2vircon assets\sounds\menu.wav -o obj\menu.vsnd || goto :failed
wav2vircon assets\sounds\pickup.wav -o obj\pickup.vsnd || goto :failed
wav2vircon assets\sounds\rotate.wav -o obj\rotate.vsnd || goto :failed
wav2vircon assets\sounds\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sounds\stageend.wav -o obj\stageend.vsnd || goto :failed
wav2vircon assets\sounds\text.wav -o obj\text.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Puzzleland.xml -o "bin\Puzzleland.v32" || goto :failed
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