@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\blockdude.c -o obj\blockdude.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\blockdude.asm -o obj\blockdude.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------

REM Fpdefault skin
png2vircon assets\graphics\fpdefault\all.png -o obj\fpdefault_all.vtex || goto :failed

REM Fptech skin
png2vircon assets\graphics\fptech\all.png -o obj\fptech_all.vtex || goto :failed

REM default skin
png2vircon assets\graphics\default\all.png -o obj\default_all.vtex || goto :failed

REM ti83 skin
png2vircon assets\graphics\ti83\all.png -o obj\ti83_all.vtex || goto :failed

REM Fptech kenney skin
png2vircon assets\graphics\kenney\all.png -o obj\kenney_all.vtex || goto :failed

REM Intro Releated
png2vircon assets\graphics\intro\all.png -o obj\intro_all.vtex || goto :failed

REM fonts
png2vircon src\fonts\Roboto_Bold_12.png -o obj\Roboto_Bold_12.vtex || goto :failed
png2vircon src\fonts\Roboto_Bold_18.png -o obj\Roboto_Bold_18.vtex || goto :failed
png2vircon src\fonts\Roboto_Bold_32.png -o obj\Roboto_Bold_32.vtex || goto :failed


echo.
echo Convert the WAV sounds
echo --------------------------
wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed
wav2vircon assets\sounds\back.wav -o obj\back.vsnd || goto :failed
wav2vircon assets\sounds\drop.wav -o obj\drop.vsnd || goto :failed
wav2vircon assets\sounds\fall.wav -o obj\fall.vsnd || goto :failed
wav2vircon assets\sounds\jump.wav -o obj\jump.vsnd || goto :failed
wav2vircon assets\sounds\menu.wav -o obj\menu.vsnd || goto :failed
wav2vircon assets\sounds\pickup.wav -o obj\pickup.vsnd || goto :failed
wav2vircon assets\sounds\select.wav -o obj\select.vsnd || goto :failed
wav2vircon assets\sounds\stageend.wav -o obj\stageend.vsnd || goto :failed
wav2vircon assets\sounds\walk.wav -o obj\walk.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Blockdude.xml -o "bin\Blockdude.v32" || goto :failed
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