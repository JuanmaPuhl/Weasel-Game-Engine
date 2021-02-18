#include "Lua_Level.h"


static int level_add_entity(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Level** level = (Level**) lua_touserdata(L, -1);
    Entity** entity = (Entity**)lua_newuserdata(L, sizeof(Entity*));  
    *entity = (*level)->addEntity();
    return 1;
}
static int level_add_camera(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 3)
        return luaL_error(L, "Got %d arguments expected 3", n);
    Level** level = (Level**) lua_touserdata(L, -3);
    float width = luaL_checknumber(L,-2);
    float height = luaL_checknumber(L,-1);
    Entity** entity = (Entity**)lua_newuserdata(L, sizeof(Entity*));  
    *entity = (*level)->addEntityCamera(width,height);
    return 1;
}
static int level_remove_entity(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Level** level = (Level**) lua_touserdata(L, -2);
    int indice = luaL_checknumber(L,-1);
    bool result = (*level)->removeEntity(indice);
    lua_pushboolean(L,result);
    return 1;
}
static int level_get_entities(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Level** level = (Level**) lua_touserdata(L, -1);
    //Level* level = Game::getCurrentLevel();
    std::vector<Entity*> lista = (*level)->getEntities();
    std::vector<Entity*>::iterator ptr;
    lua_createtable(L, lista.capacity(), 0);
    printf("Capacidad: %d\n",lista.capacity());
    int newTable = lua_gettop(L);
    int indice = 1;
    for(ptr = lista.begin(); ptr < lista.end(); ptr++)
    {
        Entity** entity = (Entity**)lua_newuserdata(L, sizeof(Entity*));  
        *entity = *ptr;
        lua_rawseti(L, newTable, indice);
        indice++;
    }
    return 1;
}

static int level_get_camera(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Level** level = (Level**) lua_touserdata(L, -1);
    Entity** camera = (Entity**)lua_newuserdata(L, sizeof(Entity*));
    *camera = (*level)->getCamera();
    return 1;
}

void level_script_init(lua_State *L)
{
    lua_pushcfunction(L, level_add_entity);
    lua_setglobal(L, "level_add_entity");
    lua_pushcfunction(L, level_add_camera);
    lua_setglobal(L, "level_add_camera");
    lua_pushcfunction(L, level_get_camera);
    lua_setglobal(L, "level_get_camera");
    lua_pushcfunction(L, level_remove_entity);
    lua_setglobal(L, "level_remove_entity");
    lua_pushcfunction(L, level_get_entities);
    lua_setglobal(L, "level_get_entities");
}