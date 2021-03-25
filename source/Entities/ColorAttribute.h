#pragma once
#include "GraphicAttribute.h"
#include "../Graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class ColorAttribute : public GraphicAttribute
{
    public:
    ColorAttribute(glm::vec4 color);
    ~ColorAttribute();
    void passToShader(Shader* shader, double deltaTime);
    GraphicAttribute* copy();
    void unbind(Shader* shader);
    glm::vec4 getColor();
    void save(std::ofstream& output_dir);
    void setColor(glm::vec4 color);
    bool registerInitialState();
    bool recoverInitialState();
    private:
    glm::vec4 color = glm::vec4(0.0f,0.0f,0.0f,0.0f);
    glm::vec4 initial_color;

};