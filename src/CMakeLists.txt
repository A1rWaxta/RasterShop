set(CORE_SOURCE_FILES main.cpp QSFMLCanvas.cpp QSFMLCanvas.h MyCanvas.cpp MyCanvas.h MainWindow.cpp MainWindow.h)

add_executable(RasterShop ${CORE_SOURCE_FILES})

#######################################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
	message(STATUS "${SFML_LIBRARIES}")
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(RasterShop sfml-graphics sfml-audio pthread)
endif()
#######################################################

#######################################################
find_package(Qt5Widgets CONFIG REQUIRED)
if(Qt5Widgets_FOUND)
	message(STATUS "Qt has been found")
	target_link_libraries(RasterShop Qt5::Widgets)
endif()
#######################################################
