#include "Graphics/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Entities/OrtographicCamera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Entities/Entity.h"
#include "Graphics/Sprite.h"
#include "Entities/ScriptComponent.h"
#include "General/Game.h"
#include "General/Level.h"
#include "Controls/KeyboardControl.h"
#include "Config.h"
#include "Entities/Scripts.h"
KeyboardControl* keyboardControl;
#define DEBUG
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 10;
const int MAX_ANIMATION_SIZE = 6;
const int MAX_FPS = 60;
Entity* entity;
Entity* lista[MAX_ENTITIES];
OrtographicCamera* camera;
/* Game* game; */


ScriptComponent* p;
/* float last_time = 0.0f;
int fps = 0;

const double maxPeriod  =1.0/double(MAX_FPS);
double lastTime = 0.0f;
double lastTimeForSleep = 0.0;
const int MAX_FRAMERATE = 120;
void loop_function_test(float deltaTime)
{
  float current = glfwGetTime();
  double delta = current - lastTime;
  lastTime = current;
  fps++;
  if(current - last_time >=1.0f)
  {
    double fpsCount = 1000.0/double(fps);
    printf("FPS: %d\n",fps);
    fps = 0;
    last_time++;
  }
  float ms = deltaTime * 1000;
  //printf("render time: %fms.\n",ms);
  glBindVertexArray(entity->getQuad()->getVAO());
/*   game->onUpdate(deltaTime);
  game->render(deltaTime); */
/*   Game::onUpdate(deltaTime);
  Game::render(deltaTime);
  //Si me paso del framerate
  while(glfwGetTime()<lastTimeForSleep+double(1.0/MAX_FRAMERATE))
  {
    //No hago nada. Limito fps.
  }
  lastTimeForSleep += 1.0/MAX_FRAMERATE; 

} */
int metodoPrincipal()
{
  printf("Main::Creando ventana...\n");
  //GLFWwindow* window = window::window_init(WIDTH,HEIGHT);
  //game = new Game(WIDTH,HEIGHT);
  Game::init(WIDTH,HEIGHT);
  p = (ScriptComponent*)new Prueba();
  EntityOriginal* entityScript = new EntityOriginal();
  CameraController* cameraController = new CameraController();
  keyboardControl = new KeyboardControl();
  entity = new Entity();
  camera = new OrtographicCamera(WIDTH,HEIGHT);
  const char* arreglo[6] = {"res/Sprites/1.png","res/Sprites/2.png","res/Sprites/3.png","res/Sprites/4.png","res/Sprites/5.png","res/Sprites/6.png"};
  Sprite *chr1 = new Sprite(arreglo,6);
  const char* arreglo2[20] = {"res/Sprites/e1.png","res/Sprites/e2.png","res/Sprites/e3.png","res/Sprites/e4.png","res/Sprites/e5.png","res/Sprites/e6.png","res/Sprites/e7.png","res/Sprites/e8.png","res/Sprites/e9.png","res/Sprites/e10.png","res/Sprites/e11.png","res/Sprites/e12.png","res/Sprites/e13.png","res/Sprites/e14.png","res/Sprites/e15.png","res/Sprites/e16.png","res/Sprites/e17.png","res/Sprites/e18.png","res/Sprites/e19.png","res/Sprites/e20.png"};
  Sprite *chr2 = new Sprite(arreglo2,20);
  chr1->setTransparency(1.0f);
  chr1->setSpeed(0.25*60);
  chr2->setSpeed(0.15*60);
  Level* level1 = Game::addLevel();
  cameraController->camera = camera;
  //entityScript->game = game;
  Entity* entity2 = level1->addEntity();
  entity2->setScript(cameraController);
  entity2->setSprite(chr1);
  Level* level2 = Game::addLevel();
  for(int i=0; i<MAX_ENTITIES; i++)
  {
      ScriptComponent* scr =(ScriptComponent*) new Prueba();
      //((Prueba*)scr)->game = game;
      lista[i] = level2->addEntity();
      float division = float(MAX_ENTITIES-1)/2.0f;
      float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
      lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
      lista[i]->setSprite(chr2);
      lista[i]->setScript(cameraController);
      lista[i]->getSprite()->setTransparency((float)(i*0.15f+0.1f));
  } 
  lista[MAX_ENTITIES-1]->getSprite()->setSpeed(0.0);
  level1->setCamera(camera);
  level2->setCamera(camera);
  Game::setLevel(1);
  Game::loop();
  printf("Main::Eliminando objetos...\n");
  //delete(game); //Esto elimina shader, niveles, entidades,camaras.
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


