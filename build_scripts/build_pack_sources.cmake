##############################################################################
# Упаковка исходных текстов
##############################################################################

  # Выполнить установку конфигурации для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_BLD "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_spack.txt")
  file(REMOVE "${BUILDDIR}/log_spack_errors.txt")

  # Выполнить упаковку исходных текстов
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --build ${CMAKEDIR}
    ${CMAKE_BLD}
    --target package_source
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_spack.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_spack_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Упаковка исходных текстов успешно завершена.")
  else()
      message(FATAL_ERROR "Упаковка исходных текстов завершена с ошибкой ${result}. Выход.")
  endif()
