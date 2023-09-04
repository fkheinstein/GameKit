#ifndef __SCRIPTCONTEXT_H__
#define __SCRIPTCONTEXT_H__


#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"


namespace fts
{

    class ScriptContext {
    protected:
        lua_State* m_State = nullptr;

    public:
        ScriptContext() {}
        virtual ~ScriptContext() {}

        lua_State* getState() { return m_State; }
    };


} // namespace fts

#endif // __SCRIPTCONTEXT_H__