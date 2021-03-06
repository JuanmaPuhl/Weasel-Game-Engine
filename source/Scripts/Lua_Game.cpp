#include "Lua_Game.h"

static int game_get_current_level(lua_State* L)
{
    Level** level = (Level**)lua_newuserdata(L, sizeof(Level*));  
    *level = Game::getCurrentLevel();
    return 1;
}

static int game_find_sprite(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    const char* sprite_name = lua_tostring(L, -1);
    Sprite** sprite = (Sprite**)lua_newuserdata(L, sizeof(Sprite*));
    Sprite* s = Game::findSpriteByName(sprite_name);
    *sprite =s->copy(s);
    return 1;
}

static int game_add_level(lua_State* L)
{
    Level** level = (Level**)lua_newuserdata(L, sizeof(Level*));  
    *level = Game::addLevel();
    return 1;
}
static int game_set_current_level(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    int i = luaL_checkinteger(L, -1);
    Game::setLevel(i);
    return 1;
}
static int game_get_delta_time(lua_State* L)
{
    lua_pushnumber(L,(float)Game::getDeltaTime());
    return 1;
}

static int log_print(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    std::string str = lua_tostring(L, -1);
    Gui::writeToLog(str.c_str());
    return 1;
}

void game_script_init(lua_State* L)
{
    lua_pushcfunction(L, game_get_current_level);
    lua_setglobal(L, "game_get_current_level");
    lua_pushcfunction(L, game_find_sprite);
    lua_setglobal(L, "game_find_sprite");
    lua_pushcfunction(L, game_set_current_level);
    lua_setglobal(L, "game_set_current_level");
    lua_pushcfunction(L, game_add_level);
    lua_setglobal(L, "game_add_level");
    lua_pushcfunction(L, game_get_delta_time);
    lua_setglobal(L, "game_get_delta_time");
    lua_pushcfunction(L, log_print);
    lua_setglobal(L, "log_print");
}