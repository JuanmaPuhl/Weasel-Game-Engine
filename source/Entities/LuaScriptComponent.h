#pragma once
#include "lua/include/lua.hpp"
#include <stdlib.h>
#include <string>
#include "Component.h"

class LuaScriptComponent : public Component
{
    public:
    LuaScriptComponent(std::string scr);
    ~LuaScriptComponent();
    void onUpdate();
    void onCreate();
    Component* copy();
    std::string getScript();
    private:
    std::string scr;
};