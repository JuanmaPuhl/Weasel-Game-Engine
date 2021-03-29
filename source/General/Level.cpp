#include "Level.h"
#include "../Entities/ComponentCamera.h"
#include "../Entities/PixelizationAttribute.h"
#include "../Entities/Sharpen.h"
#include "../Entities/DilationAttribute.h"

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

void Level::createAllScripts()
{
    for(Entity* e : this->entities)
    {
        e->createScript();
    }
}
void Level::setGammaCorrection(bool b)
{
    this->gammaCorrection = b;
}
bool Level::getGammaCorrection()
{
    return this->gammaCorrection;
}

void Level::loadProject(nlohmann::json level)
{
    //Tengo que cargar la cámara
    nlohmann::json camera = level["camera"];
    /* int width = camera["width"];
    int height = camera["height"]; */
    Entity* entity_camera = Level::addEntityCamera(1920, 1080);
    entity_camera->loadProject(camera);
    //Tengo que cargar las entidades
    int cant_entities = level["cant_entidades"];
    nlohmann::json entities = level["entidades"];
    for(int i = 0; i < cant_entities; i++)
    {
        nlohmann::json entity = entities[i];
        Entity* e = Level::addEntity();
        e->loadProject(entity);
    }
    //Tengo que cargar los atributos
    int cant_atributos = level["cant_atributos"];
    nlohmann::json atributos = level["atributos"];
    for(int i = 0; i < cant_atributos; i++)
    {
        nlohmann::json a = atributos[i];
        std::string name = a["name"];
        if(!strcmp(name.c_str(), "pixelization"))
        {
            PixelizationAttribute* pixelization = new PixelizationAttribute();
            int pixelSize = a["pixelSize"];
            pixelization->setPixelSize(pixelSize);
            Level::addAttribute(pixelization);
        }
        if(!strcmp(name.c_str(), "sharpen"))
        {
            Sharpen* sharpen = new Sharpen();
            float amount = a["amount"];
            sharpen->setAmount(amount);
            Level::addAttribute(sharpen);
        }
        if(!strcmp(name.c_str(), "dilation"))
        {
            DilationAttribute* dilation = new DilationAttribute();
            int size = a["size"];
            float separation = a["separation"];
            float minThreshold = a["minThreshold"];
            float maxThreshold = a["maxThreshold"];
            Level::addAttribute(dilation);
        }
    }
    //Tengo que cargar el gamma correction
    std::string gamma = level["gammaCorrection"];
    bool gamma_correction = (gamma == "1");
    this->gammaCorrection = gamma_correction;
}