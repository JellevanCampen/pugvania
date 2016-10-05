#
# [Engine CMakeLists.txt] 
# Engine is a static library project containing engine code. 
#

#
# Import all source files and organize them in source groups.
#

# [ engine ]
set (SRC_ENGINE 
	"engine.h"
	"engine.cpp"
	"engine_subsystem.h"
	)
source_group (engine FILES ${SRC_ENGINE})

# [ engine/utility ]
set (SRC_ENGINE_UTILITY 
	"utility/game_time.h"
	"utility/game_time.cpp"
	)
source_group (engine\\utility FILES ${SRC_ENGINE_UTILITY})

# [ <ALL> ]
set (SRC_ALL
	${SRC_ENGINE}
	${SRC_ENGINE_UTILITY}
	)

# Make Engine static library project
add_library (engine ${SRC_ALL})

# The headers containing version information are generated in the binary 
# directory. This directory is therefore added as an include directory.
target_include_directories(engine PUBLIC "${PROJECT_BINARY_DIR}/engine")

# Add the library's source directory as an include directory so that the Game 
# project can find its headers when linking to Engine.
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})