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
    if(cc != NULL && strcmp((*cc)->getName().c_str(),"camera"))
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
    if(cc != NULL && strcmp((*cc)->getName().c_str(),"camera"))
        (*cc)->zoom(zoom);
    return 1;
}

int component_camera_get_position(lua_State* L)
{
    
}

//TODO: Creo que es mejor hacer un setPosition
int component_camera_move(lua_State* L)
{

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
}