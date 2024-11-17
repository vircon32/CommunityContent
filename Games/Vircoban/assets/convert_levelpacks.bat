@echo off
REM Enable delayed variable expansion
setlocal enabledelayedexpansion

REM Change to the directory where the script is located
cd /d "%~dp0"

REM Create the output directory if it doesn't exist
mkdir levelpacks

REM Loop through all *.lev files in the levels_original directory
for %%f in (levelpacks_orig\*.sok) do (
    REM Extract the file name without path
    set "filename=%%~nf"
    
    REM Set the input and output file paths
    set "input_file=%%f"
    set "output_file=levelpacks\!filename!.sok"
    
    REM Run the Python script with the input and output file paths
    python3 convert_file.py "!input_file!" "!output_file!" "38000"
)

echo All files have been converted.
pause