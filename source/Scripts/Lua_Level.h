#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../General/Level.h"
#include "../General/Game.h"
#include "../Entities/Entity.h"

static int level_add_entity(lua_State *L);
static int level_add_camera(lua_State *L);
static int level_remove_entity(lua_State *L);
static int level_get_entities(lua_State *L);
static int level_get_camera(lua_State *L);
void level_script_init(lua_State *L);