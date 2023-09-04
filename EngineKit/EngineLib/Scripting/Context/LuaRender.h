#ifndef __LUARENDER_H__
#define __LUARENDER_H__

#pragma once

#include <glm/vec2.hpp>




struct  lua_State;
namespace fts {


    class LuaRender {
    public:
        static glm::vec2 viewport();

        void static add(lua_State* state);
    };

} // namespace fts

#endif // __LUARENDER_H__