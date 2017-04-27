project(SizeGripDemo)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sizegripitemdemo_SOURCES ../SizeGripItem.cpp main.cpp)
set(sizegripitemdemo_HEADERS ../SizeGripItem.h)

qt5_wrap_cpp(sizegripitemdemo_HEADERS_MOC ${sizegripitemdemo_HEADERS})

add_executable(SizeGripDemo
  ${sizegripitemdemo_SOURCES}
  ${sizegripitemdemo_HEADERS_MOC})

target_link_libraries(SizeGripDemo Qt5::Gui Qt5::Core Qt5::Widgets)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)