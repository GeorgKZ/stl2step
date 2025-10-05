@ECHO OFF

CALL "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

CD ..\build_scripts
CHCP 65001 > NUL
cmake -P 1_clean_config.cmake
CHCP 866 > NUL
