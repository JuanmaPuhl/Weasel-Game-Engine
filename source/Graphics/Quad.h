#ifndef QUAD_H
#define QUAD_H
#include <stdlib.h>
class Quad
{
    public:
        /**
         * @brief Construct a new Quad:: Quad object
         * 
         */
        Quad();
        /**
         * @brief Destroy the Quad object
         * 
         */
        ~Quad();
        /**
         * @brief obtener el VAO del quad
         * 
         * @return unsigned int el VAO
         */
        unsigned int getVAO();
        /**
         * @brief obtener el VBO del quad
         * 
         * @return unsigned int el VBO
         */
        unsigned int getVBO();
        /**
         * @brief obtener el EBO del quad
         * 
         * @return unsigned int el EBO
         */
        unsigned int getEBO();
    private:
        float vertices[32] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };
        unsigned int VBO, VAO, EBO;
        unsigned int indices[6] = 
        {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        }; 

};
#endif