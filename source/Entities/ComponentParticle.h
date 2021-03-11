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
    private:
    int firstUnusedParticle();
    void respawnParticle(Particle* particle, glm::vec3 offset);
    std::vector<Particle*> particles;
    int maxParticles, newparticles;
    int lastUsedParticle = 0;
    Entity* generator;
    std::string initial_visibleName;
    int initial_maxParticles, initial_newParticles;
    struct initialState
    {
        std::string initial_visibleName;
        int initial_maxParticles, initial_newParticles;
    };
    initialState* iniState;
};