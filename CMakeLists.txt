# Build Elision.
#

# Verify the version of CMake required.
cmake_minimum_required( VERSION 2.8 )

# Define the project and the current version numbers.
project( elision )
SET( ELI_MAJOR 0 )
SET( ELI_MINOR 0 )
SET( ELI_VERSION ${ELI_MAJOR}.${ELI_MINOR} )
SET( ELI_DIST_NAME "elision-${ELI_VERSION}" )

# Specify the list of source files to use for the core library here.
# We could use a glob, but that's not recommended, since cmake won't
# detect (thanks to evil caching) when files are added or removed.
#FILE( GLOB lib_sources "core/*.cpp" )
FILE(GLOB_RECURSE lib_sources RELATIVE ${CMAKE_HOME_DIRECTORY} src/*.cpp)

# Someday we will have tests.
FILE(GLOB_RECURSE tests RELATIVE ${CMAKE_HOME_DIRECTORY} test/*_test.cpp)

# Someday we will have examples.
#FILE(GLOB_RECURSE lib_examples RELATIVE ${CMAKE_HOME_DIRECTORY} src/*_ex.cpp)

# Remove the "other" files from the source files.
#list(REMOVE_ITEM lib_sources ${lib_tests})
#list(REMOVE_ITEM lib_sources ${lib_examples})

# Figure out if this is a debug or release.
if( NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE "Release" )
endif( NOT CMAKE_BUILD_TYPE )

# Compiler flags.
set( CMAKE_CXX_FLAGS "-g -Wall -std=c++0x" )

# Modify the include path so we can find our own files.
include_directories( AFTER SYSTEM src src/core )

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
    add_executable( ${test_exec} EXCLUDE_FROM_ALL ${test_exec}.cpp )
    target_link_libraries( ${test_exec} elision )
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
