@echo off
setlocal EnableDelayedExpansion

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja
set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

chcp 65001

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G "%BUILD_TYPE%" ..\%SOURCE_FOLDER%

cmake --build .

copy ..\run_tests.bat .