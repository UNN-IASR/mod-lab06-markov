cmake_minimum_required (VERSION 3.10.2)
project (mod-lab06-markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

add_definitions(
    -DINPUT_FILE_PATH="${CMAKE_SOURCE_DIR}/input_data.txt"
    -DOUTPUT_FILE_PATH="${CMAKE_SOURCE_DIR}/result/gen.txt"
)

set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")

add_subdirectory(src)
add_subdirectory(test)
