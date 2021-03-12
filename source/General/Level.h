#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "../Entities/Entity.h"
#include "../Graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

class Level
{
    public:
    /**
     * @brief Construct a new Level object
     * 
     */
    Level();
    /**
     * @brief Destroy the Level object
     * 
     */
    ~Level();
    /**
     * @brief Renderiza el nivel
     * 
     */
    void render(Shader* shader, double deltaTime);
    Entity* addEntity();
    Entity* addEntityCamera(int width, int height);
    bool removeEntity(int entity);
    std::vector<Entity*> getEntities();
    bool registerInitialState();
    bool recoverInitialState();
    void addAttribute(GraphicAttribute* attr);
    std::vector<GraphicAttribute*> getAttributes();
    Entity* getCamera();
    /**
     * @brief Actualiza todas las entidades del nivel
     * 
     */
    void onUpdate(double deltaTime);
    void save(std::ofstream& output_dir);
    
    private:
    std::vector<Entity*> entities;
    Entity* cameraEntity = NULL;
    std::vector<Entity*> initial_entities;
    struct initialState
    {
        std::vector<Entity*> initial_entities;
        Entity* initial_cameraEntity;
    };
    initialState* iniState;
    std::vector<GraphicAttribute*> attributes;

};


#endif