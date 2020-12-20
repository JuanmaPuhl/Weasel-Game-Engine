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
#define DEBUG
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 10;


int metodoPrincipal()
{
  printf("Main::Creando ventana...\n");
  Game::init(WIDTH,HEIGHT);
  Level* level1 = Game::addLevel();
  Entity* cameraEntity = level1->addEntityCamera(WIDTH,HEIGHT);

  //Creo el personaje
  Entity* personaje = level1->addEntity();
  const char* arr[1] = {"res/sprites/e20.png"};
  Sprite* sprIdle = new Sprite(arr,1);
  GraphicAttribute* attrColor1 = new SpriteAttribute(sprIdle);
  personaje->addAttribute(attrColor1);
  Game::setLevel(0);
  PlayerMovement* scr = new PlayerMovement();
  Component* scriptComponent = new ComponentScript(scr);
  const char* walkingAnimation[9] = {"res/sprites/ew1.png","res/sprites/ew2.png","res/sprites/ew3.png","res/sprites/ew4.png","res/sprites/ew5.png","res/sprites/ew6.png","res/sprites/ew7.png","res/sprites/ew8.png","res/sprites/ew9.png"};
  Sprite* walkingSpr = new Sprite(walkingAnimation,9);
  walkingSpr->setSpeed(0.2*60.0);
  scr->player = personaje;
  scr->spriteIdle = sprIdle;
  scr->spriteWalking = walkingSpr;
  personaje->addComponent(scriptComponent);

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
  const char* bg[1] = {"res/sprites/bg3.gif"};
  Entity* entityBg = level1->addEntity();
  GraphicAttribute* attrFondo = new SpriteAttribute(new Sprite(bg,1));
  entityBg->addAttribute(attrFondo);
  entityBg->scale(glm::vec3(40.0f,22.5f,1.0f));
  entityBg->translate(glm::vec3(0.0f,0.0f,-0.1f));

  //Creo el pajaro
  const char* birdSprite[8] = {"res/sprites/b1.png","res/sprites/b2.png","res/sprites/b3.png","res/sprites/b4.png","res/sprites/b5.png","res/sprites/b6.png","res/sprites/b7.png","res/sprites/b8.png"};
  Entity* bird = level1->addEntity();
  Sprite* sprBird = new Sprite(birdSprite,8);
  sprBird->setSpeed(0.125*60);
  GraphicAttribute* attrBird = new SpriteAttribute(sprBird);
  bird->addAttribute(attrBird);
  bird->scale(glm::vec3(-0.5f,0.5f,0.0f));
  bird->translate(glm::vec3(256.0f,320.0f,0.0f));
  BirdMovement* birdScr = new BirdMovement();
  birdScr->bird = bird;
  ComponentScript* birdScrComponent = new ComponentScript(birdScr);
  bird->addComponent(birdScrComponent); 
  
  

  Game::loop();
  printf("Main::Eliminando objetos...\n");
  Game::close();
  delete(level1);
  delete(attrColor);
  glfwTerminate(); //Cierro glfw
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