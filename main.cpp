#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include "Quad.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FileManager.h"
#define WIDTH 800
#define HEIGHT 800
Quad* q;
unsigned int shaderProgram;
void loop_function_test(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float ms = deltaTime * 1000;
    //printf("render time: %fms.\n",ms);
    glUseProgram(shaderProgram);
    glBindVertexArray(q->getVAO());
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, q->getEBO());
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(void)
{
    std::string dir = "Shader.shader";
    GLFWwindow* window = window_init(WIDTH,HEIGHT);
    q = new Quad();
    char shaderFile[14] = "Shader.shader";
    std::vector<std::string> shaderFiles = parse_file(dir);
    const std::string& vertex = shaderFiles[0];
    const std::string& fragment = shaderFiles[1];
    unsigned int vertexShader;
    const char* vertexSource = vertex.c_str();
    const char* fragmentSource = fragment.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n",infoLog);
    }
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s\n",infoLog);
    }
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED %s\n",infoLog);
    }
    window_loop(window,loop_function_test);
    return 0;
}


