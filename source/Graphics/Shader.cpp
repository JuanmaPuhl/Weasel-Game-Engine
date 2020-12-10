#include "Shader.h"
#include "../FileManagement/FileManager.h"


#define DEBUG
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
    aux = 0;
    glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &count);
    aux += count;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
    aux +=count;
    names = new std::string[aux];
    types = new GLenum[aux];
    locations = new int[aux];
    getAttributes();
    getUniforms();

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

int Shader::getLocation(const std::string& variable)
{
  const char *var = variable.c_str();
  return glGetUniformLocation(this->shaderProgram, var);
}

void Shader::getAttributes()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &count);
  for (int i = 0; i < count; i++)
  {
      glGetActiveAttrib(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      indexSaved++;
  }
}

void Shader::getUniforms()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
  for (int i = 0; i < count; i++)
  {
      glGetActiveUniform(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      locations[indexSaved] = glGetUniformLocation(shaderProgram,name);
      indexSaved++;
  }
}

