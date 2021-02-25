#pragma once
#include "lua/include/lua.hpp"
#include "../General/Game.h"

static int game_get_current_level(lua_State* L);
static int game_find_sprite(lua_State* L);
static int game_add_level(lua_State* L);
static int game_set_current_level(lua_State* L);
static int game_get_delta_time(lua_State* L);
void game_script_init(lua_State* L);