##############################################################################
# Установка пути к требуемой версии Qt
##############################################################################

  # для MacOS
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
      set(QT_ROOT "/opt/qt660")
  # Для Linux
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
      set(QT_ROOT "/opt/qt692")
  # Для Windows
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
      set(QT_ROOT "C:/QT_692")
  endif()

  if(NOT DEFINED QT_ROOT)
      message(FATAL_ERROR "SetQt: Необходимо определить значение QT_ROOT. Выход.")
  endif()
  if("^^${QT_ROOT}" STREQUAL "^^")
      message(FATAL_ERROR "SetQt: Необходимо установить значение QT_ROOT. Выход.")
  endif()
  if(NOT EXISTS "${QT_ROOT}")
      message(FATAL_ERROR "SetQt: Указанная директория расположения Qt ${QT_ROOT} отсутствует. Выход.")
  endif()

  # Сохранить директорию в переменной окружения
  set(ENV{QT_ROOT} "${QT_ROOT}")
