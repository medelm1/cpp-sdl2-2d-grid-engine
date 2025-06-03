@echo off

REM Batch Script to Compile or Run the C++ Project

REM === Configuration ===
set OUTPUT_NAME=g2de
set SOURCE_DIR=src
set SOURCE_FILES=%SOURCE_DIR%\*.cpp ^
				%SOURCE_DIR%\game\*.cpp ^
				%SOURCE_DIR%\systems\audio\*.cpp ^
				%SOURCE_DIR%\systems\input\*.cpp ^
				%SOURCE_DIR%\utils\*.cpp

set BUILD_DIR=build
set THIRD_PARTY_DIR=third_party
set INCLUDE_DIRS=-I%SOURCE_DIR% -I%THIRD_PARTY_DIR%\SDL2\include -L%THIRD_PARTY_DIR%\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
set CPP_FLAGS=-std=c++17
set EXE_PATH=%BUILD_DIR%\%OUTPUT_NAME%.exe

REM === Parse First Argument ===
set COMMAND=%1
shift

REM === Commands
if "%COMMAND%"=="compile" (
	call :compile
	goto :eof
) else if "%COMMAND%"=="run" (
	if not exist "%EXE_PATH%" (
		echo Executable not found. Compiling first...
		call :compile
		if not exist "%EXE_PATH%" goto :eof
	)
	echo Running program...
	"%EXE_PATH%" %*
	goto :eof
) else if "%COMMAND%"=="rebuild" (
	call :clean
	call :compile
	goto :eof
) else if "%COMMAND%"=="clean" (
	call :clean
	goto :eof
) else if "%COMMAND%"=="help" (
	goto :usage
) else (
	echo Invalid or missing command.
	goto :usage
)

:compile
	echo Compiling project...
	if not exist "%BUILD_DIR%" (
		mkdir "%BUILD_DIR%"
	)
	g++ %SOURCE_FILES% -o "%EXE_PATH%" %INCLUDE_DIRS% %CPP_FLAGS%
	if %ERRORLEVEL%==0 (
		echo Compilation successful
	) else (
		echo Compilation failed
	)
	goto :eof

:clean
	echo Cleaning project...
	if exist "%BUILD_DIR%" (
		rmdir /s /q "%BUILD_DIR%"
		echo Build directory removed.
	) else (
		echo Nothing to clean.
	)
	goto :eof

:usage
	echo Usage:
	echo script.bat compile        - compile the project
	echo script.bat run            - Run the executable
	echo script.bat rebuild        - Clean and recompile
	echo script.bat clean          - Delete build directory
	echo help.bat help             - Show this help message
	goto :eof