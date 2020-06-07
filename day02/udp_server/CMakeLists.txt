cmake_minimum_required(VERSION 3.16)
project(udp_server)

set(CMAKE_CXX_STANDARD 11)

# Auto call moc, uic, rcc to process qt extend
set(CMAKE_AUTOMOC ON) # signal and slot
set(CMAKE_AUTOUIC ON) # ui
set(CMAKE_AUTORCC ON) # position

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../3rdparty/qt/bin)

# Set find__xxx path
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/qt)

# Qt config
file(
        WRITE
        ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/qt.conf
        "[Paths]
#Prefix=../lib/Qt
#Binaries=bin
#Libraries=lib
Plugins=${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qt/plugins
#Imports=imports
#Qml2Imports=qml"
)

# Find Qt libraries
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)

set(QT_LIBRARIES
        ${Qt5_LIBRARIES}
        ${Qt5Gui_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5OpenGL_LIBRARIES}
        ${Qt5Network_LIBRARIES}
        ${Qt5Xml_LIBRARIES}
        ${Qt5Qml_LIBRARIES}
)

include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
)

# Thread
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -g3 -Wall")

# PIC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

FILE(GLOB SRC_FILES "./*.cpp")
FILE(GLOB HEAD_FILES "./*.h")
FILE(GLOB UI_FILES "./*.ui")

# qt_wrap_ui called with incorrect number of arguments ???
#qt_wrap_ui(WRAP_FILES ${UI_FILES})

set(RCC_FILES resources.qrc)

#add_library(${PROJECT_NAME} SHARED
#        ${SRC_FILES}
#        ${HEAD_FILES}
#        ${RCC_FILES}
#        ${WRAP_FILES}
#)
add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ${HEAD_FILES}
#        ${RCC_FILES}
#        ${WRAP_FILES}
)
target_link_libraries(
        ${PROJECT_NAME}
        ${QT_LIBRARIES}
)