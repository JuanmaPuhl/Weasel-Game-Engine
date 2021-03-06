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

void executeLuaScript(lua_State* lua_state)
{
  


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
  
}

int metodoPrincipal()
{

  nlohmann::json json = nlohmann::json::parse("{ \"happy\": true, \"pi\": 3.141 }");
  std::string toPrint = to_string(json["happy"]);
  printf("El json es: %s\n",toPrint.c_str());
  printf("%s\n",GetLastErrorAsString().c_str());
  // create new Lua state

  irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();
  //SoundEngine->play2D("res/audio/breakout.mp3", true);
  printf("MAIN::Creando nuevo estado de LUA...\n");
  lua_State *lua_state;
  lua_state = luaL_newstate();
    // load Lua libraries
  static const luaL_Reg lualibs[] =
  {
      { "base", luaopen_base },
      { "math", luaopen_math},
      { NULL, NULL}
  };
  luaL_openlibs(lua_state);
  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
  {
      lib->func(lua_state);
      lua_settop(lua_state, 0);
  }
  entity_script_init(lua_state);
  //init_level(lua_state);
  level_script_init(lua_state);
  game_script_init(lua_state);
  attribute_script_init(lua_state);
  keyboard_script_init(lua_state);
  sprite_script_init(lua_state);
  component_init(lua_state);
  printf("MAIN::Estado de LUA creado.\n");
  
  printf("Main::Creando ventana...\n");
  Game::init(WIDTH,HEIGHT,false);
  Game::setLuaState(lua_state);
  GLFWimage icons[1];
  const char* dirIcon = "res/sprites/undefined.png";
  icons[0].pixels = stbi_load(dirIcon, &icons[0].width, &icons[0].height, 0, 0);
  glfwSetWindowIcon(Game::getWindow(), 1, icons);
  stbi_image_free(icons[0].pixels);
  const char* img[1] = {"res/sprites/undefined.png"};
  Sprite* sprUndefined = new Sprite(img,1,"undefined");
  Game::addSystemSprite(sprUndefined);
/*   const char* birdSprite[5] = {"res/sprites/c1.png","res/sprites/c2.png","res/sprites/c3.png","res/sprites/c4.png","res/sprites/c5.png"};
  Sprite* sprBird = new Sprite(birdSprite,5,"bird");
  sprBird->setSpeed(0.2*60); 
  Game::addSprite(sprBird); */
  /* const char* arr[6] = {"res/sprites/e1.png","res/sprites/e2.png","res/sprites/e3.png","res/sprites/e4.png","res/sprites/e5.png","res/sprites/e6.png"};
  Sprite* sprIdle = new Sprite(arr,6,"idle");
  Game::addSprite(sprIdle);
  sprIdle->setSpeed(0.16*60);
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
  const char* bg[1] = {"res/sprites/background.png"};
  Sprite* fondo = new Sprite(bg,1,"fondo");
  Game::addSprite(fondo);
  const char* bgLevel[1] = {"res/sprites/level-bg.png"};
  Sprite* fondo2 = new Sprite(bgLevel,1,"fondo2");
  Game::addSprite(fondo2);
   */
  /* Level* level1 = Game::addLevel();
  Entity* cameraEntity = level1->addEntityCamera(WIDTH,HEIGHT);
  ComponentCamera* cmpCamera = (ComponentCamera*)cameraEntity->getComponent("camera");
  cmpCamera->zoom(0.35f);
  cmpCamera->move(glm::vec3(-2610.0f,-185.5f,0.0f));
  cmpCamera->onUpdate();
  //Creo el personaje
  
  //cameraEntity->addComponent(new ComponentScript(scrCamera));
  Entity* personaje = level1->addEntity();
  
  GraphicAttribute* attrColor1 = new SpriteAttribute(sprIdle);
  personaje->addAttribute(attrColor1);
  Game::setLevel(0);
  Gui::writeToLog("Holiwi\n");
  
  Entity* fireEntity = level1->addEntity();
  personaje->scale(glm::vec3(1.4f,1.8f,1.0f));
  personaje->setPosition(glm::vec3(-2755.0f,-210.0f,0.0f));
  fireEntity->setPosition(glm::vec3(-2755.0f,-210.0f,0.0f));
  GraphicAttribute* fireAttr = new SpriteAttribute(fireSpr);
  fireEntity->addAttribute(fireAttr);
  //Creo el piso
  GraphicAttribute* attrColor = new ColorAttribute(glm::vec3(0.5f,0.1f,0.2f));

  //Creo el fondo
  
  Entity* entityBg = level1->addEntity();
  
  GraphicAttribute* attrFondo = new SpriteAttribute(fondo);

  entityBg->addAttribute(attrFondo);
  entityBg->scale(glm::vec3(500.0f/32.0f,289.36f/32.0f,1.0f));
  entityBg->setPosition(glm::vec3(-2586.0f,-192.0f,-2.0f));

  
  Entity* entityLevelBg = level1->addEntity();
  
  GraphicAttribute* attrFondoLevel = new SpriteAttribute(fondo2);
  entityLevelBg->addAttribute(attrFondoLevel);
  entityLevelBg->scale(glm::vec3(173.625f,26.75f,1.0f));
  entityLevelBg->setPosition(glm::vec3(-56.0f,0.0f,-1.0f));

  //Creo el pajaro
  
  Entity* bird = level1->addEntity();
  
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
  //personaje->addComponent(scriptComponent);
  fireEntity->addComponent(new ComponentMusic(SoundEngine));
  ((ComponentMusic*)(fireEntity->getComponent("music")))->setMusic("res/audio/disparo.wav");
  //((ComponentMusic*)(fireEntity->getComponent("music")))->playMusic();
  personaje->addComponent(new ComponentCollisionBox(personaje->getPosition().x,personaje->getPosition().y,personaje->getScale().x,personaje->getScale().y,personaje));
  bird->addComponent(new ComponentCollisionBox(bird->getPosition().x,bird->getPosition().y,bird->getScale().x,bird->getScale().y,bird));

  personaje->setName("JIM");
  //personaje->addComponent(new ComponentParticle(500,2,personaje));
  personaje->addAttribute(new ColorAttribute(glm::vec3(0.0f)));
  //level1->addAttribute(new Sharpen());
  
  //executeLuaScript(lua_state);
  personaje->addComponent(new ComponentMusic(SoundEngine));
  ((ComponentMusic*)(personaje->getComponent("music")))->setMusic("res/audio/01 - New Junk City.mp3");
  ((ComponentMusic*)(personaje->getComponent("music")))->setPlaying(true);
  ((ComponentMusic*)(personaje->getComponent("music")))->setLoop(true);
  //((ComponentMusic*)(personaje->getComponent("music")))->playMusic(true);
  personaje->addComponent(new ComponentMusic(irrklang::createIrrKlangDevice()));
  personaje->addComponent(new LuaScriptComponent("res/scripts/jim_script.lua", lua_state));
  file_manager::save_project("savedproject.wsl");
  //Game::loadProject("savedproject.wsl");
  Game::setLevel(0); */
  Game::loop();
  printf("Main::Eliminando objetos...\n");
  Game::close();  

/*   delete(level1);
  delete(attrColor); */
  printf("Main::Cerrando estado de LUA...\n");
  // close the Lua state
  lua_close(lua_state);
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