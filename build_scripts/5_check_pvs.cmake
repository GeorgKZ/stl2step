##############################################################################
# Настройка требуемой версии CMake
##############################################################################

  cmake_minimum_required(VERSION 3.9...3.28)

##############################################################################
# Настройка параметров сборки
##############################################################################

  # Использовать модуль установки генератора для CMAKE
  include(build_set_generator.cmake)

  # Использовать модуль установки конфигурации
  include(build_set_config.cmake)

  # Использовать модуль установки уровня детализации сообщений сборки
  include(build_set_loglevel.cmake)

##############################################################################
# Настройка окружения
##############################################################################

  # Использовать модуль установки пути к исходным текстам
  include(build_set_source.cmake)

  # Использовать модуль установки директории для сборки и файлов CMAKE
  include(build_set_builddir.cmake)

  # Использовать модуль установки компилятора
  include(build_set_compiler.cmake)

  # Использовать модуль установки пути к требуемой версии Qt
  include(build_set_qt.cmake)

##############################################################################
# Статический анализ при помощи PVS-Studio
##############################################################################

  # Установить конфигурацию для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_BLD "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_pvs.txt")
  file(REMOVE "${BUILDDIR}/log_pvs_errors.txt")

  # Выполнить статический анализ
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --build ${CMAKEDIR}
    ${CMAKE_BLD}
    --target analyze
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_pvs.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_pvs_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Статический анализ успешно завершён.")
  else()
      message(FATAL_ERROR "Статический анализ завершён с ошибкой ${result}. Выход.")
  endif()
