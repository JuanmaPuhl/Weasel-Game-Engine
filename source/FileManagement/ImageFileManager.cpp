#include "ImageFileManager.h"
Image* imageFileManager::loadImage(const char* dir)
{
    Image* img = (Image*)malloc(sizeof(Image));
    img->dir = dir;

    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(img->dir, &img->width, &img->height, &img->nr_channels, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenTextures(1, &img->image);  
    
    glBindTexture(GL_TEXTURE_2D, img->image);  
    if (data)
    {   
        if(img->nr_channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if(img->nr_channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {   
        #if defined(DEBUG)
            printf("No se pudo cargar la textura %s.\n",dir);
        #endif
    }
    stbi_image_free(data);
    return img;
}