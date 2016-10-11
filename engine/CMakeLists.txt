#
# [Engine CMakeLists.txt] 
# Engine is a static library project containing engine code. 
#

message (STATUS "Configuring engine project (static library)")

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

# [ engine/debugging ]
set (SRC_ENGINE_DEBUGGING
	"debugging/logging.h"
	"debugging/logging.cpp"
	"debugging/log_channel.h"
	"debugging/log_channel.cpp"
	"debugging/log_output.h"
	"debugging/log_output_terminal.h"
	"debugging/log_output_terminal.cpp"
	"debugging/log_output_files.h"
	"debugging/log_output_files.cpp"
	"debugging/log_output_globalfile.h"
	"debugging/log_output_globalfile.cpp"
	)
source_group (engine\\debugging FILES ${SRC_ENGINE_DEBUGGING})

# [ engine/common ]
set (SRC_ENGINE_COMMON 
	"common/game_time.h"
	"common/game_time.cpp"
	)
source_group (engine\\common FILES ${SRC_ENGINE_COMMON})

# [ engine/common/datatypes ]
set (SRC_ENGINE_COMMON_DATATYPES 
	"common/datatypes/color_types.h"
	)
source_group (engine\\common\\datatypes FILES ${SRC_ENGINE_COMMON_DATATYPES})

# [ engine/common/patterns ]
set (SRC_ENGINE_COMMON_PATTERNS 
	"common/patterns/reverse_iterator.h"
	)
source_group (engine\\common\\patterns FILES ${SRC_ENGINE_COMMON_PATTERNS})

# [ engine/common/utility ]
set (SRC_ENGINE_COMMON_UTILITY 
	"common/utility/config_file.cpp"
	"common/utility/config_file.h"
	"common/utility/path.cpp"
	"common/utility/windows_terminal_colors.h"
	)
source_group (engine\\common\\utility FILES ${SRC_ENGINE_COMMON_UTILITY})

# [ <ALL> ]
set (SRC_ALL
	${SRC_ENGINE}
	${SRC_ENGINE_DEBUGGING}
	${SRC_ENGINE_COMMON}
	${SRC_ENGINE_COMMON_DATATYPES}
	${SRC_ENGINE_COMMON_PATTERNS}
	${SRC_ENGINE_COMMON_UTILITY}
	)

# Make Engine static library project
add_library (engine ${SRC_ALL})

# The headers containing version information are generated in the binary 
# directory. This directory is therefore added as an include directory.
target_include_directories(engine PUBLIC "${PROJECT_BINARY_DIR}/engine")

# Add the library's source directory as an include directory so that the Game 
# project can find its headers when linking to Engine.
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#
# Make all required external libraries available
#

# [Boost]
find_package(Boost 1.62.0 REQUIRED)
if (Boost_FOUND)
	target_include_directories(engine PUBLIC ${Boost_INCLUDE_DIRS})
	target_link_libraries(engine PUBLIC ${Boost_LIBRARIES})
endif (Boost_FOUND)
