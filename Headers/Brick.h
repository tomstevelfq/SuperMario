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
enum Direc{UP,DOWN,LEFT,RIGHT};//检测哪个方向的碰撞
class Brick:public Entity{
    public:
        void update();
        Brick(Mario& mario,Map& m,sf::RenderWindow& wind);
        void setPos(int x,int y);
        void draw();
    private:
        bool checkCollision(float x,float y,Direc direct);
};
#endif