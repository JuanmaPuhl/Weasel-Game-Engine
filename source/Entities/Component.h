#pragma once
#include "string"
class Component
{
    public:
    Component(){}
    ~Component(){}
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual Component* copy() = 0;
    void setName(std::string n)
    {
        name = n;
    }
    std::string getName()
    {
        return name;
    }
    private: 
    std::string name;
};