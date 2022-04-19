project(UnixTaskbook)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
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
    if (${FILE_NAME} STREQUAL "utbThread" AND NOT ${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/aarch64-linux-gnu-g++" AND CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${FILE_NAME} tbb)
    endif()
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        install(TARGETS ${FILE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/UnixTaskbook)
    elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        install(TARGETS ${FILE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
    endif()
endforeach()

install(CODE "EXECUTE_PROCESS(COMMAND cp ../lib/unixTaskbook.conf /etc/ld.so.conf.d)")
install(CODE "EXECUTE_PROCESS(COMMAND ldconfig)")

# set up the test
enable_testing()

macro(test_execute_with_all TASK)
    ADD_TEST(NAME test_${TASK}_execute_with_all COMMAND unixTaskbook -t ./${TASK}.c WORKING_DIRECTORY ../test/)
    SET_TESTS_PROPERTIES(test_${TASK}_execute_with_all
        PROPERTIES PASS_REGULAR_EXPRESSION "Testing successfully finished")
endmacro(test_execute_with_all)

macro(test_execute_without_path TASK)
    ADD_TEST(NAME test_${TASK}_execute_without_path COMMAND unixTaskbook -t ${TASK}.c WORKING_DIRECTORY ../test/)
    SET_TESTS_PROPERTIES(test_${TASK}_execute_without_path
        PROPERTIES PASS_REGULAR_EXPRESSION "Testing successfully finished")
endmacro(test_execute_without_path)

macro(test_execute_without_extension TASK)
    ADD_TEST(NAME test_${TASK}_execute_without_extension COMMAND unixTaskbook  -t ./${TASK} WORKING_DIRECTORY ../test/)
    SET_TESTS_PROPERTIES(test_${TASK}_execute_without_extension
        PROPERTIES PASS_REGULAR_EXPRESSION "Testing successfully finished")
endmacro(test_execute_without_extension)

macro(test_execute_without_path_extension TASK)
    ADD_TEST(NAME test_${TASK}_execute_without_path_extension COMMAND unixTaskbook  -t ${TASK} WORKING_DIRECTORY ../test/)
    SET_TESTS_PROPERTIES(test_${TASK}_execute_without_extension
        PROPERTIES PASS_REGULAR_EXPRESSION "Testing successfully finished")
endmacro(test_execute_without_path_extension)

macro(test_execute TASK)
test_execute_with_all(${TASK})
test_execute_without_extension(${TASK})
test_execute_without_path(${TASK})
test_execute_without_path_extension(${TASK})
endmacro(test_execute)

macro(test_info TASK LANGUAGE)
    ADD_TEST(NAME test_${TASK}_info_${LANGUAGE} COMMAND unixTaskbook -t ${TASK} -l ${LANGUAGE})
    SET_TESTS_PROPERTIES(test_${TASK}_info_${LANGUAGE}
        PROPERTIES PASS_REGULAR_EXPRESSION "TASK INFO")
endmacro(test_info)

macro(test_execute_dir DIR)
    ADD_TEST(NAME test_execute_dir COMMAND unixTaskbook -d ${DIR})
    SET_TESTS_PROPERTIES(test_execute_dir
        PROPERTIES PASS_REGULAR_EXPRESSION "Finish checking the directory")
endmacro(test_execute_dir)

foreach(i RANGE 1 9)
    test_info(Dir${i} ru)
    test_info(Dir${i} ch)
    test_info(Dir${i} en)
endforeach()

foreach(i RANGE 1 17)
    test_info(File${i} ru)
    test_info(File${i} ch)
    test_info(File${i} en)    
endforeach()

foreach(i RANGE 1 16)
    test_info(Text${i} ru)
    test_info(Text${i} ch)
    test_info(Text${i} en)
endforeach()

foreach(i RANGE 1 9)
    test_info(Shell${i} ru)
    test_info(Shell${i} ch)
    test_info(Shell${i} en)
endforeach()

foreach(i RANGE 1 16)
    test_info(Thread${i} ru)
    test_info(Thread${i} ch)
    test_info(Thread${i} en)
endforeach()

test_execute(Dir9)
test_execute(Shell1)
test_execute(Shell6)
test_execute(Text11)
test_execute(Text14)
test_execute(Shell4)
test_execute(Thread8)
test_execute(Thread10)
test_execute_dir(../test)