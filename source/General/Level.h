#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "../Entities/Entity.h"
#include "../Graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

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
     * @brief Renderiza todas las entidades
     * 
     * @param shader shader utilizado
     * @param deltaTime Tiempo que paso entre cuadros
     */
    void render(Shader* shader, double deltaTime);
    /**
     * @brief Añade una entidad al nivel
     * 
     * @return Entity* Referencia a la entidad creada
     */
    Entity* addEntity();
    /**
     * @brief Añade una cámara al nivel
     * 
     * @param width ancho de la cámara
     * @param height alto de la cámara
     * @return Entity* referencia a la cámara
     */
    Entity* addEntityCamera(int width, int height);
    /**
     * @brief Elimina una entidad
     * 
     * @param entity indice a eliminar
     * @return true si fue exitoso
     * @return false si fallo
     */
    bool removeEntity(int entity);
    /**
     * @brief Get the Entities object
     * 
     * @return std::vector<Entity*> 
     */
    std::vector<Entity*> getEntities();
    /**
     * @brief Guarda en distintas variables el valor inicial antes de empezar a ejecutar
     * 
     * @return true 
     * @return false 
     */
    bool registerInitialState();
    /**
     * @brief Restaura los valores iniciales luego de detener el juego
     * 
     * @return true 
     * @return false 
     */
    bool recoverInitialState();
    void addAttribute(GraphicAttribute* attr);
    std::vector<GraphicAttribute*> getAttributes();
    void removeAttribute(std::string name);
    Entity* getCamera();
    void onUpdate(double deltaTime);
    void save(std::ofstream& output_dir);
    void setGammaCorrection(bool b);
    bool getGammaCorrection();
    void loadProject(nlohmann::json level);
    void createAllScripts();
    private:
    std::vector<Entity*> entities;
    Entity* cameraEntity = NULL;
    std::vector<Entity*> initial_entities;
    Entity* initial_cameraEntity;
    std::vector<GraphicAttribute*> attributes;
    std::vector<GraphicAttribute*> initial_attributes;
    int getCantAttributesSameType(std::string type);
    bool gammaCorrection = false, initial_gammaCorrection;
};


#endif