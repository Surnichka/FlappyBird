cmake_minimum_required(VERSION 2.8)
project(learnSFML)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Core)
add_subdirectory(Utils)
add_subdirectory(Enviroment)
add_subdirectory(Character)
add_executable(learnSFML "main.cpp")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/SFML/cmake/Modules/")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

IF( NOT SFML_FOUND )
   message( FATAL_ERROR "\nLibrary SFML is not installed!")
ENDIF()

target_link_libraries(learnSFML PRIVATE
	                  Core
					  Utils
					  Character
					  Enviroment
					  ${SFML_LIBRARIES}
					  -lGL)

target_include_directories(learnSFML PRIVATE ${SFML_INCLUDE_DIR})
