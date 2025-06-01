cmake_minimum_required(VERSION 3.14)
project(Task4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    mainwindow.cpp
    students_data.cpp
    logger.cpp
)

set(HEADERS
    mainwindow.h
    students_data.h
    logger.h
)

add_executable(Task4 main.cpp ${SOURCES} ${HEADERS})

# Подключаем include директории
# target_include_directories(Task4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Линкуем с Qt
target_link_libraries(Task4 PRIVATE Qt5::Widgets) 