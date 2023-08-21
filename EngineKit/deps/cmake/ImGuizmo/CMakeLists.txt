cmake_minimum_required(VERSION 3.0)

project("ImGuizmo")


include_directories("${DEPS_DIR}/src/SDL2/include")
include_directories("${DEPS_DIR}/src/SDL2_image/include")
include_directories("${DEPS_DIR}/src/SDL2_mixer/include")
include_directories("${DEPS_DIR}/src/SDL2_ttf/include")



include_directories(../../src/imgui)
include_directories(../../src/ImGuizmo)



add_library(ImGui
     ../../src/imgui/imconfig.h
     ../../src/imgui/imgui.cpp
     ../../src/imgui/imgui.h
     ../../src/imgui/imgui_demo.cpp
     ../../src/imgui/imgui_draw.cpp
     ../../src/imgui/imgui_internal.h
     ../../src/imgui/imgui_tables.cpp
     ../../src/imgui/imgui_widgets.cpp
     ../../src/imgui/imstb_rectpack.h
     ../../src/imgui/imstb_textedit.h
     ../../src/imgui/imstb_truetype.h


    ../../src/imgui/backends/imgui_impl_sdl.h
    ../../src/imgui/backends/imgui_impl_sdl.cpp
    ../../src/imgui/backends/imgui_impl_glfw.h
    ../../src/imgui/backends/imgui_impl_glfw.cpp
    ../../src/imgui/backends/imgui_impl_opengl3.h
    ../../src/imgui/backends/imgui_impl_opengl3.cpp
)


add_library(ImGuizmo
        ../../src/ImGuizmo/ImGuizmo.cpp
        ../../src/ImGuizmo/ImGuizmo.h)



target_link_libraries(ImGui PRIVATE libglew_static  glfw )
target_link_libraries(ImGuizmo PRIVATE libglew_static  glfw )


set_property(TARGET ImGui PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET ImGuizmo PROPERTY FOLDER "ThirdPartyLibraries")

