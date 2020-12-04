#ifndef SCRIPT_COMPONENT_H
#define SCRIPT_COMPONENT_H
class ScriptComponent
{
    public:
        ScriptComponent()
        {
            
        }
        ~ScriptComponent()
        {

        }
        virtual void onCreate() = 0;
        virtual void onUpdate() = 0;
};
#endif