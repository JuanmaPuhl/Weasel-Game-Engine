#include "Graphics/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

  std::string cmd = "return 7 + 11";
  lua_State *L = luaL_newstate();
  luaL_loadfilex(L,"script.lua",0);
  lua_callk(L, 0,1,0,NULL);
  const auto result = (int) lua_tointegerx(L,1,0);
  printf("Resultado: %d\n",result);

  lua_close(L);

  printf("Main::Creando ventana...\n");
  Game::init(WIDTH,HEIGHT);
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
  Game::addSprite(sprUndefined);
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
  personaje->setPosition(glm::vec3(-2459.0f,-120.0f,0.0f));
  fireEntity->setPosition(glm::vec3(-2459.0f,-120.0f,0.0f));
  GraphicAttribute* fireAttr = new SpriteAttribute(fireSpr);
  fireEntity->addAttribute(fireAttr);
  //Creo el piso
  GraphicAttribute* attrColor = new ColorAttribute(glm::vec3(0.5f,0.1f,0.2f));
  for(int i = 0; i < 20; i++)
  {
    Entity* piso = level1->addEntity();
    float division = float(20-1)/2.0f;
    float new_x = float((32.0f)*i-(32.0f)*division);
    piso->addAttribute(attrColor);
    piso->translate(glm::vec3(new_x,-32.0f,0.0f));
  }
  //Creo el fondo
  const char* bg[1] = {"res/sprites/background.png"};
  Entity* entityBg = level1->addEntity();
  Sprite* fondo = new Sprite(bg,1,"fondo");
  Game::addSprite(fondo);
  GraphicAttribute* attrFondo = new SpriteAttribute(fondo);

  entityBg->addAttribute(attrFondo);
  entityBg->scale(glm::vec3(173.625f,86.98f,1.0f));
  entityBg->translate(glm::vec3(0.0f,0.0f,-0.1f));

  const char* bgLevel[1] = {"res/sprites/level-bg.png"};
  Entity* entityLevelBg = level1->addEntity();
  Sprite* fondo2 = new Sprite(bgLevel,1,"fondo2");
  Game::addSprite(fondo2);
  GraphicAttribute* attrFondoLevel = new SpriteAttribute(fondo2);
  entityLevelBg->addAttribute(attrFondoLevel);
  entityLevelBg->scale(glm::vec3(173.625f,26.75f,1.0f));
  entityLevelBg->translate(glm::vec3(0.0f,0.0f,-0.01f));

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