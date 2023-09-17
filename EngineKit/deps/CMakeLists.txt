
if((NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.bootstrap.json") OR ("${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" IS_NEWER_THAN "${CMAKE_CURRENT_SOURCE_DIR}/.bootstrap.json"))
	execute_process(
		COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap.py"
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		RESULT_VARIABLE bootstrap_result
	)
	if (NOT (${bootstrap_result} EQUAL 0))
		message(FATAL_ERROR "Cannot run bootstrap.py")
	endif()
endif()


#set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")


set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")



add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/glew-cmake")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/glfw")

set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "")
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "")


set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "")
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "")


set(FREETYPE_INCLUDE_DIRS       "${DEPS_DIR}/src/freetype/include")
set(FREETYPE_LIBRARY            "${LIBRARY_OUTPUT_PATH}/Debug/freetyped.lib")

set(ALSOFT_UTILS OFF)
set(ALSOFT_EXAMPLES OFF)
set(ALSOFT_INSTALL OFF)
set(ALSOFT_INSTALL_CONFIG OFF)
set(ALSOFT_INSTALL_HRTF_DATA OFF)
set(ALSOFT_INSTALL_AMBDEC_PRESETS OFF)
set(ALSOFT_INSTALL_EXAMPLES OFF)
set(ALSOFT_INSTALL_UTILS OFF)
set(LIBTYPE STATIC)



set(CMAKE_MODULE_PATH  ${ENGINEKit_MODULE_PATH})


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/glm")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/spdlog")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/entt")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/assimp")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/eventpp")

#This project is tested using GoogleTest.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/googletest")


 
set(LUABRIDGE_TESTING OFF CACHE BOOL "")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/LuaBridge")


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/freetype")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Lua")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ImGuizmo")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Freetype-GL")

#set_property(TARGET common          PROPERTY FOLDER "ThirdPartyLibraries")

set_property(TARGET LuaBridge          PROPERTY FOLDER "ThirdPartyLibraries")


set_property(TARGET gtest_main          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET gtest          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET gmock_main          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET gmock          PROPERTY FOLDER "ThirdPartyLibraries")

set_property(TARGET freetype        PROPERTY FOLDER "ThirdPartyLibraries")


set_property(TARGET glfw            PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET spdlog          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET assimp          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET aob             PROPERTY FOLDER "ThirdPartyLibraries")


if(WIN32)
 set_property(TARGET zlib          PROPERTY FOLDER "ThirdPartyLibraries")
 set_property(TARGET zlibstatic    PROPERTY FOLDER "ThirdPartyLibraries")
 set_property(TARGET IrrXML        PROPERTY FOLDER "ThirdPartyLibraries")
 set_property(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTY FOLDER "ThirdPartyLibraries")
endif()

set_property(TARGET uninstall        PROPERTY FOLDER "ThirdPartyLibraries")

#set_property(TARGET libglew_shared   PROPERTY FOLDER "ThirdPartyLibraries")
#set_property(TARGET libglew_static   PROPERTY FOLDER "ThirdPartyLibraries")

