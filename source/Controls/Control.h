#ifndef CONTROL_H
#define CONTROL_H
template< typename ENUM_TYPE >
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
    virtual bool isPressed(ENUM_TYPE key) = 0;
    
};
#endif