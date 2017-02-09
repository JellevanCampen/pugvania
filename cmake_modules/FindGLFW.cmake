# FindGLFW
# Copyright (c) 2017 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- GLFW_FOUND : true if both the includes and libraries are found
# -- GLFW_INCLUDE_DIRS : location of the include files
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : directory where project's include files are located
#
# Usage: 
# -- find_package(GLFW REQUIRED)
# -- if (GLFW_FOUND)
# --     target_include_directories(<target> ${GLFW_INCLUDE_DIRS})
# -- endif (GLFW_FOUND)

# Include directories
find_path( GLFW_INCLUDE_DIRS 
	NAMES 
		glfw3.h
	PATHS 
		${CMAKE_INCLUDE_PATH}/glfw
	DOC 
		"The include directory for the GLFW library"
)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_INCLUDE_DIRS)