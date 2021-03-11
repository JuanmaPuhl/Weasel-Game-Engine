#include "LuaScriptComponent.h"

LuaScriptComponent::LuaScriptComponent(std::string scr, lua_State* L)
{
    this->scr = scr; //La dirección del script
    this->lua_state = L;
    this->setName("lua_script");
    this->onCreate();
}
LuaScriptComponent::~LuaScriptComponent()
{
    this->scr.clear();
}
void LuaScriptComponent::onUpdate()
{
    if (luaL_dofile(this->lua_state, this->scr.c_str() ) != LUA_OK) {
        printf("ERROR: %s\n",lua_tostring(this->lua_state,-1));
    }
    lua_getglobal(this->lua_state, "on_update");
    if(lua_isfunction(this->lua_state, -1))
        if(lua_pcall(this->lua_state, 0, 0, 0) != LUA_OK)
        {
            printf("error running function `f': %s", lua_tostring(this->lua_state, -1));  
        }

}
void LuaScriptComponent::onCreate()
{
    if (luaL_dofile(this->lua_state, this->scr.c_str() ) != LUA_OK) {
        printf("ERROR: %s\n",lua_tostring(this->lua_state,-1));
    }
    lua_getglobal(this->lua_state, "on_create");
    if(lua_isfunction(this->lua_state, -1))
        if(lua_pcall(this->lua_state, 0, 0, 0) != LUA_OK)
        {
            printf("error running function `f': %s", lua_tostring(this->lua_state, -1));  
        }
}

void LuaScriptComponent::onCollision(Entity* other)
    {
        if (luaL_dofile(this->lua_state, this->scr.c_str() ) != LUA_OK) {
            printf("ERROR: %s\n",lua_tostring(this->lua_state,-1));
        }
        lua_getglobal(this->lua_state, "on_collision");
        if(lua_isfunction(this->lua_state, -1))
        {
            Entity** entity = (Entity**)lua_newuserdata(this->lua_state, sizeof(Entity*));  
            *entity = other;
            if(lua_pcall(this->lua_state, 1, 0, 0) != LUA_OK)
            {
                printf("error running function `f': %s", lua_tostring(this->lua_state, -1));  
            }
        }
    }

Component* LuaScriptComponent::copy()
{
    LuaScriptComponent* cs = new LuaScriptComponent(this->scr,this->lua_state);
    return cs;
}
std::string LuaScriptComponent::getScript()
{
    return this->scr;
}

void LuaScriptComponent::setScript(std::string script)
{
    this->scr = script;
    this->onCreate();
}


void LuaScriptComponent::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName() << "\" , ";
    output << "\"script\" : \"" << this->scr << "\"";
    //El estado lo genero por codigo automaticamente.
}