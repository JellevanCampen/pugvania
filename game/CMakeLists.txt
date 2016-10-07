#
# [Game CMakeLists.txt] 
# Game is an executable project containing game code. 
#

message (STATUS "Configuring game project (executable)")

#
# Import all source files and organize them in source groups.
#

# [ game ]
set (SRC_GAME 
	"main.cpp"
	)
source_group (game FILES ${SRC_GAME})

# [ <ALL> ]
set (SRC_ALL
	${SRC_GAME}
	)

# Make Game an executable project
add_executable (game ${SRC_ALL})

# The headers containing version information are generated in the binary 
# directory. This directory is therefore added as an include directory.
target_include_directories(game PUBLIC "${PROJECT_BINARY_DIR}/game")

# Make the Engine static library available when linking the Game executable
target_link_libraries (game LINK_PUBLIC engine)