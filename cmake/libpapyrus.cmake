# Find libpapyus directory
find_path(PAPYRUS_INCLUDE_DIR Papyrus.h)

if ((NOT PAPYRUS_INCLUDE_DIR) OR (NOT EXISTS ${PAPYRUS_INCLUDE_DIR}))
	# We could not find the header files for libpapyrus
	message("Unable to find libpapyrus")
	
	# We have a git submodule for libpapyrus, assume it is found at
	# external/libpapyrus. Need to clone the submodule
	execute_process(COMMAND git submodule update --init -- external/libpapyrus
										WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
										
	# Set PAPYRUS_INCLUDE_DIR properly
	set(PAPYRUS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/libpapyrus/include
				CACHE PATH "libpapyrus include directory")
				
	set(PAPYRUS_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/libpapyrus)
				
	# Also installs it
	install(DIRECTORY ${PAPYRUS_INCLUDE_DIR}/Papyrus.h DESTINATION ${PAPYRUS_INSTALL_DIR})
	
	# For convenience setup a target
	add_library(Papyrus TARGET)
	target_include_directories(Papyrus INTERFACE
															$<BUILD_INTERFACE:${PAPYRUS_INCLUDE_DIR}>
															$<INSTALL_INTERFACE:${PAPYRUS_INSTALL_DIR})
														
	# Need to export target
	install(TARGETS libpapyrus EXPORT papyrus_export DESTINATION ${PAPYRUS_INSTALL_DIR})
else()
	# Need to install it
	install(DIRECTORY ${PAPYRUS_INCLUDE_DIR}/Papyrus.h DESTINATION ${PAPYRUS_INSTALL_DIR})
	
	# For convenience setup a target
	add_library(Papyrus TARGET)
	target_include_directories(Papyrus INTERFACE
															$<BUILD_INTERFACE:${PAPYRUS_INCLUDE_DIR}>
															$<INSTALL_INTERFACE:${PAPYRUS_INSTALL_DIR})
														
	# Need to export target
	install(TARGETS libpapyrus EXPORT papyrus_export DESTINATION ${PAPYRUS_INSTALL_DIR})
	
endif()