#ifndef ENTITY_H
#define ENTITY_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
class Mario; 
class Map;
class Brick;
class Entity{
    friend class Brick;
    public:
        Entity(Mario& m,Map& map_):mario(m),marioMap(map_){}
        virtual void update()=0;
        virtual void setPos(int x,int y)=0;
    private:
        Mario& mario;
        Map& marioMap;
        int px;
        int py;
};
#endif