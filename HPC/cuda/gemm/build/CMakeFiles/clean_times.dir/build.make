# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/whd/2026Autumn-recruitment/HPC/cuda/gemm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build

# Utility rule file for clean_times.

# Include any custom commands dependencies for this target.
include CMakeFiles/clean_times.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clean_times.dir/progress.make

CMakeFiles/clean_times:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Removing kernel timings file..."
	rm -f /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build/kernel_timings.txt

clean_times: CMakeFiles/clean_times
clean_times: CMakeFiles/clean_times.dir/build.make
.PHONY : clean_times

# Rule to build all files generated by this target.
CMakeFiles/clean_times.dir/build: clean_times
.PHONY : CMakeFiles/clean_times.dir/build

CMakeFiles/clean_times.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clean_times.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clean_times.dir/clean

CMakeFiles/clean_times.dir/depend:
	cd /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/whd/2026Autumn-recruitment/HPC/cuda/gemm /home/whd/2026Autumn-recruitment/HPC/cuda/gemm /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build /home/whd/2026Autumn-recruitment/HPC/cuda/gemm/build/CMakeFiles/clean_times.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/clean_times.dir/depend

