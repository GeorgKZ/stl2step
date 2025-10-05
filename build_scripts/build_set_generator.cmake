##############################################################################
# Установка генератора для CMAKE
##############################################################################

  # Генератор по умолчанию (для CMake это Makefile)
# set(MULTICONFIG 0)

  # Генератор Makefile - создаёт стандартные файлы makefile
# set(GENERATOR "Unix Makefiles")
# set(MULTICONFIG 0)

  # Генератор Ninja - создаёт конфигурационные файлы build.ninja
  set(GENERATOR "Ninja")
  set(MULTICONFIG 0)

  # Генератор Ninja мультиконфигурационный - создаёт конфигурационные файлы build-<Config>.ninja
# set(GENERATOR "Ninja Multi-Config")
# set(MULTICONFIG 1)

  if( (NOT DEFINED GENERATOR) OR ("^^${GENERATOR}" STREQUAL "^^") )
      message(STATUS "SetGenerator: Генератор не определён, будет использовано значение по умолчанию Unix Makefiles")
  endif()
