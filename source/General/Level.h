#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "../Entities/Entity.h"
#include "../Graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>

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
    std::vector<Entity*> getEntities();
    /**
     * @brief Actualiza todas las entidades del nivel
     * 
     */
    void onUpdate(double deltaTime);
    private:
    std::vector<Entity*> entities;
    Entity* cameraEntity;
};


#endif