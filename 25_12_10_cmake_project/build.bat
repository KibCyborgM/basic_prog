@echo off
setlocal EnableDelayedExpansion

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

copy ..\%SOURCE_FOLDER%\multiple_level_menu\run_multiple_menu.bat .\multiple_menu
copy ..\%SOURCE_FOLDER%\merge_sort\run_app.bat .\merge_sort

copy ..\run_tests.bat .