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

# [ engine/common/datatypes ]
set (SRC_ENGINE_COMMON_DATATYPES 
	"common/datatypes/color_types.h"
	"common/datatypes/shape_types.h"
	)
source_group (engine\\common\\datatypes FILES ${SRC_ENGINE_COMMON_DATATYPES})

# [ engine/common/patterns ]
set (SRC_ENGINE_COMMON_PATTERNS 
	"common/patterns/reverse_iterator.h"
	"common/patterns/enum_class_iterator.h"
	)
source_group (engine\\common\\patterns FILES ${SRC_ENGINE_COMMON_PATTERNS})

# [ engine/common/utility ]
set (SRC_ENGINE_COMMON_UTILITY 
	"common/utility/config_file.cpp"
	"common/utility/config_file.h"
	"common/utility/debug_defines.h"
	"common/utility/float_comparison.h"
	"common/utility/path.cpp"
	"common/utility/pi.h"
	"common/utility/windows_terminal_colors.h"
	)
source_group (engine\\common\\utility FILES ${SRC_ENGINE_COMMON_UTILITY})

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

# [ engine/graphics ]
set (SRC_ENGINE_GRAPHICS
	"graphics/graphics.h"
	"graphics/graphics_bootstrapper.h"
	"graphics/graphics_bootstrapper.cpp"
	"graphics/graphics_glfw.h"
	"graphics/graphics_glfw.cpp"
	)
source_group (engine\\graphics FILES ${SRC_ENGINE_GRAPHICS})

# [ engine/timing ]
set (SRC_ENGINE_TIMING
	"timing/timing.h"
	"timing/timing.cpp"
	)
source_group (engine\\timing FILES ${SRC_ENGINE_TIMING})

# [ <ALL> ]
set (SRC_ALL
	${SRC_ENGINE}
	${SRC_ENGINE_COMMON}
	${SRC_ENGINE_COMMON_DATATYPES}
	${SRC_ENGINE_COMMON_PATTERNS}
	${SRC_ENGINE_COMMON_UTILITY}
	${SRC_ENGINE_DEBUGGING}
	${SRC_ENGINE_GRAPHICS}
	${SRC_ENGINE_TIMING}
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
	message(STATUS ">> Found: Boost 1.62.0 library")
	target_include_directories(engine PUBLIC ${Boost_INCLUDE_DIRS})
	target_link_libraries(engine PUBLIC ${Boost_LIBRARIES})
endif (Boost_FOUND)

# [Date]
find_package(Date REQUIRED)
if (Date_FOUND)
	message(STATUS ">> Found: Howard Hinnant's Date library")
    target_include_directories(engine PUBLIC ${Date_INCLUDE_DIRS})
endif (Date_FOUND)

# [GLFW] (compiled along with the engine)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) # Don't build docs
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) # Don't build tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build examples
message(STATUS "$ENV{GLFW_ROOT}")
message(STATUS ${CMAKE_CURRENT_BINARY_DIR})
if (NOT "$ENV{GLFW_ROOT}" STREQUAL "")
	add_subdirectory($ENV{GLFW_ROOT} libs/glfw)
	target_link_libraries(engine PUBLIC glfw)
	message(STATUS ">> Found: GLFW library")
else()
	message(FATAL_ERROR ">> Not found: GLFW library. Set environment variable GLFW_ROOT to the GLFW root directory to locate it.")
endif()
