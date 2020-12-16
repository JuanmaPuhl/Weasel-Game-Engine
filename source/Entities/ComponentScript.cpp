#include "ComponentScript.h"

ComponentScript::ComponentScript(ScriptComponent* scr)
{
    this->scr = scr;
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