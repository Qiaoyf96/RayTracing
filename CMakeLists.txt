cmake_minimum_required(VERSION 3.7)
project(Ray_Tracing)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(ALL_LIBS ${OpenCV_LIBS})
link_libraries(${ALL_LIBS})

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${OpenCV_INCLUDE_DIRS}
)

message(STATUS "OpenCV Library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES main.cpp float3.cpp float3.h int4.cpp int4.h BezierGen.cpp BezierGen.h RayTracer.cpp RayTracer.h Camera.hpp Film.cpp Film.h header.h Sample.cpp Sample.h Scene.cpp Scene.h PathTracer.cpp PathTracer.h color.h Ray.h Shape.cpp Shape.h Sphere.cpp Sphere.h Texture.cpp Texture.h)
add_executable(Ray_Tracing ${SOURCE_FILES})
