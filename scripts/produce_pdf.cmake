##############################################################################
# Скрипт создания и установки файла документации pdf
# Аргументы:
# SRC_DOC_PATH
# DOC_PATH - директория для собираемых файлов документации
# INST_DOC_PATH - директория для устанавливаемых файлов документации
# INST_DOC_FILE - имя устанавливаемого файла документации
##############################################################################

# Удалить файл warnings.log, если он нулевой длины
if(EXISTS "${DOC_PATH}/warnings.log")
    file(SIZE "${DOC_PATH}/warnings.log" FILE_SIZE)
    if(FILE_SIZE EQUAL 0)
        file(REMOVE "${DOC_PATH}/warnings.log")
    endif()
endif()

if(EXISTS "${SRC_DOC_PATH}/images")
    file(COPY "${SRC_DOC_PATH}/images" DESTINATION "${DOC_PATH}/latex")
endif()

# Выполнить создание файла документации pdf
execute_process(
  WORKING_DIRECTORY "${DOC_PATH}/latex"
  COMMAND "make"
  RESULT_VARIABLE result
  OUTPUT_VARIABLE output
  ERROR_VARIABLE  output_error
)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Ошибка выполнения скрипта produce_pdf: ${output_error}")
endif()

# При отсутствии создать директорию установки документации
if(NOT EXISTS "${INST_DOC_PATH}")
    file(MAKE_DIRECTORY "${INST_DOC_PATH}")
endif()

# Скопировать файл документации pdf в директорию установки
file(COPY_FILE "${DOC_PATH}/latex/refman.pdf" "${INST_DOC_PATH}/manual.pdf")
