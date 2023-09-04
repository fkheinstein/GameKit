#include <spch.h>




#include "LuaRender.h"


#include <lua.hpp>

#include "Application/IApplication.h"

#include "LuaBridge/LuaBridge.h"




namespace fts {

    void LuaRender::add(lua_State* state) 
    {
        luabridge::getGlobalNamespace(state)
            .beginNamespace("Render")
            .addFunction("viewport", &LuaRender::viewport)
            .endNamespace();
    }

    glm::vec2 LuaRender::viewport() {

        //auto& viewport = Application::GetApp().getRender().getViewport();
        //return glm::vec2(viewport.width, viewport.height);

        return glm::vec2(256);

    }

} // namespace fts