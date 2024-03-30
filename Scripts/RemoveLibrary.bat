@echo off
REM Change to the parent directory
cd ..

REM Change to the Engine directory
cd Engine

REM Remove library directory with subdirectories
rd /s /q "%1"

echo Removed %1 library.