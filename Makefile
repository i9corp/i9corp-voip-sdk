# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Workspace\i9corp-voip-sdk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Workspace\i9corp-voip-sdk

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E echo "No interactive CMake dialog available."
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\" \"dev\" \"runtime\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Workspace\i9corp-voip-sdk\CMakeFiles D:\Workspace\i9corp-voip-sdk\CMakeFiles\progress.marks
	$(MAKE) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Workspace\i9corp-voip-sdk\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) -f CMakeFiles\uninstall.dir\build.make CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named i9corp-voip-sdk

# Build rule for target.
i9corp-voip-sdk: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 i9corp-voip-sdk
.PHONY : i9corp-voip-sdk

# fast build rule for target.
i9corp-voip-sdk/fast:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/build
.PHONY : i9corp-voip-sdk/fast

#=============================================================================
# Target rules for targets named voip-demo

# Build rule for target.
voip-demo: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 voip-demo
.PHONY : voip-demo

# fast build rule for target.
voip-demo/fast:
	$(MAKE) -f CMakeFiles\voip-demo.dir\build.make CMakeFiles/voip-demo.dir/build
.PHONY : voip-demo/fast

extras/main.obj: extras/main.cpp.obj

.PHONY : extras/main.obj

# target to build an object file
extras/main.cpp.obj:
	$(MAKE) -f CMakeFiles\voip-demo.dir\build.make CMakeFiles/voip-demo.dir/extras/main.cpp.obj
.PHONY : extras/main.cpp.obj

extras/main.i: extras/main.cpp.i

.PHONY : extras/main.i

# target to preprocess a source file
extras/main.cpp.i:
	$(MAKE) -f CMakeFiles\voip-demo.dir\build.make CMakeFiles/voip-demo.dir/extras/main.cpp.i
.PHONY : extras/main.cpp.i

extras/main.s: extras/main.cpp.s

.PHONY : extras/main.s

# target to generate assembly for a file
extras/main.cpp.s:
	$(MAKE) -f CMakeFiles\voip-demo.dir\build.make CMakeFiles/voip-demo.dir/extras/main.cpp.s
.PHONY : extras/main.cpp.s

src/i9corp/voip/controller/VoipHandlerController.obj: src/i9corp/voip/controller/VoipHandlerController.cpp.obj

.PHONY : src/i9corp/voip/controller/VoipHandlerController.obj

# target to build an object file
src/i9corp/voip/controller/VoipHandlerController.cpp.obj:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/controller/VoipHandlerController.cpp.obj
.PHONY : src/i9corp/voip/controller/VoipHandlerController.cpp.obj

src/i9corp/voip/controller/VoipHandlerController.i: src/i9corp/voip/controller/VoipHandlerController.cpp.i

.PHONY : src/i9corp/voip/controller/VoipHandlerController.i

# target to preprocess a source file
src/i9corp/voip/controller/VoipHandlerController.cpp.i:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/controller/VoipHandlerController.cpp.i
.PHONY : src/i9corp/voip/controller/VoipHandlerController.cpp.i

src/i9corp/voip/controller/VoipHandlerController.s: src/i9corp/voip/controller/VoipHandlerController.cpp.s

.PHONY : src/i9corp/voip/controller/VoipHandlerController.s

# target to generate assembly for a file
src/i9corp/voip/controller/VoipHandlerController.cpp.s:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/controller/VoipHandlerController.cpp.s
.PHONY : src/i9corp/voip/controller/VoipHandlerController.cpp.s

src/i9corp/voip/model/VoipAccount.obj: src/i9corp/voip/model/VoipAccount.cpp.obj

.PHONY : src/i9corp/voip/model/VoipAccount.obj

# target to build an object file
src/i9corp/voip/model/VoipAccount.cpp.obj:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipAccount.cpp.obj
.PHONY : src/i9corp/voip/model/VoipAccount.cpp.obj

src/i9corp/voip/model/VoipAccount.i: src/i9corp/voip/model/VoipAccount.cpp.i

.PHONY : src/i9corp/voip/model/VoipAccount.i

# target to preprocess a source file
src/i9corp/voip/model/VoipAccount.cpp.i:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipAccount.cpp.i
.PHONY : src/i9corp/voip/model/VoipAccount.cpp.i

src/i9corp/voip/model/VoipAccount.s: src/i9corp/voip/model/VoipAccount.cpp.s

.PHONY : src/i9corp/voip/model/VoipAccount.s

# target to generate assembly for a file
src/i9corp/voip/model/VoipAccount.cpp.s:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipAccount.cpp.s
.PHONY : src/i9corp/voip/model/VoipAccount.cpp.s

src/i9corp/voip/model/VoipCall.obj: src/i9corp/voip/model/VoipCall.cpp.obj

.PHONY : src/i9corp/voip/model/VoipCall.obj

# target to build an object file
src/i9corp/voip/model/VoipCall.cpp.obj:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipCall.cpp.obj
.PHONY : src/i9corp/voip/model/VoipCall.cpp.obj

src/i9corp/voip/model/VoipCall.i: src/i9corp/voip/model/VoipCall.cpp.i

.PHONY : src/i9corp/voip/model/VoipCall.i

# target to preprocess a source file
src/i9corp/voip/model/VoipCall.cpp.i:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipCall.cpp.i
.PHONY : src/i9corp/voip/model/VoipCall.cpp.i

src/i9corp/voip/model/VoipCall.s: src/i9corp/voip/model/VoipCall.cpp.s

.PHONY : src/i9corp/voip/model/VoipCall.s

# target to generate assembly for a file
src/i9corp/voip/model/VoipCall.cpp.s:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipCall.cpp.s
.PHONY : src/i9corp/voip/model/VoipCall.cpp.s

src/i9corp/voip/model/VoipLine.obj: src/i9corp/voip/model/VoipLine.cpp.obj

.PHONY : src/i9corp/voip/model/VoipLine.obj

# target to build an object file
src/i9corp/voip/model/VoipLine.cpp.obj:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipLine.cpp.obj
.PHONY : src/i9corp/voip/model/VoipLine.cpp.obj

src/i9corp/voip/model/VoipLine.i: src/i9corp/voip/model/VoipLine.cpp.i

.PHONY : src/i9corp/voip/model/VoipLine.i

# target to preprocess a source file
src/i9corp/voip/model/VoipLine.cpp.i:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipLine.cpp.i
.PHONY : src/i9corp/voip/model/VoipLine.cpp.i

src/i9corp/voip/model/VoipLine.s: src/i9corp/voip/model/VoipLine.cpp.s

.PHONY : src/i9corp/voip/model/VoipLine.s

# target to generate assembly for a file
src/i9corp/voip/model/VoipLine.cpp.s:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/model/VoipLine.cpp.s
.PHONY : src/i9corp/voip/model/VoipLine.cpp.s

src/i9corp/voip/tools/VoipTools.obj: src/i9corp/voip/tools/VoipTools.cpp.obj

.PHONY : src/i9corp/voip/tools/VoipTools.obj

# target to build an object file
src/i9corp/voip/tools/VoipTools.cpp.obj:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/tools/VoipTools.cpp.obj
.PHONY : src/i9corp/voip/tools/VoipTools.cpp.obj

src/i9corp/voip/tools/VoipTools.i: src/i9corp/voip/tools/VoipTools.cpp.i

.PHONY : src/i9corp/voip/tools/VoipTools.i

# target to preprocess a source file
src/i9corp/voip/tools/VoipTools.cpp.i:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/tools/VoipTools.cpp.i
.PHONY : src/i9corp/voip/tools/VoipTools.cpp.i

src/i9corp/voip/tools/VoipTools.s: src/i9corp/voip/tools/VoipTools.cpp.s

.PHONY : src/i9corp/voip/tools/VoipTools.s

# target to generate assembly for a file
src/i9corp/voip/tools/VoipTools.cpp.s:
	$(MAKE) -f CMakeFiles\i9corp-voip-sdk.dir\build.make CMakeFiles/i9corp-voip-sdk.dir/src/i9corp/voip/tools/VoipTools.cpp.s
.PHONY : src/i9corp/voip/tools/VoipTools.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... install/strip
	@echo ... uninstall
	@echo ... i9corp-voip-sdk
	@echo ... rebuild_cache
	@echo ... voip-demo
	@echo ... install/local
	@echo ... install
	@echo ... edit_cache
	@echo ... list_install_components
	@echo ... extras/main.obj
	@echo ... extras/main.i
	@echo ... extras/main.s
	@echo ... src/i9corp/voip/controller/VoipHandlerController.obj
	@echo ... src/i9corp/voip/controller/VoipHandlerController.i
	@echo ... src/i9corp/voip/controller/VoipHandlerController.s
	@echo ... src/i9corp/voip/model/VoipAccount.obj
	@echo ... src/i9corp/voip/model/VoipAccount.i
	@echo ... src/i9corp/voip/model/VoipAccount.s
	@echo ... src/i9corp/voip/model/VoipCall.obj
	@echo ... src/i9corp/voip/model/VoipCall.i
	@echo ... src/i9corp/voip/model/VoipCall.s
	@echo ... src/i9corp/voip/model/VoipLine.obj
	@echo ... src/i9corp/voip/model/VoipLine.i
	@echo ... src/i9corp/voip/model/VoipLine.s
	@echo ... src/i9corp/voip/tools/VoipTools.obj
	@echo ... src/i9corp/voip/tools/VoipTools.i
	@echo ... src/i9corp/voip/tools/VoipTools.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

