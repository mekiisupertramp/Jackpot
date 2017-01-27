cmake_minimum_required(VERSION 3.6)
project(bigScan)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

set(SOURCE_FILES src/bigScan.c src/daemon.h src/daemon.c src/filter.c src/filter.h src/hashmap.c src/hashmap.h src/header.h src/parser.c src/parser.h)
add_executable(bigScan ${SOURCE_FILES})

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            )
endif(DOXYGEN_FOUND)