#include "Sharpen.h"

Sharpen::Sharpen()
{
    this->setName("sharpen");
}
Sharpen::~Sharpen()
{

}
void Sharpen::passToShader(Shader* shader,double deltaTime)
{
    int b = 1;
    //Shader* shaderToUse = gamedata->shaderGeneral;
    //shaderToUse->use();
    //shaderToUse->setUniform("pixelization", &b);
    GLint sharpenLocation = glGetUniformLocation(shader->getShaderProgram(), "sharpen");
    glUniform1i(sharpenLocation, b);

   /*  GLint amountLocation = glGetUniformLocation(shader->getShaderProgram(), "amount");
    glUniform1i(amountLocation, this->amount); */
    shader->setUniform("amount",&(this->amount));
}
GraphicAttribute* Sharpen::copy()
{
    Sharpen* s = new Sharpen();
    s->setAmount(this->amount);
    return s;
}
void Sharpen::unbind(Shader* shader)
{
    int b = 0;
    float aux = 0.0f;
    //Shader* shaderToUse = gamedata->shaderGeneral;
    //shaderToUse->use();
    //shaderToUse->setUniform("pixelization", &b);
    GLint sharpenLocation = glGetUniformLocation(shader->getShaderProgram(), "sharpen");
    glUniform1i(sharpenLocation, b);

   /*  GLint amountLocation = glGetUniformLocation(shader->getShaderProgram(), "amount");
    glUniform1i(amountLocation, this->amount); */
    shader->setUniform("amount",&aux);
}
void Sharpen::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName().c_str() << "\" , ";
    output << "\"amount\" : " << this->amount;
}
bool Sharpen::registerInitialState()
{
    this->initial_amount = this->amount;
}
bool Sharpen::recoverInitialState()
{
    this->amount = this->initial_amount;
}
void Sharpen::setAmount(float amount)
{
    this->amount = amount;
}
float Sharpen::getAmount()
{
    return this->amount;
}