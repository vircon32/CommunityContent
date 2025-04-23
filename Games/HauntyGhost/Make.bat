@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Assemble the ASM code
echo --------------------------
assemble HauntyGhost.asm            -o obj\HauntyGhost.vbin   || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\alpha.png         -o obj\alpha.vtex         || goto :failed
png2vircon assets\bottomBorder.png  -o obj\bottomBorder.vtex  || goto :failed
png2vircon assets\brickBackani1.png -o obj\brickBackani1.vtex || goto :failed
png2vircon assets\brickBackani2.png -o obj\brickBackani2.vtex || goto :failed
png2vircon assets\brickBackani3.png -o obj\brickBackani3.vtex || goto :failed
png2vircon assets\mainMenuani1.png  -o obj\mainMenuani1.vtex  || goto :failed
png2vircon assets\mainMenuani2.png  -o obj\mainMenuani2.vtex  || goto :failed
png2vircon assets\mainMenuani3.png  -o obj\mainMenuani3.vtex  || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom HauntyGhost.xml             -o bin\HauntyGhost.v32    || goto :failed
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
