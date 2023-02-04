project(IG_new_project)

find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.5)
### Policy settings
cmake_policy(SET CMP0054 NEW)   # don't implicitly dereference inside if()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(glad_file ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
set(EXT_LIBS ${OPENGL_LIBRARIES} glfw)


# Définir le répertoire de destination pour les fichiers de shaders
set(SHADER_DIR ${EXECUTABLE_OUTPUT_PATH}/shaders/)

set(IG_new_project_BACKEND_OPENGL3_GLFW "ON" CACHE BOOL "Enable openGL3_glfw backend")
set(IG_new_project_BACKEND_OPENGL_MOCK "ON" CACHE BOOL "Enable openGL_mock backend")

FILE(GLOB_RECURSE folder_source ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.hpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE folder_header ${EXECUTABLE_OUTPUT_PATH}/*.h)


# Copier les fichiers de shaders à partir du répertoire source vers le répertoire de construction
FILE(GLOB_RECURSE SHADER_SOURCES "${CMAKE_SOURCE_DIR}/src/shaders/*.glsl")
FILE(COPY ${SHADER_SOURCES} DESTINATION ${SHADER_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glm)


configure_file(
    "${CMAKE_SOURCE_DIR}/CMakeConfig.h.in"
    "${CMAKE_SOURCE_DIR}/src/CMakeConfig.h"
    )
    
include_directories( GLOB_RECURSE
${CMAKE_SOURCE_DIR}/src
${CMAKE_SOURCE_DIR}/lib/glad/include
${CMAKE_SOURCE_DIR}/lib/glm)
include_directories(${SHADER_DIR})
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui/backends)

FILE (GLOB imgui_source ${CMAKE_SOURCE_DIR}/lib/imgui/*.cpp)
set (folder_source ${folder_source} ${imgui_source})
set (folder_source ${folder_source} ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp)
set (folder_source ${folder_source} ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp)

FILE (GLOB imgui_header ${CMAKE_SOURCE_DIR}/lib/imgui/*.h)
set (folder_header ${folder_header} ${imgui_header})
set (folder_header ${folder_header} ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.h)
set (folder_header ${folder_header} ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.h)



add_executable(${CMAKE_PROJECT_NAME} ${folder_source} ${glad_file} ${folder_header})

target_link_libraries(${CMAKE_PROJECT_NAME} ${EXT_LIBS})