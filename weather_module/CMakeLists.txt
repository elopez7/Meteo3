 cmake_minimum_required(VERSION 3.23)

 set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Qml)

 set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
     CACHE STRING "Qt Creator weather module import path"
     FORCE
 )

qt_add_library(weatherModule STATIC)
qt6_add_qml_module(weatherModule
    URI "weatherModule"
    AUTO_RESOURCE_PREFIX
    VERSION 1.0
    PLUGIN_TARGET weatherPlugin
    IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    SOURCES
        enumconverters.h
        apiclient.h
        apiclient.cpp
        datasource.h
        datasource.cpp
        weatherDTO.h
        dailyweathermodel.h
        dailyweathermodel.cpp
    RESOURCES
        weatherResources.qrc
)

target_include_directories(weatherModule
    PUBLIC "{CMAKE_CURRENT_SOURCE_DIR}/../"
    PRIVATE "{CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(weatherModule
    PRIVATE Qt6::Core
    PRIVATE Qt6::Qml
)
