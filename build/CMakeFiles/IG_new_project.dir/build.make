# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build

# Include any dependencies generated for this target.
include CMakeFiles/IG_new_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/IG_new_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IG_new_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IG_new_project.dir/flags.make

CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o: CMakeFiles/IG_new_project.dir/flags.make
CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o: ../src/ShaderProgram.cpp
CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o: CMakeFiles/IG_new_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o -MF CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o.d -o CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/ShaderProgram.cpp

CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/ShaderProgram.cpp > CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.i

CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/ShaderProgram.cpp -o CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.s

CMakeFiles/IG_new_project.dir/src/main.cpp.o: CMakeFiles/IG_new_project.dir/flags.make
CMakeFiles/IG_new_project.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/IG_new_project.dir/src/main.cpp.o: CMakeFiles/IG_new_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/IG_new_project.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IG_new_project.dir/src/main.cpp.o -MF CMakeFiles/IG_new_project.dir/src/main.cpp.o.d -o CMakeFiles/IG_new_project.dir/src/main.cpp.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/main.cpp

CMakeFiles/IG_new_project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IG_new_project.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/main.cpp > CMakeFiles/IG_new_project.dir/src/main.cpp.i

CMakeFiles/IG_new_project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IG_new_project.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/src/main.cpp -o CMakeFiles/IG_new_project.dir/src/main.cpp.s

CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o: CMakeFiles/IG_new_project.dir/flags.make
CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o: ../lib/glad/src/glad.c
CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o: CMakeFiles/IG_new_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o -MF CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o.d -o CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glad/src/glad.c

CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glad/src/glad.c > CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.i

CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glad/src/glad.c -o CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.s

# Object files for target IG_new_project
IG_new_project_OBJECTS = \
"CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o" \
"CMakeFiles/IG_new_project.dir/src/main.cpp.o" \
"CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o"

# External object files for target IG_new_project
IG_new_project_EXTERNAL_OBJECTS =

../bin/IG_new_project: CMakeFiles/IG_new_project.dir/src/ShaderProgram.cpp.o
../bin/IG_new_project: CMakeFiles/IG_new_project.dir/src/main.cpp.o
../bin/IG_new_project: CMakeFiles/IG_new_project.dir/lib/glad/src/glad.c.o
../bin/IG_new_project: CMakeFiles/IG_new_project.dir/build.make
../bin/IG_new_project: /usr/lib/x86_64-linux-gnu/libGL.so
../bin/IG_new_project: /usr/lib/x86_64-linux-gnu/libGLU.so
../bin/IG_new_project: lib/glfw/src/libglfw3.a
../bin/IG_new_project: /usr/lib/x86_64-linux-gnu/librt.a
../bin/IG_new_project: /usr/lib/x86_64-linux-gnu/libm.so
../bin/IG_new_project: /usr/lib/x86_64-linux-gnu/libX11.so
../bin/IG_new_project: CMakeFiles/IG_new_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/IG_new_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IG_new_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IG_new_project.dir/build: ../bin/IG_new_project
.PHONY : CMakeFiles/IG_new_project.dir/build

CMakeFiles/IG_new_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IG_new_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IG_new_project.dir/clean

CMakeFiles/IG_new_project.dir/depend:
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles/IG_new_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IG_new_project.dir/depend

