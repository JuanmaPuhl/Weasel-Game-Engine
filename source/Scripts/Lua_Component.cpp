#include "Lua_Component.h"

/*SCRIPT*/
int component_add_script(lua_State* L)
{

}

int component_enable_script(lua_State* L)
{

}

/*CAMARA*/
int component_camera_get_zoom(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ComponentCamera** cc = (ComponentCamera**) lua_touserdata(L, -1);
    if(cc != NULL && !strcmp((*cc)->getName().c_str(),"camera"))
        lua_pushnumber(L, (*cc)->getZoom());
    else
        lua_pushnumber(L, 0);
    
    return 1;
}

int component_camera_set_zoom(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    ComponentCamera** cc = (ComponentCamera**) lua_touserdata(L, -2);
    float zoom = luaL_checknumber(L, -1);
    if(cc != NULL && !strcmp((*cc)->getName().c_str(),"camera"))
        (*cc)->zoom(zoom);
    return 1;
}

int component_camera_get_position(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ComponentCamera** entity = (ComponentCamera**) lua_touserdata(L, -1);
    glm::vec3 position = (*entity)->getPosition();
    //Paso la tabla con las coordenadas
    lua_createtable(L, 3, 0);
    int newTable = lua_gettop(L);
    lua_pushnumber(L, position.x);
    lua_rawseti(L, newTable, 1);
    lua_pushnumber(L, position.y);
    lua_rawseti(L, newTable, 2);
    lua_pushnumber(L, position.z);
    lua_rawseti(L, newTable, 3);
    return 1;
}

//TODO: Creo que es mejor hacer un setPosition
int component_camera_move(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    ComponentCamera** camera = (ComponentCamera**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*camera)->setPosition(glm::vec3(x,y,z));
}

int component_camera_get_direction(lua_State* L)
{

}

int component_camera_get_target(lua_State* L)
{

}

int component_camera_get_front(lua_State* L)
{

}

int component_camera_get_right(lua_State* L)
{

}

int component_camera_get_up(lua_State* L)
{

}

int component_camera_get_width(lua_State* L)
{

}

int component_camera_get_height(lua_State* L)
{

}

int component_camera_get_velocity(lua_State* L)
{

}

/*COLLIDER*/
int component_collider_set_x(lua_State* L)
{

}

int component_collider_set_y(lua_State* L)
{

}

int component_collider_set_width(lua_State* L)
{

}

int component_collider_set_height(lua_State* L)
{

}

int component_collider_get_x(lua_State* L)
{

}

int component_collider_get_y(lua_State* L)
{

}

int component_collider_get_height(lua_State* L)
{

}

int component_collider_get_width(lua_State* L)
{

}

/*PARTICLES*/
int component_particle_get_max_particles(lua_State* L)
{

}

int component_particle_get_new_particles(lua_State* L)
{

}

int component_particle_set_new_particles(lua_State* L)
{

}

int component_particle_set_max_particles(lua_State* L)
{

}

int component_music_set_track(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -2);
    std::string music_dir = lua_tostring(L,-1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        (*cc)->setMusic(music_dir);
}

int component_music_get_track(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        lua_pushstring(L, (*cc)->getMusic().c_str());
}

int component_music_play_track(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -2);
    bool loop = lua_toboolean(L,-1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        (*cc)->playMusic(loop);
}

int component_music_stop_track(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        (*cc)->stopMusic();
}

int component_music_pause_track(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        (*cc)->pauseMusic();
}

int component_music_set_volume(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    ComponentMusic** cc = (ComponentMusic**) lua_touserdata(L, -2);
    float volume = luaL_checknumber(L, -1);
    if(cc != NULL && (*cc) != NULL && !strcmp((*cc)->getName().c_str(),"music"))
        (*cc)->setVolume(volume);
}

void component_init(lua_State* L)
{
    lua_pushcfunction(L, component_camera_get_zoom);
    lua_setglobal(L, "component_camera_get_zoom");
    lua_pushcfunction(L, component_camera_set_zoom);
    lua_setglobal(L, "component_camera_set_zoom");
    lua_pushcfunction(L, component_camera_get_position);
    lua_setglobal(L, "component_camera_get_position");
    lua_pushcfunction(L, component_camera_move);
    lua_setglobal(L, "component_camera_move");
    lua_pushcfunction(L, component_camera_get_direction);
    lua_setglobal(L, "component_camera_get_direction");
    lua_pushcfunction(L, component_camera_get_target);
    lua_setglobal(L, "component_camera_get_target");
    lua_pushcfunction(L, component_camera_get_front);
    lua_setglobal(L, "component_camera_get_front");
    lua_pushcfunction(L, component_camera_get_right);
    lua_setglobal(L, "component_camera_get_right");
    lua_pushcfunction(L, component_camera_get_up);
    lua_setglobal(L, "component_camera_get_up");
    lua_pushcfunction(L, component_camera_get_width);
    lua_setglobal(L, "component_camera_get_width");
    lua_pushcfunction(L, component_camera_get_height);
    lua_setglobal(L, "component_camera_get_height");
    lua_pushcfunction(L, component_camera_get_velocity);
    lua_setglobal(L, "component_camera_get_velocity");

    lua_pushcfunction(L, component_collider_set_x);
    lua_setglobal(L, "component_collider_set_x");
    lua_pushcfunction(L, component_collider_set_y);
    lua_setglobal(L, "component_collider_set_y");
    lua_pushcfunction(L, component_collider_set_width);
    lua_setglobal(L, "component_collider_set_width");
    lua_pushcfunction(L, component_collider_set_height);
    lua_setglobal(L, "component_collider_set_height");
    lua_pushcfunction(L, component_collider_get_x);
    lua_setglobal(L, "component_collider_get_x");
    lua_pushcfunction(L, component_collider_get_y);
    lua_setglobal(L, "component_collider_get_y");
    lua_pushcfunction(L, component_collider_get_height);
    lua_setglobal(L, "component_collider_get_height");
    lua_pushcfunction(L, component_collider_get_width);
    lua_setglobal(L, "component_collider_get_width");

    lua_pushcfunction(L, component_particle_get_max_particles);
    lua_setglobal(L, "component_particle_get_max_particles");
    lua_pushcfunction(L, component_particle_get_new_particles);
    lua_setglobal(L, "component_particle_get_new_particles");
    lua_pushcfunction(L, component_particle_set_new_particles);
    lua_setglobal(L, "component_particle_set_new_particles");
    lua_pushcfunction(L, component_particle_set_max_particles);
    lua_setglobal(L, "component_particle_set_max_particles");

    lua_pushcfunction(L, component_music_set_track);
    lua_setglobal(L, "component_music_set_track");
    lua_pushcfunction(L, component_music_get_track);
    lua_setglobal(L, "component_music_get_track");
    lua_pushcfunction(L, component_music_play_track);
    lua_setglobal(L, "component_music_play_track");
    lua_pushcfunction(L, component_music_stop_track);
    lua_setglobal(L, "component_music_stop_track");
    lua_pushcfunction(L, component_music_pause_track);
    lua_setglobal(L, "component_music_pause_track");
    lua_pushcfunction(L, component_music_set_volume);
    lua_setglobal(L, "component_music_set_volume");
}