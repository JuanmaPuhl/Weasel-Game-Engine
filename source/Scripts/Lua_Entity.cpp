#include "Lua_Entity.h"

Entity* checkEntity(lua_State* L, int index)
{
  void* ud = 0;
  luaL_checktype(L, index, LUA_TTABLE);
  lua_getfield(L, index, "__self");
  ud = luaL_checkudata(L, index, "Lusion.Entity");
  //luaL_argcheck(L, ud != 0, "`Lusion.Entity' expected");  
  
  return *((Entity**)ud);      
}

int Lua_Entity::newEntity(lua_State* L)
{
    printf("Creating new Entity.\n");
}

int Lua_Entity::scale(lua_State* L)
{
    printf("Hello, im scaling");
    int n = lua_gettop(L);  // Number of arguments
  
    if (n == 4) {

        Entity* entity = checkEntity(L,1);
        assert(entity != 0);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L,3);
        entity->setScale(glm::vec3(x,y,1));
    }
    else
        luaL_error(L, "Got %d arguments expected 4 (self, x,y,z)", n);
    
    return 0;
}