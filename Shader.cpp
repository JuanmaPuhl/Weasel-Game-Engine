#include "Shader.h"
#include "FileManager.h"
#include <GL/glew.h>

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

Shader::Shader(std::string &dir)
{
    std::vector<std::string> shaderFiles = file_manager::parse_file(dir);
    const std::string& vertex = shaderFiles[0];
    const std::string& fragment = shaderFiles[1];
    const char* vertexSource = vertex.c_str();
    const char* fragmentSource = fragment.c_str();
    this->vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &vertexSource, NULL);
    glCompileShader(this->vertexShader);
    check_shader_compilation_status(this->vertexShader,vs);

    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(this->fragmentShader);
    check_shader_compilation_status(this->fragmentShader,fs);

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    glLinkProgram(this->shaderProgram);
    check_shader_compilation_status(this->shaderProgram,ps);
}

Shader::~Shader()
{

}

unsigned int Shader::getFragmentShader()
{
    return this->fragmentShader;
}

unsigned int Shader::getVertexShader()
{
    return this->vertexShader;
}

unsigned int Shader::getShaderProgram()
{
    return this->shaderProgram;
}

void Shader::use()
{
    glUseProgram(this->shaderProgram);
}


