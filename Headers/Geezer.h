#ifndef GEEZER_H
#define GEEZER_H
#include"Entity.h"
class Geezer:public Entity{
    public:
        Geezer();
        void update() override;
        void draw() override;
        void setPos(int x,int y) override;
        Vector2f getPosition();
        void startDead();
        void startDead2();
    private:
        bool checkCollision(float x,float y,Direc direct);
        bool checkCollision(Direc direct,Type type);
        void walkAnimation();
        float vspeed=0;
        float hspeed=0;
        float px=0;
        float py=0;
        int dua=0;
        int anipos=0;
        int dyingTimer;
        int deadTimer;
        int deadBounceTimer=0;
        bool enemyJumpFlag=false;
};
#endif