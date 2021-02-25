#pragma once
#include <glm/glm.hpp>

class Particle
{
    public:
    Particle();
    ~Particle();
    void setPosition(glm::vec3 position);
    void setSpeed(glm::vec3 speed);
    void setColor(glm::vec4 color);
    void setLife(float life);
    glm::vec3 getPosition();
    glm::vec3 getSpeed();
    glm::vec4 getColor();
    float getLife();

    private:
    glm::vec3 position = glm::vec3(0.0f), speed = glm::vec3(0.0f);
    glm::vec4 color = glm::vec4(0.0f);
    float life = 0.0f;
};