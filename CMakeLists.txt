cmake_minimum_required(VERSION 3.10)
project(MarkovTextGenerator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(markov_gen
  src/main.cpp
  src/textgen.cpp
)

enable_testing()
find_package(GTest REQUIRED)

set(TEST_BINARY_DIR "${CMAKE_BINARY_DIR}/tests")  # Папка tests в корне build/
add_executable(mod-lab06-markov.test test/test.cpp src/textgen.cpp)
set_target_properties(mod-lab06-markov.test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TEST_BINARY_DIR}")


target_link_libraries(mod-lab06-markov.test
  GTest::GTest
  GTest::Main
)

add_test(
    NAME MarkovTest
    COMMAND ./test/mod-lab06-markov.test
)
