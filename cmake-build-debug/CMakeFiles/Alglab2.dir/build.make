# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sasha\CLionProjects\AlgLab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\AlgLab2.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\AlgLab2.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\AlgLab2.dir\flags.make

CMakeFiles\AlgLab2.dir\main.cpp.obj: CMakeFiles\AlgLab2.dir\flags.make
CMakeFiles\AlgLab2.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AlgLab2.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\AlgLab2.dir\main.cpp.obj /FdCMakeFiles\AlgLab2.dir\ /FS -c C:\Users\sasha\CLionProjects\AlgLab2\main.cpp
<<

CMakeFiles\AlgLab2.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlgLab2.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\AlgLab2.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sasha\CLionProjects\AlgLab2\main.cpp
<<

CMakeFiles\AlgLab2.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlgLab2.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\AlgLab2.dir\main.cpp.s /c C:\Users\sasha\CLionProjects\AlgLab2\main.cpp
<<

# Object files for target AlgLab2
AlgLab2_OBJECTS = \
"CMakeFiles\AlgLab2.dir\main.cpp.obj"

# External object files for target AlgLab2
AlgLab2_EXTERNAL_OBJECTS =

AlgLab2.exe: CMakeFiles\AlgLab2.dir\main.cpp.obj
AlgLab2.exe: CMakeFiles\AlgLab2.dir\build.make
AlgLab2.exe: lib\gtest.lib
AlgLab2.exe: lib\gtest_main.lib
AlgLab2.exe: lib\gtest.lib
AlgLab2.exe: CMakeFiles\AlgLab2.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AlgLab2.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\AlgLab2.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\AlgLab2.dir\objects1.rsp @<<
 /out:AlgLab2.exe /implib:AlgLab2.lib /pdb:C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug\AlgLab2.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  lib\gtest.lib lib\gtest_main.lib lib\gtest.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\AlgLab2.dir\build: AlgLab2.exe
.PHONY : CMakeFiles\AlgLab2.dir\build

CMakeFiles\AlgLab2.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AlgLab2.dir\cmake_clean.cmake
.PHONY : CMakeFiles\AlgLab2.dir\clean

CMakeFiles\AlgLab2.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\sasha\CLionProjects\AlgLab2 C:\Users\sasha\CLionProjects\AlgLab2 C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug C:\Users\sasha\CLionProjects\AlgLab2\cmake-build-debug\CMakeFiles\AlgLab2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\AlgLab2.dir\depend

