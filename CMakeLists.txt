project(IG_new_project)

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0043 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glm)



find_package(OpenGL REQUIRED)

FILE(GLOB_RECURSE folder_source ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.hpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE shader_files ${CMAKE_SOURCE_DIR}/src/shaders/*.glsl)

set(glad_file ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
# FILE(GLOB_RECURSE imgui_files ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/*.cpp ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/*.h)

include_directories( GLOB_RECURSE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/imgui/imgui)
    # ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/backends)

add_executable(${CMAKE_PROJECT_NAME} ${folder_source} ${shader_files} ${glad_file} ${folder_header} ${imgui_files})

file(COPY ${shader_files} DESTINATION "shaders")

set(EXT_LIBS ${OPENGL_LIBRARIES} glfw)

target_link_libraries(${CMAKE_PROJECT_NAME} ${EXT_LIBS})
