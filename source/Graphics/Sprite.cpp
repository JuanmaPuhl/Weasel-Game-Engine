#include "Sprite.h"
#include <string.h>
#include <string>
Sprite::Sprite(const char** dir,int size, std::string name)
{
    this->size = size;
    this->name = name;
    this->listImages.reserve(20);
    //this->spriteImage = loadImage(dir,mode);
    for(int i = 0; i < size; i++)
    {
        std::string aux = dir[i];
        Image* img = imageFileManager::loadImage(aux.c_str());
        
        this->spriteImage.push_back( img);
        char c[256];
        strcpy(c,aux.c_str());
        this->listImages.push_back(c);
    }
}
    
Sprite::Sprite(std::vector<Image*> arr, int size, std::string name)
{
    this->spriteImage = arr;
    this->size = size;
    this->name = name;
}

Sprite::Sprite()
{
    this->size = 0;
    this->name = "";
}

Sprite::~Sprite()
{
    this->spriteImage.clear();
}

unsigned int Sprite::getSpriteImage(int index)
{
    if(index > -1 && index < spriteImage.size())
        return this->spriteImage[index]->image;
    else 
        return -1;
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
void Sprite::restart()
{
    this->index_aux = 0;
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
    if(i > this->spriteImage.size() || i < 0 || this->spriteImage.size() == 0)
        return false;
    this->spriteImage.erase(this->spriteImage.begin() + (i));
    this->listImages.erase(this->listImages.begin() + (i));
    this->size--;
    return true;
}

Image* Sprite::getProperties(int i)
{
    return this->spriteImage.at(i);
}

bool Sprite::addImage(const char* dir)
{
    std::string aux = dir;
    aux = sReplaceAll(aux,"\\","/");
    //std::replace(aux.begin(), aux.end(), '\\', '/'); // replace all 'x' to 'y'
    this->spriteImage.push_back( imageFileManager::loadImage(aux.c_str())) ;
    this->listImages.push_back(aux);
    this->size++;
    return true;
}

void Sprite::setName(std::string name)
{
    this->name = name;
}

void Sprite::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->name.c_str() << "\" , ";
    output << "\"speed\" : " << this->speed << " , ";
    output << "\"transparency\" : " << this->transparency << " , ";
    output << "\"cant_imagenes\" : " << this->size << " , ";
    //Ahora tengo que guardar las imagenes
    output << "\"imagenes\" : [";
    int img_index = 0;
    for(int i = 0; i < this->listImages.size(); i++)
    {
        char c[256];
        strcpy(c,this->listImages.at(i).c_str());
        output << " \"" << this->listImages.at(i) << "\"";
        if(img_index + 1 < this->listImages.size())
            output << " , ";
        img_index++;
    }
    output << " ] ";


}

bool Sprite::registerInitialState()
{
    this->initial_index_aux = this->index_aux;
    this->initial_transparency = this->transparency;
    this->initial_speed = this->speed;
    this->initial_name = this->name;
    return true;
}
bool Sprite::recoverInitialState()
{
    this->index_aux = this->initial_index_aux;
    this->transparency = this->initial_transparency;
    this->speed = this->initial_speed;
    this->name = this->initial_name;
    return true;
}

std::string& Sprite::sReplaceAll(std::string& sS, 
                         const std::string& sWhat, 
                         const std::string& sReplacement)
{
    size_t pos = 0, fpos;
    while ((fpos = sS.find(sWhat, pos)) != std::string::npos)
    {
        sS.replace(fpos, sWhat.size(), sReplacement);
        pos = fpos + sReplacement.size();
    }
    return sS;
}