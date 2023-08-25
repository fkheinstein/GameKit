#include <spch.h>


#include "ImGuiLayer.h"


#include <Utils/OpenGLLibInclude.h>

namespace fts
{

    ImGuiLayer::ImGuiLayer(Window* window) : Layer("ImGuiLayer"), m_window(window)
    {

        IMGUI_CHECKVERSION();
        //ImGui::CreateContext();
        m_context = ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

        io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
        io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
        io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
        io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
        io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
        io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
        io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
        io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
        io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
        io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
        io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
        io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
        io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
        io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

       
        //
      /*  Window* window = static_cast<Window*>(m_window);
        ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)window->GetNativeWindow(), window->GetGraphicsContext());
        ImGui_ImplOpenGL3_Init("#version 460");*/
        // Setup Platform/Renderer backends
        m_window->ImGuiInitBackend();
    }

    ImGuiLayer::~ImGuiLayer() {
        
        /*ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();*/

        m_window->ImGuiShutdown();
        ImGui::DestroyContext();

    }

    void ImGuiLayer::Begin()
    {
        m_window->ImGuiNewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_window->GetWidth(), m_window->GetHeight());

        ImGui::Render();
        m_window->ImGuiRenderDrawData();
    }


    void ImGuiLayer::SetDarkThemeColor()
    {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }
} // namespace fts