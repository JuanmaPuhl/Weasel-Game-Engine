#pragma once
#include "../Graphics/Shader.h"
class GraphicAttribute
{
    public:
    GraphicAttribute(){}
    ~GraphicAttribute(){}
    virtual void passToShader(Shader* shader,double deltaTime) = 0;
    virtual GraphicAttribute* copy() = 0;
};