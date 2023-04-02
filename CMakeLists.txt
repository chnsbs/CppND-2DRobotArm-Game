cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(RobotArmGame VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the path to the custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find the SDL2 and SDL2_ttf libraries
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

# Add an executable target with the source files
add_executable(RobotArmGame src/main.cpp src/robot.cpp src/renderer.cpp src/controller.cpp src/game.cpp)

# Link the SDL2 and SDL2_ttf libraries to the executable
target_include_directories(RobotArmGame PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(RobotArmGame ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})