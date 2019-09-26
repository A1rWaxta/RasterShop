find_package(Qt5 REQUIRED COMPONENTS Core Widgets UiTools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources
		main.cpp
		UserInterface.cpp
		Canvas.cpp
		ApplicationSettings.cpp
		MainWindow.cpp
		MainWindowX.cpp
		)

set(project_headers
		UserInterface.h
		Canvas.h
		ApplicationSettings.h
		MainWindow.h
		MainWindowX.h
		)

set(project_ui
		MainWindowX.ui
		)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(AUTOMOC_MACRO_NAMES ${project_headers})
set(AUTOGEN_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nowyXD)

add_executable(RasterShop ${project_sources} ${project_headers})

set_target_properties(RasterShop PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set_target_properties(RasterShop PROPERTIES OUTPUT_NAME_DEBUG RasterShop-debug)
set_target_properties(RasterShop PROPERTIES OUTPUT_NAME_RELEASE RasterShop)

if(Qt5Widgets_FOUND AND Qt5UiTools_FOUND)
	message(STATUS "Qt has been found")
	target_link_libraries(RasterShop Qt5::Widgets Qt5::UiTools)
endif()