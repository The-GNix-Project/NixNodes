cmake_minimum_required(VERSION 3.16)
project(NixNodes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/main.cpp
    src/nodes/Port.cpp
    src/nodes/Node.cpp
    src/nodes/Canvas.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/nodes
)

# 6) Link against Qt6 
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
)
