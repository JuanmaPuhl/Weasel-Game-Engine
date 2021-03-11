#include "Level.h"
#include "../Entities/ComponentCamera.h"
Level::Level()
{
    //Asigno espacio para el estado inicial
    this->iniState = (initialState*)malloc(sizeof(initialState));
    
}

Level::~Level()
{   
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        delete((*(ptr)));
    }
    free(this->iniState);
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
    output << "]";
}

bool Level::registerInitialState()
{
    //Primero tengo que agarrar todas las entidades y agregarlas al estado inicial
    this->initial_entities.clear();
    
    printf("Capacidad: %d\n", this->initial_entities.capacity());
     for(Entity* e : this->entities)
    {
        e->registerInitialState();
        this->initial_entities.push_back(e);
    } 
    this->cameraEntity->registerInitialState();
    this->iniState->initial_cameraEntity = this->cameraEntity;
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
    this->cameraEntity = NULL;
    //this->iniState->initial_cameraEntity->recoverInitialState();
    this->cameraEntity = this->iniState->initial_cameraEntity;
}