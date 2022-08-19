#ifndef MAP_DESIGNER_H
#define MAP_DESIGNER_H
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<memory>
#include<iostream>
#include<map>
#include"Map.h"
using namespace std;
using namespace sf;
class MapDesigner{
    public:
        void start();
        MapDesigner();
    private:
        RenderWindow window;
        View view;
        string filename;
        Texture brick_pic;
        Texture arrow_pic;
        Texture enemy_pic;
        Sprite sprite;
        Sprite map_pic;
        RectangleShape rec;
        vector<vector<int>> edge;
        int gap=8;
        int offset=0;
        bool tool=false;
        float timer=0;
        Point toolPos;
        map<pair<int,int>,pair<int,int>> bricks;
        map<pair<int,int>,pair<int,int>> enemys;
        map<pair<int,int>,Point> m;

        void draw();
        void drawLines();
        void drawTools();
        void loadFiles();
        pair<int,int> getTopLeft(int x,int y);
        int checkClick(int x,int y,Point&);
        void click();
        void drawMap();
        void close();
};
#endif