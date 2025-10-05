cmake_minimum_required(VERSION 3.9...3.28)

##############################################################################
# Функция удаления файла нулевой длины
##############################################################################
function(remove_zerofile FILENAME)
    if(EXISTS "${FILENAME}")
        file(SIZE "${FILENAME}" FILE_SIZE)
        if(FILE_SIZE EQUAL 0)
            file(REMOVE "${FILENAME}")
        endif()
    endif()
endfunction()
