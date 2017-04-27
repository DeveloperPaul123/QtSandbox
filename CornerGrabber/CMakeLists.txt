project(CornerGrabber)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(project_sources main.cpp cornergrabber.cpp gridlines.cpp mainwindow.cpp statebox.cpp)
set(project_headers cornergrabber.h gridlines.h mainwindow.h statebox.h)

qt5_wrap_ui(ui_sources mainwindow.ui)
qt5_wrap_cpp(moc_srcs ${project_headers})

add_executable(CornerGrabber ${project_sources} ${project_headers} ${ui_sources} ${moc_srcs})

target_link_libraries(CornerGrabber Qt5::Gui Qt5::Core Qt5::Widgets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)