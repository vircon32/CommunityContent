@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\Retrotime.c -o obj\Retrotime.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\Retrotime.asm -o obj\Retrotime.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\graphics\fasterdave\fasterdave.png -o obj\fasterdave.vtex || goto :failed
png2vircon assets\graphics\blockstacker\blockstacker.png -o obj\blockstacker.vtex || goto :failed
png2vircon assets\graphics\breakout\breakout.png -o obj\breakout.vtex || goto :failed
png2vircon assets\graphics\frog\frog.png -o obj\frog.vtex || goto :failed
png2vircon assets\graphics\invaders\invaders.png -o obj\invaders.vtex || goto :failed
png2vircon assets\graphics\pang\pang.png -o obj\pang.vtex || goto :failed
png2vircon assets\graphics\main\main.png -o obj\main.vtex || goto :failed
png2vircon assets\graphics\gamepreview\gamepreview.png -o obj\gamepreview.vtex || goto :failed
png2vircon assets\graphics\ramit\ramit.png -o obj\ramit.vtex || goto :failed
png2vircon assets\graphics\snakey\snakey.png -o obj\snakey.vtex || goto :failed

REM fonts
png2vircon src\fonts\Roboto_Regular_14.png -o obj\Roboto_Reguluar_14.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_17.png -o obj\Roboto_Reguluar_17.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_19.png -o obj\Roboto_Reguluar_19.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_20.png -o obj\Roboto_Reguluar_20.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_22.png -o obj\Roboto_Reguluar_22.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_25.png -o obj\Roboto_Reguluar_25.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_30.png -o obj\Roboto_Reguluar_30.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_40.png -o obj\Roboto_Reguluar_40.vtex || goto :failed


echo.
echo Convert the WAV sounds
echo --------------------------
REM music
wav2vircon assets\music\main\music.wav -o obj\mainmusic.vsnd || goto :failed
wav2vircon assets\music\blockstacker\music.wav -o obj\blockstackermusic.vsnd || goto :failed
wav2vircon assets\music\breakout\music.wav -o obj\breakoutmusic.vsnd || goto :failed
wav2vircon assets\music\fasterdave\music.wav -o obj\fasterdavemusic.vsnd || goto :failed
wav2vircon assets\music\frog\music.wav -o obj\frogmusic.vsnd || goto :failed
wav2vircon assets\music\invaders\music.wav -o obj\invadersmusic.vsnd || goto :failed
wav2vircon assets\music\pang\music.wav -o obj\pangmusic.vsnd || goto :failed
wav2vircon assets\music\ramit\music.wav -o obj\ramitmusic.vsnd || goto :failed
wav2vircon assets\music\snakey\music.wav -o obj\snakeymusic.vsnd || goto :failed
	
REM sound 

wav2vircon assets\sound\blockstacker\drop.wav -o obj\blockstackerdrop.vsnd || goto :failed
wav2vircon assets\sound\blockstacker\lineclear.wav -o obj\blockstackerlineclear.vsnd || goto :failed
wav2vircon assets\sound\blockstacker\rotate.wav -o obj\blockstackerrotate.vsnd || goto :failed
wav2vircon assets\sound\breakout\bat.wav -o obj\breakoutbat.vsnd || goto :failed
wav2vircon assets\sound\breakout\brick.wav -o obj\breakoutbrick.vsnd || goto :failed
wav2vircon assets\sound\frog\move.wav -o obj\frogmove.vsnd || goto :failed
wav2vircon assets\sound\invaders\enemydeath.wav -o obj\invadersenemydeath.vsnd || goto :failed
wav2vircon assets\sound\invaders\enemyshoot.wav -o obj\invadersenemyshoot.vsnd || goto :failed
wav2vircon assets\sound\invaders\playerdeath.wav -o obj\invadersplayerdeath.vsnd || goto :failed
wav2vircon assets\sound\invaders\playershoot.wav -o obj\invadersplayershoot.vsnd || goto :failed
wav2vircon assets\sound\pang\pop.wav -o obj\pangpop.vsnd || goto :failed
wav2vircon assets\sound\pang\shoot.wav -o obj\pangshoot.vsnd || goto :failed
wav2vircon assets\sound\ramit\hit.wav -o obj\ramithit.vsnd || goto :failed
wav2vircon assets\sound\ramit\shoot.wav -o obj\ramitshoot.vsnd || goto :failed
wav2vircon assets\sound\snakey\food.wav -o obj\snakeyfood.vsnd || goto :failed
wav2vircon assets\sound\common\coin.wav -o obj\commoncoin.vsnd || goto :failed
wav2vircon assets\sound\common\die.wav -o obj\commondie.vsnd || goto :failed
wav2vircon assets\sound\common\one.wav -o obj\commonone.vsnd || goto :failed
wav2vircon assets\sound\common\oneminute.wav -o obj\commononeminute.vsnd || goto :failed
wav2vircon assets\sound\common\readygo.wav -o obj\commonreadygo.vsnd || goto :failed
wav2vircon assets\sound\common\succes.wav -o obj\commonsucces.vsnd || goto :failed
wav2vircon assets\sound\common\three.wav -o obj\commonthree.vsnd || goto :failed
wav2vircon assets\sound\common\timeover.wav -o obj\commontimeover.vsnd || goto :failed
wav2vircon assets\sound\common\two.wav -o obj\commontwo.vsnd || goto :failed
wav2vircon assets\sound\main\back.wav -o obj\mainback.vsnd || goto :failed
wav2vircon assets\sound\main\confirm.wav -o obj\mainconfirm.vsnd || goto :failed
wav2vircon assets\sound\main\score.wav -o obj\mainscore.vsnd || goto :failed
wav2vircon assets\sound\main\select.wav -o obj\mainselect.vsnd || goto :failed


echo.
echo Pack the ROM
echo --------------------------
packrom Retrotime.xml -o "bin\Retrotime.v32" || goto :failed
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