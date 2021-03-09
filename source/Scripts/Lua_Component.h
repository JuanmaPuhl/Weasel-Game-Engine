#pragma once
#include "lua/include/lua.hpp"
#include "../Entities/ComponentCamera.h"
#include "../Entities/ComponentMusic.h"
#include <string>
#include <string.h>
#include <stdio.h>
/*SCRIPT*/
int component_add_script(lua_State* L);
int component_enable_script(lua_State* L);

/*CAMARA*/
int component_camera_get_zoom(lua_State* L);
int component_camera_set_zoom(lua_State* L);
int component_camera_get_position(lua_State* L);
//TODO: Creo que es mejor hacer un setPosition
int component_camera_move(lua_State* L);
int component_camera_get_direction(lua_State* L);
int component_camera_get_target(lua_State* L);
int component_camera_get_front(lua_State* L);
int component_camera_get_right(lua_State* L);
int component_camera_get_up(lua_State* L);
int component_camera_get_width(lua_State* L);
int component_camera_get_height(lua_State* L);
int component_camera_get_velocity(lua_State* L);

/*COLLIDER*/
int component_collider_set_x(lua_State* L);
int component_collider_set_y(lua_State* L);
int component_collider_set_width(lua_State* L);
int component_collider_set_height(lua_State* L);
int component_collider_get_x(lua_State* L);
int component_collider_get_y(lua_State* L);
int component_collider_get_height(lua_State* L);
int component_collider_get_width(lua_State* L);

/*PARTICLES*/
int component_particle_get_max_particles(lua_State* L);
int component_particle_get_new_particles(lua_State* L);
int component_particle_set_new_particles(lua_State* L);
int component_particle_set_max_particles(lua_State* L);

/*MUSIC*/
int component_music_set_track(lua_State* L);
int component_music_get_track(lua_State* L);
int component_music_play_track(lua_State* L);
int component_music_stop_track(lua_State* L);
int component_music_pause_track(lua_State* L);
int component_music_set_volume(lua_State* L);



void component_init(lua_State* L);