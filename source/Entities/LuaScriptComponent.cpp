#include "LuaScriptComponent.h"

    LuaScriptComponent::LuaScriptComponent(std::string scr)
    {
        this->scr = scr; //La dirección del script
        this->onCreate();
    }
    LuaScriptComponent::~LuaScriptComponent()
    {
        this->scr.clear();
    }
    void LuaScriptComponent::onUpdate()
    {
        if (luaL_dofile(lua_state, this->scr.c_str() ) != LUA_OK) {
            printf("ERROR: %s\n",lua_tostring(lua_state,-1));
        }
        else
        {
            printf("No paso nada.\n");
        }
        lua_getglobal(lua_state, "on_update");
        if(lua_isfunction(lua_state, -1))
            if(lua_pcall(lua_state, 0, 0, 0) != LUA_OK)
            {
            printf("A ver.\n");
            printf("error running function `f': %s",
                        lua_tostring(lua_state, -1));  
            }
  
    }
    void LuaScriptComponent::onCreate()
    {
        
    }
    Component* LuaScriptComponent::copy()
    {
        LuaScriptComponent* cs = new LuaScriptComponent(this->scr);
        return cs;
    }
    std::string LuaScriptComponent::getScript()
    {
        return this->scr;
    }