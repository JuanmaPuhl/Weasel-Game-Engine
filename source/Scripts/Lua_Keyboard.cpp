#include "Lua_Keyboard.h"
#include "../Controls/KeyboardControl.h"
#include "../Config.h"

int is_pressed(lua_State* L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1", n);
    keyboard::Key key = (keyboard::Key)luaL_checknumber(L, -1); 
    lua_pushboolean(L, keyboardControl->isPressed(key));
    return 1;
}

void keyboard_script_init(lua_State* L)
{
    lua_pushnumber(L, keyboard::KEY_UP);
    lua_setglobal(L, "KEY_UP");
    lua_pushnumber(L, keyboard::KEY_DOWN);
    lua_setglobal(L, "KEY_DOWN");
    lua_pushnumber(L, keyboard::KEY_LEFT);
    lua_setglobal(L, "KEY_LEFT");
    lua_pushnumber(L, keyboard::KEY_RIGHT);
    lua_setglobal(L, "KEY_RIGHT");
    lua_pushnumber(L, keyboard::KEY_Q);
    lua_setglobal(L, "KEY_Q");
    lua_pushnumber(L, keyboard::KEY_W);
    lua_setglobal(L, "KEY_W");
    lua_pushnumber(L, keyboard::KEY_E);
    lua_setglobal(L, "KEY_E");
    lua_pushnumber(L, keyboard::KEY_R);
    lua_setglobal(L, "KEY_R");
    lua_pushnumber(L, keyboard::KEY_T);
    lua_setglobal(L, "KEY_T");
    lua_pushnumber(L, keyboard::KEY_U);
    lua_setglobal(L, "KEY_U");
    lua_pushnumber(L, keyboard::KEY_I);
    lua_setglobal(L, "KEY_I");
    lua_pushnumber(L, keyboard::KEY_O);
    lua_setglobal(L, "KEY_O");
    lua_pushnumber(L, keyboard::KEY_P);
    lua_setglobal(L, "KEY_P");
    lua_pushnumber(L, keyboard::KEY_A);
    lua_setglobal(L, "KEY_A");
    lua_pushnumber(L, keyboard::KEY_S);
    lua_setglobal(L, "KEY_S");
    lua_pushnumber(L, keyboard::KEY_D);
    lua_setglobal(L, "KEY_D");
    lua_pushnumber(L, keyboard::KEY_F);
    lua_setglobal(L, "KEY_F");
    lua_pushnumber(L, keyboard::KEY_G);
    lua_setglobal(L, "KEY_G");
    lua_pushnumber(L, keyboard::KEY_H);
    lua_setglobal(L, "KEY_H");
    lua_pushnumber(L, keyboard::KEY_J);
    lua_setglobal(L, "KEY_J");
    lua_pushnumber(L, keyboard::KEY_K);
    lua_setglobal(L, "KEY_K");
    lua_pushnumber(L, keyboard::KEY_L);
    lua_setglobal(L, "KEY_L");
    lua_pushnumber(L, keyboard::KEY_Z);
    lua_setglobal(L, "KEY_Z");
    lua_pushnumber(L, keyboard::KEY_X);
    lua_setglobal(L, "KEY_X");
    lua_pushnumber(L, keyboard::KEY_C);
    lua_setglobal(L, "KEY_C");
    lua_pushnumber(L, keyboard::KEY_V);
    lua_setglobal(L, "KEY_V");
    lua_pushnumber(L, keyboard::KEY_B);
    lua_setglobal(L, "KEY_B");
    lua_pushnumber(L, keyboard::KEY_N);
    lua_setglobal(L, "KEY_N");
    lua_pushnumber(L, keyboard::KEY_M);
    lua_setglobal(L, "KEY_M");

    lua_pushcfunction(L, is_pressed);
    lua_setglobal(L, "is_pressed");
}