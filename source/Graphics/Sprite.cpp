#include "Sprite.h"


Sprite::Sprite(const char** dir,int size, std::string name)
{
    this->size = size;
    this->name = name;
    //this->spriteImage = loadImage(dir,mode);
    for(int i = 0; i < size; i++)
    {
        this->spriteImage.push_back( imageFileManager::loadImage(dir[i])) ;
    }
}
    
Sprite::Sprite(std::vector<Image*> arr, int size, std::string name)
{
    this->spriteImage = arr;
    this->size = size;
    this->name = name;
}


Sprite::~Sprite()
{
    this->spriteImage.clear();
}

unsigned int Sprite::getSpriteImage(int index)
{
    return this->spriteImage[index]->image;
}

int Sprite::getCurrentSprite(float deltaTime)
{
    this->index_aux += this->speed * (double)deltaTime;
    int aux = (int)this->index_aux;
    if(aux>=this->size)
    {
        aux = 0;
        index_aux = 0.0;
    }
    return aux;
}

int Sprite::getCurrentSpriteIndex()
{
    return (int)this->index_aux;
}

void Sprite::setSpeed(double speed)
{
    this->speed = speed;
}

Sprite* Sprite::copy(Sprite* sprite)
{
    std::vector<Image*> arr = sprite->getImages();
    int size = sprite->getSize();
    Sprite* spr = new Sprite(arr,size,sprite->getName());
    spr->setSpeed(sprite->getSpeed());
    spr->setTransparency(sprite->getTransparency());
    return spr;
}

int Sprite::getSize()
{
    return this->size;
}

std::vector<Image*> Sprite::getImages()
{
    return this->spriteImage;
}

double Sprite::getSpeed()
{
    return this->speed;
}

void Sprite::setTransparency(float transparency)
{
    this->transparency = transparency;
}

float Sprite::getTransparency()
{
    return this->transparency;
}

std::string Sprite::getName()
{
    return this->name;
}

bool Sprite::removeImage(int i)
{
    if(i > this->spriteImage.size() || i < 0)
        return false;
    printf("I: %d\n",i);
    this->spriteImage.erase(this->spriteImage.begin() + (i));
    this->size--;
    return true;
}

Image* Sprite::getProperties(int i)
{
    return this->spriteImage.at(i);
}