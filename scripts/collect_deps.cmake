##############################################################################
# Скрипт формирования набора файлов-зависимостей в директории ${FOUND_DEPS_PATH}
# для списка файлов ${MISC_PATH}/${ARGUMENT}
##############################################################################

include("${ROOT_DIR}/scripts/get_file_deps.cmake")

# Функция, выполняющая установку во временную директорию
# указанной библиотеки и её зависимостей
function(install_library_with_deps NAME PROCESSED_LIST)

    # Проверить, может эта библиотека уже обработана
    list(FIND PROCESSED_LIST "${NAME}" INDEX)
    if(NOT (INDEX EQUAL -1))
        return()
    endif()
    list(APPEND PROCESSED_LIST ${NAME})
    set(PROCESSED_LIST ${PROCESSED_LIST} PARENT_SCOPE)

    set(framework 0)

    # Проверить, может это библиотека из указанного Qt
    if(EXISTS "${QT_DIR}/../../${NAME}")
        set(PATH_TO_NAME "${QT_DIR}/../..")
#       message(STATUS "FOUND Qt library ${NAME}")

    elseif(EXISTS "${QT_DIR}/../../../bin/${NAME}")
        set(PATH_TO_NAME "${QT_DIR}/../../../bin")
#       message(STATUS "FOUND Qt library ${NAME}")

    # Проверить, может это фреймворк из указанного Qt
    elseif(EXISTS "${QT_DIR}/../../${NAME}.framework")
        set(PATH_TO_NAME "${QT_DIR}/../..")
#       message(STATUS "FOUND Qt framework ${NAME}")
        set(framework 1)

    # Проверить, может это библиотека приложения
    elseif(EXISTS "${FIND_DEPS_PATH}/${NAME}")
        set(PATH_TO_NAME "${FIND_DEPS_PATH}")
#       message(STATUS "FOUND application library ${NAME}")

    # !!!
    # Проверить, может это системная библиотека приложения
    elseif((EXISTS "/lib/${NAME}") OR (EXISTS "/lib/x86_64-linux-gnu/${NAME}"))
#       message(STATUS "FOUND system library ${NAME}")
        return()

    # Проверить, может такая библиотека уже найдена, тогда ничего не делать
    elseif((EXISTS "${FOUND_DEPS_PATH}/${NAME}") OR (EXISTS "${FOUND_DEPS_PATH}/${NAME}.framework"))
#       message(STATUS "SKIPPED founded library ${NAME}")
        return(PROPAGATE PROCESSED_LIST)
        return()

    else()

        message(STATUS "Не удалось определить расположение библиотеки ${NAME}")
        return()

    endif()

    set(PATH_WITH_NAME "${PATH_TO_NAME}/${NAME}")

    # Скопировать фреймворк в директорию найденных библиотек
    if(${framework})
        file(COPY "${PATH_WITH_NAME}.framework/Versions/A/Resources"
          DESTINATION "${FOUND_DEPS_PATH}/${NAME}.framework/Versions/A"
        )
        file(COPY "${PATH_WITH_NAME}.framework/Versions/A/${NAME}"
          DESTINATION "${FOUND_DEPS_PATH}/${NAME}.framework/Versions/A"
        )
        file(COPY "${PATH_WITH_NAME}.framework/Versions/Current"
          DESTINATION "${FOUND_DEPS_PATH}/${NAME}.framework/Versions"
        )
        file(COPY "${PATH_WITH_NAME}.framework/Resources"
          DESTINATION "${FOUND_DEPS_PATH}/${NAME}.framework"
        )
        file(COPY "${PATH_WITH_NAME}.framework/${NAME}"
          DESTINATION "${FOUND_DEPS_PATH}/${NAME}.framework"
        )
    # Скопировать библиотеку в директорию найденных библиотек
    else()
        file(COPY
          "${PATH_WITH_NAME}"
          DESTINATION "${FOUND_DEPS_PATH}"
        )
    endif()

    # Эта зависимотсь - символическиая ссылка
    if(IS_SYMLINK ${PATH_WITH_NAME})
        # Повотрить процедуру для файла, на который указывает эта сылка.
        file(READ_SYMLINK ${PATH_WITH_NAME} SYM_FILE)
        get_filename_component(SYM_FILE_NAME "${SYM_FILE}" NAME)
        install_library_with_deps("${SYM_FILE_NAME}" "${PROCESSED_LIST}")
        set(PROCESSED_LIST ${PROCESSED_LIST} PARENT_SCOPE)
        return()
    endif()

#   message(STATUS "2) Поиск зависимостей для ${PATH_WITH_NAME}")

    if(framework)
        get_prerequisites("${PATH_WITH_NAME}.framework/Versions/A/${NAME}" FOUND_DEPS)
    else()
        get_prerequisites("${PATH_WITH_NAME}" FOUND_DEPS)
    endif()
#   message(STATUS "2X) FOUND: ${FOUND_DEPS}")

    # Перебрать все зависимости, для каждой повторить процедуру
    foreach(FILE ${FOUND_DEPS})
        install_library_with_deps("${FILE}" "${PROCESSED_LIST}")
    endforeach()

    set(PROCESSED_LIST ${PROCESSED_LIST} PARENT_SCOPE)
endfunction()



# Список обработанных библиотек
set(PROCESSED_LIST "")

# Прочитать из файла список файлов, для которых ищется завивимость
file(READ "${MISC_PATH}/${ARGUMENT}" LIST)
foreach(F ${LIST})
 #  message(STATUS "1) Поиск зависимостей для ${F}")
    get_prerequisites("${F}" FOUND_DEPS)

    foreach(FILE ${FOUND_DEPS})
        install_library_with_deps("${FILE}" "${PROCESSED_LIST}")
    endforeach()

endforeach()
