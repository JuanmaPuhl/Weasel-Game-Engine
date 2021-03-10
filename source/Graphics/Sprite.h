#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "../FileManagement/ImageFileManager.h"
#include <iostream>
#include <fstream>
class Sprite
{
    public:
    Sprite(const char** dir, int size, std::string name);
    Sprite(std::vector<Image*> arr, int size, std::string name);
    Sprite();
    ~Sprite();
    unsigned int getSpriteImage(int index);
    /**
     * @brief Obtiene el indice del sprite actual, actualizando el contador interno
     * 
     * @param deltaTime 
     * @return int 
     */
    bool addImage(const char* dir);
    int getCurrentSprite(float deltaTime);
    int getCurrentSpriteIndex();
    void setSpeed(double speed);
    int getSize();
    Image* getProperties(int i);
    std::vector<Image*> getImages();
    float getTransparency();
    void setTransparency(float transparency);
    bool removeImage(int i);
    Sprite* copy(Sprite* sprite);
    double getSpeed();
    void save(std::ofstream& output);
    std::string getName();
    void setName(std::string name);
    private:
    std::string name;
    double speed = 0.0;
    int size;
    double index_aux = 0.0;
    std::vector<Image*> spriteImage;
    float transparency = 1.0f;
};
#endif