#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include "Quad.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FileManager.h"
#include <math.h>
#include <string.h>

#include "OrtographicCamera.h"
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "Entity.h"
#include "Sprite.h"
#include "Debug.h"
#include "Animation.h"
#include "ScriptComponent.h"
#include "Game.h"
#include "Level.h"
#include "KeyboardControl.h"
#include "Control.h"
#include "Config.h"
#include "Scripts.h"
KeyboardControl* keyboardControl;
#define DEBUG
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 60;
const int MAX_ANIMATION_SIZE = 6;
const int MAX_FPS = 60;
Entity* entity,*entity2;
Sprite *spr1,*spr2;
Entity* lista[MAX_ENTITIES];
Animation* animation;
OrtographicCamera* camera;
glm::vec2 camera_movement_direction = glm::vec2(0.0f);
Game* game;


ScriptComponent* p;
float last_time = 0.0f;
int fps = 0;

const double maxPeriod  =1.0/double(MAX_FPS);
double lastTime = 0.0f;

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
  //printf("ITERACION.\n");
  float ms = deltaTime * 1000;
  #if defined(DEBUG)
    //printf("render time: %fms.\n",ms);
  #endif
  //camera->update(deltaTime);
  glBindVertexArray(entity->getQuad()->getVAO());
  game->render(deltaTime);

}

int main(int argc, char** argv)
{
  GLFWwindow* window = window::window_init(WIDTH,HEIGHT);
  game = new Game();
  entity = new Entity();
  entity2 = new Entity();
  entity2->scale(glm::vec3(-1.0f,1.0f,1.0f));
  entity2->translate(glm::vec3(0.0f,64.0f,0.0f));
  camera = new OrtographicCamera(WIDTH,HEIGHT);
  p = (ScriptComponent*)new Prueba();
  const char* arreglo[6] = {"res/Sprites/1.png","res/Sprites/2.png","res/Sprites/3.png","res/Sprites/4.png","res/Sprites/5.png","res/Sprites/6.png"};
  Sprite *chr1 = new Sprite(arreglo,6);
  const char* arreglo2[20] = {"res/Sprites/e1.png","res/Sprites/e2.png","res/Sprites/e3.png","res/Sprites/e4.png","res/Sprites/e5.png","res/Sprites/e6.png","res/Sprites/e7.png","res/Sprites/e8.png","res/Sprites/e9.png","res/Sprites/e10.png","res/Sprites/e11.png","res/Sprites/e12.png","res/Sprites/e13.png","res/Sprites/e14.png","res/Sprites/e15.png","res/Sprites/e16.png","res/Sprites/e17.png","res/Sprites/e18.png","res/Sprites/e19.png","res/Sprites/e20.png"};
  Sprite *chr2 = new Sprite(arreglo2,20);
  chr1->setTransparency(0.5f);
  chr1->setSpeed(0.25*60);
  entity2->setSprite(chr1);
  chr2->setSpeed(0.15*60);
  keyboardControl = new KeyboardControl();
  
  printf("A crear 1.\n");
  Level* level1 = new Level();
  EntityOriginal* entityScript = new EntityOriginal();
  entityScript->game = game;
  entity2->setScript(entityScript);
  level1->addEntity(entity2);
  printf("A crear 2.\n");
  Level* level2 = new Level();
  for(int i=0; i<MAX_ENTITIES; i++)
  {
      ScriptComponent* scr =(ScriptComponent*) new Prueba();
      ((Prueba*)scr)->game = game;
      lista[i] = new Entity();
      float division = float(MAX_ENTITIES-1)/2.0f;
      float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
      lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
      lista[i]->setSprite(chr2);
      lista[i]->setScript(scr);
      lista[i]->getSprite()->setTransparency((float)(i*0.15f+0.1f));
      level2->addEntity(lista[i]);
  } 
  level1->setCamera(camera);
  level2->setCamera(camera);
  game->addLevel(level1);
  game->addLevel(level2);
  game->setLevel(0);
  window::window_loop(window,loop_function_test);
  for(int i=0; i<MAX_ENTITIES; i++)
  {
    free(lista[i]);
  }
  delete(chr1);
  delete(chr2);
  delete(p);
  for(int i=0; i<MAX_ENTITIES; i++)
  {
    free(lista[i]);
  } 
/*   delete(e5); */
  return 0;
}


