#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/OrtographicCamera.h"
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
    void addEntity(Entity* entity);
    /**
     * @brief Actualiza todas las entidades del nivel
     * 
     */
    void onUpdate(double deltaTime);
    /**
     * @brief Set the Camera object
     * 
     * @param camera la camara a setear
     */
    void setCamera(OrtographicCamera* camera);
    private:
    std::vector<Entity*> entities;
    OrtographicCamera* camera;
};


#endif