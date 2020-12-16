#pragma once
class Component
{
    public:
    Component(){}
    ~Component(){}
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
};