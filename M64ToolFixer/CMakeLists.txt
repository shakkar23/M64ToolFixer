# CMakeList.txt : CMake project for pong, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project ("M64ToolFixer")

if(NOT PLATFORM_NAME)
	set(PLATFORM_NAME "SDL2")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(GAME_SOURCES
	"main.cpp" 
	"main.hpp"
	"impl.cpp"
)

# Add source to this project's executable.
add_executable (M64ToolFixer ${GAME_SOURCES})
target_link_libraries(M64ToolFixer PUBLIC SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2::SDL2main )
