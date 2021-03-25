#pragma once
#include "lua/include/lua.hpp"
#include <glm/glm.hpp>
#include "../Entities/Entity.h"

/*
Gracias a DavePoo por sus tutoriales: https://www.youtube.com/channel/UCQcBTumGQK1Qqc7epDf19sQ
*/

/**
 * @brief Método intermediario entre LUA y C++ para la creación de entidades. Sin parámetros
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_new(lua_State *L);

/**
 * @brief Método intermediario entre LUA y C++ para la traslación de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_translate(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para la rotación de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_rotate(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para la escala de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_scale(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para agregar componente a una entidad. Parámetros: Entidad, componente.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_add_component(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para obtener un componente de una entidad. Parámetros: Entidad, índice.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_get_component(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para obtener un atributo de una entidad. Parámetros: Entidad, índice.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_get_attribute(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para agregar atributo a una entidad. Parámetros: Entidad, atributo.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_add_attribute(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para setear la posición de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_set_position(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para setear la rotación de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_set_rotation(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para setear la escala de entidades. Parámetros: Entidad, x, y, z.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_set_scale(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para obtener la posición de entidades. Parámetros: Entidad.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_get_position(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para obtener la rotación de entidades. Parámetros: Entidad.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_get_rotation(lua_State* L);

/**
 * @brief Método intermediario entre LUA y C++ para obtener la escala de entidades. Parámetros: Entidad.
 * 
 * @param L El estado de LUA
 * @return int 1
 */
static int entity_get_scale(lua_State* L);

/**
 * @brief Método para cargar todas las funciones a LUA. 
 * 
 * @param L Estado de LUA
 */
void entity_script_init(lua_State *L);

static int entity_get_name(lua_State* L);