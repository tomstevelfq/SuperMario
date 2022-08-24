#ifndef TREASURE_H
#define TREASURE_H
#include<SFML/Graphics.hpp>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
#include"Entity.h"
class Treasure:public Entity{
    public:
        void update();
        Treasure();
        void setPos(int x,int y);
        void draw();
        Vector2f getPosition();
        void startDead();
    private:
        bool checkCollision(float x,float y,Direc direct);
        void coinAnimation();
        void drawCoin();
        int dua=0;
        int anipos=0;
        Sprite coinSprite;
        float coinvspeed=-3.5;
        float coinx;
        float coiny;
        float vspeed=0;
        float dpy;
        float nowdpy;
};
#endif