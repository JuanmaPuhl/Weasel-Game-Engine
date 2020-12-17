#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Graphics/Quad.h"
#include "../Graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Config.h"
#include "../Graphics/Sprite.h"
#include "Component.h"
#include <vector>
#include "GraphicAttribute.h"
#include "SpriteAttribute.h"

class Entity
{
    public:
    Entity();
    ~Entity();
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);
    void setSprite(Sprite* sprite);
    void addComponent(Component* component);
    Sprite* getSprite();
    glm::mat4 getModelMatrix();
    Quad* getQuad();
    void onUpdate();
    void render(Shader* shader,double deltaTime);
    Component* getComponent(int index);
    GraphicAttribute* getAttribute(int index);
    void addAttribute(GraphicAttribute* attribute);
    private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;
    Quad* quad;
    glm::mat4 modelMatrix;
    Sprite* sprite = NULL;
    void updateModelMatrix();
    std::vector<Component*> components;
    std::vector<GraphicAttribute*> attributes;
};