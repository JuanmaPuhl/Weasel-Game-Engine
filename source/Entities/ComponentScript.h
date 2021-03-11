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
    void save(std::ofstream& output_dir);
    Component* copy();
    ScriptComponent* getScript();
    private:
    ScriptComponent* scr;
};
