cmake_minimum_required(VERSION 3.10)
project(textgen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_executable(textgen
    src/main.cpp
    src/textgen.cpp
)

target_include_directories(textgen PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data.txt
    ${CMAKE_CURRENT_BINARY_DIR}/data.txt
    COPYONLY
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test/tests.cpp)
    find_package(GTest REQUIRED)
    
    add_executable(textgen_tests
        test/tests.cpp
        src/textgen.cpp
    )
    
    target_include_directories(textgen_tests PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    target_link_libraries(textgen_tests GTest::GTest GTest::Main)
    
    enable_testing()
    add_test(NAME textgen_tests COMMAND textgen_tests)
endif()