set PATH=%PATH%;C:\Program Files\MiKTeX\miktex\bin\x64\;D:\Program Files\MiKTeX\miktex\bin\x64\;C:\Program Files\doxygen\bin\;C:\Program Files\Graphviz\bin;D:\Program Files\Graphviz\bin;

call clean.bat

@doxygen.exe stl2step.Doxyfile

@for /F %%A in ("warnings.log") do @If %%~zA equ 0 del warnings.log
