 
project(HandleItem LANGUAGES C CXX)
 
QT5_WRAP_UI(UISrcs form.ui)
QT5_WRAP_CPP(MOCSrcs form.h)
 
include_directories(${include_directories} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
 
set(project_sources HandleItem.cpp main.cpp form.cpp)
set(project_headers HandleItem.h form.h)
add_executable(${PROJECT_NAME} ${project_sources} ${project_headers} ${MOCSrcs} ${UISrcs})
target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Widgets Qt5::Core)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)