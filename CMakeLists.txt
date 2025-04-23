cmake_minimum_required(VERSION 3.16)
project(NixNodes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt package
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/lang/io.cpp
    src/lang/node.cpp
    src/lang/graph.cpp
    src/lang/connection.cpp
)

set(HEADERS
    include/lang/io.hpp
    include/lang/graph.hpp
    include/lang/connection.hpp
    include/lang/node.hpp
)

# set(RESOURCES
#     resources/resources.qrc
# )

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Enable automoc, autouic, and autorcc for Qt
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

add_subdirectory(extern/QtNodes)
include_directories(${QtNodes_INCLUDE_DIRS})