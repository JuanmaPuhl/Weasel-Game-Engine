#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Graphics/Quad.h"
#include "ScriptComponent.h"
#include "../Graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Config.h"
#include "../Graphics/Sprite.h"
#include "Component.h"
#include <vector>

class Entity
{
    public:
    Entity();
    ~Entity();
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);
    void setSprite(Sprite* sprite);
    void setScript(ScriptComponent* script);
    void addComponent(Component* component);
    ScriptComponent* getScript();
    Sprite* getSprite();
    glm::mat4 getModelMatrix();
    Quad* getQuad();
    //TODO Deberian ejecutarse los updates de todos los componentes de la entidad.
    void onUpdate();
    //TODO Implementar el render
    void render(Shader* shader,double deltaTime);
    private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;
    Quad* quad;
    glm::mat4 modelMatrix;
    Sprite* sprite = NULL;
    ScriptComponent* script = NULL;
    void updateModelMatrix();
    std::vector<Component*> components;
};