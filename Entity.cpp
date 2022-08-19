#include"Headers/Entity.h"
#include"Headers/Brick.h"
#include"Headers/Geezer.h"

void Entity::setProperty(Mario* mario_,shared_ptr<Map> map,RenderWindow* wind){
    mario=mario_;
    marioMap=map;
    window=wind;
}
shared_ptr<Entity> EntityFactory::getEntity(Type type,Mario* mario,shared_ptr<Map> map,RenderWindow* wind){
    shared_ptr<Entity> ptr;
    switch(type){
        case Brick_:
            ptr=shared_ptr<Brick>(new Brick());
            ptr->setProperty(mario,map,wind);
            return ptr;
        case Enemy:
            ptr=shared_ptr<Geezer>(new Geezer());
            ptr->setProperty(mario,map,wind);
            return ptr;
        default:
            return ptr;
    }
}