cmake_minimum_required(VERSION 3.10)
project(markov_text_generator)

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

add_executable(tests
    test/tests.cpp
    src/textgen.cpp
)

target_link_libraries(tests
    GTest::gtest_main
)
