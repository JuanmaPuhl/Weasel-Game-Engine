#pragma once
#include "lua/include/lua.hpp"

/*Por ahora tengo solo dos tipos de componentes, camara y script. La cámara es una entidad, por lo que para modificarla lo hago desde entity
Lo unico que tiene el componente es el metodo para pasar datos a la placa de video*/
void component_add_script(lua_State* L);
void component_enable_script(lua_State* L);
void component_script_init(lua_State* L);