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
#include "Windows.h"
#define DEBUG
extern "C" {
  #include "lua/include/lua.h"
  #include "lua/include/lualib.h"
  #include "lua/include/lauxlib.h"
  
}
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 10;


//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

void executeLuaScript()
{
  // create new Lua state
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
  //init_level(lua_state);
  level_script_init(lua_state);
  // run the Lua script
  if (luaL_dofile(lua_state, "script.lua") != LUA_OK) {
    printf("ERROR: %s\n",lua_tostring(lua_state,-1));
  }
  else
  {
    printf("No paso nada.\n");
  }
  lua_getglobal(lua_state, "on_update");
  if(lua_isfunction(lua_state, -1))
    if(lua_pcall(lua_state, 0, 0, 0) != LUA_OK)
    {
      printf("A ver.\n");
      printf("error running function `f': %s",
                 lua_tostring(lua_state, -1));  
    }
  // close the Lua state
  lua_close(lua_state);
}

int metodoPrincipal()
{
  printf("%s\n",GetLastErrorAsString().c_str());

  

  printf("Main::Creando ventana...\n");
  Game::init(WIDTH,HEIGHT);
  GLFWimage icons[1];
  const char* dirIcon = "res/sprites/undefined.png";
  icons[0].pixels = stbi_load(dirIcon, &icons[0].width, &icons[0].height, 0, 0);
  glfwSetWindowIcon(Game::getWindow(), 1, icons);
  stbi_image_free(icons[0].pixels);

  Level* level1 = Game::addLevel();
  Entity* cameraEntity = level1->addEntityCamera(WIDTH,HEIGHT);
  ComponentCamera* cmpCamera = (ComponentCamera*)cameraEntity->getComponent(0);
  cmpCamera->zoom(0.35f);
  cmpCamera->move(glm::vec3(-2610.0f,-185.5f,0.0f));
  //Creo el personaje
  ScriptComponent* scrCamera = new CameraController();
  ((CameraController*)(scrCamera))->camera = cameraEntity;
  const char* img[1] = {"res/sprites/undefined.png"};
  Sprite* sprUndefined = new Sprite(img,1,"undefined");
  Game::addSystemSprite(sprUndefined);
  //cameraEntity->addComponent(new ComponentScript(scrCamera));
  Entity* personaje = level1->addEntity();
  const char* arr[6] = {"res/sprites/e1.png","res/sprites/e2.png","res/sprites/e3.png","res/sprites/e4.png","res/sprites/e5.png","res/sprites/e6.png"};
  Sprite* sprIdle = new Sprite(arr,6,"idle");
  Game::addSprite(sprIdle);
  sprIdle->setSpeed(0.16*60);
  GraphicAttribute* attrColor1 = new SpriteAttribute(sprIdle);
  personaje->addAttribute(attrColor1);
  Game::setLevel(0);
  Gui::writeToLog("Holiwi\n");
  const char* walkingAnimation[9] = {"res/sprites/ew1.png","res/sprites/ew2.png","res/sprites/ew3.png","res/sprites/ew4.png","res/sprites/ew5.png","res/sprites/ew6.png","res/sprites/ew7.png","res/sprites/ew8.png","res/sprites/ew9.png"};
  Sprite* walkingSpr = new Sprite(walkingAnimation,9,"walking");
  Game::addSprite(walkingSpr);
  const char* shootingAnimation[2] = {"res/sprites/es1.png","res/sprites/es2.png"};
  Sprite* shootingSpr = new Sprite(shootingAnimation,2,"shooting");
  Game::addSprite(shootingSpr);
  shootingSpr->setSpeed(0.5*60.0);
  const char* fireAnimation[3] = {"res/sprites/f1.png","res/sprites/f2.png","res/sprites/f3.png"};
  Sprite* fireSpr = new Sprite(fireAnimation,3,"fire");
  Game::addSprite(fireSpr);
  fireSpr->setSpeed(0.3*60.0);
  walkingSpr->setSpeed(0.2*60.0);
  Entity* fireEntity = level1->addEntity();
  personaje->scale(glm::vec3(1.4f,1.8f,1.0f));
  personaje->setPosition(glm::vec3(-2755.0f,-210.0f,0.0f));
  fireEntity->setPosition(glm::vec3(-2755.0f,-210.0f,0.0f));
  GraphicAttribute* fireAttr = new SpriteAttribute(fireSpr);
  fireEntity->addAttribute(fireAttr);
  //Creo el piso
  GraphicAttribute* attrColor = new ColorAttribute(glm::vec3(0.5f,0.1f,0.2f));

  //Creo el fondo
  const char* bg[1] = {"res/sprites/background.png"};
  Entity* entityBg = level1->addEntity();
  Sprite* fondo = new Sprite(bg,1,"fondo");
  Game::addSprite(fondo);
  GraphicAttribute* attrFondo = new SpriteAttribute(fondo);

  entityBg->addAttribute(attrFondo);
  entityBg->scale(glm::vec3(173.625f,86.98f,1.0f));
  entityBg->translate(glm::vec3(-56.0f,0.0f,-0.1f));

  const char* bgLevel[1] = {"res/sprites/level-bg.png"};
  Entity* entityLevelBg = level1->addEntity();
  Sprite* fondo2 = new Sprite(bgLevel,1,"fondo2");
  Game::addSprite(fondo2);
  GraphicAttribute* attrFondoLevel = new SpriteAttribute(fondo2);
  entityLevelBg->addAttribute(attrFondoLevel);
  entityLevelBg->scale(glm::vec3(173.625f,26.75f,1.0f));
  entityLevelBg->translate(glm::vec3(-56.0f,0.0f,-0.01f));

  //Creo el pajaro
  const char* birdSprite[5] = {"res/sprites/c1.png","res/sprites/c2.png","res/sprites/c3.png","res/sprites/c4.png","res/sprites/c5.png"};
  Entity* bird = level1->addEntity();
  Sprite* sprBird = new Sprite(birdSprite,5,"bird");
  sprBird->setSpeed(0.2*60);
  GraphicAttribute* attrBird = new SpriteAttribute(sprBird);
  bird->addAttribute(attrBird);
  bird->scale(glm::vec3(-1.0f,0.6f,0.0f));
  bird->setPosition(glm::vec3(-2460.0f,-80.0f,0.0f));
  BirdMovement* birdScr = new BirdMovement();
  birdScr->bird = bird;
  ComponentScript* birdScrComponent = new ComponentScript(birdScr);
  bird->addComponent(birdScrComponent); 
  PlayerMovement* scr = new PlayerMovement();
  scr->player = personaje;
  scr->fire = fireEntity;
  Component* scriptComponent = new ComponentScript(scr);
  personaje->addComponent(scriptComponent);



  executeLuaScript();


  Game::loop();
  printf("Main::Eliminando objetos...\n");
  Game::close();  

  delete(level1);
  delete(attrColor);
  printf("Main::Objetos eliminados. Cerrando programa.\n");
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