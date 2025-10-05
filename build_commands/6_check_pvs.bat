@ECHO OFF

CD ..\build_scripts
CHCP 65001 > NUL
cmake -P 5_check_pvs.cmake
CHCP 866 > NUL
