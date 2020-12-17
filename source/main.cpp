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
#define DEBUG
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 10;
Entity* entity;
Entity* lista[MAX_ENTITIES];
ScriptComponent* p;

int metodoPrincipal()
{
  printf("Main::Creando ventana...\n");
  Game::init(WIDTH,HEIGHT);
  p = (ScriptComponent*)new Prueba();
  EntityOriginal* entityScript = new EntityOriginal();
  CameraController* cameraController = new CameraController();
  entity = new Entity();
  const char* arreglo[6] = {"res/Sprites/1.png","res/Sprites/2.png","res/Sprites/3.png","res/Sprites/4.png","res/Sprites/5.png","res/Sprites/6.png"};
  Sprite *chr1 = new Sprite(arreglo,6);
  const char* arreglo2[20] = {"res/Sprites/e1.png","res/Sprites/e2.png","res/Sprites/e3.png","res/Sprites/e4.png","res/Sprites/e5.png","res/Sprites/e6.png","res/Sprites/e7.png","res/Sprites/e8.png","res/Sprites/e9.png","res/Sprites/e10.png","res/Sprites/e11.png","res/Sprites/e12.png","res/Sprites/e13.png","res/Sprites/e14.png","res/Sprites/e15.png","res/Sprites/e16.png","res/Sprites/e17.png","res/Sprites/e18.png","res/Sprites/e19.png","res/Sprites/e20.png"};
  Sprite *chr2 = new Sprite(arreglo2,20);
  chr1->setTransparency(1.0f);
  chr1->setSpeed(0.25*60);
  chr2->setSpeed(0.15*60);
  Level* level1 = Game::addLevel();
  Entity* entity2 = level1->addEntity();
  //entity2->setSprite(chr1);
  Level* level2 = Game::addLevel();
  Entity* cameraEntity = level2->addEntityCamera(WIDTH,HEIGHT);
  cameraController->camera = cameraEntity;
  Component* cmp = new ComponentScript(cameraController);
  cameraEntity->addComponent(cmp);
  entity2->addComponent(cmp);
  GraphicAttribute* attr1 = new SpriteAttribute(chr1);
  GraphicAttribute* attr2 = new SpriteAttribute(chr2);
  entity2->addAttribute(attr1);
  for(int i=0; i<MAX_ENTITIES; i++)
  {
      ScriptComponent* scr =(ScriptComponent*) new Prueba();
      lista[i] = level2->addEntity();
      float division = float(MAX_ENTITIES-1)/2.0f;
      float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
      lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
      //lista[i]->setSprite(chr2);
      lista[i]->addAttribute(attr2);
      ((SpriteAttribute*)(lista[i]->getAttribute(0)))->getSprite()->setTransparency((float)(i*0.15f+0.1f));
  } 
  ((SpriteAttribute*)(lista[MAX_ENTITIES-1]->getAttribute(0)))->getSprite()->setSpeed(0.0);
  Game::setLevel(1);
  Game::loop();
  printf("Main::Eliminando objetos...\n");
  Game::close();
  /*Elimino los sprites*/
  delete(chr1); 
  delete(chr2);
  /*Elimino los scripts*/
  delete(p);
  delete(cameraController);
  delete(entityScript);
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