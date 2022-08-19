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
enum Sta{Alive,Dying,Dead};
class Entity{
    friend class Brick;
    friend class Geezer;
    friend class Turtle;
    public:
        Entity()=default;
        void setProperty(Mario*,shared_ptr<Map>,RenderWindow*);
        virtual void draw(){};
        virtual void update(){};
        virtual void setPos(int x,int y){};
        void setTexturePos(int x,int y){
            textureX=x;
            textureY=y;
            sprite.setTextureRect(IntRect(textureX*CellSize,textureY*CellSize,CellSize,CellSize));
        }
        Type type=Empty;
    private:
        Mario* mario;
        shared_ptr<Map> marioMap;
        RenderWindow* window;
        Sprite sprite;
        int textureX;
        int textureY;
        int px;
        int py;
};
class EntityFactory{
    public:
        static shared_ptr<Entity> getEntity(Type type,Mario* mario,shared_ptr<Map> map,RenderWindow* wind);
};
#endif