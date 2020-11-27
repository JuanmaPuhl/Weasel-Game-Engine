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
#define WIDTH 800
#define HEIGHT 600
Shader* shader;
Entity* entity,*entity2;
OrtographicCamera* camera;
Sprite *spr1,*spr2;
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
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(entity->getModelMatrix()));
    glUniform4f(vertexColorLocation, 0.0f, green_color, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, spr1->getSpriteImage());
    //Dibujo primera entidad
    glBindVertexArray(entity->getQuad()->getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Dibujo segunda entidad
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(entity2->getModelMatrix()));
    glBindTexture(GL_TEXTURE_2D, spr2->getSpriteImage());
    glBindVertexArray(entity2->getQuad()->getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(int argc, char** argv)
{
    std::string dir = "Shader.shader";
    GLFWwindow* window = window_init(WIDTH,HEIGHT);
    entity = new Entity();
    entity2 = new Entity();
    entity2->translate(glm::vec3(100.0f,0.0f,0.0f));
    camera = new OrtographicCamera(WIDTH,HEIGHT);
    shader = new Shader(dir);
    spr1 = new Sprite("container.jpg");
    spr2 = new Sprite("wall.jpg");

    
    window_loop(window,loop_function_test);

    return 0;
}


