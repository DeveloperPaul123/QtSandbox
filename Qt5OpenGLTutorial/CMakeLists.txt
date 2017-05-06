project(QtOpenGLTutorial)

find_package(OPENGL REQUIRED)

set(project_sources 
	src/main.cpp 
	src/mainwindow.cpp
	src/window.cpp
	src/transform3d.cpp
	src/input.cpp
	src/camera3d.cpp)

set(project_headers 
	src/mainwindow.h
	src/window.h
	src/vertex.h
	src/transform3d.h
	src/input.h
	src/camera3d.h)

qt5_wrap_ui(ui_sources ui/mainwindow.ui)
qt5_wrap_cpp(moc_srcs ${project_headers})
qt5_add_resources(resources resources.qrc)

add_library(GUI STATIC ${ui_sources} ${moc_srcs})
target_link_libraries(GUI Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${project_sources} ${project_headers} ${resources})

target_include_directories(${PROJECT_NAME} PRIVATE src ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} GUI Qt5::Gui Qt5::Core Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)