##############################################################################
# Построение документации в формате HTML
##############################################################################

  # Установить конфигурацию для мультиконфигурационного варианта этапа сборки
  if( (DEFINED MULTICONFIG) AND (MULTICONFIG GREATER 0) )
      set(CMAKE_BLD "--config ${CONFIG}")
  endif()

  file(REMOVE "${BUILDDIR}/log_hdoc.txt")
  file(REMOVE "${BUILDDIR}/log_hdoc_errors.txt")

  # Выполнить построение документации в формате HTML
  execute_process(
    COMMAND ${CMAKE_COMMAND}
    --build ${CMAKEDIR}
    ${CMAKE_BLD}
    --target html_doc
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output_error
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
  )
  file(WRITE "${BUILDDIR}/log_hdoc.txt" "${output}")
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_hdoc_errors.txt" "${output_error}")
  endif()
  if (result EQUAL 0)
      message(STATUS "Построение и установка документации HTML успешно завершено.")
  else()
      message(FATAL_ERROR "Построение документации HTML завершено с ошибкой ${result}. Выход.")
  endif()
