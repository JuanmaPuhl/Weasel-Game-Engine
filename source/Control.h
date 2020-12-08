#ifndef CONTROL_H
#define CONTROL_H
class Control
{
    protected:
        bool* keys;
        
        
    public:
    enum Action
    {
        PRESSED = true,
        RELEASED = false
    };
    Control()
    {
    }
    ~Control()
    {

    }
    virtual void setKey(int key, bool action) = 0 ;
    virtual bool isPressed(int key) = 0;
    
};
#endif