#pragma once
#include "GraphicAttribute.h"
#include "../Graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class ColorAttribute : public GraphicAttribute
{
    public:
    ColorAttribute(glm::vec3 color);
    ~ColorAttribute();
    void passToShader(Shader* shader, double deltaTime);
    GraphicAttribute* copy();
    void unbind(Shader* shader);
    private:
    glm::vec3 color = glm::vec3(0.0f);
};