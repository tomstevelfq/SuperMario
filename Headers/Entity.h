#ifndef ENTITY_H
#define ENTITY_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
using namespace sf;
class Mario; 
class Map;
class Brick;
class Geezer;
class Entity{
    friend class Brick;
    friend class Geezer;
    public:
        Entity(Mario& m,Map& map_,sf::RenderWindow& wind):mario(m),marioMap(map_),window(wind){}
        virtual void draw()=0;
        virtual void update()=0;
        virtual void setPos(int x,int y)=0;
        void setTexturePos(int x,int y){
            textureX=x;
            textureY=y;
            sprite.setTextureRect(IntRect(textureX*CellSize,textureY*CellSize,CellSize,CellSize));
        }
        Type type;
    private:
        Mario& mario;
        Map& marioMap;
        sf::RenderWindow& window;
        Sprite sprite;
        int textureX;
        int textureY;
        int px;
        int py;
};
#endif