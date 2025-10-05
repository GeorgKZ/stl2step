##############################################################################
# Скрипт формирования значков требуемых типов и размеров
# Аргументы:
# SVGTORASTER_HINT - путь к собранной утилите преобразования значков
# SOURCE_SVG - путь/имя исходного значка формата SVG
# ICONS_PATH - путь, по которому будут размещены созданные значки
##############################################################################

# Найти исполняемый файл SvgToRaster
find_program (
  SVGTORASTER_EXE
  NAMES svgtoraster svgtoraster.exe
  HINTS ${SVGTORASTER_HINT}
  HINTS ${SVGTORASTER_HINT}/bin
  REQUIRED
  NO_DEFAULT_PATH
  NO_PACKAGE_ROOT_PATH
  NO_CMAKE_PATH
  NO_CMAKE_ENVIRONMENT_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PATH
)

# Выполнить SvgToRaster для создания значков
execute_process(
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 16   --o ${ICONS_PATH}/icon_16.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 24   --o ${ICONS_PATH}/icon_24.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 32   --o ${ICONS_PATH}/icon_32.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 48   --o ${ICONS_PATH}/icon_48.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 64   --o ${ICONS_PATH}/icon_64.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 128  --o ${ICONS_PATH}/icon_128.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 256  --o ${ICONS_PATH}/icon_256.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 512  --o ${ICONS_PATH}/icon_512.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 1024 --o ${ICONS_PATH}/icon_1024.png
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 32   --o ${ICONS_PATH}/icon_32.xpm
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG} --s 16 24 32 48 64 128 256 --o ${ICONS_PATH}/icon.ico
  COMMAND ${SVGTORASTER_EXE} --i ${SOURCE_SVG}          --o ${ICONS_PATH}/icon.icns
  RESULT_VARIABLE result
  OUTPUT_VARIABLE output
  ERROR_VARIABLE  output_error
)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Ошибка выполнения скрипта build_icons: ${output_error}")
endif()
