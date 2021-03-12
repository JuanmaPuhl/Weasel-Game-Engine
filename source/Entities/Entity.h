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
#include "ColorAttribute.h"
#include <iostream>
#include <fstream>

class Entity
{
    public:
    Entity();
    ~Entity();
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);
    void addComponent(Component* component);
    void onCollision(Entity* other);
    void onUpdate();
    bool removeComponent(std::string name);
    void render(Shader* shader,double deltaTime);
    Component* getComponent(std::string name);
    std::vector<Component*> getAllComponents();
    std::vector<GraphicAttribute*> getAllAttributes();
    GraphicAttribute* getAttribute(std::string name);
    void addAttribute(GraphicAttribute* attribute);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scaling);
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    Quad* getQuad();
    void setName(std::string name);
    std::string getName();
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;
    Quad* quad;
    glm::mat4 modelMatrix;
    Sprite* sprite = NULL;
    void updateModelMatrix();
    int getCantComponentsSameType(std::string type);
    int getCantAttributesSameType(std::string type);
    std::vector<Component*> components;
    std::vector<GraphicAttribute*> attributes;
    std::string name;
    std::vector<Component*> initial_components;
    std::vector<GraphicAttribute*> initial_attributes;
    glm::vec3 initial_position = glm::vec3(0.0f);
    glm::vec3 initial_rotation = glm::vec3(0.0f);
    glm::vec3 initial_scaling = glm::vec3(0.0f);
    std::string initial_name = "";

};