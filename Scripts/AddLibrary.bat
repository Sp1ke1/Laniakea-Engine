@echo off
setlocal enabledelayedexpansion

goto MainScript

:ToUpper
set "str=%~1"

for %%i in (A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
    set "str=!str:%%i=%%i!"
)

set "result=!str!"
goto :eof



:MainScript

IF "%1"=="" (
    echo Usage: .\AddLibrary ^<LibraryName^>
    exit
)

set "LIB_NAME=%1"
call :ToUpper "%LIB_NAME%"
set "LIB_NAME_UPPER=%result%"

REM Change to the parent directory
cd ..

REM Change to the Engine directory
cd Engine

REM Create and change to library directory
mkdir %LIB_NAME%

cd %LIB_NAME%

REM Create the directories. %1 represents the first argument passed to the script.
mkdir Include\Laniakea\%LIB_NAME%
mkdir Source
mkdir Test

echo Created directories.

REM Push boilerplate into CMakeLists file.
echo file ( GLOB_RECURSE LANIAKEA_%LIB_NAME_UPPER%_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Include/*.h") > CMakeLists.txt
echo file ( GLOB_RECURSE LANIAKEA_%LIB_NAME_UPPER%_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Source/*.cpp") >> CMakeLists.txt
echo # Add Library >> CMakeLists.txt
echo set (LANIAKEA_%LIB_NAME_UPPER%_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/" )  >> CMakeLists.txt
echo add_library (Laniakea-%LIB_NAME% SHARED ${LANIAKEA_%LIB_NAME_UPPER%_SOURCE})  >> CMakeLists.txt
echo target_include_directories( Laniakea-%LIB_NAME% PUBLIC ${LANIAKEA_%LIB_NAME_UPPER%_INCLUDE_DIR} )  >> CMakeLists.txt
echo target_link_libraries ( Laniakea-%LIB_NAME% )  >> CMakeLists.txt
echo # Add tests >> CMakeLists.txt
echo add_executable( Test-%1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/Test_%LIB_NAME%.cpp)  >> CMakeLists.txt
echo target_compile_definitions ( Test-%LIB_NAME% PRIVATE ${LANIAKEA_DEFINITIONS} )  >> CMakeLists.txt
echo target_compile_options( Test-%LIB_NAME% PRIVATE ${LANIAKEA_CXX_FLAGS} )  >> CMakeLists.txt
echo target_link_libraries (Test-%LIB_NAME% PRIVATE gtest Laniakea-%LIB_NAME% )  >> CMakeLists.txt
echo enable_testing() >> CMakeLists.txt
echo add_test ( "%LIB_NAME% test"^ Test-%LIB_NAME% ) >> CMakeLists.txt

echo Created CMake file.

REM Push windows specifier definition into Core.h file.
cd Include\Laniakea\%LIB_NAME%
echo #ifdef LANIAKEA_PLATFORM_WINDOWS > Core.h
echo     #ifdef LANIAKEA_BUILD_DLL >> Core.h
echo         #define LANIAKEA_%LIB_NAME_UPPER%_API __declspec (dllexport) >> Core.h
echo     #else >> Core.h
echo         #define LANIAKEA_%LIB_NAME_UPPER%_API __declspec(dllimport) >> Core.h
echo     #endif >> Core.h
echo #else >> Core.h
echo     #error Laniakea supports only windows >> Core.h
echo #endif >> Core.h
cd ..\..\..

echo Created library Core.h macro file.

REM Create library files
cd Include\Laniakea\%LIB_NAME%
echo #pragma once > %LIB_NAME%.h
cd ..\..\..
cd Source\
echo #include "Laniakea/%1/%1.h" > %LIB_NAME%.cpp
cd ..\

echo Created library empty .cpp and .h files.

REM Create test file
cd Test
echo #include "gtest/gtest.h" > Test_%LIB_NAME%.cpp
echo: >> Test_%LIB_NAME%.cpp
echo: >> Test_%LIB_NAME%.cpp
echo int main ( int argc, char ** argv ) >> Test_%LIB_NAME%.cpp
echo { >> Test_%LIB_NAME%.cpp
echo 	testing::InitGoogleTest( ^&argc, argv ); >> Test_%LIB_NAME%.cpp
echo 	return RUN_ALL_TESTS(); >> Test_%LIB_NAME%.cpp
echo } >> Test_%LIB_NAME%.cpp

echo Created library Test_%LIB_NAME%.cpp file.

echo ---- Created %LIB_NAME% library successfully ----