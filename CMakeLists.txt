cmake_minimum_required(VERSION 3.5)

project(WebcamViewer)

# Find the Qt5 package
find_package(Qt5Widgets REQUIRED)

# Include the headers and source files
set(SOURCES
    src/main.cpp
    src/webcamviewer.cpp
)

# If you have UI files (Qt Designer .ui files), include them here
set(UIS
    ui/mainwindow.ui
)

# Set up automatic MOC, UIC, and RCC handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Create the executable
add_executable(webcam_viewer ${SOURCES} ${UIS})

# Link against Qt5 modules
target_link_libraries(webcam_viewer Qt5::Widgets)
