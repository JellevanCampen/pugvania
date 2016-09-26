cmake_minimum_required (VERSION 2.6)

#
# Project information
#

project (pugvania)
set (pugvania_VERSION_MAJOR 0)
set (pugvania_VERSION_MINOR 0)
set (pugvania_VERSION_PATCH 1)
set (pugvania_VERSION_TWEAK 0)

# Pass project information binary
configure_file (
	"game/pugvania_config.h.in"
	"game/pugvania_config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

add_executable(pugvania game/main.cpp)