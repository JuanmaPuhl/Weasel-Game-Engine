#pragma once
#include "../Graphics/Shader.h"
#include <string>
class GraphicAttribute
{
    public:
    GraphicAttribute(){}
    ~GraphicAttribute(){}
    virtual void passToShader(Shader* shader,double deltaTime) = 0;
    virtual GraphicAttribute* copy() = 0;
    virtual void unbind(Shader* shader) = 0;
    void setName(std::string n)
    {
        name = n;
    }
    std::string getName()
    {
        return name;
    }
    private:
    std::string name;
};