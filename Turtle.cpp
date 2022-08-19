#include"Headers/Turtle.h"
#include"Headers/Map.h"
#include"Headers/Mario.h"
using namespace std;
using namespace sf;

Turtle::Turtle(){
    sprite.setTexture(GenTexture::getTexture("Turtle.png"),true);
    sprite.setTextureRect(IntRect(0,0,TurtleWidth,TurtleHeight));
    type=Enemy;
    state=Alive;
    hspeed=TurtleHSpeed;
}
void Turtle::walkAnimation(){
    if(dua--==0){
        dua=TurtleAnimationDuration;
        sprite.setTextureRect(IntRect((anipos++%2)*TurtleWidth,0,TurtleWidth,TurtleHeight));
    }
}
void Turtle::draw(){
    sprite.setPosition(Vector2f(px,py));
    window->draw(sprite);
}
void Turtle::update(){
    switch(state){
        case Alive:{
            Vector2f pos=mario->pos;
            if(mario->vspeed>0){
                if(checkCollision(pos.x,pos.y,DOWN)){
                    startDead();
                }
            }else{
                if(checkCollision(pos.x,pos.y,ALL)){
                    mario->startDead();
                }
            }
            //更新位置
            vspeed=min(vspeed+Gravity,MaxVSpeed);
            if(vspeed>0){
                if(checkCollision(DOWN,Brick_)){
                    vspeed=0;
                }
            }
            if(hspeed!=0){
                walkAnimation();
            }
            if(hspeed>0){
                if(checkCollision(RIGHT,Brick_)){
                    hspeed=-hspeed;
                }
            }else{
                if(checkCollision(LEFT,Brick_)){
                    hspeed=-hspeed;
                }
            }
            //更新位置
            px+=hspeed;
            py+=vspeed;
            break;
        }
        case Dying:

        case Dead:

    }
}
void Turtle::startDead(){
    state=Dying;
}
void Turtle::setPos(int x,int y){
    px=x*CellSize;
    py=y*CellSize;
}
bool Turtle::checkCollision(float x,float y,Direc direct){
    switch(direct){
        case UP:
            if(x-px>=-TurtleWidth&&x-px<=TurtleWidth&&y-py>=0&&y-py<=TurtleHeight){
                return true;
            }
            break;
        case DOWN:
            if(x-px>=-TurtleWidth&&x-px<=TurtleWidth&&y-py<=0&&y-py>=-TurtleHeight){
                return true;
            }
            break;
        case LEFT:
            if(x-px>0&&x-px<TurtleWidth&&y-py>-TurtleHeight&&y-py<TurtleHeight){
                return true;
            }
            break;
        case RIGHT:
            if(x-px<0&&x-px>-TurtleWidth&&y-py>-TurtleHeight&&y-py<TurtleHeight){
                return true;
            }
            break;
        case ALL:
            if(x-px>=-TurtleWidth&&x-px<=TurtleWidth&&y-py>=-TurtleHeight&&y-py<=TurtleHeight){
                return true;
            }
    }
    return false;
}
bool Turtle::checkCollision(Direc direct,Type type){
    if(direct==DOWN){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){//砖块检测方向正好相反
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,UP)){
                        return true;
                    }
                }
            }
           } 
        }
    }else if(direct==LEFT){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,RIGHT)){
                        return true;
                    }
                }
            }
           } 
        }
    }else if(direct==RIGHT){
        if(type==Brick_){
           for(auto& v:marioMap->m){
            for(auto& it:v){
                if(it.type==Brick_){
                    if(checkCollision(it.entity->px*CellSize,it.entity->py*CellSize,LEFT)){
                        return true;
                    }
                }
            }
           } 
        }
    }
    return false;
}