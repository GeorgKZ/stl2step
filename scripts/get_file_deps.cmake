##############################################################################
# Функция поиска зависимостей в исполняемом файле или библиотеке по мотивам
# /opt/cmake-4.0.2-linux-x86_64/share/cmake-4.0/Modules/GetPrerequisites.cmake
#
# Аргумент target - путь/имя анализируемого файла
# Аргумент prerequisites_var - имя переменной-списка, в которую будет помещён
# список найденных зависимостей (без рекурсии)
##############################################################################


# Получить список имён файлов - зависимостей файла target
function(get_prerequisites target prerequisites_var)
    # Кросскомпиляция не поддерживается
    if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL CMAKE_SYSTEM_NAME)
        return()
    endif()

    set(eol_char "E")
    set(${prerequisites_var} "")

    # При работе в среде MacOS/OS X - otool
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
        set(gp_tool "otool")
        find_program(gp_cmd ${gp_tool})
    # При работе в среде Linux - ldd
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(gp_tool "ldd")
        find_program(gp_cmd ${gp_tool})
    # При работе в среде Windows - dumpbin
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(gp_cmd_paths ${gp_cmd_paths}
          "$ENV{VS170COMNTOOLS}/../../VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\14.0;InstallDir]/../../VC/bin"
          "$ENV{VS140COMNTOOLS}/../../VC/bin"
          "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\12.0;InstallDir]/../../VC/bin"
          "$ENV{VS120COMNTOOLS}/../../VC/bin"
          "C:/Program Files (x86)/Microsoft Visual Studio 12.0/VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\11.0;InstallDir]/../../VC/bin"
          "$ENV{VS110COMNTOOLS}/../../VC/bin"
          "C:/Program Files (x86)/Microsoft Visual Studio 11.0/VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\10.0;InstallDir]/../../VC/bin"
          "$ENV{VS100COMNTOOLS}/../../VC/bin"
          "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\9.0;InstallDir]/../../VC/bin"
          "$ENV{VS90COMNTOOLS}/../../VC/bin"
          "C:/Program Files/Microsoft Visual Studio 9.0/VC/bin"
          "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0;InstallDir]/../../VC/bin"
          "$ENV{VS80COMNTOOLS}/../../VC/bin"
          "C:/Program Files/Microsoft Visual Studio 8/VC/BIN"
          "C:/Program Files (x86)/Microsoft Visual Studio 8/VC/BIN"
          "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\7.1;InstallDir]/../../VC7/bin"
          "$ENV{VS71COMNTOOLS}/../../VC7/bin"
          "C:/Program Files/Microsoft Visual Studio .NET 2003/VC7/BIN"
          "C:/Program Files (x86)/Microsoft Visual Studio .NET 2003/VC7/BIN"
        )
        set(gp_tool "dumpbin")
        find_program(gp_cmd ${gp_tool} PATHS ${gp_cmd_paths})
    # При работе в среде Cygwin - ?
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "CYGWIN.*")
        find_program(gp_dumpbin "dumpbin" PATHS ${gp_cmd_paths})
        if(gp_dumpbin)
          set(gp_tool "dumpbin")
        endif()
    # При работе в среде MinGW - objdump
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "MINGW.*")
        set(gp_tool "${CMAKE_OBJDUMP}")
    else()
        message(FATAL_ERROR "Неизвестная среда функционирования ${CMAKE_HOST_SYSTEM_NAME}")
        return()
    endif()

    if(NOT gp_cmd)
        message(FATAL_ERROR "Не удалось найти утилиту '${gp_tool}', необходимую для поиска зависимостей")
        return()
    endif()

###############################################################################
# Для Linux - LDD
###############################################################################

  if(gp_tool MATCHES "ldd$")

      # Вызвать инструмент ldd для исследуемого файла
      execute_process(
        COMMAND ${gp_cmd} ${target}
        RESULT_VARIABLE gp_rv
        OUTPUT_VARIABLE gp_cmd_ov
        ERROR_VARIABLE gp_ev
      )

      # Проверить код завершения
      if(NOT gp_rv STREQUAL "0")
          message(FATAL_ERROR "Программа ${gp_cmd} завершилась с ошибкой: ${gp_rv}\n${gp_ev}")
      endif()

      # Заменить перевод строки на специально введённый символ
      string(REPLACE "\n" "${eol_char};" gp_cmd_ov "${gp_cmd_ov}")

      # Проверить каждую строку на предмет соответствия регулярному выражению
      set(ldd_regex "^[\t ]*([^\t ]+) =>.*${eol_char}$")
      foreach(line ${gp_cmd_ov})
          if("${line}" MATCHES "${ldd_regex}")
              string(REGEX REPLACE "${ldd_regex}" "\\1" raw_item "${line}")
              set(${prerequisites_var} ${${prerequisites_var}} "${raw_item}" )
          endif()
      endforeach()

###############################################################################
# Для MacOS/OS X - otool
###############################################################################

  elseif(gp_tool MATCHES "otool$")

      # Вызвать инструмент otool для исследуемого файла
      execute_process(
        COMMAND ${gp_cmd} "-L" ${target}
        RESULT_VARIABLE gp_rv
        OUTPUT_VARIABLE gp_cmd_ov
        ERROR_VARIABLE gp_ev
      )

      # Проверить код завершения
      if(NOT gp_rv STREQUAL "0")
          message(FATAL_ERROR "Программа otool -L завершилась с ошибкой: ${gp_rv}\n${gp_ev}")
      endif()

#      # check for install id and remove it from list, since otool -L can include a
#      # reference to itself
#      set(gp_install_id)
#
      # Экранировать символ "точка с запятой"
#     string(REPLACE ";" "\\;" candidates "${gp_cmd_ov}")
      # Заменить перевод строки на специально введённый символ
      string(REPLACE "\n" "${eol_char};" candidates "${gp_cmd_ov}")

      get_filename_component(TARGET_NAME "${target}" NAME)

#      # Повторный запуск для получения gp_install_id самого otool
#      execute_process(
#        COMMAND ${gp_cmd} -D ${target}
#        RESULT_VARIABLE otool_rv
#        OUTPUT_VARIABLE gp_install_id_ov
#        ERROR_VARIABLE otool_ev
#        )
#      if(NOT otool_rv STREQUAL "0")
#          message(FATAL_ERROR "Программа otool -D завершилась с ошибкой: ${otool_rv}\n${otool_ev}")
#      endif()
#      # second line is install name
#      string(REGEX REPLACE ".*:\n" "" gp_install_id "${gp_install_id_ov}")

#      if(gp_install_id)
#          # trim
#          string(REGEX MATCH "[^\n ].*[^\n ]" gp_install_id "${gp_install_id}")
#          message("INSTALL ID is \"${gp_install_id}\"")
#      endif()

      set(gp_regex "^\t([^\t]+) \\(compatibility version ([0-9]+.[0-9]+.[0-9]+), current version ([0-9]+.[0-9]+.[0-9]+)(, weak)?\\)${eol_char}$")

      # Проверить каждую строку на предмет соответствия регулярному выражению gp_regex
      foreach(candidate ${candidates})

          if("${candidate}" MATCHES "${gp_regex}")
              string(REGEX REPLACE "${gp_regex}" "\\1" raw_item "${candidate}")

              string(REGEX REPLACE "${gp_regex}" "\\2" raw_compat_version "${candidate}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\1" compat_major_version "${raw_compat_version}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\2" compat_minor_version "${raw_compat_version}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" compat_patch_version "${raw_compat_version}")

              string(REGEX REPLACE "${gp_regex}" "\\3" raw_current_version "${candidate}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\1" current_major_version "${raw_current_version}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\2" current_minor_version "${raw_current_version}")
              string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" current_patch_version "${raw_current_version}")

              get_filename_component(item "${raw_item}" NAME)

#              if(NOT raw_item STREQUAL gp_install_id)
              if(NOT item STREQUAL TARGET_NAME)
#                  message(STATUS "!!!add name ${item}")
                  set(${prerequisites_var} ${${prerequisites_var}} "${item}" )
#              else()
#                  message(STATUS "!!!skip same name ${item}")
              endif()
          endif()
      endforeach()

###############################################################################
# Для Windows - DumpBin
###############################################################################

  elseif(gp_tool MATCHES "dumpbin$")

      # When running dumpbin, it also needs the "Common7/IDE" directory in the
      # PATH. It will already be in the PATH if being run from a Visual Studio
      # command prompt. Add it to the PATH here in case we are running from a
      # different command prompt.
      #
      get_filename_component(gp_cmd_dir "${gp_cmd}" PATH)
      get_filename_component(gp_cmd_dlls_dir "${gp_cmd_dir}/../../Common7/IDE" ABSOLUTE)
      # Use cmake paths as a user may have a PATH element ending with a backslash.
      # This will escape the list delimiter and create havoc!
      if(EXISTS "${gp_cmd_dlls_dir}")
        # only add to the path if it is not already in the path
        set(gp_found_cmd_dlls_dir 0)
        file(TO_CMAKE_PATH "$ENV{PATH}" env_path)
        foreach(gp_env_path_element ${env_path})
          if(gp_env_path_element STREQUAL gp_cmd_dlls_dir)
            set(gp_found_cmd_dlls_dir 1)
          endif()
        endforeach()
    
        if(NOT gp_found_cmd_dlls_dir)
          file(TO_NATIVE_PATH "${gp_cmd_dlls_dir}" gp_cmd_dlls_dir)
          set(ENV{PATH} "$ENV{PATH};${gp_cmd_dlls_dir}")
        endif()
      endif()

#    set(gp_cmd_args "/dependents")
      set(gp_regex "^    ([^ ].*[Dd][Ll][Ll])${eol_char}$")
#    set(gp_regex_error "")
#    set(gp_regex_fallback "")
#    set(gp_regex_cmp_count 1)



      # Вызвать инструмент dumpbin для исследуемого файла
      execute_process(
        COMMAND ${gp_cmd} /dependents ${target}
        RESULT_VARIABLE gp_rv
        OUTPUT_VARIABLE gp_cmd_ov
        ERROR_VARIABLE gp_ev
      )

      # Exclude delay load dependencies under windows (they are listed in dumpbin output after the message below)
      string(FIND "${gp_cmd_ov}" "Image has the following delay load dependencies" gp_delayload_pos)
      if (${gp_delayload_pos} GREATER -1)
        string(SUBSTRING "${gp_cmd_ov}" 0 ${gp_delayload_pos} gp_cmd_ov_no_delayload_deps)
        string(SUBSTRING "${gp_cmd_ov}" ${gp_delayload_pos} -1 gp_cmd_ov_delayload_deps)
        set(gp_cmd_ov ${gp_cmd_ov_no_delayload_deps})
      endif()
    
      if(NOT gp_rv STREQUAL "0")
          # dumpbin error messages seem to go to stdout
          message(FATAL_ERROR "${gp_cmd} failed: ${gp_rv}\n${gp_ev}\n${gp_cmd_ov}")
      endif()

      # check for install id and remove it from list, since otool -L can include a
      # reference to itself
      set(gp_install_id)

      # Экранировать символ "точка с запятой"
      string(REPLACE ";" "\\;" candidates "${gp_cmd_ov}")
      # Заменить перевод строки на специально введённый символ
      string(REPLACE "\n" "${eol_char};" candidates "${candidates}")

      # Проверить каждую строку на предмет соответствия регулярному выражению gp_regex
      foreach(candidate ${candidates})
          if("${candidate}" MATCHES "${gp_regex}")
              # Extract information from each candidate:
              string(REGEX REPLACE "${gp_regex}" "\\1" raw_item "${candidate}")
#             message(STATUS "Found items: ${raw_item}") 
              set(${prerequisites_var} ${${prerequisites_var}} "${raw_item}" )
          endif()
      endforeach()

###############################################################################
# Для Windows - ObjBin
###############################################################################

  elseif(gp_tool MATCHES "objdump(\\.exe)?$")

      set(gp_cmd_maybe_filter)      # optional command to pre-filter gp_tool results

      # objdump generates copious output so we create a grep filter to pre-filter results
      if(WIN32)
          find_program(gp_grep_cmd findstr)
          set(gp_grep_cmd_arg "")
      else()
          find_program(gp_grep_cmd grep)
          set(gp_grep_cmd_arg "-a")
      endif()
      if(gp_grep_cmd)
          set(gp_cmd_maybe_filter COMMAND ${gp_grep_cmd} "${gp_grep_cmd_arg}" "^[[:blank:]]*DLL Name: ")
      endif()


      # Вызвать инструмент gp_cmd для исследуемого файла
      execute_process(
        COMMAND ${gp_cmd} -p ${target}
        ${gp_cmd_maybe_filter}
        RESULT_VARIABLE gp_rv
        OUTPUT_VARIABLE gp_cmd_ov
        ERROR_VARIABLE gp_ev
      )    
      if(NOT gp_rv STREQUAL "0")
          message(FATAL_ERROR "${gp_cmd} failed: ${gp_rv}\n${gp_ev}")
      endif()

      # Экранировать символ "точка с запятой"
      string(REPLACE ";" "\\;" candidates "${gp_cmd_ov}")
      # Заменить перевод строки на специально введённый символ
      string(REPLACE "\n" "${eol_char};" candidates "${candidates}")

      set(gp_regex "^[\t ]*DLL Name: (.*\\.[Dd][Ll][Ll])${eol_char}$")

      # Проверить каждую строку на предмет соответствия регулярному выражению gp_regex
      foreach(candidate ${candidates})

          if("${candidate}" MATCHES "${gp_regex}")
              # Extract information from each candidate:
              string(REGEX REPLACE "${gp_regex}" "\\1" raw_item "${candidate}")
#             message(STATUS "Found items: ${raw_item}") 
              set(${prerequisites_var} ${${prerequisites_var}} "${raw_item}" )       
          endif()
      endforeach()


  else()
      message(STATUS "warning: gp_tool='${gp_tool}' is an unknown tool...")
      message(STATUS "CMake function get_prerequisites needs more code to handle '${gp_tool}'")
      message(STATUS "Valid gp_tool values are dumpbin, ldd, objdump and otool.")
      return()
  endif()

  set(${prerequisites_var} ${${prerequisites_var}} PARENT_SCOPE)

endfunction()
