##############################################################################
# Установка компилятора
##############################################################################

  # Сборка под ОС Windows
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
      # Компиляция с Microsoft Visual Studio для Windows x86_64 (64битное приложение)
#     execute_process(COMMAND "C:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Auxiliary/Build/vcvars64.bat")
      execute_process(COMMAND "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat")
  # Сборка под ОС Linux
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
      if(DEFINED MINGW32)
          # Кросскомпиляция с MinGW для Windows i686 (32битное приложение)
         set(COMPILER
           "-DCMAKE_SYSTEM_NAME:STRING=Windows"
           "-DCMAKE_C_COMPILER:FILEPATH=i686-w64-mingw32-gcc-posix"
           "-DCMAKE_CXX_COMPILER:FILEPATH=i686-w64-mingw32-g++-posix"
           "-DCMAKE_RC_COMPILER:FILEPATH=i686-w64-mingw32-windres"
           "-DCMAKE_FIND_ROOT_PATH:PATH=/usr/i686-w64-mingw32"
         )
      elseif(DEFINED MINGW64)
          # Кросскомпиляция с MinGW для Windows x86_64 (64битное приложение)
         set(COMPILER
           "-DCMAKE_SYSTEM_NAME=Windows"
           "-DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc-posix"
           "-DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++-posix"
           "-DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres"
           "-DCMAKE_FIND_ROOT_PATH=/usr/x86_64-w64-mingw32"
         )
      elseif(DEFINED CLANG)
          # Компиляция с Clang для Linux x86_64 (64битное приложение)
          set(COMPILER "-DCMAKE_CXX_COMPILER=clang++")
      else()
          # Компиляция с GNU GCC для Linux x86_64 (64битное приложение)
          set(COMPILER "-DCMAKE_CXX_COMPILER=g++")
      endif()
  # Сборка под ОС macOS / OS X
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
      # Компиляция с Clang для macOS / OS X
      set(COMPILER "-DCMAKE_CXX_COMPILER=clang++")
  endif()
