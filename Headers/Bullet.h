#ifndef BULLET_H
#define BULLET_H
#include<SFML/Graphics.hpp>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
#include"Entity.h"
class Bullet:public Entity{
    public:
        Bullet();
        void draw();
        void update();
        void setPos(int,int);
        Vector2f getPosition();
        float hspeed;
        float vspeed;
    private:
        void flyAnimation();
        bool checkCollision(float x,float y,int objWidth=CellSize,int objHeight=CellSize);
        int checkCollision();
        void startDead();
        void DeadAnimation();
        int dua=0;
        int anipos=0;
        float px;
        float py;
};
#endif