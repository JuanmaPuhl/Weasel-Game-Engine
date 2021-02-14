#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../Entities/Entity.h"

/*
Gracias a DavePoo por sus tutoriales: https://www.youtube.com/channel/UCQcBTumGQK1Qqc7epDf19sQ
*/



static int entity_new(lua_State *L)
{
  Entity* entity = (Entity*)lua_newuserdata(L, sizeof(Entity));  
  entity->setPosition(glm::vec3(10.0f,1.0f,0.0f));
    
  return 1;
}



static int entity_translate(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity* entity = (Entity*) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    printf("[%f,%f,%f]\n",x,y,z);
    entity->translate(glm::vec3(x,y,z));
    return 1;
}

static int entity_rotate(lua_State* L)
{
    return 1;
}

static int entity_scale(lua_State* L)
{
return 1;
}

static int entity_add_component(lua_State* L)
{
return 1;
}

static int entity_get_component(lua_State* L)
{
return 1;
}

static int entity_get_attribute(lua_State* L)
{
return 1;
}

static int entity_add_attribute(lua_State* L)
{
return 1;
}

static int entity_set_position(lua_State* L)
{
return 1;
}

static int entity_set_rotation(lua_State* L)
{
return 1;
}

static int entity_set_scale(lua_State* L)
{
return 1;
}

static int entity_get_position(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Entity* entity = (Entity*) lua_touserdata(L, -1);
    glm::vec3 position = entity->getPosition();
    printf("La posicion es: [%f,%f,%f]\n",position.x,position.y,position.z);
    return 1;
}

static int entity_get_rotation(lua_State* L)
{
return 1;
}

static int entity_get_scale(lua_State* L)
{
return 1;
}

void entity_script_init(lua_State *L)
{
    lua_pushcfunction(L, entity_new);
    lua_setglobal(L, "entity_new");
    lua_pushcfunction(L, entity_translate);
    lua_setglobal(L, "entity_translate");
    lua_pushcfunction(L, entity_rotate);
    lua_setglobal(L, "entity_rotate");
    lua_pushcfunction(L, entity_scale);
    lua_setglobal(L, "entity_scale");
    lua_pushcfunction(L, entity_add_component);
    lua_setglobal(L, "entity_add_component");
    lua_pushcfunction(L, entity_get_component);
    lua_setglobal(L, "entity_get_component");
    lua_pushcfunction(L, entity_add_attribute);
    lua_setglobal(L, "entity_add_attribute");
    lua_pushcfunction(L, entity_get_attribute);
    lua_setglobal(L, "entity_get_attribute");
    lua_pushcfunction(L, entity_set_position);
    lua_setglobal(L, "entity_set_position");
    lua_pushcfunction(L, entity_set_rotation);
    lua_setglobal(L, "entity_set_rotation");
    lua_pushcfunction(L, entity_set_scale);
    lua_setglobal(L, "entity_set_scale");
    lua_pushcfunction(L, entity_get_position);
    lua_setglobal(L, "entity_get_position");
    lua_pushcfunction(L, entity_get_rotation);
    lua_setglobal(L, "entity_get_rotation");
    lua_pushcfunction(L, entity_get_scale);
    lua_setglobal(L, "entity_get_scale");
}