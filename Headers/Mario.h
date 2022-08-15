#ifndef MARIO_H
#define MARIO_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<memory>
#include"Map.h"
#include"Global.h"
using namespace std;
using namespace sf;
class Mario{
    public:
        Mario(RenderWindow& wind,View& view);
        void update();
        void draw();
    private:
        shared_ptr<Map> marioMap;
        vector<shared_ptr<Texture>> person;
        RenderWindow& window;
        View& view;
        Texture person_pic;
        Sprite sprite;
        Sprite ground_sprite;
        Texture stand_pic;
        Texture ground_pic;
        float sp=1.0;
        float dy=0;
        float dx=0;
        float timer2=0;
        float hspeed=0;
        float vspeed=0;
        bool ground=false;
        int jump=1;
        int keepTimer=15;
        int anipos=0;
        int dua=0;
        int rdua=0;
        int offset=0;
        Clock clock;
        void walkAnimation();
        void rwalkAnimation();
        void stand();
        void drawGround();
        void loadResource();
        void move(int x);
        Type checkCollision(IntRect rec,bool flag=true);
        Type checkBottomCollision(FloatRect rec);
        Type checkCollision2(FloatRect rec,int direct);
        void print(string,vector<int>);
};
#endif