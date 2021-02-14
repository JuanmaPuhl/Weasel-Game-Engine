#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../Entities/Entity.h"

/*
Gracias a DavePoo por sus tutoriales: https://www.youtube.com/channel/UCQcBTumGQK1Qqc7epDf19sQ
*/

static int entity_new(lua_State *L);

static int entity_translate(lua_State* L);

static int entity_rotate(lua_State* L);

static int entity_scale(lua_State* L);

static int entity_add_component(lua_State* L);

static int entity_get_component(lua_State* L);

static int entity_get_attribute(lua_State* L);

static int entity_add_attribute(lua_State* L);

static int entity_set_position(lua_State* L);

static int entity_set_rotation(lua_State* L);

static int entity_set_scale(lua_State* L);

static int entity_get_position(lua_State* L);

static int entity_get_rotation(lua_State* L);

static int entity_get_scale(lua_State* L);

void entity_script_init(lua_State *L);