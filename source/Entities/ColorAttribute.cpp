#include "ColorAttribute.h"

ColorAttribute::ColorAttribute(glm::vec3 color)
{
    this->color = color;
    this->setName("color");
    this->iniState = (initialState*)malloc(sizeof(initialState));
}

ColorAttribute::~ColorAttribute()
{
    free(this->iniState);
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

glm::vec3 ColorAttribute::getColor()
{
    return this->color;
}

void ColorAttribute::setColor(glm::vec3 color)
{
    this-> color = color;
}

void ColorAttribute::save(std::ofstream& output)
{
    output << "\"name\" : \"color\" , ";
    output << "\"color\" : {\"x\" : " << this->color.x << " , \"y\" : " << this->color.y << " , \"z\" : " << this->color.z << "}"; 
}

bool ColorAttribute::registerInitialState()
{
    this->initial_color = this->color;
    return true;
}
bool ColorAttribute::recoverInitialState()
{
    this->color = this->initial_color;
    return true;
}