project(UnixTaskbook)
cmake_minimum_required(VERSION 3.0)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if (${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/aarch64-linux-gnu-g++")
    add_definitions(-D__arm__)
endif()
# set up the kernal of the project
aux_source_directory(./src SRC)
aux_source_directory(./shared/src SHARED_SRC)

include_directories(./inc)
include_directories(./shared/inc)

add_executable(unixTaskbook ${SRC} ${SHARED_SRC})
target_link_libraries(unixTaskbook dl)

install(TARGETS unixTaskbook DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# set up the library
add_compile_options(-std=c++17)
aux_source_directory(./lib/src LIB_SRC)
include_directories(./lib/inc)

foreach(file ${LIB_SRC})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${file})
    add_library(${FILE_NAME} SHARED ${file} ${SHARED_SRC})
    if (${FILE_NAME} STREQUAL "utbThread" AND NOT ${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/aarch64-linux-gnu-g++")
        target_link_libraries(${FILE_NAME} tbb)
    endif()
    install(TARGETS ${FILE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/UnixTaskbook)
endforeach()

