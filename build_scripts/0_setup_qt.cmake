##############################################################################
# Настройка требуемой версии CMake
##############################################################################
#
  cmake_minimum_required(VERSION 3.9...3.28)
#
##############################################################################
# Настройка списка зеркал с архивами Qt
##############################################################################
#
# Список зеркал с архивами Qt
set(qt_mirrors
  "mirror.yandex.ru/mirrors/qt.io"
  "mirror.aarnet.edu.au/pub/qtproject"
  "mirror.accum.se/mirror/qt.io/qtproject"
  "mirrors.ukfast.co.uk/sites/qt.io"
  "mirrors.sau.edu.cn/qt"
  "mirrors.ocf.berkeley.edu/qt"
  "mirrors.dotsrc.org/qtproject"
  "mirrors.20i.com/pub/qt.io"
  "www.nic.funet.fi/pub/mirrors/download.qt-project.org"
  "ftp.fau.de/qtproject"
  "qt.mirror.constant.com"
  "ftp.acc.umu.se/mirror/qt.io/qtproject"
  "qtproject.mirror.liquidtelecom.com"
  "ftp.jaist.ac.jp/pub/qtproject"
  "tp1.nluug.nl/languages/qt"
)
#
##############################################################################
# Настройка требуемой версии Qt
##############################################################################
#
set(qt_version "6.9.2")
#
##############################################################################
# Настройки для отладочного режима
##############################################################################
#
# Возможность проверить скрипт без загрузки архивов
# set(DEBUG_DRY_RUN 1)
# Вывод отладочных сообщений
# set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")
#
##############################################################################
# Настройка в зависимости от требуемой ОС
##############################################################################
#
# Получить версию Qt без точек (только цифры)
string(REPLACE "." "" qt_version_dotless "${qt_version}")
#
# Windows x86
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(ARCH_PATH "T:/archive")
    set(url_os "windows_x86")
    set(compiler_id1 "msvc2022_64")
#   set(compiler_id1 "mingw_64")
#   set(compiler_id1 "llvm-mingw_64")
    set(compiler_id "win64_msvc2022_64")
#   set(compiler_id "win64_mingw")
#   set(compiler_id "win64_llvm_mingw")
    set(qt_dir "C:/QT_${qt_version_dotless}")
# Windows arm64
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND 0)
    set(ARCH_PATH "T:/archive")
    set(url_os "windows_arm64")
    set(compiler_id1 "msvc2022_arm64")
    set(compiler_id "win64_msvc2022_arm64")
    set(qt_dir "C:/QT_${qt_version_dotless}")
# Linux x86
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(ARCH_PATH "/var/tmp/archive")
    set(url_os "linux_x64")
    set(compiler_id1 "gcc_64")
    set(compiler_id "linux_gcc_64")
    set(qt_dir "/opt/qt${qt_version_dotless}")
# Linux arm64
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" AND 0)
    set(ARCH_PATH "/var/tmp/archive")
    set(url_os "linux_arm64")
    set(compiler_id1 "arm_64")
    set(compiler_id "linux_arm_64")
    set(qt_dir "/opt/qt${qt_version_dotless}")
# macOS / OS X
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(ARCH_PATH "/tmp/archive")
    set(url_os "mac_x64")
    set(compiler_id1 "macos")
    set(compiler_id "clang_64")
    set(qt_dir "/opt/qt${qt_version_dotless}")
endif()
#
# Получить major-версию Qt
string(SUBSTRING "${qt_version_dotless}" 0 1 qt_major_version)
# Получить длину compiler_id
string(LENGTH "${compiler_id}" compiler_id_len)
#
# Создать директорию для установки Qt
message(STATUS "Загрузка Qt ${qt_version} в ${qt_dir}")
if (NOT DEBUG_DRY_RUN)
    file(MAKE_DIRECTORY "${qt_dir}")
endif()
#
##############################################################################
# Последовательные попытки загружать последовательно с каждого зеркала
##############################################################################
#
foreach(mirror ${qt_mirrors})
    set(qt_base_url "https://${mirror}/online/qtsdkrepository/${url_os}/desktop/qt${qt_major_version}_${qt_version_dotless}/qt${qt_major_version}_${qt_version_dotless}")
    #
    # Выполнить 10 попыток загрузки файла Updates.xml
    foreach(retry RANGE 10)
        cmake_language(EVAL CODE
          "file(DOWNLOAD \"${qt_base_url}/Updates.xml\" \"${ARCH_PATH}/Updates.xml\")"
        )
        file(SIZE ${ARCH_PATH}/Updates.xml fileSize)
        if (fileSize GREATER 0)
            break()
        endif()
    endforeach()
    #
    # Если за 10 попыток файл Updates.xml не загрузился, перейти к следующему зеркалу
    file(SIZE ${ARCH_PATH}/Updates.xml fileSize)
    if (fileSize EQUAL 0)
        continue()
    endif()
    #
    # Прочитать файл Updates.xml в переменную и удалить его
    file(READ ${ARCH_PATH}/Updates.xml updates_xml)
    file(REMOVE ${ARCH_PATH}/Updates.xml)
    message(STATUS "Загружен и прочитан 'Updates.xml'")
    #
    # Получить блоки XML-описаний для указанного компилятора без отладочной информации
    string(REGEX REPLACE "<PackageUpdate>" ";<PackageUpdate>" sections_list "${updates_xml}")
    list(LENGTH sections_list sections_len)
    message(DEBUG "В 'Updates.xml' количество секций ${sections_len}")
    #
    # Последовательно обработать все блоки XML-описаний
    foreach(section ${sections_list})
        #
        # Получить строку в теге <Name>
        string(REGEX MATCH "<Name>(.*)</Name>" match "${section}")
        set(name ${CMAKE_MATCH_1})
        string(LENGTH "${name}" name_len)
        # Проверить тег <name>:
        # 1. Пропустить секцию без этого тега
        if(name_len EQUAL 0)
            continue()
        endif()
        message(DEBUG "Проверяется '${name}'")
        # 2. Проверить, что тег <name> начинается с
        # qt${qt_major_version}.${qt_version_dotless}
        string(FIND "${name}" "qt.qt${qt_major_version}.${qt_version_dotless}" tst)
        if(NOT tst EQUAL 0)
            message(FATAL_ERROR "Строка в теге <name> не начинается с 'qt.qt${qt_major_version}.${qt_version_dotless}'")
            continue()
        endif()
        # 3. Проверить, что эта секция не относится отладочной информации 
        string(FIND "${name}" ".debug_info" tst)
        if(tst GREATER -1)
            message(DEBUG "Пропустить секцию '${name}' с отладочной информацией")
            continue()
        endif()
        # 4. Проверить, что эта секция относится к нужному компилятору
        string(FIND "${name}" ".${compiler_id}" tst)
        # Строка оканчивается на ".${compiler_id}",
        # если tst = name_len - compiler_id_len - 1
        math(EXPR tst_good "${name_len} - ${compiler_id_len} - 1")
        if(NOT tst EQUAL tst_good)
            message(DEBUG "Пропустить секцию '${name}', не относящуюся к компилятору '${compiler_id}'")
            continue()
        endif()
        #
        # Получить строку в теге <DisplayName>
        string(REGEX MATCH "<DisplayName>(.*)</DisplayName>" match "${section}")
        set(display_name ${CMAKE_MATCH_1})
        # Получить строку в теге <Version>
        string(REGEX MATCH "<Version>(.*)</Version>" match "${section}")
        set(version ${CMAKE_MATCH_1})
        # Получить строку в теге <DownloadableArchives>
        string(REGEX MATCH "<DownloadableArchives>(.*)</DownloadableArchives>" match "${section}")
        set(down_list ${CMAKE_MATCH_1})
        # Заменить запятую с пробелом в этой строке на точку с запятой, сформировав список
        string(REPLACE ", " ";" down_list "${down_list}")
        #
        # Определить шаблон директории для разжатия
        set(PREFIX "@TargetDir@/${qt_version}/${compiler_id1}")
        # Разместить строки в тегах <Argument> в два списка:
        # с директориями для разжатия
        set(dest_list "")
        # и именами архивов
        set(arch_list "")
        string(REGEX MATCHALL "<Argument>([^<]+)</Argument>" matches "${section}")
        foreach(match IN LISTS matches)
            string(REGEX REPLACE "<[^>]+>([^<]+)</[^>]+>" "\\1" content "${match}")
            if(content MATCHES "^${PREFIX}")
                list(APPEND dest_list ${content})
            else()
                list(APPEND arch_list ${content})
            endif()
        endforeach(match)
        # Выполнить проверки размеров списков
        list(LENGTH arch_list arch_list_len)
        list(LENGTH dest_list dest_list_len)
        list(LENGTH down_list down_list_len)
        if(NOT ${arch_list_len} EQUAL ${dest_list_len})
            message(FATAL_ERROR "Различается количество элементов списков 'архив' и 'расположение'")
        endif()
        if(NOT ${arch_list_len} EQUAL ${down_list_len})
            message(FATAL_ERROR "Различается количество элементов списков 'архив' и 'загрузка'")
        endif()
        #
        # Перебрать списки, загружая и распаковывая архивы этой секции
        message(STATUS "Загрузка секции '${display_name}'")
        math(EXPR len "${arch_list_len} - 1")
        foreach(i RANGE 0 ${len})
            list(GET dest_list ${i} dest_dir)
            list(GET arch_list ${i} arch_name)
            list(GET down_list ${i} down_name)
            if(NOT "${arch_name}" STREQUAL "${down_name}")
                message(FATAL_ERROR "Различаются имена архивов в списках 'архив' и 'загрузка'")
            endif()
            #
            # Определить директорию для разжатия архива
            string(REPLACE "${PREFIX}" "" dest_dir "${dest_dir}")
            if(^^${content} STREQUAL "^^")
               set(dest_dir "${qt_dir}")
            else()
               set(dest_dir "${qt_dir}${dest_dir}/")
            endif()
            #
            # Загрузить архив
            message(DEBUG "Загрузка архива '${arch_name}'")
            if (NOT DEBUG_DRY_RUN)
                # Выполнить 10 попыток загрузки архива
                foreach(retry RANGE 10)
                    cmake_language(EVAL CODE
                      "file(DOWNLOAD \"${qt_base_url}/${name}/${version}${arch_name}\" \"${ARCH_PATH}/${arch_name}\")"
                    )
                    # Если загрузка успешна (размер файла не равен нулю), завершить попытки загрузки
                    file(SIZE "${ARCH_PATH}/${arch_name}" fileSize)
                    if (fileSize GREATER 0)
                        break()
                    endif()
                endforeach(retry)
            endif()
            #
            # Распаковать архив
            message(DEBUG "Распаковка архива '${arch_name}'")
            if (NOT DEBUG_DRY_RUN)
                execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf "${ARCH_PATH}/${arch_name}"
                  WORKING_DIRECTORY "${dest_dir}"
                  OUTPUT_QUIET
                )
                # Удалить архив
                file(REMOVE "${ARCH_PATH}/${arch_name}")
            endif()
        endforeach(i)
    endforeach(section)
    #
    # Завершить перебор зеркал
    break()
endforeach(mirror)
#
# для Windows поместить системные библиотеки в директорию Qt, чтобы их было проще собрать в установочный пакет
#if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
#    foreach(file vcruntime140.dll concrt140.dll msvcp140_1.dll msvcp140_2.dll
#                 msvcp140_codecvt_ids.dll vcruntime140_1.dll msvcp140.dll)
#    file(INSTALL "C:/Windows/System32/${file}"
#      DESTINATION "qt/bin")
#    endforeach()
#endif()
