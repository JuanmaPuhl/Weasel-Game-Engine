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
#define MAX_ENTITIES 25
Shader* shader;
Entity* entity,*entity2;
OrtographicCamera* camera;
Sprite *spr1,*spr2;
Entity* lista[MAX_ENTITIES];

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
          printf("Aprete la tecla A.\n");
          entity->setSprite(spr1);
      }
      if(key==GLFW_KEY_D)
      {
          printf("Aprete la tecla D.\n");
          entity->setSprite(spr2);
      }  
    }
    else 
        if (action == GLFW_RELEASE)
        {
            
        }
    
  }
}

void loop_function_test(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float ms = deltaTime * 1000;
    //printf("render time: %fms.\n",ms);
    float timeValue = glfwGetTime();
    float green_color = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader->getShaderProgram(), "ourColor");
    int projectionLocation = glGetUniformLocation(shader->getShaderProgram(),"projection");
    int viewLocation = glGetUniformLocation(shader->getShaderProgram(),"view");
    int modelLocation = glGetUniformLocation(shader->getShaderProgram(),"model");
    shader->use();
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(camera->getProjectionMatrix()));
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(camera->getViewMatrix()));
    //glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(entity->getModelMatrix()));
    glUniform4f(vertexColorLocation, 0.0f, green_color, 0.0f, 1.0f);
    //glBindTexture(GL_TEXTURE_2D, entity->getSprite()->getSpriteImage());
    //Dibujo primera entidad
    
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Dibujo segunda entidad
    glBindVertexArray(entity->getQuad()->getVAO());
    for(int i=0;i<MAX_ENTITIES;i++)
    {
      glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(lista[i]->getModelMatrix()));
      glBindTexture(GL_TEXTURE_2D, lista[i]->getSprite()->getSpriteImage());
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(entity2->getModelMatrix()));
    glBindTexture(GL_TEXTURE_2D, entity2->getSprite()->getSpriteImage());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(int argc, char** argv)
{
    std::string dir = "Shader.shader";
    GLFWwindow* window = window::window_init(WIDTH,HEIGHT);
    entity = new Entity();
    entity2 = new Entity();
    entity2->translate(glm::vec3(2.0f,64.0f,0.0f));
    camera = new OrtographicCamera(WIDTH,HEIGHT);
    shader = new Shader(dir);
    spr1 = new Sprite("container.jpg");
    spr2 = new Sprite("wall.jpg");
    entity->setSprite(spr1);
    entity2->setSprite(spr2);
    window::set_key_callback(window,key_callback);
    for(int i=0; i<MAX_ENTITIES; i++)
    {
        lista[i] = new Entity();
        float division = float(MAX_ENTITIES-1)/2.0f;
        printf("Division: %f\n",division);
        float new_x = float((32.0f+5.0f)*i-(32.0f+5.0f)*division);
        printf("NEW X: %f\n",new_x);
        lista[i]->translate(glm::vec3(new_x,0.0f,0.0f));
        lista[i]->setSprite(spr1);
    }
    window::window_loop(window,loop_function_test);
    return 0;
}


