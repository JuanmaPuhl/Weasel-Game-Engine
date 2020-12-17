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
  Entity* personaje = level1->addEntity();
  const char* arr[1] = {"res/sprites/1.png"};
  GraphicAttribute* attrColor1 = new SpriteAttribute(new Sprite(arr,1));
  GraphicAttribute* attrColor = new ColorAttribute(glm::vec3(0.5f,0.1f,0.2f));
  personaje->addAttribute(attrColor1);
  personaje->addAttribute(attrColor);
  Game::setLevel(0);
  PlayerMovement* scr = new PlayerMovement();
  Component* scriptComponent = new ComponentScript(scr);
  scr->player = personaje;
  personaje->addComponent(scriptComponent);
  //Creo el piso
  for(int i = 0; i < 20; i++)
  {
    Entity* piso = level1->addEntity();
    float division = float(20-1)/2.0f;
    float new_x = float((32.0f)*i-(32.0f)*division);
    piso->addAttribute(attrColor);
    piso->translate(glm::vec3(new_x,-32.0f,0.0f));
  }

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