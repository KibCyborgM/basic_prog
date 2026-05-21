@echo off
setlocal enabledelayedexpansion

set "CHOICE=%~1"

if "!CHOICE!"=="" (
    echo Using:
    echo   1 - not_refactored
    echo   2 - refactored
    echo   3 - OOP
    set /p "CHOICE=Select version (1/2/3): "
)

if "!CHOICE!"=="1" set "DIR=not_refactored"
if "!CHOICE!"=="2" set "DIR=refactored"
if "!CHOICE!"=="3" set "DIR=OOP"

set "SRC=!DIR!\!DIR!.cpp"
set "OUT=!DIR!\SuperMario.exe"

if "!DIR!"=="OOP" (
    set "SRC=!DIR!\main.cpp !DIR!\level.cpp !DIR!\objects.cpp !DIR!\engine.cpp"
    set "OUT=!DIR!\SuperMario.exe"
)

g++ -o "!OUT!" !SRC!

if !errorlevel! neq 0 (
    echo Not compiled :(
    pause
    exit /b 1
)


"!OUT!"