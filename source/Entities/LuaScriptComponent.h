#pragma once
#include "lua/include/lua.hpp"
#include <stdlib.h>
#include <string>
#include "Component.h"
#include "Entity.h"

class LuaScriptComponent : public Component
{
    public:
    LuaScriptComponent(std::string scr, lua_State* L);
    ~LuaScriptComponent();
    void setScript(std::string script);
    void onUpdate();
    void onCreate();
    void onCollision(Entity* other);
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    Component* copy();
    std::string getScript();
    private:
    lua_State* lua_state;
    std::string scr;
    struct initialState
    {
        std::string initial_visibleName = "", initial_scr ="";
    };
    initialState* iniState;
};