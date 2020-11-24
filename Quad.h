#ifndef QUAD_H
#define QUAD_H
#include <stdlib.h>
class Quad
{
    public:
        Quad();
        ~Quad();
        unsigned int getVAO();
        unsigned int getVBO();
        unsigned int getEBO();
    private:
        float vertices[12] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int indices[6] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
        }; 
};
#endif