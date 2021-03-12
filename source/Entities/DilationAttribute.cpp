#include "DilationAttribute.h"

DilationAttribute::DilationAttribute()
{
    this->setName("dilation");
}
DilationAttribute::~DilationAttribute()
{

}
void DilationAttribute::passToShader(Shader* shader,double deltaTime)
{
    int b = 1;
    //shaderToUse->use();
    GLint dilationLocation = glGetUniformLocation(shader->getShaderProgram(), "dilation");
    glUniform1i(dilationLocation, b);
    
    GLint sizeLocation = glGetUniformLocation(shader->getShaderProgram(), "size");
    glUniform1i(sizeLocation, this->size);

    shader->setUniform("separation",&this->separation);
    shader->setUniform("minThreshold",&this->minThreshold);
    shader->setUniform("maxThreshold",&this->maxThreshold);
}
DilationAttribute* DilationAttribute::copy()
{
    DilationAttribute* d = new DilationAttribute();
    d->setSize(this->size);
    d->setSeparation(this->separation);
    d->setMinThreshold(this->minThreshold);
    d->setMaxThreshold(this->maxThreshold);
    return d;
}
void DilationAttribute::unbind(Shader* shader)
{
    int b = 0;
    //shaderToUse->use();
    GLint dilationLocation = glGetUniformLocation(shader->getShaderProgram(), "dilation");
    glUniform1i(dilationLocation, b);
    
    GLint sizeLocation = glGetUniformLocation(shader->getShaderProgram(), "size");
    glUniform1i(sizeLocation, 0.0f);
    float f = 0.0f;
    shader->setUniform("separation",&f);
    shader->setUniform("minThreshold",&f);
    shader->setUniform("maxThreshold",&f);
}

void DilationAttribute::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"size\" : " << this->size << " , ";
    output << "\"separation\" : " << this->separation << " , ";
    output << "\"minThreshold\" : " << this->minThreshold << " , ";
    output << "\"maxThreshold\" : " << this->maxThreshold;
}
bool DilationAttribute::registerInitialState()
{
    this->initial_size = this->size;
    this->initial_separation = this->separation;
    this->initial_minThreshold = this->minThreshold;
    this->initial_maxThreshold = this->maxThreshold;
}
bool DilationAttribute::recoverInitialState()
{
    this->size = this->initial_size;
    this->separation = this->initial_separation;
    this->minThreshold = this->initial_minThreshold;
    this->maxThreshold = this->initial_maxThreshold;
}
void DilationAttribute::setSize(int size)
{
    this->size = size;
}
void DilationAttribute::setSeparation(float separation)
{
    this->separation = separation;
}
void DilationAttribute::setMinThreshold(float minThreshold)
{
    this->minThreshold = minThreshold;
}
void DilationAttribute::setMaxThreshold(float maxThreshold)
{
    this->maxThreshold = maxThreshold;
}
int DilationAttribute::getSize()
{
    return this->size;
}
float DilationAttribute::getSeparation()
{
    return this->separation;
}
float DilationAttribute::getMinThreshold()
{
    return this->minThreshold;
}
float DilationAttribute::getMaxThreshold()
{
    return this->maxThreshold;
}