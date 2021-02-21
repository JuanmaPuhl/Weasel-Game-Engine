#pragma once
#include "lua/include/lua.hpp"
#include <stdlib.h>
#include <string>
#include "Component.h"

class LuaScriptComponent : public Component
{
    public:
    LuaScriptComponent(std::string scr, lua_State* L);
    ~LuaScriptComponent();
    void onUpdate();
    void onCreate();
    Component* copy();
    std::string getScript();
    private:
    lua_State* lua_state;
    std::string scr;
};