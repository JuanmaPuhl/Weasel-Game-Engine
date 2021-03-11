#include "ComponentScript.h"

ComponentScript::ComponentScript(ScriptComponent* scr)
{
    this->scr = scr;
    this->setName("script");
    this->onCreate();
    
}

ComponentScript::~ComponentScript()
{
    delete(this->scr);
}

void ComponentScript::onCreate()
{
    this->scr->onCreate();
}

void ComponentScript::onUpdate()
{
    this->scr->onUpdate();
}

Component* ComponentScript::copy()
{
    ComponentScript* cs = new ComponentScript(this->scr);
    return cs;
}

ScriptComponent* ComponentScript::getScript()
{
    return this->scr;
}

void ComponentScript::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName() << "\" , ";
    output << "\"script\" : \"" << this->scr << "\"";
}