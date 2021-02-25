#pragma once
#include "../Graphics/Sprite.h"
#include "lua/include/lua.hpp"

/* int getCurrentSprite(float deltaTime);
    int getCurrentSpriteIndex();
    void setSpeed(double speed);
    float getTransparency();
    void setTransparency(float transparency);
    double getSpeed();
    std::string getName(); */

int sprite_get_current_image(lua_State* L);
int sprite_set_speed(lua_State* L);
int sprite_get_transparency(lua_State* L);
int sprite_set_transparency(lua_State* L);
int sprite_get_speed(lua_State* L);
int sprite_get_name(lua_State* L);

void sprite_script_init(lua_State* L);
