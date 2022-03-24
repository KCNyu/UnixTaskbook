project(UnixTaskbook)
cmake_minimum_required(VERSION 3.16)

aux_source_directory(./src SRC)
aux_source_directory(./shared/src SHARED_SRC)

include_directories(./inc)
include_directories(./shared/inc)

add_executable(unixTaskbook ${SRC} ${SHARED_SRC})

TARGET_LINK_LIBRARIES(unixTaskbook dl)

add_compile_options(-std=c++17)
aux_source_directory(./lib/src LIB_SRC)
include_directories(./lib/inc)
message(STATUS "LIB_SRC: ${LIB_SRC}")
foreach(file ${LIB_SRC})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${file})
    add_library(${FILE_NAME} SHARED ${file} ${SHARED_SRC})
    if (${FILE_NAME} STREQUAL "utbThread")
        target_link_libraries(${FILE_NAME} tbb)
    endif()
endforeach()