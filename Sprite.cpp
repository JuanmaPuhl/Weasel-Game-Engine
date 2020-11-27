#include "Sprite.h"
Sprite::Sprite(const char* dir)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(dir, &width, &height, &nrChannels, 0);
    
    glGenTextures(1, &this->spriteImage);  
    glBindTexture(GL_TEXTURE_2D, this->spriteImage);  
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {   
        #if defined(DEBUG)
            printf("No se pudo cargar la textura.\n");
        #endif
    }
    stbi_image_free(data);
}

Sprite::~Sprite()
{

}

unsigned int Sprite::getSpriteImage()
{
    return this->spriteImage;
}