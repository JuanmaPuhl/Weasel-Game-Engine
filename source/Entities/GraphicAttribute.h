#pragma once
#include "../Graphics/Shader.h"
#include <string>
#include <iostream>
#include <fstream>
class GraphicAttribute
{
    public:
    GraphicAttribute(){}
    ~GraphicAttribute(){}
    virtual void passToShader(Shader* shader,double deltaTime) = 0;
    virtual GraphicAttribute* copy() = 0;
    virtual void unbind(Shader* shader) = 0;
    virtual void save(std::ofstream& output_dir) = 0;
    virtual bool registerInitialState() = 0;
    virtual bool recoverInitialState() = 0;
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