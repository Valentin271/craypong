@echo off

set RAYLIB_SRC_PATH="..\raylib\src"

REM Get current working directory
set PROJECT_DIR=%cd%
set BUILD_DIR="build\craypong_win"

REM Build raylib for desktop
cd %RAYLIB_SRC_PATH%
mingw32-make.exe clean
mingw32-make.exe PLATFORM=PLATFORM_DESKTOP --always-make --jobs

REM Build project
cd %PROJECT_DIR%
mingw32-make.exe clean
mingw32-make.exe PLATFORM=PLATFORM_DESKTOP --always-make --jobs


REM Recreate build dir
REM /S remove subdirs and files
REM /Q quiet, no confirmation
rd /S /Q %BUILD_DIR%
mkdir %BUILD_DIR%

REM Move build files and resources to build dir
move /Y craypong.exe %BUILD_DIR%
xcopy /E /I /Y resources %BUILD_DIR%\resources\