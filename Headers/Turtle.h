#ifndef TURTLE_H
#define TURTLE_H
#include<SFML/Graphics.hpp>
#include<algorithm>
#include<vector>
#include<memory>
#include"Global.h"
#include"Entity.h"
class Turtle:public Entity{
    public:
        Turtle();
        void draw();
        void update();
        void setPos(int x,int y);
    private:
        float vspeed=0;
        float hspeed=0;
        float px=0;
        float py=0;
        int dua=0;
        int anipos=0;
        int dyingTimer;
        int deadTimer;
        Sta state;
        void walkAnimation();
        bool checkCollision(float x,float y,Direc direct);
        bool checkCollision(Direc direct,Type type);
        void startDead();
};
#endif