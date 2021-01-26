#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "../FileManagement/ImageFileManager.h"
class Sprite
{
    public:
    Sprite(const char** dir, int size, std::string name);
    Sprite(std::vector<unsigned int> arr, int size, std::string name);
    ~Sprite();
    unsigned int getSpriteImage(int index);
    /**
     * @brief Obtiene el indice del sprite actual, actualizando el contador interno
     * 
     * @param deltaTime 
     * @return int 
     */
    int getCurrentSprite(float deltaTime);
    int getCurrentSpriteIndex();
    void setSpeed(double speed);
    int getSize();
    std::vector<unsigned int> getImages();
    float getTransparency();
    void setTransparency(float transparency);
    bool removeImage(int i);
    Sprite* copy(Sprite* sprite);
    double getSpeed();
    std::string getName();
    private:
    std::string name;
    double speed = 0.0;
    int size;
    double index_aux = 0.0;
    std::vector<unsigned int> spriteImage;
    float transparency = 1.0f;
};
#endif