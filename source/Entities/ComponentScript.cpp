#include "ComponentScript.h"

ComponentScript::ComponentScript(ScriptComponent* scr)
{
    this->scr = scr;
    this->setName("script");
    this->onCreate();
    this->iniState = (initialState*)malloc(sizeof(initialState));
    
}

ComponentScript::~ComponentScript()
{
    delete(this->scr);
    free(this->iniState);
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

bool ComponentScript::registerInitialState()
{
    printf("Script\n");
    this->iniState->initial_name = this->getVisibleName();
    this->iniState->initial_scr = this->scr;
    return true;
}
bool ComponentScript::recoverInitialState()
{
    this->setVisibleName(this->iniState->initial_name);
    this->scr = this->iniState->initial_scr;
    return true;
}