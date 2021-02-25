#include "ComponentParticle.h"
#include "../General/Game.h"
#include <math.h> 
ComponentParticle::ComponentParticle(int maxParticles, int newParticles, Entity* generator)
{
    this->setName("particle");
    this->maxParticles = maxParticles;
    this->newparticles = newParticles;
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
    particle->setColor(glm::vec4(rColorR,rColorG,rColorB,1.0f));
    particle->setLife(0.5f);
    particle->setSpeed(particle->getSpeed()*0.1f);
}

int ComponentParticle::firstUnusedParticle()
{
    for(int i = this->lastUsedParticle; i < this->maxParticles; i++)
    {
        if(this->particles.at(i)->getLife() <= 0.0f)
        {
            this->lastUsedParticle = i;
            return i;
        }
    }
    for(int i = 0; i < this->lastUsedParticle; i++)
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
    for(int i = 0; i < this->newparticles; i++)
    {
        int firstUnusedParticle = this->firstUnusedParticle();
        float x = rand()%100*pow(-1.0f,rand()%2);
        float y = rand()%100*pow(-1.0f,rand()%2);
        this->respawnParticle(this->particles.at(firstUnusedParticle), glm::vec3(x,y,0.0f));
    }

    for(int i = 0; i < this->maxParticles; i++)
    {
        Particle* particle = this->particles.at(i);
        particle->setLife(particle->getLife() - Game::getDeltaTime());
        if(particle->getLife() > 0.0f)
        {
            particle->setPosition(particle->getPosition() - (particle->getSpeed() * (float)Game::getDeltaTime()));
            glm::vec4 colorViejo = particle->getColor();
            particle->setColor(glm::vec4(colorViejo.x,colorViejo.y,colorViejo.z,particle->getLife()*2.0f) );
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

void ComponentParticle::setMaxParticles(int maxParticles)
{
    this->maxParticles = maxParticles;
}

std::vector<Particle*> ComponentParticle::getParticles()
{
    return this->particles;
}