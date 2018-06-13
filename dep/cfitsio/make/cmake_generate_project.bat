@echo OFF

set CMAKE_EXE="C:\Program Files\CMake\bin\cmake.exe"
set CMAKE_SOURCE_DIR=%~dp0..\
set CMAKE_BIN_DIR=%~dp0..\projects\

set ValueName=
set VSVersion=%~1

set Platform=%~2
if "%Platform%"=="" (
	set Platform=Win64
)

set BuildDir="%CMAKE_BIN_DIR%"

if not exist "%BuildDir%" (
	mkdir "%BuildDir%"
)

set CMAKE_COMMAND=%CMAKE_EXE% -G

:: If nothing specified, try to setup 2017 by default
if "%VSVersion%"=="" (
	set VSVersion=vs2017
)

if exist "%BuildDir%\%VSVersion%" (
	@RD /S /Q "%BuildDir%\%VSVersion%"
)

mkdir "%BuildDir%\%VSVersion%"

echo # Generate CFITSIO "%VSVersion%" "%Platform%" with cmake.

if %VSVersion%==vs2015 goto :generatevs2015
if %VSVersion%==vs2017 goto :generatevs2017

:generatevs2017
set CMAKE_COMMAND=%CMAKE_COMMAND% "Visual Studio 15 2017 %Platform%"

:generatevs2015
set CMAKE_COMMAND=%CMAKE_COMMAND% "Visual Studio 14 2015 %Platform%"

:: 

set CMAKE_COMMAND=%CMAKE_COMMAND% -DCMAKE_SOURCE_DIR=%CMAKE_SOURCE_DIR% -DCMAKE_BINARY_DIR=%CMAKE_BIN_DIR% %CMAKE_SOURCE_DIR%
@echo CMAKE_COMMAND = %CMAKE_COMMAND%

pushd "%BuildDir%\%VSVersion%"
call %CMAKE_COMMAND%
popd