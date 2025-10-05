# 2006-2008 (c) Viva64.com Team
# 2008-2020 (c) OOO "Program Verification Systems"
# 2020-2022 (c) PVS-Studio LLC
# Version 12

cmake_minimum_required(VERSION 3.0.0...3.25)
cmake_policy(SET CMP0054 NEW)

if (PVS_STUDIO_AS_SCRIPT)
    # This code runs at build time.
    # It executes pvs-studio-analyzer and propagates its return value.

    set(in_cl_params FALSE)
    set(additional_args)

    foreach (arg ${PVS_STUDIO_COMMAND})
        if (NOT in_cl_params)
            if ("${arg}" STREQUAL "--cl-params")
                set(in_cl_params TRUE)
            endif()
        else()
            # A workaround for macOS frameworks (e.g. QtWidgets.framework)
            # You can test this workaround on this project: https://github.com/easyaspi314/MidiEditor/tree/gba
            if (APPLE AND "${arg}" MATCHES "^-I(.*)\\.framework$")
                STRING(REGEX REPLACE "^-I(.*)\\.framework$" "\\1.framework" framework "${arg}")
                if (IS_ABSOLUTE "${framework}")
                    get_filename_component(framework "${framework}" DIRECTORY)
                    list(APPEND additional_args "-iframework")
                    list(APPEND additional_args "${framework}")
                endif()
            endif()
        endif()
    endforeach()

    file(REMOVE "${PVS_STUDIO_LOG_FILE}")
    execute_process(COMMAND ${PVS_STUDIO_COMMAND} ${additional_args}
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output
                    ERROR_VARIABLE error)

    if (result AND NOT output MATCHES "^No compilation units were found\\.")
        message(FATAL_ERROR "PVS-Studio exited with non-zero code.\nStdout:\n${output}\nStderr:\n${error}\n")
    endif()

    return()
endif()

if(__PVS_STUDIO_INCLUDED)
    return()
endif()
set(__PVS_STUDIO_INCLUDED TRUE)

set(PVS_STUDIO_SCRIPT "${CMAKE_CURRENT_LIST_FILE}")

function (pvs_studio_log TEXT)
    if (PVS_STUDIO_DEBUG)
        message("PVS-Studio: ${TEXT}")
    endif()
endfunction()

function (pvs_studio_relative_path VAR ROOT FILEPATH)
    if (CMAKE_HOST_WIN32)
        STRING(REGEX REPLACE "\\\\" "/" ROOT ${ROOT})
        STRING(REGEX REPLACE "\\\\" "/" FILEPATH ${FILEPATH})
    endif()
    set("${VAR}" "${FILEPATH}" PARENT_SCOPE)
    if (IS_ABSOLUTE "${FILEPATH}")
        file(RELATIVE_PATH RPATH "${ROOT}" "${FILEPATH}")
        if (NOT IS_ABSOLUTE "${RPATH}")
            set("${VAR}" "${RPATH}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

function (pvs_studio_join_path VAR DIR1 DIR2)
    if ("${DIR2}" MATCHES "^(/|~|.:/).*$" OR "${DIR1}" STREQUAL "")
        set("${VAR}" "${DIR2}" PARENT_SCOPE)
    else()
        set("${VAR}" "${DIR1}/${DIR2}" PARENT_SCOPE)
    endif()
endfunction()

macro (pvs_studio_append_flags_from_property CXX C DIR PREFIX)
    if (NOT "${PROPERTY}" STREQUAL "NOTFOUND" AND NOT "${PROPERTY}" STREQUAL "PROPERTY-NOTFOUND")
        foreach (PROP ${PROPERTY})
            pvs_studio_join_path(PROP "${DIR}" "${PROP}")

            if (APPLE AND "${PREFIX}" STREQUAL "-I" AND IS_ABSOLUTE "${PROP}" AND "${PROP}" MATCHES "\\.framework$")
                get_filename_component(FRAMEWORK "${PROP}" DIRECTORY)
                list(APPEND "${CXX}" "-iframework")
                list(APPEND "${CXX}" "${FRAMEWORK}")
                list(APPEND "${C}" "-iframework")
                list(APPEND "${C}" "${FRAMEWORK}")
                pvs_studio_log("framework: ${FRAMEWORK}")
            elseif (NOT "${PROP}" STREQUAL "")
                list(APPEND "${CXX}" "${PREFIX}${PROP}")
                list(APPEND "${C}" "${PREFIX}${PROP}")
            endif()
        endforeach()
    endif()
endmacro()

macro (pvs_studio_append_standard_flag FLAGS STANDARD)
    if ("${STANDARD}" MATCHES "^(99|11|14|17|20)$")
        if ("${PVS_STUDIO_PREPROCESSOR}" MATCHES "gcc|clang")
            list(APPEND "${FLAGS}" "-std=c++${STANDARD}")
        endif()
    endif()
endmacro()

function (pvs_studio_set_directory_flags DIRECTORY CXX C)
    set(CXX_FLAGS "${${CXX}}")
    set(C_FLAGS "${${C}}")

    get_directory_property(PROPERTY DIRECTORY "${DIRECTORY}" INCLUDE_DIRECTORIES)
    pvs_studio_append_flags_from_property(CXX_FLAGS C_FLAGS "${DIRECTORY}" "-I")

    get_directory_property(PROPERTY DIRECTORY "${DIRECTORY}" COMPILE_DEFINITIONS)
    pvs_studio_append_flags_from_property(CXX_FLAGS C_FLAGS "" "-D")

    set("${CXX}" "${CXX_FLAGS}" PARENT_SCOPE)
    set("${C}" "${C_FLAGS}" PARENT_SCOPE)
endfunction()

function (pvs_studio_set_target_flags TARGET CXX C)
    set(CXX_FLAGS "${${CXX}}")
    set(C_FLAGS "${${C}}")

    if (NOT MSVC)
        list(APPEND CXX_FLAGS "$<$<BOOL:${CMAKE_SYSROOT}>:--sysroot=${CMAKE_SYSROOT}>")
        list(APPEND C_FLAGS "$<$<BOOL:${CMAKE_SYSROOT}>:--sysroot=${CMAKE_SYSROOT}>")
    endif()

    set(prop_incdirs "$<TARGET_PROPERTY:${TARGET},INCLUDE_DIRECTORIES>")
    list(APPEND CXX_FLAGS "$<$<BOOL:${prop_incdirs}>:-I$<JOIN:${prop_incdirs},$<SEMICOLON>-I>>")
    list(APPEND C_FLAGS "$<$<BOOL:${prop_incdirs}>:-I$<JOIN:${prop_incdirs},$<SEMICOLON>-I>>")

    set(prop_compdefs "$<TARGET_PROPERTY:${TARGET},COMPILE_DEFINITIONS>")
    list(APPEND CXX_FLAGS "$<$<BOOL:${prop_compdefs}>:-D$<JOIN:${prop_compdefs},$<SEMICOLON>-D>>")
    list(APPEND C_FLAGS "$<$<BOOL:${prop_compdefs}>:-D$<JOIN:${prop_compdefs},$<SEMICOLON>-D>>")

    set(prop_compopt "$<TARGET_PROPERTY:${TARGET},COMPILE_OPTIONS>")
    list(APPEND CXX_FLAGS "$<$<BOOL:${prop_compopt}>:$<JOIN:${prop_compopt},$<SEMICOLON>>>")
    list(APPEND C_FLAGS "$<$<BOOL:${prop_compopt}>:$<JOIN:${prop_compopt},$<SEMICOLON>>>")

    set("${CXX}" "${CXX_FLAGS}" PARENT_SCOPE)
    set("${C}" "${C_FLAGS}" PARENT_SCOPE)
endfunction()

function (pvs_studio_set_source_file_flags SOURCE)
    set(LANGUAGE "")

    string(TOLOWER "${SOURCE}" SOURCE_LOWER)
    if ("${LANGUAGE}" STREQUAL "" AND "${SOURCE_LOWER}" MATCHES "^.*\\.(c|cpp|cc|cx|cxx|cp|c\\+\\+)$")
        if ("${SOURCE}" MATCHES "^.*\\.c$")
            set(LANGUAGE C)
        else()
            set(LANGUAGE CXX)
        endif()
    endif()

    if ("${LANGUAGE}" STREQUAL "C")
        set(CL_PARAMS ${PVS_STUDIO_C_FLAGS} ${PVS_STUDIO_TARGET_C_FLAGS} -DPVS_STUDIO)
    elseif ("${LANGUAGE}" STREQUAL "CXX")
        set(CL_PARAMS ${PVS_STUDIO_CXX_FLAGS} ${PVS_STUDIO_TARGET_CXX_FLAGS} -DPVS_STUDIO)
    endif()

    set(PVS_STUDIO_LANGUAGE "${LANGUAGE}" PARENT_SCOPE)
    set(PVS_STUDIO_CL_PARAMS "${CL_PARAMS}" PARENT_SCOPE)
endfunction()

function (pvs_studio_analyze_file SOURCE SOURCE_DIR BINARY_DIR)
    set(PLOGS ${PVS_STUDIO_PLOGS})
    pvs_studio_set_source_file_flags("${SOURCE}")

    get_filename_component(SOURCE "${SOURCE}" REALPATH)

    get_source_file_property(PROPERTY "${SOURCE}" HEADER_FILE_ONLY)
    if (PROPERTY)
        return()
    endif()

    pvs_studio_relative_path(SOURCE_RELATIVE "${SOURCE_DIR}" "${SOURCE}")
    pvs_studio_join_path(SOURCE "${SOURCE_DIR}" "${SOURCE}")

    set(LOG "${BINARY_DIR}/PVS-Studio/${SOURCE_RELATIVE}.log")
    get_filename_component(LOG "${LOG}" REALPATH)
    get_filename_component(PARENT_DIR "${LOG}" DIRECTORY)

    if (EXISTS "${SOURCE}" AND NOT TARGET "${LOG}" AND NOT "${PVS_STUDIO_LANGUAGE}" STREQUAL "")
        # A workaround to support implicit dependencies for ninja generators.
        set(depPvsArg)
        set(depCommandArg)
        if (CMAKE_VERSION VERSION_GREATER 3.6 AND "${CMAKE_GENERATOR}" STREQUAL "Ninja")
            pvs_studio_relative_path(relLog "${CMAKE_BINARY_DIR}" "${LOG}")
            set(depPvsArg --dep-file "${LOG}.d" --dep-file-target "${relLog}")
            set(depCommandArg DEPFILE "${LOG}.d")
        endif()

        # https://public.kitware.com/Bug/print_bug_page.php?bug_id=14353
        # https://public.kitware.com/Bug/file/5436/expand_command.cmake
        #
        # It is a workaround to expand generator expressions.
        set(cmdline "${PVS_STUDIO_BIN}" analyze
                    --output-file "${LOG}"
                    --source-file "${SOURCE}"
                    ${depPvsArg}
                    ${PVS_STUDIO_ARGS}
                    --cl-params "${PVS_STUDIO_CL_PARAMS}" "${SOURCE}")

        string(REPLACE ";" "$<SEMICOLON>" cmdline "${cmdline}")
        set(pvscmd "${CMAKE_COMMAND}"
                   -D "PVS_STUDIO_AS_SCRIPT=TRUE"
                   -D "PVS_STUDIO_COMMAND=${cmdline}"
                   -D "PVS_STUDIO_LOG_FILE=${LOG}"
                   -P "${PVS_STUDIO_SCRIPT}")

        add_custom_command(OUTPUT "${LOG}"
                           COMMAND "${CMAKE_COMMAND}" -E make_directory "${PARENT_DIR}"
                           COMMAND "${CMAKE_COMMAND}" -E remove_directory "${LOG}"
                           COMMAND ${pvscmd}
                           WORKING_DIRECTORY "${BINARY_DIR}"
                           DEPENDS "${SOURCE}" "${PVS_STUDIO_SUPPRESS_BASE}" "${PVS_STUDIO_DEPENDS}"
                           IMPLICIT_DEPENDS "${PVS_STUDIO_LANGUAGE}" "${SOURCE}"
                           ${depCommandArg}
                           VERBATIM
                           COMMENT "Analyzing ${PVS_STUDIO_LANGUAGE} file ${SOURCE_RELATIVE}")
        list(APPEND PLOGS "${LOG}")
    endif()
    set(PVS_STUDIO_PLOGS "${PLOGS}" PARENT_SCOPE)
endfunction()

function (pvs_studio_analyze_target TARGET DIR)
    set(PVS_STUDIO_PLOGS "${PVS_STUDIO_PLOGS}")
    set(PVS_STUDIO_TARGET_CXX_FLAGS "")
    set(PVS_STUDIO_TARGET_C_FLAGS "")

    get_target_property(PROPERTY "${TARGET}" SOURCES)
    pvs_studio_relative_path(BINARY_DIR "${CMAKE_SOURCE_DIR}" "${DIR}")
    if ("${BINARY_DIR}" MATCHES "^/.*$")
        pvs_studio_join_path(BINARY_DIR "${CMAKE_BINARY_DIR}" "PVS-Studio/__${BINARY_DIR}")
    else()
        pvs_studio_join_path(BINARY_DIR "${CMAKE_BINARY_DIR}" "${BINARY_DIR}")
    endif()

    file(MAKE_DIRECTORY "${BINARY_DIR}")

    pvs_studio_set_directory_flags("${DIR}" PVS_STUDIO_TARGET_CXX_FLAGS PVS_STUDIO_TARGET_C_FLAGS)
    pvs_studio_set_target_flags("${TARGET}" PVS_STUDIO_TARGET_CXX_FLAGS PVS_STUDIO_TARGET_C_FLAGS)

    if (NOT "${PROPERTY}" STREQUAL "NOTFOUND" AND NOT "${PROPERTY}" STREQUAL "PROPERTY-NOTFOUND")
        foreach (SOURCE ${PROPERTY})
            pvs_studio_join_path(SOURCE "${DIR}" "${SOURCE}")
            pvs_studio_analyze_file("${SOURCE}" "${DIR}" "${BINARY_DIR}")
        endforeach()
    endif()

    set(PVS_STUDIO_PLOGS "${PVS_STUDIO_PLOGS}" PARENT_SCOPE)
endfunction()

set(PVS_STUDIO_RECURSIVE_TARGETS)
set(PVS_STUDIO_RECURSIVE_TARGETS_NEW)

macro(pvs_studio_get_recursive_targets TARGET)
    get_target_property(libs "${TARGET}" LINK_LIBRARIES)
    foreach (lib IN LISTS libs)
        list(FIND PVS_STUDIO_RECURSIVE_TARGETS "${lib}" index)
        if (TARGET "${lib}" AND "${index}" STREQUAL -1)
            get_target_property(target_type "${lib}" TYPE)
            if (NOT "${target_type}" STREQUAL "INTERFACE_LIBRARY")
                list(APPEND PVS_STUDIO_RECURSIVE_TARGETS "${lib}")
                list(APPEND PVS_STUDIO_RECURSIVE_TARGETS_NEW "${lib}")
                pvs_studio_get_recursive_targets("${lib}")
            endif()
        endif()
    endforeach()
endmacro()

option(PVS_STUDIO_DISABLE OFF "Disable PVS-Studio targets")
option(PVS_STUDIO_DEBUG OFF "Add debug info")

# pvs_studio_add_target
# Target options:
# ALL                           add PVS-Studio target to default build (default: off)
# TARGET target                 name of analysis target (default: pvs)
# ANALYZE targets...            targets to analyze
# RECURSIVE                     analyze target's dependencies (requires CMake 3.5+)
# COMPILE_COMMANDS              use compile_commands.json instead of targets (specified by the 'ANALYZE' option) to determine files for analysis
#                               (set CMAKE_EXPORT_COMPILE_COMMANDS, available only for Makefile and Ninja generators)
#
# Output options:
# OUTPUT                        prints report to stdout
# LOG path                      path to report (default: ${CMAKE_CURRENT_BINARY_DIR}/PVS-Studio.log)
# FORMAT format                 format of report
# MODE mode                     analyzers/levels filter (default: GA:1,2)
# HIDE_HELP                     do not print help message
#
# Analyzer options:
# PLATFORM name                 linux32/linux64 (default: linux64)
# PREPROCESSOR name             preprocessor type: gcc/clang (default: auto detected)
# LICENSE path                  path to PVS-Studio.lic (default: ~/.config/PVS-Studio/PVS-Studio.lic)
# CONFIG path                   path to PVS-Studio.cfg
# CFG_TEXT text                 embedded PVS-Studio.cfg
# SUPPRESS_BASE                 path to suppress base file
# KEEP_COMBINED_PLOG            do not delete combined plog file *.pvs.raw for further processing with plog-converter
#
# Misc options:
# DEPENDS targets..             additional target dependencies
# SOURCES path...               list of source files to analyze
# BIN path                      path to pvs-studio-analyzer (Unix) or CompilerCommandsAnalyzer.exe (Windows)
# CONVERTER path                path to plog-converter (Unix) or HtmlGenerator.exe (Windows)
# C_FLAGS flags...              additional C_FLAGS
# CXX_FLAGS flags...            additional CXX_FLAGS
# ARGS args...                  additional pvs-studio-analyzer/CompilerCommandsAnalyzer.exe flags
# CONVERTER_ARGS args...        additional plog-converter/HtmlGenerator.exe flags
function (pvs_studio_add_target)
    macro (default VAR VALUE)
        if ("${${VAR}}" STREQUAL "")
            set("${VAR}" "${VALUE}")
        endif()
    endmacro()

    set(PVS_STUDIO_SUPPORTED_PREPROCESSORS "gcc|clang|visualcpp")
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        set(DEFAULT_PREPROCESSOR "clang")
    elseif (MSVC)
        set(DEFAULT_PREPROCESSOR "visualcpp")
    else()
        set(DEFAULT_PREPROCESSOR "gcc")
    endif()

    set(OPTIONAL OUTPUT ALL RECURSIVE HIDE_HELP KEEP_COMBINED_PLOG COMPILE_COMMANDS KEEP_INTERMEDIATE_FILES)
    set(SINGLE LICENSE CONFIG TARGET LOG FORMAT BIN CONVERTER PLATFORM PREPROCESSOR CFG_TEXT SUPPRESS_BASE)
    set(MULTI SOURCES C_FLAGS CXX_FLAGS ARGS DEPENDS ANALYZE MODE CONVERTER_ARGS)
    cmake_parse_arguments(PVS_STUDIO "${OPTIONAL}" "${SINGLE}" "${MULTI}" ${ARGN})


    default(PVS_STUDIO_C_FLAGS "")
    default(PVS_STUDIO_CXX_FLAGS "")
    default(PVS_STUDIO_TARGET "pvs")
    default(PVS_STUDIO_LOG "PVS-Studio.log")

    set(PATHS)

    if (CMAKE_HOST_WIN32)
        # The registry value is only read when you do some cache operation on it.
        # https://stackoverflow.com/questions/1762201/reading-registry-values-with-cmake
        GET_FILENAME_COMPONENT(ROOT "[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\ProgramVerificationSystems\\PVS-Studio;installDir]" ABSOLUTE CACHE)

        if (EXISTS "${ROOT}")
           set(PATHS "${ROOT}")
        else()
           set(ROOT "PROGRAMFILES(X86)")
           set(ROOT "$ENV{${ROOT}}/PVS-Studio")
           string(REPLACE \\ / ROOT "${ROOT}")

           if (EXISTS "${ROOT}")
              set(PATHS "${ROOT}")
            else()
              set(ROOT "PATH")
              set(ROOT "$ENV{${ROOT}}")
              set(PATHS "${ROOT}")
           endif()
        endif()



        default(PVS_STUDIO_BIN "CompilerCommandsAnalyzer.exe")
        default(PVS_STUDIO_CONVERTER "HtmlGenerator.exe")
    else()
        default(PVS_STUDIO_BIN "pvs-studio-analyzer")
        default(PVS_STUDIO_CONVERTER "plog-converter")
    endif()

    find_program(PVS_STUDIO_BIN_PATH "${PVS_STUDIO_BIN}" ${PATHS})
    set(PVS_STUDIO_BIN "${PVS_STUDIO_BIN_PATH}")

    if (NOT EXISTS "${PVS_STUDIO_BIN}")
        message(FATAL_ERROR "pvs-studio-analyzer is not found")
    endif()

    find_program(PVS_STUDIO_CONVERTER_PATH "${PVS_STUDIO_CONVERTER}" ${PATHS})
    set(PVS_STUDIO_CONVERTER "${PVS_STUDIO_CONVERTER_PATH}")

    if (NOT EXISTS "${PVS_STUDIO_CONVERTER}")
        message(FATAL_ERROR "plog-converter is not found")
    endif()

    default(PVS_STUDIO_MODE "GA:1,2")
    default(PVS_STUDIO_PREPROCESSOR "${DEFAULT_PREPROCESSOR}")
    if (WIN32)
        default(PVS_STUDIO_PLATFORM "x64")
    else()
        default(PVS_STUDIO_PLATFORM "linux64")
    endif()

    string(REPLACE ";" "+" PVS_STUDIO_MODE "${PVS_STUDIO_MODE}")

    if ("${PVS_STUDIO_CONFIG}" STREQUAL "" AND NOT "${PVS_STUDIO_CFG_TEXT}" STREQUAL "")
        set(PVS_STUDIO_CONFIG "${CMAKE_BINARY_DIR}/PVS-Studio.cfg")

        set(PVS_STUDIO_CONFIG_COMMAND "${CMAKE_COMMAND}" -E echo "${PVS_STUDIO_CFG_TEXT}" > "${PVS_STUDIO_CONFIG}")

        add_custom_command(OUTPUT "${PVS_STUDIO_CONFIG}"
                           COMMAND ${PVS_STUDIO_CONFIG_COMMAND}
                           WORKING_DIRECTORY "${BINARY_DIR}"
                           COMMENT "Generating PVS-Studio.cfg")

        list(APPEND PVS_STUDIO_DEPENDS "${PVS_STUDIO_CONFIG}")
    endif()
    if (NOT "${PVS_STUDIO_PREPROCESSOR}" MATCHES "^${PVS_STUDIO_SUPPORTED_PREPROCESSORS}$")
        message(FATAL_ERROR "Preprocessor ${PVS_STUDIO_PREPROCESSOR} isn't supported. Available options: ${PVS_STUDIO_SUPPORTED_PREPROCESSORS}.")
    endif()

    pvs_studio_append_standard_flag(PVS_STUDIO_CXX_FLAGS "${CMAKE_CXX_STANDARD}")
    pvs_studio_set_directory_flags("${CMAKE_CURRENT_SOURCE_DIR}" PVS_STUDIO_CXX_FLAGS PVS_STUDIO_C_FLAGS)

    if (NOT "${PVS_STUDIO_LICENSE}" STREQUAL "")
        list(APPEND PVS_STUDIO_ARGS --lic-file "${PVS_STUDIO_LICENSE}")
    endif()

    if (NOT ${PVS_STUDIO_CONFIG} STREQUAL "")
        list(APPEND PVS_STUDIO_ARGS --cfg "${PVS_STUDIO_CONFIG}")
    endif()

    list(APPEND PVS_STUDIO_ARGS --platform "${PVS_STUDIO_PLATFORM}"
                                --preprocessor "${PVS_STUDIO_PREPROCESSOR}")

    if (NOT "${PVS_STUDIO_SUPPRESS_BASE}" STREQUAL "")
        pvs_studio_join_path(PVS_STUDIO_SUPPRESS_BASE "${CMAKE_CURRENT_SOURCE_DIR}" "${PVS_STUDIO_SUPPRESS_BASE}")
        list(APPEND PVS_STUDIO_ARGS --suppress-file "${PVS_STUDIO_SUPPRESS_BASE}")
    endif()

    if (NOT "${CMAKE_CXX_COMPILER}" STREQUAL "")
        list(APPEND PVS_STUDIO_ARGS --cxx "${CMAKE_CXX_COMPILER}")
    endif()

    if (NOT "${CMAKE_C_COMPILER}" STREQUAL "")
        list(APPEND PVS_STUDIO_ARGS --cc "${CMAKE_C_COMPILER}")
    endif()

    if (PVS_STUDIO_KEEP_INTERMEDIATE_FILES)
        list(APPEND PVS_STUDIO_ARGS --dump-files)
    endif()

    string(REGEX REPLACE [123,:] "" ANALYZER_MODE ${PVS_STUDIO_MODE})
    if (NOT "$ANALYZER_MODE" STREQUAL "GA")
        list (APPEND PVS_STUDIO_ARGS -a "${ANALYZER_MODE}")
    endif()

    set(PVS_STUDIO_PLOGS "")

    set(PVS_STUDIO_RECURSIVE_TARGETS_NEW)
    if (${PVS_STUDIO_RECURSIVE})
        foreach (TARGET IN LISTS PVS_STUDIO_ANALYZE)
            list(APPEND PVS_STUDIO_RECURSIVE_TARGETS_NEW "${TARGET}")
            pvs_studio_get_recursive_targets("${TARGET}")
        endforeach()
    endif()

    set(inc_path)

    foreach (TARGET ${PVS_STUDIO_ANALYZE})
        set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        string(FIND "${TARGET}" ":" DELIM)
        if ("${DELIM}" GREATER "-1")
            math(EXPR DELIMI "${DELIM}+1")
            string(SUBSTRING "${TARGET}" "${DELIMI}" "-1" DIR)
            string(SUBSTRING "${TARGET}" "0" "${DELIM}" TARGET)
            pvs_studio_join_path(DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${DIR}")
        else()
            get_target_property(TARGET_SOURCE_DIR "${TARGET}" SOURCE_DIR)
            if (EXISTS "${TARGET_SOURCE_DIR}")
                set(DIR "${TARGET_SOURCE_DIR}")
            endif()
        endif()
        pvs_studio_analyze_target("${TARGET}" "${DIR}")
        list(APPEND PVS_STUDIO_DEPENDS "${TARGET}")

        if ("${inc_path}" STREQUAL "")
            set(inc_path "$<TARGET_PROPERTY:${TARGET},INCLUDE_DIRECTORIES>")
        else()
            set(inc_path "${inc_path}$<SEMICOLON>$<TARGET_PROPERTY:${TARGET},INCLUDE_DIRECTORIES>")
        endif()
    endforeach()

    foreach (TARGET ${PVS_STUDIO_RECURSIVE_TARGETS_NEW})
        set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        get_target_property(TARGET_SOURCE_DIR "${TARGET}" SOURCE_DIR)
        if (EXISTS "${TARGET_SOURCE_DIR}")
            set(DIR "${TARGET_SOURCE_DIR}")
        endif()
        pvs_studio_analyze_target("${TARGET}" "${DIR}")
        list(APPEND PVS_STUDIO_DEPENDS "${TARGET}")
    endforeach()

    set(PVS_STUDIO_TARGET_CXX_FLAGS "")
    set(PVS_STUDIO_TARGET_C_FLAGS "")
    foreach (SOURCE ${PVS_STUDIO_SOURCES})
        pvs_studio_analyze_file("${SOURCE}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
    endforeach()

    if (PVS_STUDIO_COMPILE_COMMANDS)
        set(COMPILE_COMMANDS_LOG "${PVS_STUDIO_LOG}.pvs.analyzer.raw")
        if (NOT CMAKE_EXPORT_COMPILE_COMMANDS)
            message(FATAL_ERROR "You should set CMAKE_EXPORT_COMPILE_COMMANDS to TRUE")
        endif()
        add_custom_command(
            OUTPUT "${COMPILE_COMMANDS_LOG}"
            COMMAND "${PVS_STUDIO_BIN}" analyze -i
                    --output-file "${COMPILE_COMMANDS_LOG}.always"
                    ${PVS_STUDIO_ARGS}
            COMMENT "Analyzing with PVS-Studio"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            DEPENDS "${PVS_STUDIO_SUPPRESS_BASE}" "${PVS_STUDIO_DEPENDS}"
        )
        list(APPEND PVS_STUDIO_PLOGS_LOGS "${COMPILE_COMMANDS_LOG}.always")
        list(APPEND PVS_STUDIO_PLOGS_DEPENDENCIES "${COMPILE_COMMANDS_LOG}")
    endif()

    pvs_studio_relative_path(LOG_RELATIVE "${CMAKE_BINARY_DIR}" "${PVS_STUDIO_LOG}")
    if (PVS_STUDIO_PLOGS OR PVS_STUDIO_COMPILE_COMMANDS)
        if (CMAKE_HOST_WIN32)
            string(REPLACE / \\ PVS_STUDIO_PLOGS "${PVS_STUDIO_PLOGS}")
            if (CMAKE_GENERATOR MATCHES "NMake")
                set(COMMAND_TYPE_FILE "${CMAKE_BINARY_DIR}/PVSConcatAllLogs.cmd")
                
                # The number of files that will be merged in one call to the type command
                set(STEP_SIZE 30)
                set(BEGIN 0)

                list(APPEND PVS_STUDIO_PLOGS ${PVS_STUDIO_PLOGS_LOGS})
                list(LENGTH PVS_STUDIO_PLOGS END)

                # Creating a bat file to call the 'type' command
                file(WRITE ${COMMAND_TYPE_FILE} "@echo off\nbreak > ${PVS_STUDIO_LOG}\n")

                while(BEGIN LESS END)
                    list(SUBLIST PVS_STUDIO_PLOGS ${BEGIN} ${STEP_SIZE} NEW_LIST)
                    file(APPEND ${COMMAND_TYPE_FILE} "type ${NEW_LIST} >> ${PVS_STUDIO_LOG} 2>nul || cd .\n")
                    math(EXPR BEGIN "${BEGIN} + ${STEP_SIZE}")
                endwhile()
                
                list(APPEND COMMANDS COMMAND call ${COMMAND_TYPE_FILE})
            else()
                set(COMMANDS COMMAND type ${PVS_STUDIO_PLOGS} ${PVS_STUDIO_PLOGS_LOGS} > "${PVS_STUDIO_LOG}" 2>nul || cd .)
            endif()
        else()
            set(COMMANDS COMMAND cat ${PVS_STUDIO_PLOGS} ${PVS_STUDIO_PLOGS_LOGS} > "${PVS_STUDIO_LOG}" 2>/dev/null || true)
        endif()
        set(COMMENT "Generating ${LOG_RELATIVE}")
        if (NOT "${PVS_STUDIO_FORMAT}" STREQUAL "" OR PVS_STUDIO_OUTPUT)
            if ("${PVS_STUDIO_FORMAT}" STREQUAL "")
              set(PVS_STUDIO_FORMAT "errorfile")
            endif()
            if (PVS_STUDIO_HIDE_HELP)
              set(PVS_STUDIO_CONVERTER_ARGS ${PVS_STUDIO_CONVERTER_ARGS} --noHelpMessages)
            endif()
            if (PVS_STUDIO_OUTPUT)
              set(PVS_STUDIO_CONVERTER_ARGS ${PVS_STUDIO_CONVERTER_ARGS} --stdout)
            endif()

            # Вставка для удаления консольного вывода конвертера
            if (CMAKE_HOST_WIN32)
              set(CMD_TO_NUL >NUL 2>&1)
            else()
              set(CMD_TO_NUL >/dev/null 2>&1)
            endif()

            list(APPEND COMMANDS
                 COMMAND "${CMAKE_COMMAND}" -E remove -f "${PVS_STUDIO_LOG}.pvs.raw"
                 COMMAND "${CMAKE_COMMAND}" -E rename "${PVS_STUDIO_LOG}" "${PVS_STUDIO_LOG}.pvs.raw"
                 COMMAND "${PVS_STUDIO_CONVERTER}" "${PVS_STUDIO_CONVERTER_ARGS}" -t "${PVS_STUDIO_FORMAT}" "${PVS_STUDIO_LOG}.pvs.raw" -o "${PVS_STUDIO_LOG}" -a "${PVS_STUDIO_MODE}" ${CMD_TO_NUL})
            if (NOT PVS_STUDIO_KEEP_COMBINED_PLOG)
                list(APPEND COMMANDS COMMAND "${CMAKE_COMMAND}" -E remove -f "${PVS_STUDIO_LOG}.pvs.raw")
            endif()
        endif()
    else()
        set(COMMANDS COMMAND "${CMAKE_COMMAND}" -E touch "${PVS_STUDIO_LOG}")
        set(COMMENT "Generating ${LOG_RELATIVE}: no sources found")
    endif()

    if (CMAKE_HOST_WIN32)
        string(REPLACE / \\ PVS_STUDIO_LOG "${PVS_STUDIO_LOG}")
    endif()

    if (CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        get_filename_component(LOG_NAME ${LOG_RELATIVE} NAME)
        set(LOG_TARGET "${PVS_STUDIO_TARGET}-${LOG_NAME}-log")
        add_custom_target("${LOG_TARGET}"
                          BYPRODUCTS "${PVS_STUDIO_LOG}"
                          ${COMMANDS}
                          COMMENT "${COMMENT}"
                          DEPENDS ${PVS_STUDIO_PLOGS} ${PVS_STUDIO_PLOGS_DEPENDENCIES}
                          WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    else()
        set(LOG_TARGET "${PVS_STUDIO_LOG}")
        add_custom_command(OUTPUT "${LOG_TARGET}"
                           ${COMMANDS}
                           COMMENT "${COMMENT}"
                           DEPENDS ${PVS_STUDIO_PLOGS} ${PVS_STUDIO_PLOGS_DEPENDENCIES}
                           WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    endif()

    if (PVS_STUDIO_ALL)
        set(ALL "ALL")
    else()
        set(ALL "")
    endif()

    add_custom_target("${PVS_STUDIO_TARGET}" ${ALL}
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
                      DEPENDS ${PVS_STUDIO_DEPENDS} "${LOG_TARGET}")

    # A workaround to add implicit dependencies of source files from include directories
    set_target_properties("${PVS_STUDIO_TARGET}" PROPERTIES INCLUDE_DIRECTORIES "${inc_path}")

    if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
        set(props_file "${CMAKE_BINARY_DIR}/${PVS_STUDIO_TARGET}.user.props")
        file(WRITE "${props_file}" [=[
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
 <ImportGroup Label="PropertySheets">
  <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
 </ImportGroup>
 <ItemDefinitionGroup>
  <CustomBuild>
   <BuildInParallel>true</BuildInParallel>
  </CustomBuild>
 </ItemDefinitionGroup>
</Project>
]=])
        set_target_properties("${PVS_STUDIO_TARGET}" PROPERTIES VS_USER_PROPS "${props_file}")
    endif()
endfunction()
