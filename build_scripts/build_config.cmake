##############################################################################
# Конфигурирование
##############################################################################

  # Подготовить параметр "генератор"
  if( (DEFINED GENERATOR) AND (NOT "^^${GENERATOR}" STREQUAL "^^") )
      set(GENERATOR_STRING "-G ${GENERATOR}")
  else()
      message(STATUS "BuildClean: Генератор не указан, будет использовано значение по умолчанию")
  endif()

  # Подготовить параметр "уровень детализации"
  if( (DEFINED LOGLEVEL) AND (NOT "^^${LOGLEVEL}" STREQUAL "^^") )
      set(LOGLEVEL_STRING "--log-level=${LOGLEVEL}")
  else()
      message(STATUS "BuildClean: Уровень детализации сообщений не указан, будет использовано значение по умолчанию")
  endif()

  # Установить конфигурацию для не мультиконфигурационного варианта этапа конфигурирования
  if( (NOT DEFINED MULTICONFIG) OR (MULTICONFIG EQUAL 0) )
      set(CMAKE_CNF "-DCMAKE_BUILD_TYPE:STRING=${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_config.txt")
  file(REMOVE "${BUILDDIR}/log_config_errors.txt")
  file(REMOVE "${BUILDDIR}/log_build.txt")
  file(REMOVE "${BUILDDIR}/log_build_errors.txt")
  file(REMOVE "${BUILDDIR}/log_install.txt")
  file(REMOVE "${BUILDDIR}/log_install_errors.txt")
  file(REMOVE "${BUILDDIR}/log_spack.txt")
  file(REMOVE "${BUILDDIR}/log_spack_errors.txt")
  file(REMOVE "${BUILDDIR}/log_pack.txt")
  file(REMOVE "${BUILDDIR}/log_pack_errors.txt")

  # Выполнить конфигурирование
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    ${COMPILER}
    ${LOGLEVEL_STRING}
    ${CMAKE_CNF}
    ${GENERATOR_STRING}
    -S ${SOURCEDIR}
    -B ${CMAKEDIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_config.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_config_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Config: Конфигурирование успешно завершено.")
  else()
      message(FATAL_ERROR "Config: Конфигурирование завершено с ошибкой ${result}. Выход.")
  endif()
