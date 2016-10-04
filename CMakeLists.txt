cmake_minimum_required (VERSION 2.6)

#
# Pugvania
#
# The Pugvania project contains the implementation of a 2D game and its engine. 
# The poject contains two subprojects: (1) Engine - a static library project 
# containing engine code, and (2) Game - an executable project containing game 
# code. 
#
# [Top-level CMakeLists.txt] 
# Contains version information for the Engine and Game projects and recursively 
# includes both projects.
#

project (pugvania)

#
# Version information
#

# Engine version
set (engine_VERSION_MAJOR 0)
set (engine_VERSION_MINOR 0)
set (engine_VERSION_PATCH 1)
set (engine_VERSION_TWEAK 0)

# Game version
set (game_VERSION_MAJOR 0)
set (game_VERSION_MINOR 0)
set (game_VERSION_PATCH 1)
set (game_VERSION_TWEAK 0)

# Pass version information to the Engine and Game projects via headers
configure_file (
	"engine/engine_config.h.in"
	"engine/engine_config.h"
)
configure_file (
	"game/game_config.h.in"
	"game/game_config.h"
)

#
# Recursively include the Engine and Game projects 
#

add_subdirectory (engine)
add_subdirectory (game)