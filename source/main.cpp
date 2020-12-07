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
#include "Shader.h"
#include "Entity.h"
#include "Sprite.h"
#include "Debug.h"
#include "Animation.h"
#include "ScriptComponent.h"
#include "Game.h"
#include "Level.h"
//#include "Config.h"

#define DEBUG
const int WIDTH = 1280;
const int HEIGHT = 720;
const int MAX_ENTITIES = 60;
const int MAX_ANIMATION_SIZE = 6;
const int MAX_FPS = 60;
Shader* shader;
Entity* entity,*entity2;
Sprite *spr1,*spr2;
Entity* lista[MAX_ENTITIES];
Animation* animation;
OrtographicCamera* camera;
glm::vec2 camera_movement_direction = glm::vec2(0.0f);
Game* game;

class Prueba : public ScriptComponent
    {
      public: 
        void onCreate()
        {
          printf("ONCREATE.\n");
        }
        void onUpdate()
        {
          //printf("Hello World, I'm %d\n",this->id);
        }
      private:
        int id = 0;
    };
ScriptComponent* p;
float last_time = 0.0f;
int fps = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {
    }
    else 
        if (action == GLFW_RELEASE)
        {
        }
    
  }
}

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
  game->render(shader,deltaTime);

}

int main(int argc, char** argv)
{

    printf("QUE SE HACE.\n");
    game = new Game();
    std::string dir = "res/shaders/Shader.shader";
    GLFWwindow* window = window::window_init(WIDTH,HEIGHT);
    entity = new Entity();
    entity2 = new Entity();
    entity2->scale(glm::vec3(-1.0f,1.0f,1.0f));
    entity2->translate(glm::vec3(0.0f,64.0f,0.0f));
    camera = new OrtographicCamera(WIDTH,HEIGHT);
    shader = new Shader(dir);
    spr1 = new Sprite("res/sprites/container.jpg",normal);
    spr2 = new Sprite("res/sprites/wall.jpg",normal);
    Sprite *spr3 = new Sprite("res/Sprites/40_corrugated cardboard texture-seamless.jpg",normal);
    Sprite *spr4 = new Sprite("res/Sprites/awesomeface.png",transparent);
    Sprite *spr5 = new Sprite("res/Sprites/ges.png",normal);
    
    p = (ScriptComponent*)new Prueba();
    Sprite *chr1 = new Sprite("res/Sprites/1.png",transparent);
    Sprite *chr2 = new Sprite("res/Sprites/2.png",transparent);
    Sprite *chr3 = new Sprite("res/Sprites/3.png",transparent);
    Sprite *chr4 = new Sprite("res/Sprites/4.png",transparent);
    Sprite *chr5 = new Sprite("res/Sprites/5.png",transparent);
    Sprite *chr6 = new Sprite("res/Sprites/6.png",transparent);
    Sprite* sprites[6] = {chr1,chr2,chr3,chr4,chr5,chr6};
    Sprite *e1 = new Sprite("res/Sprites/e1.png",transparent);
    Sprite *e2 = new Sprite("res/Sprites/e2.png",transparent);
    Sprite *e3 = new Sprite("res/Sprites/e3.png",transparent);
    Sprite *e4 = new Sprite("res/Sprites/e4.png",transparent);
    Sprite *e5 = new Sprite("res/Sprites/e5.png",transparent);
    Sprite *e6 = new Sprite("res/Sprites/e6.png",transparent);
    Sprite *e7 = new Sprite("res/Sprites/e7.png",transparent);
    Sprite *e8 = new Sprite("res/Sprites/e8.png",transparent);
    Sprite *e9 = new Sprite("res/Sprites/e9.png",transparent);
    Sprite *e10 = new Sprite("res/Sprites/e10.png",transparent);
    Sprite *e11 = new Sprite("res/Sprites/e11.png",transparent);
    Sprite *e12 = new Sprite("res/Sprites/e12.png",transparent);
    Sprite *e13 = new Sprite("res/Sprites/e13.png",transparent);
    Sprite *e14 = new Sprite("res/Sprites/e14.png",transparent);
    Sprite *e15 = new Sprite("res/Sprites/e15.png",transparent);
    Sprite *e16 = new Sprite("res/Sprites/e16.png",transparent);
    Sprite *e17 = new Sprite("res/Sprites/e17.png",transparent);
    Sprite *e18 = new Sprite("res/Sprites/e18.png",transparent);
    Sprite *e19 = new Sprite("res/Sprites/e19.png",transparent);
    Sprite *e20 = new Sprite("res/Sprites/e20.png",transparent);
    
    Sprite* spritesE[20] = {e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16,e17,e18,e19,e20};
    animation = new Animation(6,sprites);
    animation->setSpeed(0.25*60);
    
    Animation* animJim = new Animation(20,spritesE);
    animJim->setSpeed(0.15*60);
    entity2->setSprite(animation);
    //loadLevel();


    window::set_key_callback(window,key_callback);
    for(int i=0; i<MAX_ENTITIES; i++)
    {
        ScriptComponent* scr =(ScriptComponent*) new Prueba();
        lista[i] = new Entity();
        float division = float(MAX_ENTITIES-1)/2.0f;
        float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
        lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
        lista[i]->setSprite(animJim);
        lista[i]->setScript(scr);
    } 
    printf("A crear 1.\n");
    Level* level1 = new Level();
    level1->addEntity(entity2);
    printf("A crear 2.\n");
    Level* level2 = new Level();
    for(int i=0;i<MAX_ENTITIES;i++)
    {
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
    free(animJim);
    free(animation);
    free(entity2);
    free(chr1);
    free(chr2);
    free(chr3);
    free(chr4);
    free(chr5);
    free(chr6);
    free(e1);
    free(e2);
    free(e3);
    free(spr3);
    free(spr4);
    free(spr5);
    free(shader);
    free(camera);
    delete(e5);
    return 0;
}


