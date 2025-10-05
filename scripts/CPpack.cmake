##############################################################################
# Скрипт выбора типов установочных пакетов в зависимости от целевой среды выполнения
# и настройка параметров для разных типов пакетов
##############################################################################

# При сборке для работы в среде Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    set(CPACK_GENERATOR
      "DEB"
    )
    set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# При сборке для работы в среде MacOS/OS X
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    set(CPACK_GENERATOR
#     "Bundle"
      "DragNDrop"  # Bundle не используется, это выбор или-или
    )

    set(CPACK_PACKAGING_INSTALL_PREFIX "/")

# При сборке для работы в среде Windows
elseif ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

#    find_program(NSIS_EXE
#      NAMES "makensis.exe" 
#      PATHS "C:/nsis-windows-x86_64/nsis-3.11"
#      PATHS "C:/Program Files (x86)/NSIS"
#    )

    set(CPACK_GENERATOR
# Для IFW необходим binarycreator
#       "IFW"
        "NSIS" 
        "ZIP"
    )
    set(CPACK_PACKAGING_INSTALL_PREFIX "")

else()
    message(WARNING "Неизвестная среда сборки " ${CMAKE_SYSTEM_NAME})
endif()

##############################################################################
# Настойки, общие для всех типов установочных пакетов
# https://cmake.org/cmake/help/latest/module/CPack.html
##############################################################################

# Имя для установочного пакета, по умолчанию PROJECT_NAME
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

# Имя поставщика
set(CPACK_PACKAGE_VENDOR "${PROJECT_VENDOR}")

# Директория, в которой будет производиться упаковка
set(CPACK_PACKAGE_DIRECTORY "${BUILD_PATH}/packaging")

# Версия упаковываемого приложения
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

# Описание приложения (для экрана приветствия)
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})

# Текстовый файл с описанием приложения, если отсутствует,
# используется значение CPACK_PACKAGE_DESCRIPTION
# CPACK_PACKAGE_DESCRIPTION_FILE

# Краткое описание приложения (буквально два-три слова)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})

# Домашняя страница пакета (по умолчанию CMAKE_PROJECT_HOMEPAGE_URL)
set(CPACK_PACKAGE_HOMEPAGE_URL "${CMAKE_PROJECT_HOMEPAGE_URL}")

# Имя файла установочного пакета без расширения
# PACK_PACKAGE_FILE_NAME

# Директория целевой среды выполненния, в которую будет выполнена установка
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME_LOWERCASE}-${CMAKE_PROJECT_VERSION})

# Изображение для установщика с графическим интерфейсом
# CPACK_PACKAGE_ICON

# Алгоритм, который будет использован для расчёта контрольной суммы пакета,
# будет указан в файле с именем ${CPACK_PACKAGE_FILE_NAME}.${CPACK_PACKAGE_CHECKSUM}
# CPACK_PACKAGE_CHECKSUM

# CPACK_PROJECT_CONFIG_FILE

# Лицензия, которая будет встроена в установочный пакет (для WIX необходимо расширение .txt)
file(CREATE_LINK
  ${CMAKE_SOURCE_DIR}/LICENSE
  ${MISC_PATH}/LICENSE.txt
  COPY_ON_ERROR)
set(CPACK_RESOURCE_FILE_LICENSE ${MISC_PATH}/LICENSE.txt)

# Файл ReadMe, который будет встроен в инсталлятор (для PRODUCTBUILD необходимо расширение .txt)
file(CREATE_LINK
  ${CMAKE_SOURCE_DIR}/README.md
  ${MISC_PATH}/readme.txt
  COPY_ON_ERROR)
set(CPACK_RESOURCE_FILE_README ${MISC_PATH}/readme.txt)

#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/Description.txt)
#set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_SOURCE_DIR}/Welcome.txt)

# CPACK_MONOLITHIC_INSTALL
# CPACK_OUTPUT_CONFIG_FILE
# CPACK_PACKAGE_EXECUTABLES
# CPACK_STRIP_FILES

# Переменные CPACK_... будут записаны в файлы конфигурации как есть, т.е.
# никакие управляющий символы не будут обработаны
set(CPACK_VERBATIM_VARIABLES YES)

# Количество потоков, которые будут задействованы при сжатии установщика
set(CPACK_THREADS 4)

# Контактные данные поставщика установочного пакета
set(CPACK_PACKAGE_CONTACT "${PROJECT_MAINTAINER}")


#if (APPLE)
#  set(CPACK_INSTALL_PREFIX "/")
#endif()

#if (NOT WIN32)
# устанавливать префикс пути установки автоматически
#  set(CPACK_SET_DESTDIR ON)

#  set(CPACK_STRIP_FILES ON)

 # if (NOT APPLE)
 #   set(CPACK_INSTALL_CMAKE_PROJECTS
 #       "${CMAKE_BINARY_DIR};${PROJECT_NAME};ALL;/"
 #       "${CMAKE_BINARY_DIR};Dependencies;Dependencies;/"
 #   )
 # endif()
#endif()

##############################################################################
# Специфичные для создания пакетов-архивов (.7z, .tar, .tar.bz2, .tar.gz,
# .tar.xz, .tar.Z, .tar.zst, .zip) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/archive.html
##############################################################################

##############################################################################
# Специфичные для создания пакета Bundle настройки
# https://cmake.org/cmake/help/latest/cpack_gen/bundle.html
# Особенности: один и более исполняемых файлов на пакет, нет необходимости
# установки опции MACOS_BUNDLE для исполняемого файла, директива install
# устанавливает файлы/директории в директорию Resources, автоматически
# размещает библиотеки и зависимости
##############################################################################

# Имя пакета
set(CPACK_BUNDLE_NAME "${PROJECT_NAME}-bundle")
# Файл Info.plist приложения
set(CPACK_BUNDLE_PLIST "${CMAKE_INSTALL_PREFIX}/${BUNDLE_CONTENT_PATH}/Info.plist")
# Значок прилжения
set(CPACK_BUNDLE_ICON "${ICONS_PATH}/${PROJECT_NAME_LOWERCASE}.icns")

##############################################################################
# Специфичные для создания пакета Cygwin настройки
# https://cmake.org/cmake/help/latest/cpack_gen/cygwin.html
##############################################################################

##############################################################################
# Специфичные для создания пакета Debian (.deb) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/deb.html
##############################################################################

# Разрешить покомпонентную установку
set(CPACK_DEB_COMPONENT_INSTALL OFF)

# Имя пакета Debian - обычно CPACK_PACKAGE_NAME в нижнем регистре
set(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME_LOWERCASE})

# Имя файла пакета Debian
#set(CPACK_DEBIAN_FILE_NAME ${PROJECT_NAME}.deb)

# CPACK_DEBIAN_PACKAGE_EPOCH

# Версия приложения в пакете
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

# Архитектура целевого процессора CPACK_DEBIAN_PACKAGE_ARCHITECTURE
# устанавливается автоматически по архитектуре среды выполнения

# Зависимости от других пакетов
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdouble-conversion3,libxcb-cursor0")

#  Поставщик пакета (по умолчанию CPACK_PACKAGE_CONTACT)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})

# Описание пакета (по умолчанию CPACK_PACKAGE_DESCRIPTION или
# содержимое файла CPACK_PACKAGE_DESCRIPTION_FILE)
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})

# Секция пакета (admin, cli-mono, comm, database, debug, devel, doc, editors, education,
# electronics, embedded, fonts, games, gnome, gnu-r, gnustep, graphics, hamradio, haskell,
# httpd, interpreters, introspection, java, javascript, kde, kernel, libdevel, libs, lisp,
# localization, mail, math, metapackages, misc, net, news, ocaml, oldlibs, otherosfs, perl,
# php, python, ruby, rust, science, shells, sound, tasks, tex, text, utils, vcs, video, web,
# x11, xfce, zope)
# По умолчанию разработка - devel
set(CPACK_DEBIAN_PACKAGE_SECTION misc)

# Используемый формат архива пакета (по умолчанию gnutar)
set(CPACK_DEBIAN_COMPRESSION_ARCHIVE gnutar)

# Алгоритм сжатия пакета (lzma, xz, bzip2, gzip, zstd)
set(CPACK_DEBIAN_COMPRESSION_TYPE gzip)

# Приоритет установки (required, important, standard, optional, extra)
# По умолчанию "необязательно" - optional
set(CPACK_DEBIAN_PACKAGE_PRIORITY optional)

# Домашняя страница пакета (по умолчанию CMAKE_PROJECT_HOMEPAGE_URL)
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${CMAKE_PROJECT_HOMEPAGE_URL}")

# Создавать более качественный (если установлено ON) список зависимостей
# CPACK_DEBIAN_PACKAGE_SHLIBDEPS
# CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS

##############################################################################
# Специфичные для создания пакета DragNDrop (.dmg) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/dmg.html
# Особенности: только один исполняемый файл на пакет, необходимость
# установки опции MACOS_BUNDLE для исполняемого файла
##############################################################################

# Имя тома создаваемого образа (по умолчанию CPACK_PACKAGE_FILE_NAME)
set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME}-dragndrop")

# Формат образа диска (по умолчанию UDZO):
# UDRO (UDIF read-only), UDZO (UDIF zlib-compressed) или UDBZ (UDIF bzip2-compressed)
set(CPACK_DMG_FORMAT UDZO)

# Путь к пользовательскому файлу .DS_Store file. Этот файл используется для 
# определения расположения/геометрии оконного менеджера Finder, а также расположения
# компонентов (скрытые полоски инструментов, разположение значков и т.д.).
# Этот файл должен быть создан при помощи Finder (вручную или скриптом).
# CPACK_DMG_DS_STORE

# Путь к пользовательскому файлу AppleScript. Этот скрипт используется для создания
# файла .DS_Store, который определяет расположение/геометрию оконного менеджера Finder,
# а также расположение компонентов (скрытые полоски инструментов, разположение значков и т.д.).
# При этом нет необходимости использования CPACK_DMG_DS_STORE, так как файл .DS_Store будет создан скриптом.
# CPACK_DMG_DS_STORE_SETUP_SCRIPT

# Path to an image file to be used as the background. This file will be copied
# to .background/background.<ext>, where <ext> is the original image file extension.
# The background image is installed into the image before CPACK_DMG_DS_STORE_SETUP_SCRIPT
# is executed or CPACK_DMG_DS_STORE is installed. By default no background image is set.
# CPACK_DMG_BACKGROUND_IMAGE

# По умолчанию (OFF) включать символическую ссылку на директорию /Applications в образ диска.
# При установке ON ссылка не включается в образ.
set(CPACK_DMG_DISABLE_APPLICATIONS_SYMLINK OFF)

# Control whether CPACK_RESOURCE_FILE_LICENSE, if set to a non-default value,
# is used as the license agreement provided when mounting the DMG.
# If CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE is not set, cpack(1) defaults to off.
# In a CMake project that uses the CPack module to generate CPackConfig.cmake,
# CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE must be explicitly enabled by the project
# to activate the SLA. See policy CMP0133.
# CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE

# Directory where license and menu files for different languages are stored.
# Setting this causes CPack to look for a <language>.menu.txt and <language>.license.txt
# or <language>.license.rtf file for every language defined in CPACK_DMG_SLA_LANGUAGES.
# If both this variable and CPACK_RESOURCE_FILE_LICENSE are set, CPack will only look
# for the menu files and use the same license file for all languages.
# If both <language>.license.txt and <language>.license.rtf exist, the .txt file will be used.
# CPACK_DMG_SLA_DIR

# Languages for which a license agreement is provided when mounting the generated DMG.
# A menu file consists of 9 lines of text. The first line is is the name of the language
# itself, uppercase, in English (e.g. German). The other lines are translations of the
# following strings:
# CPACK_DMG_SLA_LANGUAGES

# Формат файловой системы (по умолчанию HFS+):
# Common values are APFS and HFS+.
set(CPACK_DMG_FILESYSTEM HFS+)

# Path to the hdiutil command used to operate on disk image files on macOS.
# This variable can be used to override the automatically detected command
# (or specify its location if the auto-detection fails to find it).
# CPACK_COMMAND_HDIUTIL

# Path to the SetFile command used to set extended attributes on files
# and directories on macOS. This variable can be used to override
# the automatically detected command (or specify its location if
# the auto-detection fails to find it).
# CPACK_COMMAND_SETFILE

# Path to the Rez command used to compile resources on macOS.
# This variable can be used to override the automatically detected command
# (or specify its location if the auto-detection fails to find it).
# CPACK_COMMAND_REZ

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/innosetup.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/ifw.html
##############################################################################

##############################################################################
# Специфичные для создания пакета NSIS (.msi) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/nsis.html
##############################################################################

# Корневая директория по умолчанию для инсталлятора NSIS.
# Полный путь будет таким: ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_PACKAGE_INSTALL_DIRECTORY}
set(CPACK_NSIS_INSTALL_ROOT "C:\\Program Files")

# Значок (*.ico) для установки пакета
if(DEFINED ICONS_PATH)
    set(CPACK_NSIS_MUI_ICON "${ICONS_PATH}/icon.ico")
endif()

# Значок (*.ico) для удаления пакета
if(DEFINED ICONS_PATH)
    set(CPACK_NSIS_MUI_UNIICON "${ICONS_PATH}/icon.ico")
endif()

# Не документировано
#set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE

# Имя файла-битмапа для MUI_WELCOMEFINISHPAGE_BITMAP
#set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP

# Имя файла-битмапа для MUI_UNWELCOMEFINISHPAGE_BITMAP
#set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP

# Дополнительные директтивы NSIS, которые будут добавлены в начало секции установки, before your install tree is available on the target system.
#set(CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS

# Дополнительные директтивы NSIS, которые будут добавлены в конец секции установки, after your install tree is available on the target system.
#set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS

# Дополнительные директтивы NSIS, которые будут добавлены к секции удаления, before your install tree is removed from the target system.
#set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS

# Параметры, которые будут переданы архиватору
set(CPACK_NSIS_COMPRESSOR "/SOLID lzma\n SetCompressorDictSize 64")

# Спросить (при значнии ON) о необходимости удаления предыдущих версий приложения
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

# Необходимость (при значнии ON) добавить к переменной окружения PATH путь к приложению
set(CPACK_NSIS_MODIFY_PATH OFF)

# Название программы, отображаемое в "Программах и компонентах" панели управления Windows
set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

# Название, отображаемое в строке заголовка окна установщика,
# а также на приветственной (если не указано CPACK_NSIS_WELCOME_TITLE)
# и заключительной странице (если не указано CPACK_NSIS_FINISH_TITLE)
set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

# Путь к исполняемому файлу, содержащему значок для установщика
set(CPACK_NSIS_INSTALLED_ICON_NAME "./${PROJECT_NAME_LOWERCASE}.exe")

# Ссылка (URL) на страницу веб-сайта, где представлена помощь в установке приложения.
#set(CPACK_NSIS_HELP_LINK

# Ссылка (URL) на страницу веб-сайта, где представлена дополнительная информация о приложении.
# Эта ссылка будет добавлена в реестр и в ссылки на программы в инструменте «Добавить или удалить программы».
set(CPACK_NSIS_URL_INFO_ABOUT "${PROJECT_HOMEPAGE_URL}")

# Contact information for questions and comments about the installation process.
#set(CPACK_NSIS_CONTACT

# Custom install directory for the specified component <compName> instead of $INSTDIR.
#set(CPACK_NSIS_<compName>_INSTALL_DIRECTORY

# Дополнительные директивы NSIS для создания ярлычков в меню "Пуск"
set(CPACK_NSIS_CREATE_ICONS_EXTRA
   "CreateShortCut '$SMPROGRAMS\\$STARTMENU_FOLDER\\${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}.lnk' '$INSTDIR\\${PROJECT_NAME_LOWERCASE}.exe'"
)

# Дополнительные директивы NSIS для удаления ярлычков в меню "Пуск".
#set(CPACK_NSIS_DELETE_ICONS_EXTRA
#  "Delete '$DESKTOP\\${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}.lnk'"
#)

# Путь (по умолчанию bin) к исполняемым файлам пакета для меню "Пуск"
set(CPACK_NSIS_EXECUTABLES_DIRECTORY "./")

# Исполняемый файл, который будет предложено запустить после установки
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "./${PROJECT_NAME_LOWERCASE}.exe")

# Specify links in [application] menu. This should contain a list of pair link link name. The link may be a URL or a path relative to installation prefix. Like:
#
# set(CPACK_NSIS_MENU_LINKS
#   "doc/cmake-@CMake_VERSION_MAJOR@.@CMake_VERSION_MINOR@/cmake.html"
#   "CMake Help" "https://cmake.org" "CMake Web Site")
#set(CPACK_NSIS_MENU_LINKS

# Имя программы для удаления приложения. По умолчанию Uninstall.
#set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")

# Название, отображаемое на странице приветствия
set(CPACK_NSIS_WELCOME_TITLE "Установка ${PROJECT_DESCRIPTION} ${CMAKE_PROJECT_VERSION}")

# Отображать (значение ON) заголовок приложения на странице приветствия в три строки, а не в две
set(CPACK_NSIS_WELCOME_TITLE_3LINES ON)

# Название, отображаемое на заключительной странице
set(CPACK_NSIS_FINISH_TITLE "Завершение установки ${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

# Отображать (значение ON) заголовок приложения на заключительной странице в три строки, а не в две
set(CPACK_NSIS_FINISH_TITLE_3LINES ON)

# Изображение, отображаемое на заголовке установочных окон
#set(CPACK_NSIS_MUI_HEADERIMAGE

# Если установлено (значение ON), указывает в манифесте установщика, что установщик
# может корректно масштабироваться при работе с экранами с высокой плотностью пикселей (DPI-aware)
set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)

# Если установлено, updates the text at the bottom of the install window. To set the string to blank, use a space (" ").
#set(CPACK_NSIS_BRANDING_TEXT " ")

# Если установлено, trim down the size of the control to the size of the branding text string. Allowed values for this variable are LEFT, CENTER or RIGHT. If not specified, the default behavior is LEFT.
#set(CPACK_NSIS_BRANDING_TEXT_TRIM_POSITION CENTER)

# Если установлено, то указывает имя исполняемого файла NSIS (по умолчанию makensis)
#set(CPACK_NSIS_EXECUTABLE makensis)

# Если установлено (значение ON), то при установке лицензия не бует отображаться
set(CPACK_NSIS_IGNORE_LICENSE_PAGE OFF)

# This variable is a semicolon-separated list of arguments to prepend to the nsis script to run. If the arguments do not start with a / or a -, it will add one automatically to the corresponding arguments. The command that will be run is:
# makensis.exe <preArgs>... "nsisFileName.nsi" <postArgs>...
# where <preArgs>... is constructed from CPACK_NSIS_EXECUTABLE_PRE_ARGUMENTS and <postArgs>... is constructed from CPACK_NSIS_EXECUTABLE_POST_ARGUMENTS.
#set(CPACK_NSIS_EXECUTABLE_PRE_ARGUMENTS

# This variable is a semicolon-separated list of arguments to append to the nsis script to run. If the arguments do not start with a / or a -, it will add one automatically to the corresponding arguments. The command that will be run is:
# makensis.exe <preArgs>... "nsisFileName.nsi" <postArgs>...
# where <preArgs>... is constructed from CPACK_NSIS_EXECUTABLE_PRE_ARGUMENTS and <postArgs>... is constructed from CPACK_NSIS_EXECUTABLE_POST_ARGUMENTS.
#set(CPACK_NSIS_EXECUTABLE_POST_ARGUMENTS

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/nuget.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/packagemaker.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/productbuild.html
##############################################################################

##############################################################################
# Специфичные для создания пакета RPM (.rpm) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/rpm.html
##############################################################################

# Обычно CPACK_PACKAGE_DESCRIPTION_SUMMARY
set(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
# defaults to lower case of CPACK_PACKAGE_NAME
set(CPACK_RPM_PACKAGE_NAME ${PROJECT_NAME_LOWERCASE})
# Обычно of CPACK_PACKAGE_VERSION.
set(CPACK_RPM_PACKAGE_VERSION $CPACK_PACKAGE_VERSION})
# Архитектура целевого процессора
set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
# Версия файла RPM
set(CPACK_RPM_PACKAGE_RELEASE "1")
#
set(CPACK_RPM_PACKAGE_GROUP "none")
#
set(CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})

##############################################################################
# Специфичные для создания пакета WIX (.msi) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/wix.html
##############################################################################

if(DEFINED ICONS_PATH)
    set(CPACK_WIX_PRODUCT_ICON "${ICONS_PATH}/icon.ico")
endif()

set(CPACK_WIX_UPGRADE_GUID "E6A093A5-83DE-47FA-B669-1DE0102BE92A")
set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

##############################################################################
# Подключить CPack из расширений CMake
##############################################################################

include(CPack)
