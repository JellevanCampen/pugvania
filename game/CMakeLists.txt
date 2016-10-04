#
# [Game CMakeLists.txt] 
# Game is an executable project containing game code. 
#

# Make Game an executable project
add_executable (game main.cpp)

# The headers containing version information are generated in the binary 
# directory. This directory is therefore added as an include directory.
target_include_directories(game PUBLIC "${PROJECT_BINARY_DIR}/game")

# Make the Engine static library available when linking the Game executable
target_link_libraries (game LINK_PUBLIC engine)