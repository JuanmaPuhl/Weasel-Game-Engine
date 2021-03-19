#include "Lua_Sprite.h"

int sprite_get_current_image(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    lua_pushnumber(L,(*spr)->getCurrentSpriteIndex());
    return 1; 
}

int sprite_set_speed(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -2);
    float speed = luaL_checknumber(L, -1);
    printf("%d\n",speed);
    (*spr)->setSpeed(speed);
    return 1; 
}

int sprite_get_transparency(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    lua_pushnumber(L,(*spr)->getTransparency());
    return 1; 
}

int sprite_set_transparency(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -2);
    float transparency = luaL_checknumber(L, -1);
    (*spr)->setTransparency(transparency);
    return 1; 
}

int sprite_get_speed(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    lua_pushnumber(L,(*spr)->getSpeed());
    return 1; 
}

int sprite_get_name(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    lua_pushstring(L,(*spr)->getName().c_str());
    return 1; 
}

int sprite_restart(lua_State* L)
{
    int n = lua_gettop(L);
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    (*spr)->restart();
    return 1;
}

void sprite_script_init(lua_State* L)
{
    lua_pushcfunction(L, sprite_get_current_image);
    lua_setglobal(L, "sprite_get_current_image");
    lua_pushcfunction(L, sprite_set_speed);
    lua_setglobal(L, "sprite_set_speed");
    lua_pushcfunction(L, sprite_set_transparency);
    lua_setglobal(L, "sprite_set_transparency");
    lua_pushcfunction(L, sprite_get_transparency);
    lua_setglobal(L, "sprite_get_transparency");
    lua_pushcfunction(L, sprite_get_speed);
    lua_setglobal(L, "sprite_get_speed");
    lua_pushcfunction(L, sprite_get_name);
    lua_setglobal(L, "sprite_get_name");
    lua_pushcfunction(L, sprite_restart);
    lua_setglobal(L, "sprite_restart");
}
