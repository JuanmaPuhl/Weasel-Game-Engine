#ifndef ORTOGRAPHIC_CAMERA_H
#define ORTOGRAPHIC_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class OrtographicCamera
{
    public:
    OrtographicCamera(int width, int height);
    ~OrtographicCamera();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void update();
    private:
    glm::vec3 position;
    glm::vec3 direction;
    float velocity = 50.0f;
    glm::vec3 cameraTarget;
    float zoom = 1.0f;
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