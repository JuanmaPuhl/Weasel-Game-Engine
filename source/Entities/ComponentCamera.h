#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
class ComponentCamera : public Component
{
    public:
        ComponentCamera(int width, int height);
        ~ComponentCamera();
        void onCreate();
        void onUpdate();
        glm::mat4 getViewMatrix();
        /**
         * @brief Get the Projection Matrix object
         * 
         * @return glm::mat4 
         */
        glm::mat4 getProjectionMatrix();
        /**
         * @brief actualiza la información de la cámara
         * 
         */
        void update(float deltaTime);
        void zoom(float factor);
        void move(glm::vec2 dir);
        Component* copy();
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float velocity = 32.0f*5;
        glm::vec3 cameraTarget;
        float zoomValue = 1.0f;
        glm::vec3 front;
        int height;
        glm::vec3 up;
        int width;
        glm::vec3 cameraRight;
        int zoomOrder = 0;
        glm::vec3 cameraUp;
        float zoomVelocity = 1.0f;
        glm::mat4 projectionMatrix;
        glm::vec2 movementDirection = glm::vec2(0.0f);
        glm::mat4 viewMatrix;

};