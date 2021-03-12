#include "PixelizationAttribute.h"
#include "../General/Game.h"
PixelizationAttribute::PixelizationAttribute()
{
    this->setName("pixelization");
}
PixelizationAttribute::~PixelizationAttribute()
{

}
void PixelizationAttribute::passToShader(Shader* shader,double deltaTime)
{
    int b = 1;
    //Shader* shaderToUse = gamedata->shaderGeneral;
    //shaderToUse->use();
    //shaderToUse->setUniform("pixelization", &b);
    GLint pixelizationLocation = glGetUniformLocation(shader->getShaderProgram(), "pixelization");
    glUniform1i(pixelizationLocation, b);

    GLint pixelSizeLocation = glGetUniformLocation(shader->getShaderProgram(), "pixelSize");
    glUniform1i(pixelSizeLocation, this->pixelSize);
    //shader->use();
}
GraphicAttribute* PixelizationAttribute::copy()
{
    return new PixelizationAttribute();
}
void PixelizationAttribute::unbind(Shader* shader)
{
    int b = 0;
    //float ps = 0.0f;
    Shader* shaderToUse = gamedata->shaderGeneral;
    //shaderToUse->use();
    GLint pixelizationLocation = glGetUniformLocation(shaderToUse->getShaderProgram(), "pixelization");
    glUniform1i(pixelizationLocation, b);
    
    GLint pixelSizeLocation = glGetUniformLocation(shaderToUse->getShaderProgram(), "pixelSize");
    glUniform1i(pixelSizeLocation, b);
    //shaderToUse->setUniform("pixelization", &b);
    //shader->setUniform("pixelSize", &b);
    //shader->use();
}
void PixelizationAttribute::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName().c_str() << "\" , ";
    output << "\"pixelSize\" : " << this->pixelSize;
}
bool PixelizationAttribute::registerInitialState()
{
    this->initial_pixelSize = this->pixelSize;
}
bool PixelizationAttribute::recoverInitialState()
{
    this->pixelSize = this->initial_pixelSize;
}  

void PixelizationAttribute::setPixelSize(int pixelSize)
{
    this->pixelSize = pixelSize;
}

int PixelizationAttribute::getPixelSize()
{
    return this->pixelSize;
}