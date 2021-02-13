#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../Entities/Entity.h"

static int newEntity(lua_State* L);
static int position(lua_State* L);

void entity_script_init(lua_State *L)
{
    lua_pushcfunction(L, position);
    lua_setglobal(L, "position");
    lua_pushcfunction(L, newEntity);
    lua_setglobal(L, "newEntity");
}

// Show registration of class
/* static const luaL_Reg gEntityFuncs[] = {
  // Creation
  { "entity", luaopen_base},
  {"position", position},
  {NULL, NULL}
}; */


static int newEntity(lua_State *L)
{
  Entity* entity = (Entity*)lua_newuserdata(L, sizeof(Entity));  
  entity->setPosition(glm::vec3(10.0f,1.0f,0.0f));
    
  return 1;
}



static int position(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Entity* entity = (Entity*) lua_touserdata(L, -1);
    glm::vec3 position = entity->getPosition();
    printf("La posicion es: [%f,%f,%f]\n",position.x,position.y,position.z);
    return 1;
}