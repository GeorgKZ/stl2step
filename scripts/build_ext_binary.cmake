##############################################################################
# Функция сборки и установки указанного субмодуля в директории /submodules
# Аргумент: EXT_NAME - имя субмодуля
##############################################################################

include(ExternalProject)

function(build_ext_binary EXT_NAME)

    ExternalProject_Add(${EXT_NAME}
      PREFIX               ${BUILD_PATH}/external/${EXT_NAME}
      TMP_DIR              ${BUILD_PATH}/external/${EXT_NAME}/tmp
      STAMP_DIR            ${BUILD_PATH}/external/${EXT_NAME}/stamp
      SOURCE_DIR           ${CMAKE_SOURCE_DIR}/submodules/${EXT_NAME}
      LOG_DIR              ${BUILD_PATH}/external/${EXT_NAME}
      BUILD_ALWAYS         OFF
      CONFIGURE_COMMAND    ${CMAKE_COMMAND}
        -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_HOST_SYSTEM_NAME}
        -DBUILDDIR=${BUILD_PATH}/external/${EXT_NAME}
#       -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#       --log-level=${CMAKE_MESSAGE_LOG_LEVEL}
#       -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#       -G ${CMAKE_GENERATOR}
        -S ${CMAKE_SOURCE_DIR}/submodules/${EXT_NAME}
        -B ${BUILD_PATH}/external/${EXT_NAME}/cmake
      BUILD_COMMAND        ${CMAKE_COMMAND}
        --build ${BUILD_PATH}/external/${EXT_NAME}/cmake
        --config ${CMAKE_BUILD_TYPE}
        --parallel
      INSTALL_COMMAND      ${CMAKE_COMMAND}
        --install ${BUILD_PATH}/external/${EXT_NAME}/cmake
        --config ${CMAKE_BUILD_TYPE}
      LOG_CONFIGURE        ON
      LOG_BUILD            ON
      LOG_INSTALL          ON
)

endfunction()
