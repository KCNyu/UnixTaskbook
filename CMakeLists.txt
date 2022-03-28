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

macro(test_execute TASK FILE)
    ADD_TEST(NAME test_${TASK}_execute COMMAND unixTaskbook -t ${TASK} -p ../test/${FILE})
    SET_TESTS_PROPERTIES(test_${TASK}_execute
        PROPERTIES PASS_REGULAR_EXPRESSION "Testing successfully finished.")
endmacro(test_execute)

macro(test_info TASK LANGUAGE)
    ADD_TEST(NAME test_${TASK}_info_${LANGUAGE} COMMAND unixTaskbook -t ${TASK} -l ${LANGUAGE})
    SET_TESTS_PROPERTIES(test_${TASK}_info_${LANGUAGE}
        PROPERTIES PASS_REGULAR_EXPRESSION "TASK INFO:")
endmacro(test_info)


foreach(i RANGE 1 9)
    test_info(Dir${i} ru)
    test_info(Dir${i} ch)
endforeach()

foreach(i RANGE 1 17)
    test_info(File${i} ru)
    test_info(File${i} ch)    
endforeach()

foreach(i RANGE 1 16)
    test_info(Text${i} ru)
    test_info(Text${i} ch)
endforeach()

foreach(i RANGE 1 9)
    test_info(Shell${i} ru)
    test_info(Shell${i} ch)
endforeach()

foreach(i RANGE 1 16)
    test_info(Thread${i} ru)
    test_info(Thread${i} ch)
endforeach()

test_execute(File14 B14.c)
test_execute(Shell1 D1.c)
test_execute(Shell6 D6.c)
test_execute(Text14 C14_t.c)
test_execute(Shell4 D4.c)
# test_execute(Dir9 A9.c)
test_execute(Thread8 E8.c)
test_execute(Thread10 E10.c)