#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Quad.h"
#include "Animation.h"
#include "ScriptComponent.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Config.h"

class Entity
{
    public:
    Entity();
    ~Entity();
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);
    void setSprite(Animation* sprite);
    void setScript(ScriptComponent* script);
    ScriptComponent* getScript();
    Animation* getAnimation();
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
    Animation* sprite = NULL;
    ScriptComponent* script;
    void updateModelMatrix();
};