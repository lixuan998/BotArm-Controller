cmake_minimum_required(VERSION 3.5)

project(BotArm-Controller VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)
find_package(OpenCV REQUIRED)

file(
    GLOB_RECURSE
    SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

file(
    GLOB_RECURSE
    HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

file(
    GLOB_RECURSE
    UI
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/*
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(PROJECT_SOURCES

    ${SOURCE}
    ${HEADER}
    ${UI}

)

add_executable(
    BotArm-Controller
    ${PROJECT_SOURCES}
)

target_link_libraries(BotArm-Controller PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${OpenCV_LIBS})

set_target_properties(BotArm-Controller PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BotArm-Controller)
endif()
