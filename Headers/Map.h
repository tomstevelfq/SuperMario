#ifndef MAP_H
#define MAP_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Global.h"
#include"Brick.h"
using namespace std;
using namespace sf;
class Point{
    public:
        Point()=default;
        Point(int x,int y):x(x),y(y){}
        Point(int x,int y,Type type):x(x),y(y),type(type){}
        int x;
        int y;
        Type type=Empty;
        shared_ptr<Entity> entity;
};
class Map{
    public:
        friend class Mario;
        friend class Brick;
        friend class Geezer;
        friend class Turtle;
        void draw();
        void update();
        Map(RenderWindow&,Mario& mario);
        void move(int x,int y);
        void init();
    private:
        RenderWindow& window;
        Mario& mario;
        vector<vector<Point>> m;
        vector<shared_ptr<Entity>> enemies;
        Texture brick;
        Sprite sprite;
};
#endif