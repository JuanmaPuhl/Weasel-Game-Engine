#ifndef ORTOGRAPHIC_CAMERA_H
#define ORTOGRAPHIC_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class OrtographicCamera
{
    public:
    /**
     * @brief Construct a new Ortographic Camera object
     * 
     * @param width 
     * @param height 
     */
    OrtographicCamera(int width, int height);
    /**
     * @brief Destroy the Ortographic Camera object
     * 
     */
    ~OrtographicCamera();
    /**
     * @brief Get the View Matrix object
     * 
     * @return glm::mat4 
     */
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
    private:
    glm::vec3 position;
    glm::vec3 direction;
    float velocity = 50.0f;
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
    int movementDirection = 0;
    glm::mat4 viewMatrix;
};
#endif