#pragma once
#include "string"
#include <iostream>
#include <fstream>
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
    void setVisibleName(std::string n)
    {
        visible_name = n;
    }
    std::string getVisibleName()
    {
        return visible_name;
    }
    virtual void save(std::ofstream& output_dir) = 0;
    virtual bool registerInitialState() = 0;
    virtual bool recoverInitialState() = 0;
    private: 
    std::string name;
    std::string visible_name = "";
};