cmake_minimum_required(VERSION 3.16)
project(NixNodes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Find the Qt6 Widgets module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 2) Add the QtNodes subproject
#    This defines the target QtNodes::QtNodes and installs its include paths.
# add_subdirectory(extern/QtNodes)

# 3) Define your executable
set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# 4) Tell CMake to handle Qt's MOC/UI/RCC automatically
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# 5) Add your own include directory
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 6) Link against Qt6 and QtNodes
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
        # QtNodes::QtNodes
)

# 7) In case QtNodes tries to create resource dirs in-source
set(QT_DISABLE_SOURCE_DIR_CREATION ON CACHE BOOL "" FORCE)
