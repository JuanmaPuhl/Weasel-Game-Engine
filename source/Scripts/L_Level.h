#pragma once
#include "../General/Level.h"
#include "../General/Game.h"
#include "lua/include/lua.hpp"
static int addEntityLevel(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);

    Level* level = (Level*) lua_touserdata(L, -1);
    Entity* entity2 = level->addEntity();
    /* Entity* entity = (Entity*)lua_newuserdata(L, sizeof(Entity));
     */
   

    return 1;
}



int getLevel(lua_State* L)
{
    Level* li = Game::getCurrentLevel();
    (li)->addEntity();
    int i = li->getEntities().capacity();
    printf("La cantidad de entidades es: %d\n",i);

    //printf("La cantidad de entidades es: %d\n",i);
    return 1;
}

static int getCantEntities(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);

    Level* level = (Level*) lua_touserdata(L, -1);
    int i = level->getEntities().capacity();
    printf("La cantidad de entidades es: %d\n",i);
    return 1;
}

void init_level(lua_State* L)
{
    printf("Llmamando");
    lua_pushcfunction(L, addEntityLevel);
    lua_setglobal(L, "addEntityLevel");
    lua_pushcfunction(L, getLevel);
    lua_setglobal(L, "getLevel");
    lua_pushcfunction(L, getCantEntities);
    lua_setglobal(L, "printCantEntities");
    printf("Llmamando");
}