#include "ColorAttribute.h"

ColorAttribute::ColorAttribute(glm::vec3 color)
{
    this->color = color;
}

ColorAttribute::~ColorAttribute()
{

}

void ColorAttribute::passToShader(Shader* shader, double deltaTime)
{
    shader->setUniform("color",glm::value_ptr(this->color));
}

GraphicAttribute* ColorAttribute::copy()
{
    ColorAttribute* a = new ColorAttribute(this->color);
    return a;
}

void ColorAttribute::unbind(Shader* shader)
{
    shader->setUniform("color",glm::value_ptr(glm::vec3(0.0f)));
}

