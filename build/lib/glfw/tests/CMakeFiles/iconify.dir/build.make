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
include lib/glfw/tests/CMakeFiles/iconify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/glfw/tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw/tests/CMakeFiles/iconify.dir/flags.make

lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/flags.make
lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o: ../lib/glfw/tests/iconify.c
lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o -MF CMakeFiles/iconify.dir/iconify.c.o.d -o CMakeFiles/iconify.dir/iconify.c.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/tests/iconify.c

lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/tests/iconify.c > CMakeFiles/iconify.dir/iconify.c.i

lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/tests/iconify.c -o CMakeFiles/iconify.dir/iconify.c.s

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/flags.make
lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: ../lib/glfw/deps/getopt.c
lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o -MF CMakeFiles/iconify.dir/__/deps/getopt.c.o.d -o CMakeFiles/iconify.dir/__/deps/getopt.c.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/getopt.c

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/getopt.c > CMakeFiles/iconify.dir/__/deps/getopt.c.i

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/getopt.c -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/flags.make
lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: ../lib/glfw/deps/glad_gl.c
lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: lib/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -MF CMakeFiles/iconify.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -c /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/glad_gl.c

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad_gl.c.i"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/glad_gl.c > CMakeFiles/iconify.dir/__/deps/glad_gl.c.i

lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad_gl.c.s"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/deps/glad_gl.c -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.o" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.o" \
"CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

../bin/iconify: lib/glfw/tests/CMakeFiles/iconify.dir/iconify.c.o
../bin/iconify: lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o
../bin/iconify: lib/glfw/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o
../bin/iconify: lib/glfw/tests/CMakeFiles/iconify.dir/build.make
../bin/iconify: lib/glfw/src/libglfw3.a
../bin/iconify: /usr/lib/x86_64-linux-gnu/libm.so
../bin/iconify: /usr/lib/x86_64-linux-gnu/librt.a
../bin/iconify: /usr/lib/x86_64-linux-gnu/libm.so
../bin/iconify: /usr/lib/x86_64-linux-gnu/libX11.so
../bin/iconify: lib/glfw/tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ../../../../bin/iconify"
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iconify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw/tests/CMakeFiles/iconify.dir/build: ../bin/iconify
.PHONY : lib/glfw/tests/CMakeFiles/iconify.dir/build

lib/glfw/tests/CMakeFiles/iconify.dir/clean:
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : lib/glfw/tests/CMakeFiles/iconify.dir/clean

lib/glfw/tests/CMakeFiles/iconify.dir/depend:
	cd /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/lib/glfw/tests /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests /home/arnal/Documents/Master2/Infographie/IG3/OpenGLBezierProject/build/lib/glfw/tests/CMakeFiles/iconify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw/tests/CMakeFiles/iconify.dir/depend

