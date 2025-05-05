@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile FlappyBird_Vircon32.c -o obj\FlappyBird_Vircon32.asm || goto :failedcomp

echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\FlappyBird_Vircon32.asm -o obj\FlappyBird_Vircon32.vbin || goto :failedass

echo.
echo Pack the ROM
echo --------------------------
packrom FlappyBird_Vircon32.xml -o bin\FlappyBird_Vircon32.v32 || goto :failedbuild
goto :succeeded

:failedcomp
echo.
echo COMPILATION FAILED
exit /b %errorlevel%

:failedass
echo.
echo ASSEMBLY FAILED
exit /b %errorlevel%

:failedbuild
echo.
echo BUILD FAILED
exit /b %errorlevel%

:succeeded
echo.
echo BUILD SUCCESSFUL
exit /b

@echo on