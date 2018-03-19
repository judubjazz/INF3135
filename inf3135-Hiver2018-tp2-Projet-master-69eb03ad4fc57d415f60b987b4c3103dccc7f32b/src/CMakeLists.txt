cmake_minimum_required(VERSION 3.8)
project(INF3135_tp2)

# Find the GTK module using pkg-config
include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "jansson")
pkg_check_modules(GTK REQUIRED "cairo")


SET(CMAKE_MODULE_PATH "/home/ju/JetBrainsProjects/CLionProjects/INF3135_tp2")

#include(FindCAIRO)
#find_package(cairo REQUIRED)


# Add the path to its header files to the compiler command line
include_directories(${GTK_INCLUDE_DIRS})

SET(GCC_COVERAGE_LINK_FLAGS "--libs cairo")

set(CMAKE_C_STANDARD 11)

# Add any compiler flags it requires
set(CMAKE_CXX_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")

set(SOURCE_FILES tp2.c array.c array.h color.c color.h  maze.c maze.h parse_args.c parse_args.h room_partition.c room_partition.h test_array.c test_maze.c test_partition.c utils.c utils.h drawing.c drawing.h)
add_executable(INF3135_tp2 ${SOURCE_FILES})
target_link_libraries(INF3135_tp2 cairo)
target_link_libraries(INF3135_tp2 jansson)
