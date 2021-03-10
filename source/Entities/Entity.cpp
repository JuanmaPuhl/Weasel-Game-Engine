#include "Entity.h"
#include <stdio.h>
#include "LuaScriptComponent.h"
#include "../General/Game.h"
#include "ComponentCamera.h"
#include "ComponentParticle.h"
#include "Particle.h"


Entity::Entity()
{
    this->quad = new Quad();
    this->position = glm::vec3(0.0f);
    this->scaling = glm::vec3(32.0f); //Lo hago 32 x 32
    this->rotation = glm::vec3(0.0f,0.0f,1.0f);
    this->modelMatrix = glm::mat4(1.0f);
    this->name = "entity";
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

void Entity::onCollision(Entity* other)
{
    //Si tengo script llamo al metodo onTrigger
    //Sino no hago nada
    LuaScriptComponent* c = (LuaScriptComponent*)this->getComponent("lua_script");
    if(c!=NULL)
        c->onCollision(other);
}

void Entity::onUpdate()
{
    std::vector<Component*>::iterator ptr;
    for(ptr = this->components.begin(); ptr<this->components.end(); ptr++)
    {
        (*(ptr))->onUpdate();
    }
}
Quad* Entity::getQuad()
{
    return this->quad;
}
void Entity::render(Shader* shader, double deltaTime)
{
    /* if(this->script != NULL)
        this->script->onUpdate(); */
    LuaScriptComponent* ls = (LuaScriptComponent*)this->getComponent("lua_script");

    glBindVertexArray(this->quad->getVAO());
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

    ComponentParticle* cp = (ComponentParticle*)this->getComponent("particle");
    if(cp!=NULL)
    {
        
        Shader* particleShader = Game::getParticleShader();
        particleShader->use();
        
        glBindVertexArray(this->quad->getVAO());
        Entity* camera = Game::getCurrentLevel()->getCamera();
        if(camera != NULL)
        {
            particleShader->setUniform("projection",glm::value_ptr(((ComponentCamera*)(camera->getComponent("camera")))->getProjectionMatrix()));
            particleShader->setUniform("view",glm::value_ptr(((ComponentCamera*)(camera->getComponent("camera")))->getViewMatrix()));
        }
        for(Particle* particle : cp->getParticles())
        {

            if(particle->getLife()>0.0f)
            {
                particleShader->setUniform("color",glm::value_ptr(particle->getColor()));
                particleShader->setUniform("offset",glm::value_ptr(particle->getPosition()));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            
        }
        glBindVertexArray(0);
        shader->use();
        //particleShader->setUniform();
    }
    


}

void Entity::addComponent(Component* component)
{
    int i = getCantComponentsSameType(component->getName());
    std::string newName;
    if(i == 0)
        newName = component->getName();
    else
        newName = component->getName()+""+std::to_string(i);
    component->setVisibleName(newName);
    this->components.push_back(component);
}

Component* Entity::getComponent(std::string name)
{
    for(int i = 0; i < this->components.size(); i++)
    {
        if(strcmp((this->components.at(i))->getVisibleName().c_str(),name.c_str())==0)
            return this->components.at(i);
    }
    return NULL;
}

GraphicAttribute* Entity::getAttribute(std::string name)
{
    for(int i = 0; i < this->attributes.size(); i++)
    {
        if(strcmp((this->attributes.at(i))->getName().c_str(),name.c_str())==0)
            return this->attributes.at(i);
    }
    return NULL;
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

std::string Entity::getName()
{
    return this->name;
}

void Entity::setName(std::string name)
{
    this->name = name;
}

std::vector<Component*> Entity::getAllComponents()
{
    return this->components;
}

int Entity::getCantComponentsSameType(std::string type)
{
    int i = 0;
    for(Component* c : this->components)
    {
        if(c != NULL && !strcmp(type.c_str(),c->getName().c_str()))
        {
            i++;
        }
    }
    return i;
}

bool Entity::removeComponent(std::string name)
{
    for(int i = 0; i < this->components.size(); i++)
    {
        if(strcmp(name.c_str(),this->components.at(i)->getVisibleName().c_str()) == 0)
        {
            this->components.erase(this->components.begin()+i);
        }
    }
}