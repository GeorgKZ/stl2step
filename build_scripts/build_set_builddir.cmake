##############################################################################
# Установка директории для сборки и файлов CMAKE
##############################################################################

  # Получаем текущую директорию
  get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
  # Получаем имя родительской директории - имя проекта
  get_filename_component(PARENT_DIR_NAME ${CURRENT_DIR} NAME)
  # Имя проекта, приведённое к нижнему регистру
  string(TOLOWER ${PARENT_DIR_NAME} PROJ_NAME)

  # для MacOS
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
      # Установить имя виртуального RAM-диска
      set(DISKNAME "RAM_Disk")

      # Установить корневую директорию сборки
      set(ROOTDIR "/Volumes/${DISKNAME}")

      # Создать RAM-диск
      if(NOT EXISTS "${ROOTDIR}")

          execute_process(COMMAND
            hdiutil attach -nomount ram://10000000
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE  output_error
          )
          # Проверить код завершения
          if(NOT result STREQUAL "0")
              message(FATAL_ERROR "Программа hdiutil завершилась с ошибкой: ${result}\n${output_error}")
          endif()

          string(REGEX REPLACE "[ \r\n\t]+" "" output1 "${output}")

          execute_process(COMMAND
            diskutil eraseVolume HFS+ ${DISKNAME} ${output1}
            RESULT_VARIABLE result2
            OUTPUT_VARIABLE output2
            ERROR_VARIABLE  output2_error
          )
          # Проверить код завершения
          if(NOT result2 STREQUAL "0")
              message(FATAL_ERROR "Программа diskutil завершилась с ошибкой: ${result2}\n${output2_error}")
          endif()
      endif()
      # Установить директорию сборки
      set(BUILDDIR "${ROOTDIR}/build_svgtoraster")
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
      # Установить корневую директорию сборки
      set(ROOTDIR "T:")
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
      # Установить корневую директорию сборки
      set(ROOTDIR "/var/tmp")

      # mkdir /cache
      # chmod 777 /cache
      # mount -t tmpfs -o size=1024M tmpfs /cache
  endif()

  # Установить директорию сборки
  set(BUILDDIR "${ROOTDIR}/build_${PROJ_NAME}")

  # Установить директорию сборки для файлов CMAKE
  set(CMAKEDIR "${BUILDDIR}/cmake")

  # Сохранить директории в переменных окружения
  set(ENV{BUILDDIR} "${BUILDDIR}")
  set(ENV{CMAKEDIR} "${CMAKEDIR}")
