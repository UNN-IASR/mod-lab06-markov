set(TEST_PROJECT_NAME ${PROJECT_NAME}.test)

set(HEADER_PATH "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(HEADER ${HEADER_PATH}/textgen.h)
set(SRC "${${PROJECT_NAME}_SOURCE_DIR}/src/textgen.cpp")

add_executable(${TEST_PROJECT_NAME}
    AllTests.cpp
    tests.cpp
    ${SRC}
)

target_include_directories(${TEST_PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/include
)

target_link_libraries(${TEST_PROJECT_NAME}
    ${PROJECT_NAME}
    pthread
    GTest::GTest
    GTest::Main
)

enable_testing()
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})