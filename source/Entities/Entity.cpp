#include "Entity.h"
#include <stdio.h>
#include "LuaScriptComponent.h"
#include "../General/Game.h"
#include "ComponentCamera.h"
#include "ComponentParticle.h"
#include "Particle.h"
#include "../Entities/ComponentCollisionBox.h"
#include "irrklang/include/irrKlang.h"
#include "../Entities/ComponentMusic.h"
#include "../Entities/LuaScriptComponent.h"
#include "../Graphics/Sprite.h"
#include <iomanip>
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
    
    
    ComponentCollisionBox* cb = (ComponentCollisionBox*) this->getComponent("collider");
    //glBindTexture(GL_TEXTURE_2D, this->sprite->getSpriteImage(this->sprite->getCurrentSprite(deltaTime)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    if(cb != NULL)
    {
        float xb = cb->getX();
        float yb = cb->getY();
        float wb = cb->getWidth();
        float hb = cb->getHeight();
        glm::vec3 original_scale = this->getScale();
        glm::vec3 new_scale = glm::vec3(wb,hb,1.0);
        this->scaling = new_scale;
        this->updateModelMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        shader->setUniform("color",glm::value_ptr(glm::vec4(235.0/255.0,183.0/255.0,52.0/255.0,0.5)));
        shader->setUniform("model",glm::value_ptr(this->modelMatrix));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        shader->setUniform("color",glm::value_ptr(glm::vec4(0.0,0.0,0.0,0.0)));
        this->scaling = original_scale;
        this->updateModelMatrix();
    }
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
    std::string newName = "";
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
    int i = getCantAttributesSameType(attribute->getName());
    if(i == 0)
    {
        GraphicAttribute* a = attribute->copy();
        this->attributes.push_back(a);
    }
    
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

std::vector<GraphicAttribute*> Entity::getAllAttributes()
{
    return this->attributes;
}

std::vector<Component*> Entity::getAllComponents()
{
    return this->components;
}

int Entity::getCantComponentsSameType(std::string type)
{
    int i = 0;
    for(Component* c : this->getAllComponents())
    {
        if(c != NULL && !strcmp(type.c_str(),c->getName().c_str()))
        {
            i++;
        }
    }
    return i;
}

int Entity::getCantAttributesSameType(std::string type)
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

void Entity::save(std::ofstream& output)
{
    //El quad se hace solo sin problemas
    output << "\"position\" : {" << "\"x\" : " << this->position.x << " , \"y\" : " << this->position.y << " , \"z\" : " << this->position.z << "} , ";
    output << "\"scaling\" : {" << "\"x\" : " << this->scaling.x << " , \"y\" : " << this->scaling.y << " , \"z\" : " << this->scaling.z << "} , ";
    output << "\"rotation\" : {" << "\"x\" : " << this->rotation.x << " , \"y\" : " << this->rotation.y << " , \"z\" : " << this->rotation.z << "} , ";
    //La model matrix se va a actualizar sola
    output << "\"name\" : \"" << this->name.c_str() << "\" , ";
    //Ahora guardo los componentes
    output << "\"cant_componentes\" : " << this->components.size() << " , ";
    output << "\"componentes\" : [";
    int cmp_index = 0;
    for(Component* cmp : this->components)
    {
        output << "{";
        cmp->save(output);
        output << "}";
        if(cmp_index + 1 < this->components.size())
            output << " , ";
        cmp_index++; 
    }
    output << "] , ";
    //Ahora guardo los atributos
    output << "\"cant_atributos\" : " << this->attributes.size() << " , ";
    output << "\"atributos\": [";
    int attr_index = 0;
    for(GraphicAttribute* attr : this->attributes)
    {
        output <<  "{";
        attr->save(output);
        output << "}";
        if(attr_index + 1 < this->attributes.size())
            output << " , ";
        attr_index++; 
    }
    output << "]";
}

bool Entity::registerInitialState()
{
    this->initial_position = this->position;
    this->initial_rotation = this->rotation;
    this->initial_scaling = this->scaling;
    this->initial_name = this->name;
    this->initial_components.clear();
    for(Component* c : this->components)
    {
        c->registerInitialState();
        this->initial_components.push_back(c);    
    }
    this->initial_attributes.clear();
    for(GraphicAttribute* a : this->attributes)
    {
        a->registerInitialState();
        this->initial_attributes.push_back(a);
    }
    return true;
}

bool Entity::recoverInitialState()
{
    this->setPosition(this->initial_position);
    this->setRotation(this->initial_rotation);
    this->setScale(this->initial_scaling);
    this->setName(this->initial_name);
    this->components.clear();
    for(Component* c : this->initial_components)
    {
        c->recoverInitialState();
        this->components.push_back(c);
    }
    this->attributes.clear();
    for(GraphicAttribute* a : this->initial_attributes)
    {
        a->recoverInitialState();
        this->attributes.push_back(a);
    }
    return true;
}

void Entity::loadProject(nlohmann::json entity)
{
    //Tengo que setear el nombre
    std::string name = entity["name"];
    if(name.c_str()!=NULL)
        this->setName(name.c_str());
    nlohmann::json position = entity["position"];
    glm::vec3 pos = glm::vec3(position["x"],position["y"],position["z"]);
    this->setPosition(pos);
    nlohmann::json rotation = entity["rotation"];
    glm::vec3 rot = glm::vec3(rotation["x"],rotation["y"],rotation["z"]);
    this->setRotation(rot);
    nlohmann::json scaling = entity["scaling"];
    glm::vec3 sca = glm::vec3(scaling["x"],scaling["y"],scaling["z"]);
    this->setScale(sca);
    //Tengo que meter los componentes
    int cant_componentes = entity["cant_componentes"];
    nlohmann::json componentes = entity["componentes"];
    for(int i = 0; i < cant_componentes; i++)
    {
        nlohmann::json cmp = componentes[i];
        std::string name = cmp["name"];
        if(!strcmp(name.c_str(),"camera"))
        {
            std::string visible_name = cmp["visible_name"];
            nlohmann::json c_pos = cmp["position"];
            glm::vec3 c_position = glm::vec3(c_pos["x"],c_pos["y"],c_pos["z"]);
            float zoom = cmp["zoom"];
            //Si estoy cargando una cámara entonces la unica posibilidad es que sea la camara del nivel
            //Yo ya le asigno la cámara cuando creo la entidad, entonces la busco nomas
            ComponentCamera* cam = (ComponentCamera*) this->getComponent("camera");
            //El width y el height ya lo tiene metido.
            cam->setPosition(c_position);
            cam->zoom(zoom);
            cam->setVisibleName(visible_name);
        }
        if(!strcmp(name.c_str(),"collider"))
        {
            std::string visible_name = cmp["visible_name"];
            int width = cmp["width"];
            int height = cmp["height"];
            int x = cmp["x"];
            int y = cmp["y"];
            //Si estoy cargando una cámara entonces la unica posibilidad es que sea la camara del nivel
            //Yo ya le asigno la cámara cuando creo la entidad, entonces la busco nomas
            ComponentCollisionBox* box = new ComponentCollisionBox(x,y,width,height,this);
            box->setVisibleName(visible_name);
            this->addComponent(box);
        }
        if(!strcmp(name.c_str(),"music"))
        {
            std::string visible_name = cmp["visible_name"];
            std::string track = cmp["track"];
            std::string loop_str = cmp["loop"];
            std::string start_str = cmp["start"];
            bool loop = (loop_str == "1");
            bool start = (start_str == "1");
            //Si estoy cargando una cámara entonces la unica posibilidad es que sea la camara del nivel
            //Yo ya le asigno la cámara cuando creo la entidad, entonces la busco nomas
            ComponentMusic* mus = new ComponentMusic(irrklang::createIrrKlangDevice());
            mus->setVisibleName(visible_name);
            mus->setMusic(track);
            mus->setLoop(loop);
            mus->setPlaying(start);
            this->addComponent(mus);
        }
        if(!strcmp(name.c_str(),"particle"))
        {
            std::string visible_name = cmp["visible_name"];
            int max_particles = cmp["max_particles"];
            int step_particles = cmp["step_particles"];
            //Si estoy cargando una cámara entonces la unica posibilidad es que sea la camara del nivel
            //Yo ya le asigno la cámara cuando creo la entidad, entonces la busco nomas
            ComponentParticle* mus = new ComponentParticle(max_particles,step_particles,this);
            mus->setVisibleName(visible_name);
            this->addComponent(mus);
        }
        if(!strcmp(name.c_str(),"lua_script"))
        {
            
            std::string visible_name = cmp["visible_name"];
            std::string script = cmp["script"];
            //Si estoy cargando una cámara entonces la unica posibilidad es que sea la camara del nivel
            //Yo ya le asigno la cámara cuando creo la entidad, entonces la busco nomas
            LuaScriptComponent* mus = new LuaScriptComponent(script, Game::getLuaState());
            mus->setVisibleName(visible_name); 
            this->addComponent(mus);
        }
    }
    //Tengo que meter los atributos
    int cant_atributos = entity["cant_atributos"];
    nlohmann::json atributos = entity["atributos"];
    for(int i = 0; i < cant_atributos; i++)
    {   
        nlohmann::json attr = atributos[i];
        std::string name = attr["name"];
        if(!strcmp(name.c_str(),"sprite"))
        {
            std::string spr = attr["sprite"];
            Sprite* s = Game::findSpriteByName(spr);
            if(s!=NULL)
            {
                SpriteAttribute* sprAttr = new SpriteAttribute(s);
                this->addAttribute(sprAttr);
            }
                
        }
        if(!strcmp(name.c_str(),"color"))
        {
            nlohmann::json color = attr["color"];
            glm::vec4 colorcito ;
            float alpha = color["a"];
            colorcito = glm::vec4(color["x"],color["y"],color["z"],alpha);
            ColorAttribute* colAttr = new ColorAttribute(colorcito);
            
            this->addAttribute(colAttr);
        }
    }
}