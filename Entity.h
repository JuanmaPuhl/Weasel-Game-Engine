#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Quad.h"
#include "Sprite.h"
class Entity
{
    public:
    Entity();
    ~Entity();
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);
    void setSprite(Sprite* sprite);
    Sprite* getSprite();
    glm::mat4 getModelMatrix();
    Quad* getQuad();
    void onUpdate();
    private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;
    Quad* quad;
    glm::mat4 modelMatrix;
    Sprite* sprite = NULL;
    void updateModelMatrix();
};