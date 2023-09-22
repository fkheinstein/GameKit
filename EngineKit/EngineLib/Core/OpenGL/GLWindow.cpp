#include <spch.h>


#include "Core/OpenGL/GLWindow.h"

#include "Core/Event.h"
#include "Core/Layer.h"




#include "Utils/OpenGLLibInclude.h"


#ifdef FTS_IMGUI
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>
#endif

#include <Events/Event.h>
#include <Events/EventManager.h>


#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Events/WindowEvent.h>




#define  DEBUG_BUILD

#include <SDL.h>

#ifdef DEBUG_BUILD
#define SDL(stmt) FTS_ASSERT_MSG(stmt == 0, SDL_GetError())
#else
#define SDL(stmt) stmt
#endif


namespace fts {

    fts::event::MouseButton::Code ConvertToButton(uint8_t button)
    {
        if (button == SDL_BUTTON_LEFT)
        {
            return fts::event::MouseButton::Code::Left;
        }
        if (button == SDL_BUTTON_MIDDLE)
        {
            return fts::event::MouseButton::Code::Middle;
        }
        else if (button == SDL_BUTTON_RIGHT)
        {
            return fts::event::MouseButton::Code::Right;
        }
        return  fts::event::MouseButton::Code::Count;
    }


    fts::MouseButton ConvertToButton1(uint8_t button)
    {
        if (button == SDL_BUTTON_LEFT)
        {
            return fts::MouseButton::Left;
        }
        if (button == SDL_BUTTON_MIDDLE)
        {
            return fts::MouseButton::Middle;
        }
        else if (button == SDL_BUTTON_RIGHT)
        {
            return fts::MouseButton::Right;
        }
        return  fts::MouseButton::Count;
    }



    GLWindow::GLWindow(const WindowCreateInfo& info) : m_is_init_imgui(false)
    {
        SDL(SDL_Init(SDL_INIT_EVERYTHING));
        uint32_t sdl_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

        // Double buffer
        SDL(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1));

        // OpenGL Version
        SDL(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4));
        SDL(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5));
        SDL(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE));

        // MultiSampling
        if (info.msaa != MultiSampleLevel::None) {
            SDL(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1));
            SDL(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,
            static_cast<int>(info.msaa)));
        }

        m_window = SDL_CreateWindow(info.title.c_str(), SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, info.width, info.height, sdl_flags);

        FTS_ASSERT_MSG(m_window != nullptr, SDL_GetError());

        m_context = SDL_GL_CreateContext(m_window);
        FTS_ASSERT_MSG(m_context != nullptr, SDL_GetError());

        SDL(SDL_GL_SetSwapInterval(info.vsync ? 1 : 0));
    }

    GLWindow::~GLWindow()
    {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    template <typename T>
    void ProcessEvent(T& e, EventStack<Layer*>& layers)
    {
        for (auto iter = layers.rbegin(); iter != layers.rend(); ++iter) {
            (*iter)->On(e);
        }
    }


   

    void GLWindow::PollEvents(EventStack<Layer*>& layers)
    {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event) == 1) {
            if (m_is_init_imgui) {
                ImGui_ImplSDL2_ProcessEvent(&sdl_event);
            }
            switch (sdl_event.type) {

          

            case SDL_MOUSEMOTION: {
                MouseMotionEvent event;
                event.x = sdl_event.motion.x;
                event.y = sdl_event.motion.y;
                event.x_rel = sdl_event.motion.xrel;
                event.y_rel = sdl_event.motion.yrel;
                ProcessEvent(event, layers);


                fts::evt::MouseMovedEvent evtMoved{ (float)event.x , (float)event.y};
                fts::evt::EventManager::eventDispatcher.dispatch(evtMoved.GetEventType(), evtMoved);

            } break;

            case SDL_MOUSEBUTTONDOWN:
            { 
                MouseButtonEvent event;
                event.button = static_cast<MouseButton>(sdl_event.button.button);
                event.x = sdl_event.button.x;
                event.y = sdl_event.button.y;
                event.clicks = sdl_event.button.clicks;
                event.state = sdl_event.button.state;
                ProcessEvent(event, layers);

                fts::evt::MouseButtonPressedEvent evtPressed{ static_cast<MouseButton>(sdl_event.button.button) };
                fts::evt::EventManager::eventDispatcher.dispatch(evtPressed.GetEventType(), evtPressed);

            }  break;

            case SDL_MOUSEBUTTONUP: {
                MouseButtonEvent event;
                event.button = static_cast<MouseButton>(sdl_event.button.button);
                event.x = sdl_event.button.x;
                event.y = sdl_event.button.y;
                event.clicks = sdl_event.button.clicks;
                event.state = sdl_event.button.state;
                ProcessEvent(event, layers);



               /* fts::event::MouseButton::Code button = ConvertToButton(sdl_event.button.button);
                fts::event::MouseButtonReleasedEvt mouseUpEvent;
                mouseUpEvent.X = sdl_event.button.x;
                mouseUpEvent.Y = sdl_event.button.y;
                mouseUpEvent.Clicks = sdl_event.button.clicks;
                mouseUpEvent.Button = button;
                mouseUpEvent.ButtonState = sdl_event.button.state == SDL_PRESSED ? fts::event::MouseButton::State::Press : fts::event::MouseButton::State::Release;
                fts::event::EventManager::event_dispatcher.dispatch(event::FtsEventType::MOUSE_BUTTON_RELEASED, mouseUpEvent);*/

                fts::evt::MouseButtonReleasedEvent evtReleased{ static_cast<MouseButton>(sdl_event.button.button) };
                fts::evt::EventManager::eventDispatcher.dispatch(evtReleased.GetEventType(), evtReleased);

            }  break;

            case SDL_MOUSEWHEEL: {
                MouseWheelEvent event;
                event.x = sdl_event.wheel.x;
                event.y = sdl_event.wheel.y;
                ProcessEvent(event, layers);

                /*fts::event::MouseWheelEvt mouseWheelEvent;
                mouseWheelEvent.Y = sdl_event.wheel.y;
                mouseWheelEvent.X = sdl_event.wheel.x;
                mouseWheelEvent.DeltaY = sdl_event.wheel.y;
                mouseWheelEvent.direction = (sdl_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? fts::event::MouseButton::WheelDirection::Normal : fts::event::MouseButton::WheelDirection::Flipped);
                fts::event::EventManager::event_dispatcher.dispatch(event::FtsEventType::MOUSE_SCROLLED_EVT, mouseWheelEvent);*/

                fts::evt::MouseScrolledEvent evt{ (float)sdl_event.wheel.x, (float)sdl_event.wheel.y };
                fts::evt::EventManager::eventDispatcher.dispatch(evt.GetEventType(), evt);

            } break;

            case SDL_KEYDOWN:
            {
                KeyEvent event;
                event.keycode = static_cast<Keycode>(sdl_event.key.keysym.sym);
                event.mod = sdl_event.key.keysym.mod;
                event.state = sdl_event.key.state;
                ProcessEvent(event, layers);


               /* fts::event::KeyPressedEvent keyPressed(static_cast<fts::Keycode>(sdl_event.key.keysym.scancode, sdl_event.key.repeat != 0 ? true : false));
                keyPressed.Key = static_cast<Keycode>(sdl_event.key.keysym.scancode);
                keyPressed.Repeat = sdl_event.key.repeat != 0 ? true : false;
                keyPressed.Mod = sdl_event.key.keysym.mod;
                fts::event::EventManager::event_dispatcher.dispatch(event::FtsEventType::KEY_PRESSED, keyPressed);*/

                fts::evt::KeyPressedEvent evtKey{ static_cast<Keycode>(sdl_event.key.keysym.scancode), sdl_event.key.repeat != 0 ? true : false };
                fts::evt::EventManager::eventDispatcher.dispatch(evtKey.GetEventType(), evtKey);


            } break;

            case SDL_KEYUP:
            {
                KeyEvent event;
                event.keycode = static_cast<Keycode>(sdl_event.key.keysym.sym);
                event.mod = sdl_event.key.keysym.mod;
                event.state = sdl_event.key.state;
                ProcessEvent(event, layers);
                

                //fts::event::KeyReleasedEvent keyReleased(static_cast<fts::Keycode>(sdl_event.key.keysym.scancode));
                //keyReleased.Key = static_cast<Keycode>(sdl_event.key.keysym.scancode);
                //keyReleased.Mod = sdl_event.key.keysym.mod;
                //fts::event::EventManager::event_dispatcher.dispatch(event::FtsEventType::KEY_RELEASED, keyReleased);

                fts::evt::KeyReleasedEvent evtKey{ static_cast<Keycode>(sdl_event.key.keysym.scancode) };
                fts::evt::EventManager::eventDispatcher.dispatch(evtKey.GetEventType(), evtKey);



            } break;
            case SDL_WINDOWEVENT: {
                switch (sdl_event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                case SDL_WINDOWEVENT_SIZE_CHANGED: {
                    WindowSizeEvent event;
                    event.width = sdl_event.window.data1;
                    event.height = sdl_event.window.data2;
                    ProcessEvent(event, layers);

                    fts::evt::WindowResizeEvent evtRzResize(sdl_event.window.data1, sdl_event.window.data2);
                    fts::evt::EventManager::eventDispatcher.dispatch(evtRzResize.GetEventType(), evtRzResize);
                } break;
                }
            } break;
            case SDL_TEXTINPUT: {
                TextInputEvent event;
                std::copy(std::begin(sdl_event.text.text), std::end(sdl_event.text.text), event.text);

                ProcessEvent(event, layers);
            } break;
            case SDL_QUIT: {

                fts::evt::WindowCloseEvent evtQuit;
                fts::evt::EventManager::eventDispatcher.dispatch(evtQuit.GetEventType(), evtQuit);


                AppQuitEvent event;
                ProcessEvent(event, layers);

            } break;
            }
        }
    }

    void* GLWindow::GetNativeWindow() const  { return (void*)m_window; }

    void GLWindow::ImGuiInitBackend()
    {
        ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
        ImGui_ImplOpenGL3_Init("#version 450");
        m_is_init_imgui = true;
    }

    void GLWindow::ImGuiShutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        m_is_init_imgui = false;
    }

    void GLWindow::ImGuiNewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
    }


    void GLWindow::ImGuiRenderDrawData()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    MultiSampleLevel GLWindow::GetMSAA() const
    {
        int value = 0;
        SDL(SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &value));
        return static_cast<MultiSampleLevel>(value);
    }

    bool GLWindow::GetIsVSync() const { return SDL_GL_GetSwapInterval() == 1; }

    glm::ivec2 GLWindow::GetSize() const
    {
        glm::ivec2 size;
        SDL_GetWindowSize(m_window, &size.x, &size.y);
        return size;
    }

    int GLWindow::GetWidth() const
    {
        int width = 0;
        SDL_GetWindowSize(m_window, &width, nullptr);
        return width;
    }

    int GLWindow::GetHeight() const
    {
        int height = 0;
        SDL_GetWindowSize(m_window, nullptr, &height);
        return height;
    }

    std::string GLWindow::GetTitle() const { return SDL_GetWindowTitle(m_window); }

    void GLWindow::SwapBuffer() { SDL_GL_SwapWindow(m_window); }


} // namespace fts