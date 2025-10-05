@ECHO OFF

CD ..\build_scripts
CHCP 65001 > NUL
cmake -P 4_build-docs_html.cmake
CHCP 866 > NUL
