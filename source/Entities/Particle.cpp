#include "Particle.h"

Particle::Particle()
{
    this->life = 0.0f;
}

Particle::~Particle()
{

}

void Particle::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Particle::setSpeed(glm::vec3 speed)
{
    this->speed = speed;
}

void Particle::setColor(glm::vec4 color)
{
    this->color = color;
}

void Particle::setLife(float life)
{
    this->life = life;
}

glm::vec3 Particle::getPosition()
{
    return this->position;
}

glm::vec3 Particle::getSpeed()
{
    return this->speed;
}

glm::vec4 Particle::getColor()
{
    return this->color;
}

float Particle::getLife()
{
    return this->life;
}
