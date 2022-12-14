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
struct Broke{
    Broke(float h,float v,RectangleShape rect):v(v),h(h),rec(rect){}
    float v;
    float h;
    RectangleShape rec;
};
class Brick:public Entity{
    public:
        void update();
        Brick();
        void setPos(int x,int y);
        void draw();
        Vector2f getPosition();
        void startDead();
        void startDead2();
    private:
        bool checkCollision(float x,float y,Direc direct);
        vector<Broke> broke;
        float vspeed=0;
        float dpy;
        float nowdpy;
};
#endif