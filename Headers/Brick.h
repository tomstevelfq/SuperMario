#ifndef BRICK_H
#define BRICK_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
#include"Entity.h"
#include<math.h>
class Brick:public Entity{
    public:
        void update();
        Brick(Mario& mario,Map& m):Entity(mario,m){}
        void setPos(int x,int y);
    private:
        Type checkCollision(sf::FloatRect rec,int direct);
        bool checkCollision2(sf::FloatRect rec);
};
#endif