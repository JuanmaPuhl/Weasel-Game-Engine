#include "Lua_Attribute.h"
#include "../Graphics/Gui.h"
int attribute_set_sprite(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 2)
        return luaL_error(L, "Got %d arguments expected 2", n);
    SpriteAttribute** sprAttr = (SpriteAttribute**) lua_touserdata(L, -2);
    Sprite** spr = (Sprite**) lua_touserdata(L, -1);
    if(*sprAttr != NULL && *spr != NULL)
        (*sprAttr)->setSprite((*spr));
    else
        printf("LUA_ERROR::attribute_set_sprite. NULL PARAMETER.\n");
    return 1;
}

int attribute_get_sprite(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    SpriteAttribute** sprAttr = (SpriteAttribute**) lua_touserdata(L, -1); 
    Sprite** sprite = (Sprite**)lua_newuserdata(L, sizeof(Sprite*));  
    if(*sprAttr != NULL)
        *sprite = (*sprAttr)->getSprite();
    else
        printf("LUA_ERROR::attribute_get_sprite. NULL PARAMETER.\n");
    return 1;
}


int attribute_set_color(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 5)
        return luaL_error(L, "Got %d arguments expected 5", n);
    ColorAttribute** colAttr = (ColorAttribute**) lua_touserdata(L, -5);
    float r = luaL_checknumber(L, -4);
    float g = luaL_checknumber(L, -3);
    float b = luaL_checknumber(L, -2);
    float a = luaL_checknumber(L, -1);
    if(*colAttr != NULL)
        (*colAttr)->setColor(glm::vec4(r,g,b,a));
    else
        printf("LUA_ERROR::attribute_set_color. NULL PARAMETER.\n");
    return 1;
}

int attribute_get_color(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    ColorAttribute** colAttr = (ColorAttribute**) lua_touserdata(L, -1); 
    if(*colAttr != NULL)
    {
        glm::vec4 color = (*colAttr)->getColor();
        //Paso la tabla con las coordenadas
        lua_createtable(L, 4, 0);
        int newTable = lua_gettop(L);
        lua_pushnumber(L, color.x);
        lua_rawseti(L, newTable, 1);
        lua_pushnumber(L, color.y);
        lua_rawseti(L, newTable, 2);
        lua_pushnumber(L, color.z);
        lua_rawseti(L, newTable, 3);
        lua_pushnumber(L, color.a);
        lua_rawseti(L, newTable, 4);
    }
    else
        printf("LUA_ERROR::attribute_get_color. NULL PARAMETER.\n");
    return 1;
}


void attribute_script_init(lua_State* L)
{
    lua_pushcfunction(L, attribute_set_sprite);
    lua_setglobal(L, "attribute_set_sprite");
    lua_pushcfunction(L, attribute_get_sprite);
    lua_setglobal(L, "attribute_get_sprite");
    lua_pushcfunction(L, attribute_set_color);
    lua_setglobal(L, "attribute_set_color");
    lua_pushcfunction(L, attribute_get_color);
    lua_setglobal(L, "attribute_get_color");
}
