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
#define DEBUG
#define WIDTH 1280
#define HEIGHT 720
#define MAX_ENTITIES 10
#define MAX_ANIMATION_SIZE 5
#define MAX_FPS 60
Shader* shader;
Entity* entity,*entity2;
OrtographicCamera* camera;
Sprite *spr1,*spr2;
Entity* lista[MAX_ENTITIES];
Sprite** animation;
int animation_index = 0;
double animation_speed = 0.01667;
float animation_elapsed_time = 0.0f;
double index_aux = 0.0;
glm::vec2 camera_movement_direction = glm::vec2(0.0f);
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
      if(key==GLFW_KEY_A)
      {
          entity->setSprite(spr1);
      }
      if(key==GLFW_KEY_D)
      {
          entity->setSprite(spr2);
      }
      if(key==GLFW_KEY_I)
      {
          camera->zoom(1.0f);
      } 
      if(key==GLFW_KEY_J)
      {
          camera->zoom(-1.0f);
      }
      if(key==GLFW_KEY_RIGHT)
      {
        camera_movement_direction += glm::vec2(1.0f,0.0f);
      }
      if(key==GLFW_KEY_LEFT)
      {
        camera_movement_direction  += glm::vec2(-1.0f,0.0f);
      }
      if(key==GLFW_KEY_UP)
      {
        camera_movement_direction += glm::vec2(0.0f,1.0f);
      }   
      if(key==GLFW_KEY_DOWN)
      {
        camera_movement_direction += glm::vec2(0.0f,-1.0f);
      }
      camera->move(camera_movement_direction);
    }
    else 
        if (action == GLFW_RELEASE)
        {
          if(key==GLFW_KEY_I)
          {
              camera->zoom(0.0f);
          }
          if(key==GLFW_KEY_J)
          {
              camera->zoom(0.0f);
          }
          if(key==GLFW_KEY_RIGHT)
          {
            camera_movement_direction += glm::vec2(-1.0f,0.0f);
          } 
          if(key==GLFW_KEY_LEFT )
          {
            camera_movement_direction += glm::vec2(1.0f,0.0f);
          } 
          if(key == GLFW_KEY_UP)
          {
            camera_movement_direction += glm::vec2(0.0f,-1.0f);
          } 
          if(key == GLFW_KEY_DOWN)
          {
            camera_movement_direction += glm::vec2(0.0f,1.0f);
          } 
          camera->move(camera_movement_direction); 
        }
    
  }
}

void loop_function_test(float deltaTime)
{
    if(fps<MAX_FPS)
      fps++;
    
    float current = glfwGetTime();
    if(current - last_time >=1.0f)
    {
      double fpsCount = 1000.0/double(fps);
      
      printf("FPS: %d\n",fps);
      fps = 0;
      last_time++;
    }
    if(fps>=MAX_FPS)
    {
      return;
    }
    //printf("ITERACION.\n");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float ms = deltaTime * 1000;
    #if defined(DEBUG)
      //printf("render time: %fms.\n",ms);
    #endif
    camera->update(deltaTime);
    float timeValue = glfwGetTime();
    float green_color = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader->getShaderProgram(), "ourColor");
    int projectionLocation = glGetUniformLocation(shader->getShaderProgram(),"projection");
    int viewLocation = glGetUniformLocation(shader->getShaderProgram(),"view");
    int modelLocation = glGetUniformLocation(shader->getShaderProgram(),"model");
    shader->use();
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(camera->getProjectionMatrix()));
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(camera->getViewMatrix()));
    glUniform4f(vertexColorLocation, 0.0f, green_color, 0.0f, 1.0f);
    //Dibujo segunda entidad
    glBindVertexArray(entity->getQuad()->getVAO());
    for(int i=0;i<MAX_ENTITIES;i++)
    {
      glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(lista[i]->getModelMatrix()));
      glBindTexture(GL_TEXTURE_2D, lista[i]->getSprite()->getSpriteImage());
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    animation_elapsed_time += ms;
    index_aux+=animation_speed;
    /* if(fps % animation_speed == 0)
    {
      if(animation_index< MAX_ANIMATION_SIZE - 1)
        animation_index++;
      else
        animation_index = 0;
      animation_elapsed_time = 0.0f;
    } */
    int aux = (int)index_aux;
    if(aux>=MAX_ANIMATION_SIZE)
    {
      aux = 0;
      index_aux = 0.0;
    }
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(entity2->getModelMatrix()));
    glBindTexture(GL_TEXTURE_2D, animation[aux]->getSpriteImage());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(int argc, char** argv)
{
    std::string dir = "res/shaders/Shader.shader";
    GLFWwindow* window = window::window_init(WIDTH,HEIGHT);
    entity = new Entity();
    entity2 = new Entity();
    entity2->translate(glm::vec3(2.0f,64.0f,0.0f));
    camera = new OrtographicCamera(WIDTH,HEIGHT);
    shader = new Shader(dir);
    spr1 = new Sprite("res/sprites/container.jpg",normal);
    spr2 = new Sprite("res/sprites/wall.jpg",normal);
    Sprite *spr3 = new Sprite("res/Sprites/40_corrugated cardboard texture-seamless.jpg",normal);
    Sprite *spr4 = new Sprite("res/Sprites/awesomeface.png",transparent);
    Sprite *spr5 = new Sprite("res/Sprites/ges.png",normal);
    animation = (Sprite**)malloc(sizeof(Sprite)*MAX_ANIMATION_SIZE);
    animation[0] = spr1;
    animation[1] = spr2;
    animation[2] = spr3;
    animation[3] = spr4;
    animation[4] = spr5;
    entity->setSprite(spr1);
    entity2->setSprite(spr2);
    window::set_key_callback(window,key_callback);
    for(int i=0; i<MAX_ENTITIES; i++)
    {
        lista[i] = new Entity();
        float division = float(MAX_ENTITIES-1)/2.0f;
        float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
        lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
        lista[i]->setSprite(spr1);
    }
    window::window_loop(window,loop_function_test);
    return 0;
}


