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
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define DEBUG
#define WIDTH 800
#define HEIGHT 600
Shader* shader;
Quad* q;
OrtographicCamera* camera;
unsigned int texture;
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
    
    shader->use();
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(camera->getProjectionMatrix()));
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(camera->getViewMatrix()));
    glUniform4f(vertexColorLocation, 0.0f, green_color, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(q->getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(int argc, char** argv)
{
    std::string dir = "Shader.shader";
    GLFWwindow* window = window_init(WIDTH,HEIGHT);
    q = new Quad();
    camera = new OrtographicCamera(WIDTH,HEIGHT);
    shader = new Shader(dir);


    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    
    glGenTextures(1, &texture);  
    glBindTexture(GL_TEXTURE_2D, texture);  
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {   
        #if defined(DEBUG)
            printf("No se pudo cargar la textura.\n");
        #endif
    }
    stbi_image_free(data);
    window_loop(window,loop_function_test);

    return 0;
}


