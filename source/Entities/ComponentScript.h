#pragma once
#include "Component.h"
#include "ScriptComponent.h"
class ComponentScript : public Component
{
    public:
    ComponentScript(ScriptComponent* scr);
    ~ComponentScript();
    void onUpdate();
    void onCreate();
    private:
    ScriptComponent* scr;
};
