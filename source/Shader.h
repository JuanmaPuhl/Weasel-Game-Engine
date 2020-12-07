#pragma once
#include <string>
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
    private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
};