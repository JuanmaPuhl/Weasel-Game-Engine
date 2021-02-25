#pragma once
#include "lua/include/lua.hpp"
#include "../Entities/SpriteAttribute.h"
#include "../Entities/ColorAttribute.h"

int attribute_set_sprite(lua_State* L);
int attribute_get_sprite(lua_State* L);

int attribute_set_color(lua_State* L);
int attribute_get_color(lua_State* L);

void attribute_script_init(lua_State* L);