cmake_minimum_required(VERSION 3.10.2)

set(PROJECT_NAME "Find_Pupusk")
project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)


add_subdirectory(./External/OpenCV)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} ./Sources/Private/main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
