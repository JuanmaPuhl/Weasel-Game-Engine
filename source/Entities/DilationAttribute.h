#pragma once
#include "GraphicAttribute.h"

class DilationAttribute : public GraphicAttribute
{
    public:
    DilationAttribute();
    ~DilationAttribute();
    void passToShader(Shader* shader,double deltaTime);
    DilationAttribute* copy();
    void unbind(Shader* shader);
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    void setSize(int size);
    void setSeparation(float separation);
    void setMinThreshold(float minThreshold);
    void setMaxThreshold(float maxThreshold);
    int getSize();
    float getSeparation();
    float getMinThreshold();
    float getMaxThreshold();
    private:
    int size = 5, initial_size;
    float separation = 0.5f,initial_separation, minThreshold = 0.2f, initial_minThreshold, maxThreshold = 0.6f, initial_maxThreshold;
    

};