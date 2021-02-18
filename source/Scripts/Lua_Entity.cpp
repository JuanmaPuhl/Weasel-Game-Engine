#include "Lua_Entity.h"
#include "../Entities/ComponentScript.h"
/*
Gracias a DavePoo por sus tutoriales: https://www.youtube.com/channel/UCQcBTumGQK1Qqc7epDf19sQ
*/

static int entity_new(lua_State *L)
{
    Entity** entity = (Entity**)lua_newuserdata(L, sizeof(Entity*));  
    *entity = new Entity();
    return 1;
}

static int entity_translate(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->translate(glm::vec3(x,y,z));
    return 1;
}

static int entity_rotate(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->rotate(glm::vec3(x,y,z));
    return 1;
}

static int entity_scale(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->scale(glm::vec3(x,y,z));
    return 1;
}

static int entity_add_component(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Entity** entity = (Entity**) lua_touserdata(L, -2);
    Component** component = (Component**) lua_touserdata(L, -1);
    (*entity)->addComponent(*component);
    return 1;
}

static int entity_get_component(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Entity** entity = (Entity**) lua_touserdata(L, -2);
    int indice = luaL_checkinteger(L,-1);
    Component** component = (Component**)lua_newuserdata(L, sizeof(Component*));  
    *component = (*entity)->getComponent(indice);
    return 1;
}

static int entity_get_attribute(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Entity** entity = (Entity**) lua_touserdata(L, -2);
    int indice = luaL_checknumber(L,-1);
    GraphicAttribute** attribute = (GraphicAttribute**)lua_newuserdata(L, sizeof(GraphicAttribute*));  
    *attribute = (*entity)->getAttribute(indice);   
    return 1;
}

static int entity_add_attribute(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    Entity** entity = (Entity**) lua_touserdata(L, -2);
    GraphicAttribute** attribute = (GraphicAttribute**) lua_touserdata(L, -1);
    (*entity)->addAttribute(*attribute);
    return 1;
}

static int entity_set_position(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->setPosition(glm::vec3(x,y,z));
    return 1;
}

static int entity_set_rotation(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->setRotation(glm::vec3(x,y,z));
    return 1;
}

static int entity_set_scale(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 4)
        return luaL_error(L, "Got %d arguments expected 4", n);
    Entity** entity = (Entity**) lua_touserdata(L, -4);
    float x = luaL_checknumber(L,-3);
    float y = luaL_checknumber(L,-2);
    float z = luaL_checknumber(L,-1);
    (*entity)->setScale(glm::vec3(x,y,z));
    return 1;
}

static int entity_get_position(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Entity** entity = (Entity**) lua_touserdata(L, -1);
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

static int entity_get_rotation(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Entity** entity = (Entity**) lua_touserdata(L, -1);
    glm::vec3 rotation = (*entity)->getRotation();
    //Paso la tabla con las coordenadas
    lua_createtable(L, 3, 0);
    int newTable = lua_gettop(L);
    lua_pushnumber(L, rotation.x);
    lua_rawseti(L, newTable, 1);
    lua_pushnumber(L, rotation.y);
    lua_rawseti(L, newTable, 2);
    lua_pushnumber(L, rotation.z);
    lua_rawseti(L, newTable, 3);
    return 1;
}

static int entity_get_scale(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    Entity** entity = (Entity**) lua_touserdata(L, -1);
    glm::vec3 scale = (*entity)->getScale();
    //Paso la tabla con las coordenadas
    lua_createtable(L, 3, 0);
    int newTable = lua_gettop(L);
    lua_pushnumber(L, scale.x);
    lua_rawseti(L, newTable, 1);
    lua_pushnumber(L, scale.y);
    lua_rawseti(L, newTable, 2);
    lua_pushnumber(L, scale.z);
    lua_rawseti(L, newTable, 3);
    return 1;
}

void entity_script_init(lua_State *L)
{
    lua_pushcfunction(L, entity_new);
    lua_setglobal(L, "entity_new");
    lua_pushcfunction(L, entity_translate);
    lua_setglobal(L, "entity_translate");
    lua_pushcfunction(L, entity_rotate);
    lua_setglobal(L, "entity_rotate");
    lua_pushcfunction(L, entity_scale);
    lua_setglobal(L, "entity_scale");
    lua_pushcfunction(L, entity_add_component);
    lua_setglobal(L, "entity_add_component");
    lua_pushcfunction(L, entity_get_component);
    lua_setglobal(L, "entity_get_component");
    lua_pushcfunction(L, entity_add_attribute);
    lua_setglobal(L, "entity_add_attribute");
    lua_pushcfunction(L, entity_get_attribute);
    lua_setglobal(L, "entity_get_attribute");
    lua_pushcfunction(L, entity_set_position);
    lua_setglobal(L, "entity_set_position");
    lua_pushcfunction(L, entity_set_rotation);
    lua_setglobal(L, "entity_set_rotation");
    lua_pushcfunction(L, entity_set_scale);
    lua_setglobal(L, "entity_set_scale");
    lua_pushcfunction(L, entity_get_position);
    lua_setglobal(L, "entity_get_position");
    lua_pushcfunction(L, entity_get_rotation);
    lua_setglobal(L, "entity_get_rotation");
    lua_pushcfunction(L, entity_get_scale);
    lua_setglobal(L, "entity_get_scale");
}