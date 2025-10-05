##############################################################################
# Установка
##############################################################################

  # Выполнить установку конфигурации для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_INSTALL_CONFIG "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_install.txt")
  file(REMOVE "${BUILDDIR}/log_install_errors.txt")
  file(REMOVE "${BUILDDIR}/log_spack.txt")
  file(REMOVE "${BUILDDIR}/log_spack_errors.txt")
  file(REMOVE "${BUILDDIR}/log_pack.txt")
  file(REMOVE "${BUILDDIR}/log_pack_errors.txt")

  # Выполнить установку
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --install ${CMAKEDIR}
    ${CMAKE_INSTALL_CONFIG}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_install.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_install_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Установка успешно завершена.")
  else()
      message(FATAL_ERROR "Установка завершена с ошибкой ${result}. Выход.")
  endif()
