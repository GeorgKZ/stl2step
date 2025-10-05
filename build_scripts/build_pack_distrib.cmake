##############################################################################
# Упаковка сборки
##############################################################################

  # Выполнить установку конфигурации для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_BLD "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_pack.txt")
  file(REMOVE "${BUILDDIR}/log_pack_errors.txt")

  # Выполнить упаковку
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --build ${CMAKEDIR}
    ${CMAKE_BLD}
    --target package
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_pack.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_pack_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Упаковка дистрибутива успешно завершена.")
  else()
      message(FATAL_ERROR "Упаковка дистрибутива завершена с ошибкой ${result}. Выход.")
  endif()
