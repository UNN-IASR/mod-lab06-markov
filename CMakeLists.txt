cmake_minimum_required(VERSION 3.10.2)
project(mod-lab06-markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")

# Устанавливаем пути установки
set(TOOL_DEST "bin")
set(LIB_DEST "lib")
set(INCLUDE_DEST "include")

# Для главного CMakeLists.txt
add_subdirectory(src)
add_subdirectory(test)