cmake_minimum_required(VERSION 3.10)
project(mod-lab06-markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_executable(textgen
    src/main.cpp
    src/textgen.cpp
)

add_executable(mod-lab06-markov.test
    test/tests.cpp
    src/textgen.cpp
)

target_link_libraries(mod-lab06-markov.test
    GTest::gtest_main
)

set_target_properties(textgen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(mod-lab06-markov.test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
)

enable_testing()
add_test(NAME mod-lab06-markov.test COMMAND mod-lab06-markov.test)
