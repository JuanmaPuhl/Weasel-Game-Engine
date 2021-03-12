#pragma once
#include "GraphicAttribute.h"

class Sharpen : public GraphicAttribute
{
    public:
    Sharpen();
    ~Sharpen();
    void passToShader(Shader* shader,double deltaTime);
    GraphicAttribute* copy();
    void unbind(Shader* shader);
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    void setAmount(float amount);
    float getAmount();
    private:
    float amount = 0.8f;
    float initial_amount;
};