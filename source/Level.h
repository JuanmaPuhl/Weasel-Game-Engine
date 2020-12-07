#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Entity.h"
#include "OrtographicCamera.h"
#include "Shader.h"
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
    void render(Shader* shader);
    void addEntity(Entity* entity);
    /**
     * @brief Actualiza todas las entidades del nivel
     * 
     */
    void onUpdate();
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