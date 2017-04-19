cmake_minimum_required(VERSION 3.5)
project(cylinders)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

set(CAMERA_UTILS_SOURCES CameraUtils/Ray.cpp CameraUtils/Ray.h CameraUtils/Camera.cpp CameraUtils/Camera.h)
set(MATH_UTILS_SOURCES MathUtils/Vector.cpp MathUtils/Vector.h MathUtils/Number.cpp MathUtils/Number.h MathUtils/Matrix.cpp MathUtils/Matrix.h)
set(MATERIAL_SOURCES Materials/Color.h Materials/Material.cpp Materials/Material.h Materials/TableMaterial.cpp Materials/TableMaterial.h)
set(OBJECT_SOURCES Objects/Object.cpp Objects/Object.h Objects/Plane.cpp Objects/Plane.h Objects/InfiniteCylinder.cpp Objects/InfiniteCylinder.h)
set(LIGHT_SOURCES Lights/Light.h Lights/AmbientLight.h Lights/PointLight.h)
set(UTIL_SOURCES Utils/Scene.cpp Utils/Scene.h)

set(SOURCE_FILES main.cpp ${UTIL_SOURCES} ${CAMERA_UTILS_SOURCES} ${MATH_UTILS_SOURCES} ${MATERIAL_SOURCES} ${OBJECT_SOURCES} ${LIGHT_SOURCES})
add_executable(cylinders ${SOURCE_FILES})


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

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(cylinders ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} Threads::Threads)