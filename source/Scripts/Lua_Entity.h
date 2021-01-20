#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../Entities/Entity.h"
class Lua_Entity
{
    public:
        static int newEntity(lua_State* L); 
        static int scale(lua_State* L);
/*         static const luaL_Reg gSpriteFuncs[] = {
            {"new", newEntity}
        };

        void registerSprite(lua_State *L)
        {
            luaL_register(L, "Entity", gSpriteFuncs);  
            lua_pushvalue(L,-1);
            lua_setfield(L, -2, "__index");     
        }*/


};