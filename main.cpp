#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include "Quad.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FileManager.h"
#include <math.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define DEBUG
#define WIDTH 800
#define HEIGHT 800
Quad* q;
unsigned int texture;
unsigned int shaderProgram;
void loop_function_test(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float ms = deltaTime * 1000;
    //printf("render time: %fms.\n",ms);
    float timeValue = glfwGetTime();
    float green_color = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    //glUniform4f(vertexColorLocation, 0.0f, green_color, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(q->getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

enum Mode {vs, fs, ps};
int check_shader_compilation_status(unsigned int shader, Mode mode)
{
    #if defined(DEBUG)
    
        int  success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR: Fallo en compilacion de %d, %s\n",mode,infoLog);
        }
        else
        {
            printf("%d Compilado correctamente.\n",mode);
        }
    #endif
    
    return 0;
}

int main(int argc, char** argv)
{
    std::string dir = "Shader.shader";
    GLFWwindow* window = window_init(WIDTH,HEIGHT);
    q = new Quad();
    std::vector<std::string> shaderFiles = parse_file(dir);
    const std::string& vertex = shaderFiles[0];
    const std::string& fragment = shaderFiles[1];
    unsigned int vertexShader;
    const char* vertexSource = vertex.c_str();
    const char* fragmentSource = fragment.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compilation_status(vertexShader,vs);
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compilation_status(fragmentShader,fs);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_shader_compilation_status(shaderProgram,ps);
    
    
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


