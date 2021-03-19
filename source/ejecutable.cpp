#include "Graphics/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Entities/Entity.h"
#include "Graphics/Sprite.h"
#include "Entities/ScriptComponent.h"
#include "General/Game.h"
#include "General/Level.h"
#include "Config.h"
#include "Entities/Scripts.h"
#include "Entities/Component.h"
#include "Entities/ComponentScript.h"
#include "Entities/GraphicAttribute.h"
#include "Entities/SpriteAttribute.h"
#include "Entities/ColorAttribute.h"
#include "Graphics/Gui.h"
#include "Scripts/Lua_Entity.h"
#include "Scripts/Lua_Level.h"
#include "Scripts/Lua_Sprite.h"
#include "Scripts/Lua_Game.h"
#include "Scripts/Lua_Keyboard.h"
#include "Scripts/Lua_Attribute.h"
#include "Entities/LuaScriptComponent.h"
#include "Scripts/Lua_Component.h"
#include "Entities/ComponentCollisionBox.h"
#include "Entities/ComponentParticle.h"
#include "Windows.h"
#include "FileManagement/FileManager.h"
#include "Entities/ComponentMusic.h"
#include "Entities/PixelizationAttribute.h"
#include "Entities/Sharpen.h"
#include "nlohmann/json.hpp"
#define DEBUG
extern "C" {
  #include "lua/include/lua.h"
  #include "lua/include/lualib.h"
  #include "lua/include/lauxlib.h"
  
}
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 10;

int metodoPrincipal()
{
  irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();
  lua_State *lua_state;
  lua_state = luaL_newstate();
    // load Lua libraries
  static const luaL_Reg lualibs[] =
  {
      { "base", luaopen_base },
      { NULL, NULL}
  };

  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
  {
      lib->func(lua_state);
      lua_settop(lua_state, 0);
  }
  entity_script_init(lua_state);
  level_script_init(lua_state);
  game_script_init(lua_state);
  attribute_script_init(lua_state);
  keyboard_script_init(lua_state);
  sprite_script_init(lua_state);
  component_init(lua_state);
  Game::init(WIDTH,HEIGHT,true);
  Game::setLuaState(lua_state);
  GLFWimage icons[1];
  const char* dirIcon = "res/sprites/undefined.png";
  icons[0].pixels = stbi_load(dirIcon, &icons[0].width, &icons[0].height, 0, 0);
  glfwSetWindowIcon(Game::getWindow(), 1, icons);
  stbi_image_free(icons[0].pixels);
  const char* img[1] = {"res/sprites/undefined.png"};
  Sprite* sprUndefined = new Sprite(img,1,"undefined");
  Game::addSystemSprite(sprUndefined);
  //Tengo que setear en Game que no cargue GUI
  Game::exportedGame(true);
  //Tengo que cargar el juego
  Game::loadProject("savedproject.wsl");
  Game::playGame();
  Game::loop();
  Game::close();  
  lua_close(lua_state);
  return 0;
}


int main(int argc, char** argv)
{
  int toReturn = metodoPrincipal();
  switch(toReturn)
  {
    case 0:
      printf("Main::Ejecucion exitosa.\n");
      break;
    default:
      printf("Main::ERROR. Codigo: %d.\n",toReturn);
  }
  return 0;
}