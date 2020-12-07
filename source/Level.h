#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Entity.h"
#include "OrtographicCamera.h"

class Level
{
    public:
    Level();
    ~Level();
    void render();
    void addEntity(Entity* entity);
    /**
     * @brief Actualiza todas las entidades del nivel
     * 
     */
    void onUpdate();
    void setCamera(OrtographicCamera* camera);
    private:
    std::vector<Entity*> entities;
    OrtographicCamera* camera;
};


#endif