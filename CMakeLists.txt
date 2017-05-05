cmake_minimum_required(VERSION 3.0)
project(QtSandbox)

find_package(Qt5 REQUIRED COMPONENTS Gui Core Widgets OpenGL)

add_subdirectory(HandleItem)
add_subdirectory(SizeGripItem)
add_subdirectory(CornerGrabber)
add_subdirectory(Qt5OpenGLTutorial)