cmake_minimum_required(VERSION 3.12)

macro(SETUP_GROUPS_OLD src_files)
	foreach(FILE ${src_files})
		get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
		#get_filename_component(PARENT_DIR "${FILE}" PATH)


		#convert source file to absolute
        #get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
        # Get the directory of the absolute source file
        #get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)

		# skip src or include and changes /'s to \\'s
		set(GROUP "${PARENT_DIR}")
		string(REPLACE "/" "\\" GROUP "${GROUP}")

		source_group("${GROUP}" FILES "${FILE}")
	endforeach()
endmacro()


macro(SETUP_GROUPS src_files)
	foreach(FILE ${src_files})
		get_filename_component(PARENT_DIR "${FILE}" PATH)

		# skip src or include and changes /'s to \\'s
		set(GROUP "${PARENT_DIR}")
		string(REPLACE "/" "\\" GROUP "${GROUP}")

		source_group("${GROUP}" FILES "${FILE}")
	endforeach()
endmacro()

macro(SET_OUTPUT_NAMES projname)
	set_target_properties(${projname} PROPERTIES OUTPUT_NAME_DEBUG ${projname}_Debug)
	set_target_properties(${projname} PROPERTIES OUTPUT_NAME_RELEASE ${projname}_Release)
	set_target_properties(${projname} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${projname}_ReleaseDebInfo)

	# On Linux/macOS the binaries go to <root>/bin folder
	if (UNIX)
		set_target_properties(${projname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	endif()
endmacro()

macro(SETUP_APP projname chapter)
	set(FOLDER_NAME ${chapter})
	set(PROJECT_NAME ${projname})
	project(${PROJECT_NAME} CXX)

	file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c??)
	file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

	file(GLOB_RECURSE ASSETS_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} assets/*.????)

	include_directories(src)
	add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${ASSETS_FILES})
	if(MSVC)
		add_definitions(-D_CONSOLE)
	endif()
	SETUP_GROUPS("${SRC_FILES}")
	SETUP_GROUPS("${HEADER_FILES}")
	SETUP_GROUPS("${ASSETS_FILES}")

	SET_OUTPUT_NAMES(${PROJECT_NAME})

	set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${FOLDER_NAME})

	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

	if(MSVC)
		set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	endif()

endmacro()
