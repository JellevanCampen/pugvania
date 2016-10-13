# FindDate
# Copyright (c) 2016 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- Date_FOUND : true if both the includes and libraries are found
# -- Date_INCLUDE_DIRS : location of the include files
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : directory where project's include files are located
#
# Usage: 
# -- find_package(Date REQUIRED)
# -- if (Date_FOUND)
# --     target_include_directories(<target> ${Date_INCLUDE_DIRS})
# -- endif (Date_FOUND)

# Include directories
find_path( Date_INCLUDE_DIRS 
	NAMES 
		date.h
	PATHS 
		${CMAKE_INCLUDE_PATH}/date
	DOC 
		"The include directory for Howard Hinnant's Date library"
)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Date DEFAULT_MSG Date_INCLUDE_DIRS)