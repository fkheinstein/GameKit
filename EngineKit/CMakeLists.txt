cmake_minimum_required(VERSION 3.22 FATAL_ERROR)


get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJ_NAME ${PROJ_NAME})



# encode version number as <major>.<minor>.<patch>:<changeset>
set(ENGINE_VERSION_MAJOR "1")
set(ENGINE_VERSION_MINOR "0")
set(ENGINE_VERSION_PATCH "1")
set(ENGINE_VERSION_EXTRA "0")
set(PROJECT_BUILD_VERSION    "${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}.${ENGINE_VERSION_PATCH}")


set(PROJECT_VERSION_MAJOR  ${ENGINE_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR  ${ENGINE_VERSION_MINOR})
set(PROJECT_VERSION_PATCH  ${ENGINE_VERSION_PATCH})

set(PROJECT_VERSION  ${PROJECT_BUILD_VERSION})

MESSAGE(STATUS "PROJECT_BUILD_VERSION: " ${PROJECT_BUILD_VERSION})

project(${PROJ_NAME}
         VERSION ${PROJECT_BUILD_VERSION}
         DESCRIPTION "A project with external library"
         LANGUAGES C;CXX )



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# -------------------------------
# Build Targets
# -------------------------------
set(WINDOWS WINDOWS)
set(MAC MACOS)
set(LINUX LINUX)

set(PLATFORM_TARGET "")

# -------------------------------
# Find Build Target
# -------------------------------
IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM_TARGET ${WINDOWS})
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_TARGET ${LINUX})
ELSEIF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    set(PLATFORM_TARGET ${MAC})
ELSE()
    message(FATAL_ERROR "Unsupported platform, configuration will end.")
ENDIF()

message(STATUS "Build Target: ${PLATFORM_TARGET}")

string(TOLOWER ${PLATFORM_TARGET} LOWER_PLATFORM_TARGET)
string(TOUPPER ${PLATFORM_TARGET} UPPER_PLATFORM_TARGET)



if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(FTS_DEBUG   "Enable FTS_DEBUG"   on)
option(FTS_IMGUI   "Enable FTS_IMGUI"   on)
#option(_DEBUG    "Enable _DEBUG"    on)
option(NDEBUG    "Enable NDEBUG"    on)

set(BUILD_TESTING ON)

# -- configure cmake modules path
set(ENGINEKit_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
#set(CMAKE_MODULE_PATH  ${ENGINEKit_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH  ${ENGINEKit_MODULE_PATH})



MESSAGE(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})



find_package(Git)

if(GIT_FOUND)
    find_program(GIT_EXECUTABLE git DOC "git command line client")

    message( STATUS "Building from GIT")
    Git_WC_INFO(${PROJECT_SOURCE_DIR} Project)
    message( STATUS "Git Tools : ${GIT_VERSION_STRING}")
    message( STATUS "Revision  : ${Project_WC_REVISION}")
    message( STATUS "Creator   : ${Project_WC_LAST_CHANGED_AUTHOR}")
    message( STATUS "Date      : ${Project_WC_LAST_CHANGED_DATE}")

    set( ENGINE_VERSION_EXTRA  ${Project_WC_REVISION})
endif(GIT_FOUND)



set(BUILD_VERSION    "${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}.${ENGINE_VERSION_PATCH}.${ENGINE_VERSION_EXTRA}")

set(ENGINE_SHORT_LICENSE "GNU General Public License")




# -------------------------------
# Setup the solution
# -------------------------------
message(STATUS "#--------------------- Starting project generation ---------------------")
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "CMake Generator: ${CMAKE_GENERATOR}")
message(STATUS "Generating project: ${PROJECT_NAME} v.${PROJECT_BUILD_VERSION}")

# -- config output directories
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (EXECUTABLE_OUTPUT_PATH            ${PROJECT_SOURCE_DIR}/Host/bin)
    set (LIBRARY_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/lib)
    set (INCLUDE_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/include)
 else()
    set (EXECUTABLE_OUTPUT_PATH            ${PROJECT_SOURCE_DIR}/Host/bin)
    set (LIBRARY_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/lib)
    set (INCLUDE_OUTPUT_PATH               ${PROJECT_SOURCE_DIR}/Host/include)
 endif()




set (DEPS_DIR                              ${PROJECT_SOURCE_DIR}/deps)
set (ASSETS_DIR                            ${PROJECT_SOURCE_DIR}/Assets)

# -- config source directories
set (Engine_DIR                            ${PROJECT_SOURCE_DIR}/EngineLib)
set (EngineTest_DIR                        ${PROJECT_SOURCE_DIR}/EngineTest)
set (EngineSandbox_DIR                     ${PROJECT_SOURCE_DIR}/Sandbox)



#used to fetch dependency on internet mainly Github
if(WIN32)
 set(PYTHON_EXECUTABLE "python")
else()
 set(PYTHON_EXECUTABLE "python3")
endif()


include(CheckTypeSize)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)


execute_process(COMMAND date "+%Y.%m.%d" OUTPUT_VARIABLE DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND hostname OUTPUT_VARIABLE HOSTNAME OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND whoami OUTPUT_VARIABLE PACKAGER    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT DATE)
    set(DATE "unknown")
endif(NOT DATE)
set(GAMEENGINE_DATE "${DATE}")

if(NOT HOSTNAME)
    set(HOSTNAME "unknown")
endif(NOT HOSTNAME)
set(GAMEENGINE_HOST "${HOSTNAME}")

if(NOT PACKAGER)
    set(PACKAGER "unknown")
endif(NOT PACKAGER)
set(GAMEENGINE_PACKAGER "${PACKAGER}")


# Call configure files on ver.h.in to set the version.
# Uses the standard ${VARIABLE} syntax in the file
configure_file("${CMAKE_SOURCE_DIR}/cmake/inConfig/VersionEngine.h.in" ${INCLUDE_OUTPUT_PATH}/VersionEngine.h)

# configure the path.h.in file.
# This file can only use the @VARIABLE@ syntax in the file
configure_file("${CMAKE_SOURCE_DIR}/cmake/inConfig/PathEngine.h.in" ${INCLUDE_OUTPUT_PATH}/PathEngine.h @ONLY)

# configuration
configure_file("${CMAKE_SOURCE_DIR}/cmake/inConfig/config.h.in" ${INCLUDE_OUTPUT_PATH}/Config.h)



message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER_ID}")


add_subdirectory (${DEPS_DIR})

add_subdirectory (${Engine_DIR})

add_subdirectory (${EngineSandbox_DIR})

if(BUILD_TESTING)
    add_subdirectory (${EngineTest_DIR})
endif()
