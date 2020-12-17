#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <typeinfo>
class Shader
{
    public:
    /**
     * @brief Construct a new Shader object
     * 
     * @param dir 
     */
    Shader(std::string &dir);
    /**
     * @brief Destroy the Shader object
     * 
     */
    ~Shader();
    /**
     * @brief Get the Vertex Shader object
     * 
     * @return unsigned int 
     */
    unsigned int getVertexShader();
    /**
     * @brief Get the Fragment Shader object
     * 
     * @return unsigned int 
     */
    unsigned int getFragmentShader();
    /**
     * @brief Get the Shader Program object
     * 
     * @return unsigned int 
     */
    unsigned int getShaderProgram();
    /**
     * @brief 
     * 
     */
    void use();
    int getLocation(const std::string& variable);
    template <typename T>void setUniform(const std::string& variable, T value)
    {
        bool encontre = false;
        int indice = 0;

        while(!encontre && indice <= aux )
        {
        if(names[indice] == variable)
        {
            encontre = true;
            checkUniform(locations[indice],types[indice],value);
        }
        else
        {
            indice++;
        }
        }
    }

    template<typename T>void checkUniform(int location, GLenum type, T value)
    {
        switch(type)
        {
        case(GL_FLOAT):       glUniform1f(location,(*value));
                                break;
        case(GL_INT):         glUniform1i(location,(*value));
                                break;
        case(GL_BOOL):        glUniform1i(location,(*value));
                                break;
        case(GL_FLOAT_VEC2):  glUniform2fv(location,1,value);
                                break;
        case(GL_FLOAT_VEC3):  glUniform3fv(location,1,value);
                                break;
        case(GL_FLOAT_VEC4):  glUniform4fv(location,1,value);
                                break;
        case(GL_FLOAT_MAT4):  glUniformMatrix4fv(location, 1, GL_FALSE, value);
                                break;
        
        }
    }

    void getAttributes();
    void getUniforms();
    private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    int aux;
    std::string message;
    int indexSaved = 0;
    std::string* names;
    GLenum* types;
    int* locations;
    static const int bufSize = 16; // maximum name length
    char name[bufSize]; // variable name in GLSL
    int length; // name length
    GLint count;
    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
};