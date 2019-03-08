cmake_minimum_required(VERSION 3.7)
project(raytracer)

set (CMAKE_CXX_STANDARD 17)

file(GLOB raytracer_SRC
    "src/**/*.cpp"
)
message( STATUS  "${PROJECT_SOURCE_DIR}")
add_executable(raytracer src/main.cpp ${raytracer_SRC})


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

if (NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif (NOT GLUT_FOUND)

if (NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif (NOT GLEW_FOUND)

target_include_directories(raytracer PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/inc)

target_link_libraries(raytracer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} Threads::Threads)