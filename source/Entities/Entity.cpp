#include "Entity.h"
#include <stdio.h>

Entity::Entity()
{
    this->quad = new Quad();
    this->position = glm::vec3(0.0f);
    this->scaling = glm::vec3(32.0f); //Lo hago 32 x 32
    this->rotation = glm::vec3(0.0f,0.0f,1.0f);
    this->modelMatrix = glm::mat4(1.0f);
    //Tengo que calcular la modelMatrix nueva
    this->updateModelMatrix();
}

Entity::~Entity()
{
    delete(this->quad);
    this->components.clear();//Limpio vector
}

void Entity::updateModelMatrix()
{
    this->modelMatrix = glm::mat4(1.0f);
    glm::mat4 translationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::translate(translationMatrix,this->position);
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix,0.0f,this->rotation);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::scale(scaleMatrix,this->scaling);
    this->modelMatrix =  rotationMatrix* translationMatrix*scaleMatrix*this->modelMatrix;
/*     this->scaling = glm::vec3(1.0f);
    this->rotation = glm::vec3(0.0f,0.0f,1.0f);
    this->position = glm::vec3(0.0f); */
}

void Entity::setSprite(Sprite* sprite)
{
    Sprite* a = sprite->copy(sprite);
    this->sprite = a;
}

Sprite* Entity::getSprite()
{
    return this->sprite;
}

void Entity::translate(glm::vec3 position)
{
    this->position += position;
    this->updateModelMatrix();
}

void Entity::rotate(glm::vec3 rotation)
{
    this->rotation += rotation;
    this->updateModelMatrix();
}

void Entity::scale(glm::vec3 scaling)
{
    this->scaling *= scaling;
    this->updateModelMatrix();
}

glm::mat4 Entity::getModelMatrix()
{
    return this->modelMatrix;
}

Quad* Entity::getQuad()
{
    return this->quad;
}

void Entity::onUpdate()
{
    std::vector<Component*>::iterator ptr;
    for(ptr = this->components.begin(); ptr<this->components.end(); ptr++)
    {
        (*(ptr))->onUpdate();
    }
}

void Entity::render(Shader* shader, double deltaTime)
{
    /* if(this->script != NULL)
        this->script->onUpdate(); */
    
    glBindVertexArray(this->getQuad()->getVAO());
    shader->setUniform("model",glm::value_ptr(this->modelMatrix));
/*     float transparency = this->sprite->getTransparency();
    shader->setUniform("transparency",&transparency); */
    std::vector<GraphicAttribute*>::iterator ptr;
    for(ptr = this->attributes.begin(); ptr<this->attributes.end(); ptr++)
    {
        (*(ptr))->passToShader(shader,deltaTime);
    }
    //glBindTexture(GL_TEXTURE_2D, this->sprite->getSpriteImage(this->sprite->getCurrentSprite(deltaTime)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    for(ptr = this->attributes.begin(); ptr<this->attributes.end(); ptr++)
    {
        (*(ptr))->unbind(shader);
    }
}

void Entity::addComponent(Component* component)
{
    this->components.push_back(component);
}

Component* Entity::getComponent(int index)
{
    if(index >= this->components.capacity())
        return NULL;
    return this->components.at(index);
}

GraphicAttribute* Entity::getAttribute(int index)
{
    if(index >= this->attributes.capacity())
        return NULL;
    return this->attributes.at(index);
}
void Entity::addAttribute(GraphicAttribute* attribute)
{
    GraphicAttribute* a = attribute->copy();
    this->attributes.push_back(a);
}

void Entity::setPosition(glm::vec3 position)
{
    this->position = position;
    this->modelMatrix = glm::mat4();
    updateModelMatrix();
}

void Entity::setRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
    this->modelMatrix = glm::mat4();
    updateModelMatrix();
}

void Entity::setScale(glm::vec3 scaling)
{
    this->scaling = scaling;
    this->modelMatrix = glm::mat4();
    updateModelMatrix();
}

glm::vec3 Entity::getPosition()
{
    return this->position;
}

glm::vec3 Entity::getRotation()
{
    return this->rotation;
}

glm::vec3 Entity::getScale()
{
    return this->scaling;
}