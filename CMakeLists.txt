cmake_minimum_required(VERSION 3.5)
project(CV_solo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        )
add_executable(CV_solo ${SOURCE_FILES} Baseball.cpp Baseball.h Singleton.cpp Singleton.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCV REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS})

target_link_libraries(CV_solo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OpenCV_LIBS} )

