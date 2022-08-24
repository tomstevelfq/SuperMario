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
enum Sta{Alive,Dying,Dead,DeadBounce,Slide,Shrink,Wobble,TreaEmpty};
class Entity{
    friend class Brick;
    friend class Geezer;
    friend class Turtle;
    friend class Bullet;
    friend class Treasure;
    public:
        Entity()=default;
        void setProperty(Mario*,Map*,RenderWindow*);
        virtual void draw(){};
        virtual void update(){};
        virtual void setPos(int x,int y){};
        virtual void startDead(){}
        virtual void startDead2(){}
        virtual Vector2f getPosition(){return Vector2f{};};
        void setTexturePos(int x,int y){
            textureX=x;
            textureY=y;
            sprite.setTextureRect(IntRect(textureX*CellSize,textureY*CellSize,CellSize,CellSize));
        }
        Type type=Empty;
        Sta state;
    private:
        Mario* mario;
        Map* marioMap;
        RenderWindow* window;
        Sprite sprite;
        int textureX;
        int textureY;
        int px;
        int py;
        int width;
        int height;
};
class EntityFactory{
    public:
        static shared_ptr<Entity> getEntity(Type type,Mario* mario,Map* map,RenderWindow* wind);
};
#endif