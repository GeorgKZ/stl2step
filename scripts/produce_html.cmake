##############################################################################
# Скрипт установки файлов документации html
# Аргументы:
# DOC_PATH - директория для собираемых файлов документации
# INST_DOC_PATH - директория для устанавливаемых файлов документации
# SOURCE_DOC_DIR - директория для исходных файлов документации
# MATH_PATH - директория с установленным MathJax
##############################################################################

# Удалить файл warnings.log, если он нулевой длины
if(EXISTS "${DOC_PATH}/warnings.log")
    file(SIZE "${DOC_PATH}/warnings.log" FILE_SIZE)
    if(FILE_SIZE EQUAL 0)
        file(REMOVE "${DOC_PATH}/warnings.log")
    endif()
endif()

# При отсутствии создать директорию установки документации
if(NOT EXISTS "${INST_DOC_PATH}/manual")
    file(MAKE_DIRECTORY "${INST_DOC_PATH}/manual")
endif()

# Скопировать директорию документации html в директорию установки документации html
file(COPY "${DOC_PATH}/html/" DESTINATION "${INST_DOC_PATH}/manual")

# Скопировать бейджи в директорию установки документации html
file(COPY "${SOURCE_DOC_DIR}/badges/" DESTINATION "${INST_DOC_PATH}/manual/doc/badges" FILES_MATCHING PATTERN "*.svg" )

if(EXISTS "${MATH_PATH}")
    # Скопировать директорию MathJax в директорию установки документации html
    file(COPY "${MATH_PATH}/" DESTINATION "${INST_DOC_PATH}/manual/es5")
endif()
