# Build Elision.
#

# Verify the version of CMake required.
cmake_minimum_required( VERSION 2.8 )

# Testing!
enable_testing()

# Define the project and the current version numbers.
project( elision )
SET( ELI_MAJOR 0 )
SET( ELI_MINOR 0 )
SET( ELI_VERSION ${ELI_MAJOR}.${ELI_MINOR} )
SET( ELI_DIST_NAME "elision-${ELI_VERSION}" )
SET( MACOSX_RPATH 1 )
cmake_policy(SET CMP0042 NEW)

# Find Boost and include it.
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
    # Look for the Boost multiprecision library.  We need it.
    find_file(CPP_INT "cpp_int.hpp" "${Boost_INCLUDE_DIR}/boost/multiprecision/")
    if(NOT CPP_INT)
        message(WARNING "Boost does not have multiprecision; falling back to int64_t.")
    else()
        add_definitions(-DHAVE_BOOST_CPP_INT)
    endif()
ENDIF()

# Locate valgrind.
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

# Specify the list of source files to use for the core library here.
FILE(GLOB_RECURSE lib_sources RELATIVE ${CMAKE_HOME_DIRECTORY} src/*.cpp)

# Specify the list of tests to complile.
FILE(GLOB_RECURSE tests RELATIVE ${CMAKE_HOME_DIRECTORY} test/*_tst.cpp)

# Figure out if this is a debug or release.
if( NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE "Release" )
endif( NOT CMAKE_BUILD_TYPE )

# Compiler flags.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-Wall" COMPILER_SUPPORTS_WALL)
CHECK_CXX_COMPILER_FLAG("-Wextra" COMPILER_SUPPORTS_WEXTRA)
CHECK_CXX_COMPILER_FLAG("-g3" COMPILER_SUPPORTS_G3)
CHECK_CXX_COMPILER_FLAG("-O3" COMPILER_SUPPORTS_O3)
if (COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.  Please use a different C++ compiler.")
endif()
if (COMPILER_SUPPORTS_WALL)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
endif()
if (COMPILER_SUPPORTS_WEXTRA)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra" )
endif()
if (COMPILER_SUPPORTS_G3)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
endif()
if (COMPILER_SUPPORTS_O3)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Modify the include path so we can find our own files.
include_directories( AFTER SYSTEM src src/term )

# Build the core library.
add_library( elision SHARED ${lib_sources} )
target_link_libraries( elision )

# Build the command line executable.
#add_executable( elision
#    core/cli/main.cpp
#)
#target_link_libraries( elision elision )

# Add a test target that builds the tests.
add_custom_target( tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test )

# Add a target that actually runs the tests.
add_custom_target( check ./run_tests.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test )
add_dependencies( check tests )
foreach( test_exec ${tests} )
    string( REGEX REPLACE "test/(.*)\\.cpp" "test/\\1" test_exec ${test_exec} )
#    add_executable( ${test_exec} EXCLUDE_FROM_ALL ${test_exec}.cpp )
    add_executable( ${test_exec} ${test_exec}.cpp )
    target_link_libraries( ${test_exec} elision )
    add_test( ${test_exec} ${test_exec} )
    add_dependencies( tests ${test_exec} )
endforeach( test_exec )

# Add a documentation target.  First we have to find doxygen.
find_program( doxygen_path doxygen PATHS ENV PATH NO_DEFAULT_PATH )
if( doxygen_path )
    set( doc_path "${CMAKE_CURRENT_BINARY_DIR}/doc/api" )
    message( "Found Doxygen at ${doxygen_path}." )
    message( "Writing API documentation to ${doc_path}" )
    FILE( MAKE_DIRECTORY "${doc_path}" )
    add_custom_target(
        doc
        ${doxygen_path} ${CMAKE_CURRENT_SOURCE_DIR}/elision.doxyfile
        working_directory ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
else( doxygen_path )
    message( "WARNING: Doxygen not found; not generating documentation." )
    add_custom_target(
        doc
        echo "WARNING: Doxygen not found; not generating documentation."
    )
endif( doxygen_path )
