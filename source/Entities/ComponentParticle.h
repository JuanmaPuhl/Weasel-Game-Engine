#pragma once
#include "Component.h"
#include "Particle.h"
#include <vector>
#include "Entity.h"

class ComponentParticle : public Component
{
    public:
    ComponentParticle(int maxParticles, int newParticles, Entity* generator);
    ~ComponentParticle();
    void onCreate();
    void onUpdate();
    Component* copy();
    int getMaxParticles();
    int getNewParticles();
    void setNewParticles(int newParticles);
    void setMaxParticles(int maxParticles);
    std::vector<Particle*> getParticles();
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    void setDirection(glm::vec3 dir);
    glm::vec3 getDirection();
    glm::vec4 getColor();
    void setColor(glm::vec4 color);
    void setLifetime(float life);
    float getLifetime();
    void setSpeed(glm::vec3 speed);
    glm::vec3 getSpeed();
    private:
    int firstUnusedParticle();
    void respawnParticle(Particle* particle, glm::vec3 offset);

    std::vector<Particle*> particles;
    int maxParticles, newparticles;
    glm::vec3 dir = glm::vec3(0.0f,1.0f,0.0f),initial_dir,speed = glm::vec3(1.0f,8.0f,1.0f), initial_speed;
    glm::vec4 color = glm::vec4(1.0f,0.78f,0.07f,0.5f),initial_color;
    float max_life = 1.0f, initial_max_life;
    int lastUsedParticle = 0;
    Entity* generator;
    std::string initial_visibleName;
    int initial_maxParticles, initial_newParticles;

};