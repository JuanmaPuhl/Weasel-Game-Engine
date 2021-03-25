#include "ColorAttribute.h"

ColorAttribute::ColorAttribute(glm::vec4 color)
{
    this->color = color;
    this->setName("color");
}

ColorAttribute::~ColorAttribute()
{
}

void ColorAttribute::passToShader(Shader* shader, double deltaTime)
{
    //printf("Color: %f,%f,%f,%f\n",this->color.x,this->color.y,this->color.z,this->color.a);
    shader->setUniform("color",glm::value_ptr(this->color));
}

GraphicAttribute* ColorAttribute::copy()
{
    ColorAttribute* a = new ColorAttribute(this->color);
    return a;
}

void ColorAttribute::unbind(Shader* shader)
{

    shader->setUniform("color",glm::value_ptr(glm::vec4(0.0f,0.0f,0.0f,0.0f)));
}

glm::vec4 ColorAttribute::getColor()
{
    return this->color;
}

void ColorAttribute::setColor(glm::vec4 color)
{
    this-> color = color;
}

void ColorAttribute::save(std::ofstream& output)
{
    output << "\"name\" : \"color\" , ";
    output << "\"color\" : {\"x\" : " << this->color.x << " , \"y\" : " << this->color.y << " , \"z\" : " << this->color.z << ", \"a\" : " << this->color.a << "}"; 
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