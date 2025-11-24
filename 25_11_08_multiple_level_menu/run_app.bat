@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp menu_functions.cpp"
set EXE=multiple_menu.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" "%CPP_FILES%" -o "%EXE%"

%EXE%