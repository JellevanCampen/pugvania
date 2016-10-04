#
# [Engine CMakeLists.txt] 
# Engine is a static library project containing engine code. 
#

# Make Engine static library project
add_library (engine engine.cpp engine.h)

# The headers containing version information are generated in the binary 
# directory. This directory is therefore added as an include directory.
target_include_directories(engine PUBLIC "${PROJECT_BINARY_DIR}/engine")

# Add the library's source directory as an include directory so that the Game 
# project can find its headers when linking to Engine.
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})