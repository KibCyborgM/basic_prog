@echo off
setlocal


if not exist "build" mkdir build
cd build

cmake .. -G "Ninja"


cmake --build .


ctest --output-on-failure