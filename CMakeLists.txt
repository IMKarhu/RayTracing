cmake_minimum_required(VERSION 3.5)

project(RayTracer)

option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext/glm)
add_subdirectory(ext/glfw-3.3.8)

include_directories(ext/glfw-3.3.8/include)
include_directories(${GLFW_SOURCE_DIR}/deps)
set(GLAD_GL ${GLFW_SOURCE_DIR}/deps/glad/gl.h ${GLFW_SOURCE_DIR}/deps/glad_gl.c)

file(GLOB_RECURSE CPP_SOURCE_FILES "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${GLAD_GL})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm)