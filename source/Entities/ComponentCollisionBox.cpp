#include "ComponentCollisionBox.h"

ComponentCollisionBox::ComponentCollisionBox(Entity* entity)
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->width = 32.0f;
    this->height = 32.0f;
    this->entity = entity;
    this->setName("collider");
    //this->iniState = (initialState*)malloc(sizeof(initialState));
/*     initialState iniState{
        0.0,0.0,0.0,0.0,""
    };
    this->iniState = &iniState; */
}

ComponentCollisionBox::ComponentCollisionBox(float x, float y, float width, float height, Entity* entity)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->entity = entity;
    this->setName("collider");
    //this->iniState = (initialState*)malloc(sizeof(initialState));
    initialState iniStateAux{
        0.0,0.0,0.0,0.0,""
    };
    this->iniState = &iniStateAux;
}

ComponentCollisionBox::~ComponentCollisionBox()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->width = 0.0f;
    this->height = 0.0f;
    this->list.clear();
    this->entity = NULL;
    free(this->iniState);
}

float ComponentCollisionBox::getX()
{
    return this->x;
}

float ComponentCollisionBox::getY()
{
    return this->y;
}

float ComponentCollisionBox::getWidth()
{
    return this->width;
}

float ComponentCollisionBox::getHeight()
{
    return this->height;
}

void ComponentCollisionBox::setX(float x)
{
    this->x = x;
}

void ComponentCollisionBox::setY(float y)
{
    this->y = y;
}

void ComponentCollisionBox::setWidth(float width)
{
    this->width = width;
}

void ComponentCollisionBox::setHeight(float height)
{
    this->height = height;
}

bool ComponentCollisionBox::checkCollision(ComponentCollisionBox* b)
{
    //Colision en eje X
    bool collisionX = this->x + this->width >= b->getX() && b->getX() + b->getWidth() >= this->x;
    //Colision en eje y
    bool collisionY = this->y + this->height >= b->getY() && b->getY() + b->getHeight() >= this->y;
    if(collisionX && collisionY)
    {
       
    }
    return collisionX && collisionY;
}

void ComponentCollisionBox::onCreate()
{

}

void ComponentCollisionBox::onUpdate()
{
    this->x = this->entity->getPosition().x;
    this->y = this->entity->getPosition().y;
    Level* level = Game::getCurrentLevel();
    this->list = level->getEntities();
    std::vector<Entity*>::iterator ptr;
    for(ptr = (this->list).begin(); ptr<(this->list).end(); ptr++)
    {   
        if(*ptr != this->entity)
        {
            Component* comp = (*ptr)->getComponent("collider");
            if(comp!=NULL)
                if(this->checkCollision((ComponentCollisionBox*)comp))
                {
                    this->entity->onCollision(*ptr);
                }
        }
    }
}

Component* ComponentCollisionBox::copy()
{
    Level* level = Game::getCurrentLevel();
    this->list = level->getEntities();
    ComponentCollisionBox* cs = new ComponentCollisionBox(this->x,this->y,this->width,this->height, this->entity);
    return cs;
}

void ComponentCollisionBox::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName() << "\" , ";
    output << "\"x\" : " << this->x << " , ";
    output << "\"y\" : " << this->y << " , ";
    output << "\"width\" : " << this->width << " , ";
    output << "\"height\" : " << this->height;
    //La entidad está claro que es la actual

}

bool ComponentCollisionBox::registerInitialState()
{
    this->initial_visibleName = this->getVisibleName().c_str();
    this->initial_x = this->x;
    this->initial_y = this->y;
    this->initial_width = this->width;
    this->initial_height = this->height;
    return true;
}
bool ComponentCollisionBox::recoverInitialState()
{
    this->setVisibleName(this->initial_visibleName);
    this->x = this->initial_x;
    this->y = this->initial_y;
    this->height = this->initial_height;
    this->width = this->initial_width;
    return true;
}