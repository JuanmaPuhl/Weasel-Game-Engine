#pragma once
#include "GraphicAttribute.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class PixelizationAttribute : public GraphicAttribute
{
    public:
    PixelizationAttribute();
    ~PixelizationAttribute();
    void passToShader(Shader* shader,double deltaTime);
    GraphicAttribute* copy();
    void unbind(Shader* shader);
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    void setPixelSize(int pixelSize);
    int getPixelSize();
    private:
    int pixelSize = 5;
    int initial_pixelSize;
};