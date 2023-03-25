set PATH=%PATH%;C:\Program Files\MiKTeX\miktex\bin\x64\;D:\Program Files\MiKTeX\miktex\bin\x64\;C:\Program Files\doxygen\bin\;C:\Program Files\Graphviz\bin;D:\Program Files\Graphviz\bin;

call make_html.bat

@call output\latex\make.bat
@copy output\latex\refman.pdf ..\
