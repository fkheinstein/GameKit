cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJ_NAME ${PROJ_NAME})

project(${PROJ_NAME} LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()



include_directories(${Engine_DIR})
include_directories(${INCLUDE_OUTPUT_PATH})


include_directories("${DEPS_DIR}/src/glew-cmake/include")
include_directories("${DEPS_DIR}/src/glm")
include_directories("${DEPS_DIR}/src/ImGuizmo")
include_directories("${DEPS_DIR}/src/imgui")
include_directories("${DEPS_DIR}/src/stb")
include_directories("${DEPS_DIR}/src/entt/src")
include_directories("${DEPS_DIR}/src/stduuid/include")
include_directories("${DEPS_DIR}/src/FastDelegate")

include_directories("${DEPS_DIR}/src/eventpp/include")

include_directories("${DEPS_DIR}/src/LuaBridge/Source")
include_directories("${DEPS_DIR}/src/Lua/src")


include_directories("${DEPS_DIR}/src/SDL2/include")
include_directories("${DEPS_DIR}/src/SDL2_image/include")
include_directories("${DEPS_DIR}/src/SDL2_mixer/include")
include_directories("${DEPS_DIR}/src/SDL2_ttf/include")
include_directories("${DEPS_DIR}/src/freetype-gl")



link_directories(${LIBRARY_OUTPUT_PATH})

link_directories("${DEPS_DIR}/src/SDL2/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_image/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_mixer/lib/x64")
link_directories("${DEPS_DIR}/src/SDL2_ttf/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/core/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/fsbank/lib/x64")
link_directories("${DEPS_DIR}/vendor/FMOD/studio/lib/x64")



file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "Src/*.h"
    "Src/*.cpp"
    "Src/*.rc")

add_executable(${PROJ_NAME}  main.cpp ${SRC_FILES}  )

target_link_libraries(${PROJ_NAME} EngineLib SDL2 SDL2main libglew_static glfw imagehlp ImGui ImGuizmo assimp spdlog  freetype-gl fmod_vc fmodstudio_vc)

