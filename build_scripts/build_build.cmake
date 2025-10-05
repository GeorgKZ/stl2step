##############################################################################
# Сборка
##############################################################################

  # Установить конфигурацию для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_BLD "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_build.txt")
  file(REMOVE "${BUILDDIR}/log_build_errors.txt")
  file(REMOVE "${BUILDDIR}/log_install.txt")
  file(REMOVE "${BUILDDIR}/log_install_errors.txt")
  file(REMOVE "${BUILDDIR}/log_spack.txt")
  file(REMOVE "${BUILDDIR}/log_spack_errors.txt")
  file(REMOVE "${BUILDDIR}/log_pack.txt")
  file(REMOVE "${BUILDDIR}/log_pack_errors.txt")

  # Выполнить построение исполняемого файла
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --build ${CMAKEDIR}
    ${CMAKE_BLD}
    --parallel
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_build.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_build_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Build: Построение успешно завершено.")
  else()
      message(FATAL_ERROR "Build: Построение завершено с ошибкой ${result}. Выход.")
  endif()
