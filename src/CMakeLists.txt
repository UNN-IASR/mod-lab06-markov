# Указываем пути к файлам
set(HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/../include/textgen.h
)
set(SOURCE_FILES
  textgen.cpp
)

# Создаем библиотеку
add_library(${PROJECT_NAME} SHARED
  ${SOURCE_FILES}
)

# Указываем пути для заголовочных файлов
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
  pthread
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}.info main.cpp)

target_include_directories(${PROJECT_NAME}.info
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME}.info
  ${PROJECT_NAME}
)

# Установка
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${LIB_DEST}
  ARCHIVE DESTINATION ${LIB_DEST}
  COMPONENT library
)

install(TARGETS ${PROJECT_NAME}.info
  RUNTIME DESTINATION ${TOOL_DEST}
  COMPONENT library
)

install(FILES ${HEADER_FILES}
  DESTINATION ${INCLUDE_DEST}
)