
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJ_NAME ${PROJ_NAME})

project(${PROJ_NAME} C CXX)


if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


include_directories(${INCLUDE_OUTPUT_PATH})
include_directories(${Engine_DIR})


include_directories("${DEPS_DIR}/src/glew-cmake/include")
include_directories("${DEPS_DIR}/src/glfw/include")
include_directories("${DEPS_DIR}/src/glm")
include_directories("${DEPS_DIR}/src/entt/src")
include_directories("${DEPS_DIR}/src/ImGuizmo")
include_directories("${DEPS_DIR}/src/imgui")
include_directories("${DEPS_DIR}/src/stb")
include_directories("${DEPS_DIR}/src/stduuid/include")
include_directories("${DEPS_DIR}/src/FastDelegate")


include_directories("${DEPS_DIR}/vendor/glad/include")
include_directories("${DEPS_DIR}/vendor/FMOD/core/inc")
include_directories("${DEPS_DIR}/vendor/FMOD/fsbank/inc")
include_directories("${DEPS_DIR}/vendor/FMOD/studio/inc")

include_directories("${DEPS_DIR}/src/freetype/include")
include_directories("${DEPS_DIR}/src/freetype-gl")


include_directories("${DEPS_DIR}/src/SDL2/include")
include_directories("${DEPS_DIR}/src/SDL2_image/include")
include_directories("${DEPS_DIR}/src/SDL2_mixer/include")
include_directories("${DEPS_DIR}/src/SDL2_ttf/include")


link_directories(${LIBRARY_OUTPUT_PATH})

link_directories("${DEPS_DIR}/src/SDL2/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_image/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_mixer/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_ttf/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/core/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/fsbank/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/studio/lib/x64")


include(${ENGINEKit_MODULE_PATH}/FTS_CommonMacros.cmake)
include(${ENGINEKit_MODULE_PATH}/utilities.cmake)

file(GLOB_RECURSE ASSETS_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} assets/*.????)


# Collect sources into the variable Engine_Framework_CmdGraphic_Common_Src
file (GLOB_RECURSE EngineCore_SRC
"${Engine_DIR}/*.txt"
"${Engine_DIR}/*.*"
"${Engine_DIR}/*.h"
"${Engine_DIR}/*.inl"
"${Engine_DIR}/*.hpp"
"${Engine_DIR}/*.c??")



#SETUP_GROUPS("${ASSETS_FILES}")

GROUPSOURCES(${Engine_DIR} Src)

add_library(${PROJ_NAME} SHARED 
        ${EngineCore_SRC} 
       # ${SHADERS} 
       # ${Engine_DIR}/Utils/glm.natvis
        )


add_custom_command(
        TARGET ${PROJ_NAME} 
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${DEPS_DIR}/src/SDL2/lib/x64/SDL2.dll" "${EXECUTABLE_OUTPUT_PATH}/Debug/SDL2.dll")

file(COPY "${LIBRARY_OUTPUT_PATH}/" DESTINATION "${EXECUTABLE_OUTPUT_PATH}/" FILES_MATCHING PATTERN "*.dll")
