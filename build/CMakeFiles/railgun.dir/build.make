# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lunar/pros/railgun

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lunar/pros/railgun/build

# Include any dependencies generated for this target.
include CMakeFiles/railgun.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/railgun.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/railgun.dir/flags.make

CMakeFiles/railgun.dir/src/epoll.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/epoll.c.o: ../src/epoll.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/railgun.dir/src/epoll.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/epoll.c.o   -c /home/lunar/pros/railgun/src/epoll.c

CMakeFiles/railgun.dir/src/epoll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/epoll.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/epoll.c > CMakeFiles/railgun.dir/src/epoll.c.i

CMakeFiles/railgun.dir/src/epoll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/epoll.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/epoll.c -o CMakeFiles/railgun.dir/src/epoll.c.s

CMakeFiles/railgun.dir/src/figure.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/figure.c.o: ../src/figure.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/railgun.dir/src/figure.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/figure.c.o   -c /home/lunar/pros/railgun/src/figure.c

CMakeFiles/railgun.dir/src/figure.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/figure.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/figure.c > CMakeFiles/railgun.dir/src/figure.c.i

CMakeFiles/railgun.dir/src/figure.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/figure.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/figure.c -o CMakeFiles/railgun.dir/src/figure.c.s

CMakeFiles/railgun.dir/src/http.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/http.c.o: ../src/http.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/railgun.dir/src/http.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/http.c.o   -c /home/lunar/pros/railgun/src/http.c

CMakeFiles/railgun.dir/src/http.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/http.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/http.c > CMakeFiles/railgun.dir/src/http.c.i

CMakeFiles/railgun.dir/src/http.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/http.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/http.c -o CMakeFiles/railgun.dir/src/http.c.s

CMakeFiles/railgun.dir/src/http_parse.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/http_parse.c.o: ../src/http_parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/railgun.dir/src/http_parse.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/http_parse.c.o   -c /home/lunar/pros/railgun/src/http_parse.c

CMakeFiles/railgun.dir/src/http_parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/http_parse.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/http_parse.c > CMakeFiles/railgun.dir/src/http_parse.c.i

CMakeFiles/railgun.dir/src/http_parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/http_parse.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/http_parse.c -o CMakeFiles/railgun.dir/src/http_parse.c.s

CMakeFiles/railgun.dir/src/main.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/railgun.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/main.c.o   -c /home/lunar/pros/railgun/src/main.c

CMakeFiles/railgun.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/main.c > CMakeFiles/railgun.dir/src/main.c.i

CMakeFiles/railgun.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/main.c -o CMakeFiles/railgun.dir/src/main.c.s

CMakeFiles/railgun.dir/src/priority_queue.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/priority_queue.c.o: ../src/priority_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/railgun.dir/src/priority_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/priority_queue.c.o   -c /home/lunar/pros/railgun/src/priority_queue.c

CMakeFiles/railgun.dir/src/priority_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/priority_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/priority_queue.c > CMakeFiles/railgun.dir/src/priority_queue.c.i

CMakeFiles/railgun.dir/src/priority_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/priority_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/priority_queue.c -o CMakeFiles/railgun.dir/src/priority_queue.c.s

CMakeFiles/railgun.dir/src/request.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/request.c.o: ../src/request.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/railgun.dir/src/request.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/request.c.o   -c /home/lunar/pros/railgun/src/request.c

CMakeFiles/railgun.dir/src/request.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/request.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/request.c > CMakeFiles/railgun.dir/src/request.c.i

CMakeFiles/railgun.dir/src/request.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/request.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/request.c -o CMakeFiles/railgun.dir/src/request.c.s

CMakeFiles/railgun.dir/src/rio.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/rio.c.o: ../src/rio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/railgun.dir/src/rio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/rio.c.o   -c /home/lunar/pros/railgun/src/rio.c

CMakeFiles/railgun.dir/src/rio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/rio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/rio.c > CMakeFiles/railgun.dir/src/rio.c.i

CMakeFiles/railgun.dir/src/rio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/rio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/rio.c -o CMakeFiles/railgun.dir/src/rio.c.s

CMakeFiles/railgun.dir/src/threadpool.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/threadpool.c.o: ../src/threadpool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/railgun.dir/src/threadpool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/threadpool.c.o   -c /home/lunar/pros/railgun/src/threadpool.c

CMakeFiles/railgun.dir/src/threadpool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/threadpool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/threadpool.c > CMakeFiles/railgun.dir/src/threadpool.c.i

CMakeFiles/railgun.dir/src/threadpool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/threadpool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/threadpool.c -o CMakeFiles/railgun.dir/src/threadpool.c.s

CMakeFiles/railgun.dir/src/timer.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/timer.c.o: ../src/timer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/railgun.dir/src/timer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/timer.c.o   -c /home/lunar/pros/railgun/src/timer.c

CMakeFiles/railgun.dir/src/timer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/timer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/timer.c > CMakeFiles/railgun.dir/src/timer.c.i

CMakeFiles/railgun.dir/src/timer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/timer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/timer.c -o CMakeFiles/railgun.dir/src/timer.c.s

CMakeFiles/railgun.dir/src/util.c.o: CMakeFiles/railgun.dir/flags.make
CMakeFiles/railgun.dir/src/util.c.o: ../src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/railgun.dir/src/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/railgun.dir/src/util.c.o   -c /home/lunar/pros/railgun/src/util.c

CMakeFiles/railgun.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/railgun.dir/src/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lunar/pros/railgun/src/util.c > CMakeFiles/railgun.dir/src/util.c.i

CMakeFiles/railgun.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/railgun.dir/src/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lunar/pros/railgun/src/util.c -o CMakeFiles/railgun.dir/src/util.c.s

# Object files for target railgun
railgun_OBJECTS = \
"CMakeFiles/railgun.dir/src/epoll.c.o" \
"CMakeFiles/railgun.dir/src/figure.c.o" \
"CMakeFiles/railgun.dir/src/http.c.o" \
"CMakeFiles/railgun.dir/src/http_parse.c.o" \
"CMakeFiles/railgun.dir/src/main.c.o" \
"CMakeFiles/railgun.dir/src/priority_queue.c.o" \
"CMakeFiles/railgun.dir/src/request.c.o" \
"CMakeFiles/railgun.dir/src/rio.c.o" \
"CMakeFiles/railgun.dir/src/threadpool.c.o" \
"CMakeFiles/railgun.dir/src/timer.c.o" \
"CMakeFiles/railgun.dir/src/util.c.o"

# External object files for target railgun
railgun_EXTERNAL_OBJECTS =

railgun: CMakeFiles/railgun.dir/src/epoll.c.o
railgun: CMakeFiles/railgun.dir/src/figure.c.o
railgun: CMakeFiles/railgun.dir/src/http.c.o
railgun: CMakeFiles/railgun.dir/src/http_parse.c.o
railgun: CMakeFiles/railgun.dir/src/main.c.o
railgun: CMakeFiles/railgun.dir/src/priority_queue.c.o
railgun: CMakeFiles/railgun.dir/src/request.c.o
railgun: CMakeFiles/railgun.dir/src/rio.c.o
railgun: CMakeFiles/railgun.dir/src/threadpool.c.o
railgun: CMakeFiles/railgun.dir/src/timer.c.o
railgun: CMakeFiles/railgun.dir/src/util.c.o
railgun: CMakeFiles/railgun.dir/build.make
railgun: CMakeFiles/railgun.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lunar/pros/railgun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C executable railgun"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/railgun.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/railgun.dir/build: railgun

.PHONY : CMakeFiles/railgun.dir/build

CMakeFiles/railgun.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/railgun.dir/cmake_clean.cmake
.PHONY : CMakeFiles/railgun.dir/clean

CMakeFiles/railgun.dir/depend:
	cd /home/lunar/pros/railgun/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lunar/pros/railgun /home/lunar/pros/railgun /home/lunar/pros/railgun/build /home/lunar/pros/railgun/build /home/lunar/pros/railgun/build/CMakeFiles/railgun.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/railgun.dir/depend

