cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(EmberLib C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Note that testing requires libcheck to be installed on the system!
# See the tests/CMakeLists.txt file for details.
if(NOT DEFINED BUILD_TESTS)
	set(BUILD_TESTS FALSE)
endif(NOT DEFINED BUILD_TESTS)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
# Check Headers
set(INCLUDES "")
macro(ck_check_include_file header var)
	check_include_file("${INCLUDES};${header}" ${var})
	if(${var})
		set(INCLUDES ${INCLUDES} ${header})
	endif(${var})
endmacro(ck_check_include_file)

ck_check_include_file("stdlib.h" HAVE_STDLIB_H)
check_type_size(intmax_t INTMAX_T)
check_type_size(uintmax_t UINTMMAX_T)

check_type_size(pid_t PID_T)
if(NOT HAVE_PID_T)
	if(WIN32)
		set(pid_t "int")
	else(WIN32)
		MESSAGE(FATAL_ERROR "pid_t doesn't exist on this platform?")
	endif(WIN32)
endif(NOT HAVE_PID_T)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG_H)
set(CONFIG_HEADER ${CMAKE_CURRENT_BINARY_DIR/config.h})

add_subdirectory(src)
add_subdirectory(demo)

if(${BUILD_TESTS})
	add_subdirectory(tests)
endif(${BUILD_TESTS})

enable_testing()
add_test(NAME check COMMAND check)
