@echo off

REM Version 1.1

set W_RAYLIB_SRC_PATH="..\raylib\src"

REM Get current working directory
set W_PROJECT_NAME=craypong
set W_PROJECT_DIR=%cd%
set W_BUILD_DIR="build\%W_PROJECT_NAME%_win"

REM Build raylib for desktop
cd %W_RAYLIB_SRC_PATH%
mingw32-make.exe clean
mingw32-make.exe PLATFORM=PLATFORM_DESKTOP --always-make --jobs

REM Build project
cd %W_PROJECT_DIR%
mingw32-make.exe clean
mingw32-make.exe PLATFORM=PLATFORM_DESKTOP BUILD_MODE=RELEASE --always-make --jobs


REM Recreate build dir
REM /S remove subdirs and files
REM /Q quiet, no confirmation
rd /S /Q %W_BUILD_DIR%
mkdir %W_BUILD_DIR%

REM Move build files and resources to build dir
move /Y %W_PROJECT_NAME%.exe %W_BUILD_DIR%
xcopy /E /I /Y resources %W_BUILD_DIR%\resources\