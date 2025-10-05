##############################################################################
# Информация о проекте
##############################################################################

# Имя проекта, соответствующее имени исполняемого файла
set(CUSTOM_PROJECT_NAME "Stl2Step")
# Версия проекта
set(CUSTOM_VERSION "1.0")
# Описание проекта
set(CUSTOM_DESCRIPTION "STL to ISO 10303 STEP converter")
set(CUSTOM_HOMEPAGE_URL "https://github.com/GeorgKZ/stl2step")
# Используемый язык программирования
set(CUSTOM_LANGUAGES CXX)

# Поставщик установочного пакета
set(CUSTOM_PROJECT_VENDOR "GeorgKZ")

# Контактные данные поставщика установочного пакета
set(CUSTOM_PROJECT_MAINTAINER "${PROJECT_VENDOR} https://github.com/GeorgKZ")

# Путь к файлу значка SVG проекта
set(CUSTOM_SVG_ICON_FILE "${CMAKE_SOURCE_DIR}/icons/icon.svg")

# Список компонентов проекта с путями, которые включаются как поддиректории
set(PROJECT_MODULES_LIST
  "stl2step"
)

# Путь к директории с изображениями для Doxygen
set(CUSTOM_IMAGES "${CMAKE_SOURCE_DIR}/doc/images")

#  Использовать MathJax, использовать расширения
set(CUSTOM_MATHJAX require ams mathtools textcomp unicode)

# Аргументы анализатора PVS-Studio
set(CUSTOM_PVS_ARGS -d V122,V2014)

##############################################################################
# Настройки Qt
##############################################################################

# Флаг использования Qt
#set(USE_QT

# Список необходимых для приложения плюгинов
#set(QT_PLUGIN_LIST

# Подсистемы Qt, для которых требуются переводы
#set(QT_SYSTEMS

# Список необходимых для приложения модулей Qt
#set(QT_MODULES_LIST

# Настройка языков локализации Qt:
# set(QT_LANG

##############################################################################
# Аргументы и комментарии тестов
##############################################################################

  # Список комментариев и аргументов
  set(TEST_ARGUMENTS_LIST
    "Запуск без параметров - вывод справки"
    ""
    "Запуск без указания результирующего файла"
    "--d3 --dp --stl ../tests/metals_l.stl"
    "Запуск без указания исходного файла"
    "--d3 --dp --out ${TEST_RESULTS}/Empty.step"
    "Простой тест с профилированием - микросхема с выводами SMD"
    "--dp --copy 0.65 0 0 1.3 0 0 1.95 0 0 --color 0.824 0.82 0.781 --name low pin --stl ../tests/metals_l.stl --copy 0.65 0 0 1.3 0 0 1.95 0 0 --name high pin --stl ../tests/metals h.stl --color 0.3 0.3 0.3 --name plastic body --stl ../tests/plastic.stl --color 0.95 0.95 0.95 --name white label --stl ../tests/label.stl --out ${TEST_RESULTS}/SimpleTest.step"
    "Тест (с отладочными сообщениями) с дублирующимся треугольником в файле STL"
    "--d3 --ocn --stl ../tests/blue.stl --out ${TEST_RESULTS}/Blue.step"
    "Тест (с отладочными сообщениями) с выпукло-вогнутой поверхностью"
    "--d3 --ocn --stl ../tests/bad_blue.stl --out ${TEST_RESULTS}/Bad_blue.step"
  )
