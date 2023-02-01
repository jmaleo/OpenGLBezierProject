project(IG_new_project)

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0043 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Définir le répertoire de destination pour les fichiers de shaders
set(SHADER_DIR ${EXECUTABLE_OUTPUT_PATH}/shaders/)

# Copier les fichiers de shaders à partir du répertoire source vers le répertoire de construction
file(GLOB_RECURSE SHADER_SOURCES "${CMAKE_SOURCE_DIR}/src/shaders/*.glsl")
file(COPY ${SHADER_SOURCES} DESTINATION ${SHADER_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glm)


configure_file(
    "${CMAKE_SOURCE_DIR}/CMakeConfig.h.in"
    "${CMAKE_SOURCE_DIR}/src/CMakeConfig.h"
)

find_package(OpenGL REQUIRED)

FILE(GLOB_RECURSE folder_source ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.hpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE folder_header ${EXECUTABLE_OUTPUT_PATH}/*.h)
FILE(GLOB_RECURSE shader_files ${CMAKE_SOURCE_DIR}/src/shaders/*.glsl)

set(glad_file ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
# FILE(GLOB_RECURSE imgui_files ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/*.cpp ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/*.h)

include_directories( GLOB_RECURSE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/imgui/imgui)
    # ${CMAKE_SOURCE_DIR}/lib/imgui/imgui/backends)

# Ajouter le répertoire des shaders à l'exécutable
include_directories(${SHADER_DIR})


add_executable(${CMAKE_PROJECT_NAME} ${folder_source} ${glad_file} ${folder_header} ${imgui_files} )


set(EXT_LIBS ${OPENGL_LIBRARIES} glfw)

target_link_libraries(${CMAKE_PROJECT_NAME} ${EXT_LIBS})
