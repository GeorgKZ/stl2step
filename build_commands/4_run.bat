@ECHO OFF

CD ..\build_scripts
CHCP 65001 > NUL
cmake -P 3_run.cmake
CHCP 866 > NUL
