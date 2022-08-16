#ifndef GEEZER_H
#define GEEZER_H
#include"Entity.h"
class Geezer:public Entity{
    public:
        Geezer(Mario& mario,Map& m,RenderWindow& wind):Entity(mario,m,wind){}
        void update();
        void setPos(int x,int y);
    private:
        float vspeed=0;
        float hspeed=0;
        float x=0;
        float y=0;
};
#endif