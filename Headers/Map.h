#ifndef MAP_H
#define MAP_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Global.h"
using namespace std;
using namespace sf;
class Point{
    public:
        Point()=default;
        Point(int x,int y,Type type):x(x),y(y),type(type){}
        int x;
        int y;
        Type type=Empty;
};
class Map{
    public:
        friend class Mario;
        void draw();
        void update();
        Map(RenderWindow&);
        void move(int x,int y);
    private:
        RenderWindow& window;
        vector<vector<Point>> m;
        Texture brick;
        Sprite sprite;
};
#endif