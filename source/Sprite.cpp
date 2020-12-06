#include "Sprite.h"

Sprite::Sprite(const char* dir,Mode mode)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(dir, &width, &height, &nrChannels, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenTextures(1, &this->spriteImage);  
    stbi_set_flip_vertically_on_load(true); 
    glBindTexture(GL_TEXTURE_2D, this->spriteImage);  
    if (data)
    {   
        if(mode == normal)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if(mode == transparent)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    printf("ELIMINANDO SPRITE.\n");
}

unsigned int Sprite::getSpriteImage()
{
    return this->spriteImage;
}