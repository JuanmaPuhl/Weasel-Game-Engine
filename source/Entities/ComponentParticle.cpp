#include "ComponentParticle.h"
#include "../General/Game.h"
#include <math.h> 
ComponentParticle::ComponentParticle(int maxParticles, int newParticles, Entity* generator)
{
    this->setName("particle");
    this->maxParticles = maxParticles;
    this->newparticles = newParticles;
    this->lastUsedParticle = 0;
    for(int i = 0; i < this->maxParticles; i++)
    {
        this->particles.push_back(new Particle());
    }
    this->generator = generator;
}

ComponentParticle::~ComponentParticle()
{
    this->particles.clear();
}

void ComponentParticle::onCreate()
{

}

void ComponentParticle::respawnParticle(Particle* particle, glm::vec3 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColorR = ((rand() % 100) / 100.0f);
    float rColorG = ((rand() % 100) / 100.0f);
    float rColorB =  ((rand() % 100) / 100.0f);
    particle->setPosition(this->generator->getPosition() + glm::vec3(random,random,0.0f) + glm::vec3(offset.x,offset.y,0.0f));
    particle->setColor(glm::vec4(1.0f,0.78f,0.07f,0.5f));
    particle->setLife(1.0f);
    particle->setSpeed(glm::vec3(1.0f,8.0f,1.0f));
}

int ComponentParticle::firstUnusedParticle()
{
    for(int i = this->lastUsedParticle; i < this->maxParticles; ++i)
    {
        if(this->particles.at(i)->getLife() <= 0.0f)
        {
            this->lastUsedParticle = i;
            return i;
        }
    }
    for(int i = 0; i < this->lastUsedParticle; ++i)
    {
        if(this->particles.at(i)->getLife() <= 0.0f)
        {
            this->lastUsedParticle = i;
            return i;
        }
    }
    this->lastUsedParticle = 0;
    return 0;

}

void ComponentParticle::onUpdate()
{
    //Tengo que spawnear las particulas
    for(int i = 0; i < this->newparticles; ++i)
    {
        int firstUnusedParticle = this->firstUnusedParticle();
        float x = rand()%15*pow(-1.0f,rand()%2);
        float y = rand()%30*pow(-1.0f,rand()%2)+80.0f;
        this->respawnParticle(this->particles.at(firstUnusedParticle), glm::vec3(x,y,0.0f));
    }

    for(int i = 0; i < this->maxParticles; ++i)
    {
        Particle* particle = this->particles.at(i);
        particle->setLife(particle->getLife() - Game::getDeltaTime());
        if(particle->getLife() > 0.0f)
        {
            particle->setPosition(particle->getPosition() + glm::vec3(0.0f,1.0f,0.0f)* (particle->getSpeed() * (float)Game::getDeltaTime()));
            glm::vec4 colorViejo = particle->getColor();
            if(particle->getPosition().y - this->generator->getPosition().y <= 70.0f)
                particle->setColor(glm::vec4(colorViejo.x,((colorViejo.y) - 0.1*Game::getDeltaTime()-(1.0f-particle->getLife())*0.05f) ,colorViejo.z,particle->getLife() + 0.2f) );
            else
                particle->setColor(glm::vec4(colorViejo.x,0.1f,colorViejo.z,particle->getLife()) );
            
        }
    }
}

Component* ComponentParticle::copy()
{
    ComponentParticle* cs = new ComponentParticle(this->maxParticles, this->newparticles, this->generator);
    return cs;
}

int ComponentParticle::getMaxParticles()
{
    return this->maxParticles;
}

int ComponentParticle::getNewParticles()
{
    return this->newparticles;
}

void ComponentParticle::setMaxParticles(int maxParticles)
{
    this->maxParticles = maxParticles;
}

void ComponentParticle::setNewParticles(int newParticles)
{
    this->newparticles = newParticles;
}
std::vector<Particle*> ComponentParticle::getParticles()
{
    return this->particles;
}

void ComponentParticle::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName() << "\" , ";
    output << "\"max_particles\" : " << this->maxParticles << " , ";
    output << "\"step_particles\" : " << this->newparticles;
    //Despues tienen que ir más variables, como color, velocidad, distancia, etc. Pero primero tengo que refactorizar un toque
    //El generador está claro que es la entidad actual

}


bool ComponentParticle::registerInitialState()
{
    this->initial_visibleName = this->getVisibleName().c_str();
    this->initial_maxParticles = this->maxParticles;
    this->initial_newParticles = this->newparticles;
    return true;
}
bool ComponentParticle::recoverInitialState()
{
    this->setVisibleName(this->initial_visibleName);
    this->maxParticles = this->initial_maxParticles;
    this->newparticles = this->initial_newParticles;
    this->particles.clear();
    this->lastUsedParticle = 0;
    for(int i = 0; i < this->maxParticles; i++)
    {
        this->particles.push_back(new Particle());
    }
    return true;
}

void ComponentParticle::setDirection(glm::vec3 dir)
{
    this->dir = dir;
}
glm::vec3 ComponentParticle::getDirection()
{
    return this->dir;
}
glm::vec4 ComponentParticle::getColor()
{
    return this->color;
}
void ComponentParticle::setColor(glm::vec4 color)
{
    this->color = color;
}

void ComponentParticle::setLifetime(float life)
{
    this->max_life = life;
}
float ComponentParticle::getLifetime()
{
    return this->max_life;
}