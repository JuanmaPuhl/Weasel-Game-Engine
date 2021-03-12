#include "Level.h"
#include "../Entities/ComponentCamera.h"
Level::Level()
{
    //Asigno espacio para el estado inicial
    
}

Level::~Level()
{   
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        delete((*(ptr)));
    }
}

Entity* Level::addEntity()
{
    Entity* entity = new Entity();
    this->entities.push_back(entity);
    return entity;
}

Entity* Level::addEntityCamera(int width, int height)
{
    Entity* entity = new Entity();
    entity->addComponent(new ComponentCamera(width,height));
    this->cameraEntity = entity;
    this->cameraEntity->onUpdate();
    return entity;
}

void Level::onUpdate(double deltaTime)
{
    if(this->cameraEntity !=NULL)
        this->cameraEntity->onUpdate();
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->onUpdate();
    }
}

void Level::render(Shader* shader, double deltaTime)
{
    //Tengo que pasar la camara al shader
    
    shader->use();
    if(this->cameraEntity!=NULL)
    {
        shader->setUniform("projection",glm::value_ptr(((ComponentCamera*)(this->cameraEntity->getComponent("camera")))->getProjectionMatrix()));
        shader->setUniform("view",glm::value_ptr(((ComponentCamera*)(this->cameraEntity->getComponent("camera")))->getViewMatrix()));
    }
    //Tengo que ciclar entre todas las entidades y renderizarlas
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->render(shader,deltaTime);
    }
}

std::vector<Entity*> Level::getEntities()
{
    return this->entities;
}

bool Level::removeEntity(int entity)
{
    if(entity < this->entities.size())
    {
        this->entities.erase(this->entities.begin()+entity);
        return true;
    }
    return false;
}

Entity* Level::getCamera()
{
    return this->cameraEntity;
}

void Level::save(std::ofstream& output)
{
    //Tengo que imprimir los datos de la entidad camara
    output << "\"camera\" : {";
    this->cameraEntity->save(output);
    output << "} , ";
    output << "\"gammaCorrection\" : \"" << this->gammaCorrection << "\" , ";
    output << "\"cant_entidades\" : " << this->entities.size() << " , ";
    output << "\"entidades\" : [";
    //Ahora imprimo todas las entidades restantes
    int ent_index = 0;
    for(Entity* e : this->entities)
    {
        output << "{";
        e->save(output);
        output << "}";
        if(ent_index + 1 < this->entities.size())
            output << " , ";
        ent_index++;
    }
    output << "],";
    //Ahora guardo los atributos
    output << "\"cant_atributos\" : " << this->attributes.size() << " , ";
    output << "\"atributos\" : [";
    int attr_index = 0;
    for(GraphicAttribute* e : this->attributes)
    {
        output << "{";
        e->save(output);
        output << "}";
        if(attr_index + 1 < this->attributes.size())
            output << " , ";
        attr_index++;
    }
    output << "]";
}

bool Level::registerInitialState()
{
    //Primero tengo que agarrar todas las entidades y agregarlas al estado inicial
    this->initial_entities.clear();
    for(Entity* e : this->entities)
    {
        e->registerInitialState();
        this->initial_entities.push_back(e);
    } 
    for(GraphicAttribute* e : this->attributes)
    {
        e->registerInitialState();
        this->initial_attributes.push_back(e);
    } 
    this->cameraEntity->registerInitialState();
    this->initial_cameraEntity = this->cameraEntity;
    return true;
}

bool Level::recoverInitialState()
{
    this->entities.clear();
    for(Entity* e : this->initial_entities)
    {
        e->recoverInitialState();
        this->entities.push_back(e);
    }
    for(GraphicAttribute* e : this->initial_attributes)
    {
        e->recoverInitialState();
        this->attributes.push_back(e);
    } 
    this->cameraEntity = NULL;
    this->initial_cameraEntity->recoverInitialState();
    this->cameraEntity = this->initial_cameraEntity;
}

std::vector<GraphicAttribute*> Level::getAttributes()
{
    return this->attributes;
}

void Level::addAttribute(GraphicAttribute* attr)
{
    if(getCantAttributesSameType(attr->getName().c_str()) == 0)
        this->attributes.push_back(attr);
}

void Level::removeAttribute(std::string name)
{
    for(int i = 0; i < this->attributes.size(); i++)
    {
        if(strcmp(name.c_str(),this->attributes.at(i)->getName().c_str()) == 0)
        {
            this->attributes.erase(this->attributes.begin()+i);
        }
    }
}

int Level::getCantAttributesSameType(std::string type)
{
    int i = 0;
    for(GraphicAttribute* c : this->attributes)
    {
        if(c != NULL && !strcmp(type.c_str(),c->getName().c_str()))
        {
            i++;
        }
    }
    return i;
}


void Level::setGammaCorrection(bool b)
{
    this->gammaCorrection = b;
}
bool Level::getGammaCorrection()
{
    return this->gammaCorrection;
}